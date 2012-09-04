#include "chi-global.h"

#include "SdlInputSystem.h"

#include "SdlInput.h"

namespace chi {

Factory<SdlInputSystem> *SdlInputSystem::factory = new Factory<SdlInputSystem>;

SdlInputSystem::SdlInputSystem() {

	Input::factory = SdlInput::factory;
}

SdlInputSystem::~SdlInputSystem() {
}

}
