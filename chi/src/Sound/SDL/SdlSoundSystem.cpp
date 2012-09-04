#include "chi-global.h"

#include "SdlSoundSystem.h"

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "SdlMusic.h"
#include "SdlSample.h"

namespace chi {

Factory<SdlSoundSystem> *SdlSoundSystem::factory = new Factory<SdlSoundSystem>;

SdlSoundSystem::SdlSoundSystem() {
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	Mix_AllocateChannels(16);

	Sample::factory = SdlSample::factory;
	Music::factory = SdlMusic::factory;
}

SdlSoundSystem::~SdlSoundSystem() {
	Mix_CloseAudio();
}

}
