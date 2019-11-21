/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_OBJECT_H_
#define _ENGINE_OBJECT_H_


#include <assert.h>

namespace engine
{

/**
 * Object class to be used as base class for each class.
 *
 * Object class provides functionality for internal object reference
 * counting. Refecence counting can be done using addRef and releaseRef
 * methods.
 * 
 */
class Object {
public:

	/**
	 * Default constructor.
	 * Creates an object and sets ref count to 0.
	 */
	Object();

	/**
	 * Class destructor.
	 */
    virtual ~Object();

	/** 
	 * Increments ref count.
	 */
	inline void addRef() {
		assert( m_numOfRefs >= 0 );
		++m_numOfRefs;
	}

	/** 
     * Decrements ref count.
	 * @return Returns current ref count.
	 */
    inline int releaseRef() {
		assert( m_numOfRefs > 0 );
		return --m_numOfRefs;
	}

	/**
	 * Returns current ref count.
	 */
	inline int getRefCount() const {
		return m_numOfRefs;
	}

private:
	// Member variables
	int m_numOfRefs;

	// Non-allowed methods (declared but not defined anywhere, result link error if used)
	Object( const Object& );
	Object& operator=( const Object& );
};


}



#endif // OBJECT_H_


