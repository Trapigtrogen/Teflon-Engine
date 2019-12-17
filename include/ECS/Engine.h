/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#pragma once

#include "Allocators.h"
#include "Core.h"

namespace ecs {

	

	///
	/// Entity, Component, System forward declarations.
	class Entity;
	class Component;
	class System;
	class Engine;

	///
	/// Pool -class. Pool class provide Compoentn Pools by different component type.
	class IPool : public core::Object {
	public:
		IPool() : Object() {}
		virtual ~IPool() {}

		virtual const core::String& getTypeName() const = 0;
		virtual Component* createComponent(const core::String& args) = 0;
		virtual System* getSystem() const = 0;
		virtual memory::Allocator* getAllocator() = 0;
	private:
		IPool(const IPool& o);
		IPool* operator=(const IPool& o);
	};
	
	///
	/// Component -class.
	class Component : public core::Object {
	public:
		virtual ~Component() {
			m_pool->getAllocator()->Free(this);
		}

		inline void setEntity(Entity* e) {
			m_entity = e;
		}

		inline const Entity* getEntity() const {
			return m_entity;
		}

		inline Entity* getEntity() {
			return m_entity;
		}

		inline System* getSystem() {
			return m_pool->getSystem();
		}

		void* operator new(size_t size, memory::PoolAllocator* pool) {
			return pool->Allocate(size);
		}

		void operator delete(void* memory, memory::PoolAllocator* pool) {
			pool->Free(memory);
		}

		void operator delete(void* /*memory*/) {
		}

		const core::String& getTypeName() const {
			return m_pool->getTypeName();
		}
	protected:
		Component(IPool* pool) : Object(), m_pool(pool), m_entity(NULL) {
		}

	private:
		Component(const Component& o);
		Component* operator=(const Component& o);

		IPool*		m_pool;
		Entity*		m_entity;
	};

	///
	/// Entity -class. Entity has components and childs.
	class Entity : public core::Object {
	public:
		Entity(Entity* parent = NULL) : Object(), m_parent(parent), m_components(), m_childs() {}
		virtual ~Entity() {}

		inline Entity* getParent() {
			return m_parent;
		}

		template<class ReturnType>
		inline ReturnType* addComponent(Component* component) {
			return dynamic_cast<ReturnType*>(addComponent(component));
		}

		inline Component* addComponent(Component* component) {
			Component* result = 0;
			if (component != NULL) {
				component->setEntity(this);
				m_components.push_back(component);
				result = component;
			}
			else {
				printf("ERR: Trying to add NULL component!\n");
				assert(0);
			}
			return result;
		}

		inline void removeComponent(Component* component) {
			component->setEntity(NULL);
			m_components.erase(std::find(m_components.begin(), m_components.end(), core::Ref<Component>(component)));
		}

		inline Entity* addChild(Entity* childEntity) {
			assert(childEntity->getParent() == NULL);
			childEntity->setParent(this);
			m_childs.push_back(childEntity);
			return childEntity;
		}

		inline Entity* addChild() {
			Entity* childEntity = new Entity(this);
			m_childs.push_back(childEntity);
			return childEntity;
		}

		inline void removeChild(Entity* childEntity) {
			m_childs.erase(std::find(m_childs.begin(), m_childs.end(), core::Ref<Entity>(childEntity)));
		}

		inline const core::Vector< core::Ref<Entity> >& getChilds() const {
			return m_childs;
		}

		inline const Component* getComponent(const core::String& typeName) const {
			for (auto it = m_components.begin(); it != m_components.end(); ++it) {
				if ((*it)->getTypeName() == typeName) {
					return (*it).ptr();
				}
			}
			return 0;
		}

		inline Component* getComponent(const core::String& typeName) {
			for (auto it = m_components.begin(); it != m_components.end(); ++it) {
				if ((*it)->getTypeName() == typeName) {
					return (*it).ptr();
				}
			}
			return 0;
		}

		template<typename T>
		inline const T* getComponent(const core::String& typeName) const {
			return dynamic_cast<const T*>(getComponent(typeName));
		}

		template<typename T>
		inline T* getComponent(const core::String& typeName) {
			return dynamic_cast<T*>(getComponent(typeName));
		}

	private:
		Entity(const Entity& o);
		Entity* operator=(const Entity& o);

		void setParent(Entity* parent) {
			m_parent = parent;
		}

