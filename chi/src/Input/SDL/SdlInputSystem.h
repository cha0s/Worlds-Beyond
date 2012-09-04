#ifndef CHI_SDLINPUTSYSTEM_H
#define CHI_SDLINPUTSYSTEM_H

#include "chi-global.h"

#include "../InputSystem.h"

namespace chi {

/**
 * @addtogroup Input
 * @{
 */

/**
 * @ingroup @SDL
 */
class SdlInputSystem : public InputSystem {

public:

	SdlInputSystem();
	~SdlInputSystem();

	static Factory<SdlInputSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlInputSystem> : public Factory<InputSystem> {

public:

	SdlInputSystem *create() { return new SdlInputSystem(); }

};

/**
 * @}
 */

}

#endif // CHI_SDLINPUTSYSTEM_H
