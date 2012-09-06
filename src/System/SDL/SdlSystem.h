#ifndef WB_SDLSYSTEM_H
#define WB_SDLSYSTEM_H

#include "wb-global.h"

#include "../System.h"

namespace chi {

/**
 * @addtogroup System
 * @{
 */

/**
 * @ingroup @SDL
 */
class SdlSystem : public System {

public:

	SdlSystem();
	~SdlSystem();

	void close();

	/**
	 * Delay execution.
	 *
	 * @param ms
	 *   The number of milliseconds to wait.
	 */
	void sleep(int ms);

	static Factory<SdlSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlSystem> : public Factory<System> {

public:

	SdlSystem *create() { return new SdlSystem() ; }

};

/**
 * @}
 */

}

#endif // WB_SDLSYSTEM_H
