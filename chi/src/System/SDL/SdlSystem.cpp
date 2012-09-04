#include "chi-global.h"

#include "SdlSystem.h"

#include "SDL/SDL.h"

namespace chi {

Factory<SdlSystem> *SdlSystem::factory = new Factory<SdlSystem>;

SdlSystem::SdlSystem() {

	SDL_putenv(const_cast<char *>("SDL_VIDEO_CENTERED=center"));

	const char *currentDriver = SDL_getenv(const_cast<char *>("SDL_VIDEODRIVER"));
	if (currentDriver) {
		std::string *driver = new std::string("CHI_SDL_VIDEODRIVER=");
		*driver += currentDriver;
		SDL_putenv(const_cast<char *>(driver->c_str()));
	}
	SDL_putenv(const_cast<char *>("CHI_SDL_VIDEORESTORE=1"));
	SDL_putenv(const_cast<char *>("SDL_VIDEODRIVER=dummy"));

	SDL_Init(SDL_INIT_EVERYTHING);
}

SdlSystem::~SdlSystem() {
	close();
}

void SdlSystem::close() {
	SDL_Quit();
}


void SdlSystem::sleep(int ms) {
	SDL_Delay(ms);
}

}
