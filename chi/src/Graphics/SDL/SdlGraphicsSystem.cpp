#include "chi-global.h"

#include "SdlGraphicsSystem.h"

#include "SdlImage.h"
#include "SdlScreen.h"

namespace chi {

Factory<SdlGraphicsSystem> *SdlGraphicsSystem::factory = new Factory<SdlGraphicsSystem>;

SdlGraphicsSystem::SdlGraphicsSystem() {

	SDL_SetVideoMode(1, 1, 32, 0);

	Image::factory = SdlImage::factory;
	Screen::factory = SdlScreen::factory;
}

SdlGraphicsSystem::~SdlGraphicsSystem() {
}

}
