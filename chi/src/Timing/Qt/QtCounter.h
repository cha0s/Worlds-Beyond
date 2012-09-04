#ifndef CHI_QTCOUNTER_H
#define CHI_QTCOUNTER_H

#include "chi-global.h"

#include <QtCore/QTime>

#include "../Counter.h"

namespace chi {

/**
 * @addtogroup Timing
 * @{
 */

/**
 * Counter class to count time passing between invocations.
 *
 * @ingroup Qt
 */
class QtCounter : public Counter {

public:

	/**
	 * Counter constructor. Initialize the current ticks.
	 */
	QtCounter();
	QtCounter(const QtCounter &counter);
	QtCounter(const Counter &counter);
	~QtCounter();

	Counter &operator =(const Counter &counter);
	QtCounter &operator =(const QtCounter &counter);

	QtCounter &copyFrom(const QtCounter &counter);

	double current();

	static Factory<QtCounter> *factory;

private:

	QTime time;

};

/**
 * @ingroup Resources
 * @ingroup Qt
 */
template<>
class Factory<QtCounter> : public Factory<Counter> {

public:

	QtCounter *create() { return new QtCounter(); };

};

/**
 * @}
 */

}

#endif // CHI_QTCOUNTER_H
