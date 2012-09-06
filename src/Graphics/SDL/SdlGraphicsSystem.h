#ifndef WB_SDLGRAPHICSSYSTEM_H
#define WB_SDLGRAPHICSSYSTEM_H

#include "wb-global.h"

#include "../GraphicsSystem.h"

namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * @ingroup @SDL
 */
class SdlGraphicsSystem : public GraphicsSystem {

public:

	SdlGraphicsSystem();
	~SdlGraphicsSystem();

	static Factory<SdlGraphicsSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlGraphicsSystem> : public Factory<GraphicsSystem> {

public:

	SdlGraphicsSystem *create() { return new SdlGraphicsSystem(); }

};

/**
 * @}
 */

}

#endif // WB_SDLGRAPHICSSYSTEM_H
