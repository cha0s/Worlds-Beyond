#include "chi-global.h"

#include "QtGraphicsSystem.h"

#include "QtImage.h"

namespace chi {

Factory<QtGraphicsSystem> *QtGraphicsSystem::factory = new Factory<QtGraphicsSystem>;

QtGraphicsSystem::QtGraphicsSystem() {

	Image::factory = QtImage::factory;
}

QtGraphicsSystem::~QtGraphicsSystem() {
}

}
