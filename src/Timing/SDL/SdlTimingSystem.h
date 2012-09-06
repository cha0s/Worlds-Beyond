#ifndef WB_SDLTIMINGSYSTEM_H
#define WB_SDLTIMINGSYSTEM_H

#include "wb-global.h"

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

#endif // WB_SDLTIMINGSYSTEM_H
