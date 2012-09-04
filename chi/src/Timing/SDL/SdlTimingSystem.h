#ifndef CHI_SDLTIMINGSYSTEM_H
#define CHI_SDLTIMINGSYSTEM_H

#include "chi-global.h"

#include "../TimingSystem.h"

namespace chi {

/**
 * @addtogroup Timing
 * @{
 */

/**
 * @ingroup @SDL
 */
class SdlTimingSystem : public TimingSystem {

public:

	SdlTimingSystem();
	~SdlTimingSystem();

	static Factory<SdlTimingSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlTimingSystem> : public Factory<TimingSystem> {

public:

	SdlTimingSystem *create() { return new SdlTimingSystem(); }

};

/**
 * @}
 */

}

#endif // CHI_SDLTIMINGSYSTEM_H
