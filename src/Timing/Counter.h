#ifndef WB_COUNTER_H
#define WB_COUNTER_H

#include "wb-global.h"

#include "Factory.h"

namespace chi {

/**
 * @addtogroup Timing
 * @{
 */

/**
 * Counter class to count time passing between invocations.
 */
class Counter {

public:

	Counter();
	Counter(const Counter &counter);

	virtual Counter &operator =(const Counter &counter);

	Counter &copyFrom(const Counter &counter);

	virtual double current() = 0;

	/**
	 * Request the time delta in milliseconds since last invocation.
	 */
	double since();

	/**
	 * Request the number of seconds since last invocation.
	 */
	double secondsSince() { return since() / 1000; };

	static Factory<Counter> *factory;

protected:

	/** The current number of system ticks.
	 *
	 *  In SDL, this is milliseconds. */
	double m_current;

};

/**
 * @ingroup Resources
 */
template<>
class Factory<Counter> {

public:

	virtual Counter *create() = 0;

};

/**
 * @}
 */

}

#endif // WB_COUNTER_H