		Entity*									m_parent;
		core::Vector< core::Ref<Component> >	m_components;
		core::Vector< core::Ref<Entity> >		m_childs;
	};

	template<typename T>
	class Pool : public IPool {
	public:
		Pool(System* system, const core::String& typeName) : IPool(), m_system(system), m_typeName(typeName), m_poolAllocator((sizeof(T))*1024*4,sizeof(T)) {
			printf("DBG: Pool<%s>(typeName=%s) created okay\n", typeid(*this).name(), typeName.c_str() );
		}

		virtual ~Pool() {
		}

		virtual const core::String& getTypeName() const {
			return m_typeName;
		}

		virtual Component* createComponent(const core::String& args) {
			return new (&m_poolAllocator) T(this, args);
		}

		virtual System* getSystem() const { return m_system; }

		virtual memory::Allocator* getAllocator() { return &m_poolAllocator; }

	private:
		Pool(const Pool& o);
		Pool* operator=(const Pool& o);

		System*			m_system;
		core::String	m_typeName;
		memory::PoolAllocator	m_poolAllocator;
	};

	///
	/// System -class. System contains all components by type.
	class System : public core::Object {
	public:
		System(Engine* engine) : Object(), m_engine(engine), m_pools() {
		}

		virtual ~System(){}
		
		inline Component* createComponent(const core::String& typeName, const core::String& args) {
			for(auto itPool = m_pools.begin(); itPool != m_pools.end(); ++itPool) {
				if( *itPool == NULL ) {
					printf("ERR: NULL pool pointer!\n");
				}
				if (typeName == (*itPool)->getTypeName()) {
					Component* res = (*itPool)->createComponent(args);
					if (res != NULL) {
						// TODO: componentCreated(typeName, res);
						m_componentsByType[typeName].push_back(res);
						return res;
					}
					else {
						printf("ERR: createComponent failed!\n");
						assert(0);
					}
				}
			}
			return NULL;
		}

		inline void removeComponent(const Component* component) {
			auto& vec = m_componentsByType[component->getTypeName()];
			auto &comp = std::find_if(vec.begin(), vec.end(), 
				[component](const core::Ref<Component>& c)->bool { 
				return c.ptr() == component; 
			});
			vec.erase(comp);
		}

		inline Engine* getEngine() {
			return m_engine;
		}

		inline const Engine* getEngine() const {
			return m_engine;
		}

		// Returns all components by given typeName.
		const core::Vector< core::Ref<Component> >& getComponents(const core::String& typeName) const {
			static const core::Vector< core::Ref<Component> > EMPTY; // Static const vector for empty components.
			if (m_componentsByType.find(typeName) == m_componentsByType.end())
				return EMPTY;// If not found, return empty.
			return m_componentsByType.at(typeName);
		}

		// Returns map of components.
		const core::Map<core::String, core::Vector< core::Ref<Component> > >& getComponents() const {
			return m_componentsByType;
		}

	protected:
		template<typename T>
		inline void registerComponent(const core::String& typeName) {
			m_pools.push_back(new Pool<T>(this, typeName));
		}
		
	private:
		System(const System& o);
		System* operator=(const System& o);

		Engine*									m_engine;
		core::Vector< core::Ref<IPool> >					m_pools;
		core::Map<core::String, core::Vector< core::Ref<Component> > >	m_componentsByType;
	};

	///
	/// Engine -class. Contains all systems.
	class Engine {
	public:
		template<typename T>
		inline void registerSystem() {
			m_systems.push_back(new T(this));
		}

		inline Component* createComponent(const core::String& typeName, const core::String args = "") {
			for(auto itSystem = m_systems.begin(); itSystem != m_systems.end(); ++itSystem) {
				if( *itSystem == NULL ) {
					printf("ERR: NULL system pointer!\n");
				}
				Component* c = (*itSystem)->createComponent(typeName, args);
				if( c != NULL ) {
					printf("DBG: Created component \"%s\" okay\n", typeName.c_str());
					return c;
				}
			}
			
			printf("ERR: Create component \"%s\" FAILED!\n", typeName.c_str());
			assert(0);
			return NULL;
		}

		const core::Vector< core::Ref<System> >& getSystems() const {
			return m_systems;
		}

	private:
		core::Vector< core::Ref<System> > m_systems;
	};


	// Implementation

	
}




