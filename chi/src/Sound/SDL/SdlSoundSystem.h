#ifndef CHI_SDLSOUNDSYSTEM_H
#define CHI_SDLSOUNDSYSTEM_H

#include "chi-global.h"

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

#endif // CHI_SDLSOUNDSYSTEM_H
