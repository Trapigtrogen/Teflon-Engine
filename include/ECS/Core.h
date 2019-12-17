/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#pragma once
#include <map>
#include <vector>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <assert.h>

namespace core {

	///
	/// Vector -class.
	template <typename T>
	class Vector : public std::vector<T> {
	public:
	};

	///
	/// Map -class.
	template <typename KeyType, typename ValueType>
	class Map : public std::map<KeyType, ValueType> {
	public:
	};

	///
	/// Object-class. Object-class provides reference counting. Ref-class uses those functions.
	class Object {
	public:
		Object() : m_numRefs(0) {}

		virtual ~Object() {}

		inline void addRef() {
			++m_numRefs;
		}

		inline int releaseRef() {
			--m_numRefs;
			return m_numRefs;
		}

	private:
		int m_numRefs;
	};

	///
	/// Ref -class. Ref class provides auto pointer -functionality.
	template < class Type >
	class Ref
	{
	public:
		inline Ref(const Ref& obj);
		inline Ref();
		inline Ref(Type* p);
		inline Ref(int p);
		inline ~Ref<Type>();
		inline Ref<Type>& operator=(const Ref<Type>& o);
		inline Ref<Type>& operator=(Type* o);
		inline Ref<Type>& operator=(int o);
		inline Type* operator->();
#if !defined(SWIG)
		inline operator Type*();
#endif
		inline Type* ptr() const;
		inline const Type* operator ->() const;
		inline bool operator ==(const Type* const pObj) const;
		inline bool operator !=(const Type* const pObj) const;
		inline bool operator ==(const Ref<Type>& obj) const;
		inline bool operator !=(const Ref<Type>& obj) const;
		inline bool operator !() const;
		inline Type& operator* () const;
	private:
		Type*		m_ptr;
	};

	template < class Type >
	inline bool operator ==(Type* lhs, Ref<Type> rhs);

	template < class Type >
	inline bool operator !=(Type* lhs, Ref<Type> rhs);

	// For inl-file
	template < class Type >
	inline Ref<Type>::Ref(const Ref& obj) : m_ptr(obj.m_ptr) {
		if (m_ptr != 0) {
			obj.m_ptr->addRef();
		}
	}

	template < class Type >
	inline Ref<Type>::Ref() : m_ptr(0) {
	}

	template < class Type >
	inline Ref<Type>::Ref(Type* p) : m_ptr(p) {
		if (m_ptr != 0) {
			m_ptr->addRef();
		}
	}

	template < class Type >
	inline Ref<Type>::Ref(int p) : m_ptr(0) {
		(void)p;
		assert(p == 0); // Not null integer pointer;
	}

	template < class Type >
	inline Ref<Type>::~Ref() {
		if (m_ptr != 0) {
			if (0 == m_ptr->releaseRef())
			{
				delete m_ptr;
				m_ptr = 0;
			}
		}
	}

	template < class Type >
	inline Ref<Type>& Ref<Type>::operator=(const Ref<Type>& o)
	{
		if (o.m_ptr != 0) {
			o.m_ptr->addRef();
		}

		if ((this->m_ptr != 0) && (0 == this->m_ptr->releaseRef())) {
			delete this->m_ptr;
		}

		this->m_ptr = o.m_ptr;
		return *this;
	}


	template < class Type >
	inline Ref<Type>& Ref<Type>::operator=(Type* o)
	{
		if (o != 0) {
			o->addRef();
		}

		if ((this->m_ptr != 0) && (0 == this->m_ptr->releaseRef())) {
			delete this->m_ptr;
		}

		this->m_ptr = o;
		return *this;
	}

	template < class Type >
	inline Ref<Type>& Ref<Type>::operator=(int o) {
		(void)o;
		assert(o == 0); // Not null integer pointer;

		if ((this->m_ptr != 0) && (0 == this->m_ptr->releaseRef())) {
			delete this->m_ptr;
		}

		this->m_ptr = 0;
		return *this;
	}

	template < class Type >
	inline Type* Ref<Type>::operator->() {
		assert(m_ptr != 0); // NULL pointer
		return m_ptr;
	}

	template < class Type >
	inline Ref<Type>::operator Type*() {
		return m_ptr;
	}

	template < class Type >
	inline Type* Ref<Type>::ptr() const {
		return m_ptr;
	}


	template < class Type >
	inline const Type* Ref<Type>::operator ->() const {
		assert(m_ptr != 0); // NULL pointer
		return m_ptr;
	}

	template < class Type >
	inline bool Ref<Type>::operator ==(const Type* const pObj) const {
		return m_ptr == pObj;
	}

	template < class Type >
	inline bool Ref<Type>::operator !=(const Type* const pObj) const {
		return m_ptr != pObj;
	}

	template < class Type >
	inline bool Ref<Type>::operator ==(const Ref<Type>& obj) const {
		return !(*this != obj);
	}

	template < class Type >
	inline bool Ref<Type>::operator !=(const Ref<Type>& obj) const {
		return (m_ptr != obj.m_ptr);
	}

	template < class Type >
	inline bool Ref<Type>::operator !() const {
		return (m_ptr == 0);
	}


	template < class Type >
	inline Type& Ref<Type>::operator* () const {
		assert(m_ptr != 0); // NULL pointer
		return *m_ptr;
	}

	template < class Type >
	inline bool operator ==(Type* lhs, Ref<Type> rhs) {
		return rhs == lhs;
	}

	template < class Type >
	inline bool operator !=(Type* lhs, Ref<Type> rhs) {
		return rhs != lhs;
	}

	///
	/// String -class.
	typedef std::string String;
}
