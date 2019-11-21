// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Copyright (C) 2016 Mikko Romppainen. All rights reserved. See license.txt for license terms.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef _ENGINE_ELAPSED_TIMER_H_
#define _ENGINE_ELAPSED_TIMER_H_

#include <core/Object.h>

namespace engine
{

/**
 * Class for ElapsedTimer. 
 * 
 * Elapsed timer is handy tool for getting elapsed time in simulation. Typical
 * Elapsed timer usage is following: Create new instance of ElapsedTimer. Call
 * reset, when you want to start/restart timer. Call getTime, when you want to know,
 * how much time has been elapsed since last reset call.
 *
 * Elapsed timer uses Windows GetTime function for internal operation, so the resolution
 * of the timer is not best possible.
 *
 * @ingroup yam2d
 * @author Mikko Romppainen (mikko@kajakbros.com)
 */
class ElapsedTimer : public Object
{
public:
	/**
	 * Default constructor.
	 *
	 * Creates new elapsed timer and initializes it. You must call reset before first getTime call.
	 */
	ElapsedTimer();

	virtual ~ElapsedTimer();

	/** Resets timer. */
	void reset();

	/** Returns elapsed time in seconds since last call to reset. */
	float getTime() const;

#if defined(_WIN32)
	typedef __int64 TIME_TYPE;
#else
	typedef long TIME_TYPE;
#endif

	static TIME_TYPE getTotalTime();
private:
	TIME_TYPE m_startTime;
};

}

#endif // ELAPSED_TIMER_H_




