#ifndef WB_SDLSOUNDSYSTEM_H
#define WB_SDLSOUNDSYSTEM_H

#include "wb-global.h"

#include "../SoundSystem.h"

namespace chi {

/**
 * @addtogroup Sounds
 * @{
 */

/**
 * @ingroup @SDL
 */
class SdlSoundSystem : public SoundSystem {

public:

	SdlSoundSystem();
	~SdlSoundSystem();

	virtual void close() { }

	static Factory<SdlSoundSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlSoundSystem> : public Factory<SoundSystem> {

public:

	SdlSoundSystem *create() { return new SdlSoundSystem(); }

};

/**
 * @}
 */

}

#endif // WB_SDLSOUNDSYSTEM_H
