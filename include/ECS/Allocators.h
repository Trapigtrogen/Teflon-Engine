/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// Note: These codes are taken from https://github.com/mtrebi/memory-allocators. Those codes are
/// licenced under MIT-license:
///
/// MIT License
///
/// Copyright(c) 2016 Mariano Trebino
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files(the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions :
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#pragma once
#include <algorithm>
#include <assert.h>

namespace memory {

	template <class T>
	class StackLinkedList {
	public:
		struct Node {
			T data;
			Node* next;
		};

		Node* head;
	public:
		StackLinkedList();

		void push(Node * newNode);
		Node* pop();
	private:
		StackLinkedList(StackLinkedList &stackLinkedList);
	};

	template <class T>
	StackLinkedList<T>::StackLinkedList() : head(NULL) {
		head = new Node();
	}

	template <class T>
	void StackLinkedList<T>::push(Node * newNode) {
		newNode->next = head;
		head = newNode;
	}

	template <class T>
	typename StackLinkedList<T>::Node* StackLinkedList<T>::pop() {
		Node * top = head;
		head = head->next;
		return top;
	}

	class Allocator {
	protected:
		std::size_t m_totalSize;
		std::size_t m_used;
		std::size_t m_peak;
	public:
		Allocator(const std::size_t totalSize) {
			m_totalSize = totalSize;
			m_used = 0;
			m_peak = 0;
		}

		virtual ~Allocator() {
			m_totalSize = 0;
		}

		virtual void* Allocate(const std::size_t size, const std::size_t alignment = 0) = 0;

		virtual void Free(void* ptr) = 0;

	//	virtual void Init() = 0;

		friend class Benchmark;
	};


	class PoolAllocator : public Allocator {
	private:
		struct  FreeHeader {
		};
		typedef StackLinkedList<FreeHeader>::Node Node;
		StackLinkedList<FreeHeader> m_freeList;

		void * m_start_ptr = nullptr;
		std::size_t m_chunkSize;
	public:
		PoolAllocator(const std::size_t totalSize, const std::size_t chunkSize)
			: Allocator(totalSize) {
			assert(chunkSize >= 8 && "Chunk size must be greater or equal to 8");
			assert(totalSize % chunkSize == 0 && "Total Size must be a multiple of Chunk Size");
			this->m_chunkSize = chunkSize;
			m_start_ptr = malloc(m_totalSize);
			Reset();
		}
		/*
		virtual void Init() {
			m_start_ptr = malloc(m_totalSize);
			Reset();
		}*/

		virtual ~PoolAllocator() {
			free(m_start_ptr);
		}

		virtual void* Allocate(const std::size_t allocationSize, const std::size_t alignment = 0) {
			(void)alignment;
			assert(allocationSize == this->m_chunkSize && "Allocation size must be equal to chunk size");

			Node * freePosition = m_freeList.pop();

			assert(freePosition != nullptr && "The pool allocator is full");

			m_used += m_chunkSize;
			m_peak = std::max(m_peak, m_used);
#ifdef _DEBUG
			//   std::cout << "A" << "\t@S " << m_start_ptr << "\t@R " << (void*) freePosition << "\tM " << m_used << std::endl;
#endif

			return (void*)freePosition;
		}

		virtual void Free(void * ptr) {
			m_used -= m_chunkSize;

			m_freeList.push((Node *)ptr);

#ifdef _DEBUG
			//    std::cout << "F" << "\t@S " << m_start_ptr << "\t@F " << ptr << "\tM " << m_used << std::endl;
#endif
		}

		virtual void Reset() {
			m_used = 0;
			m_peak = 0;
			// Create a linked-list with all free positions
			const int nChunks = m_totalSize / m_chunkSize;
			for (int i = 0; i < nChunks; ++i) {
				std::size_t address = (std::size_t) m_start_ptr + i * m_chunkSize;
				m_freeList.push((Node *)address);
			}
		}

	private:
		PoolAllocator(PoolAllocator &poolAllocator);

	};

}


