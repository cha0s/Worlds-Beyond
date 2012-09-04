#include "chi-global.h"

#include "QtTimingSystem.h"

#include "QtCounter.h"

namespace chi {

Factory<QtTimingSystem> *QtTimingSystem::factory = new Factory<QtTimingSystem>;

QtTimingSystem::QtTimingSystem() {

	Counter::factory = QtCounter::factory;
}

QtTimingSystem::~QtTimingSystem() {
}

}
