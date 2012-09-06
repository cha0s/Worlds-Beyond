#ifndef WB_TIMINGSYSTEM_H
#define WB_TIMINGSYSTEM_H

#include "wb-global.h"

#include "Factory.h"

namespace chi {

/**
 * @addtogroup Timing
 * @{
 */

class TimingSystem {

public:

	TimingSystem();
	virtual ~TimingSystem();

	virtual void close() { }

	static Factory<TimingSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<TimingSystem> {

public:

	virtual TimingSystem *create() = 0;

};

/**
 * @}
 */

}

#endif // WB_TIMINGSYSTEM_H
