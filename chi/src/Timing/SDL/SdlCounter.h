#ifndef CHI_SDLCOUNTER_H
#define CHI_SDLCOUNTER_H

#include "chi-global.h"

#include "../Counter.h"

namespace chi {

/**
 * @addtogroup Timing
 * @{
 */

/**
 * Counter class to count time passing between invocations.
 *
 * @ingroup SDL
 */
class SdlCounter : public Counter {

public:

	/**
	 * Counter constructor. Initialize the current ticks.
	 */
	SdlCounter();
	SdlCounter(const SdlCounter &counter);
	SdlCounter(const Counter &counter);
	~SdlCounter();

	Counter &operator =(const Counter &counter);
	SdlCounter &operator =(const SdlCounter &counter);

	SdlCounter &copyFrom(const SdlCounter &counter);

	static Factory<SdlCounter> *factory;

	double current();
};

/**
 * @ingroup Resources
 * @ingroup SDL
 */
template<>
class Factory<SdlCounter> : public Factory<Counter> {

public:

	SdlCounter *create() { return new SdlCounter(); };

};

/**
 * @}
 */

}

#endif // CHI_SDLCOUNTER_H
