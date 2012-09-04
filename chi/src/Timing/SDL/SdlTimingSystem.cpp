#include "chi-global.h"

#include "SdlTimingSystem.h"

#include "SdlCounter.h"

namespace chi {

Factory<SdlTimingSystem> *SdlTimingSystem::factory = new Factory<SdlTimingSystem>;

SdlTimingSystem::SdlTimingSystem() {

	Counter::factory = SdlCounter::factory;
}

SdlTimingSystem::~SdlTimingSystem() {
}

}
