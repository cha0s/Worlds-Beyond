#ifndef WB_QTTIMINGSYSTEM_H
#define WB_QTTIMINGSYSTEM_H

#include "wb-global.h"

#include "../TimingSystem.h"

namespace chi {

/**
 * @addtogroup Timing
 * @{
 */

/**
 * @ingroup @QT
 */
class QtTimingSystem : public TimingSystem {

public:

	QtTimingSystem();
	~QtTimingSystem();

	static Factory<QtTimingSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<QtTimingSystem> : public Factory<TimingSystem> {

public:

	QtTimingSystem *create() { return new QtTimingSystem(); }

};

/**
 * @}
 */

}

#endif // WB_QTTIMINGSYSTEM_H
