#ifndef CHI_TIMINGSYSTEM_H
#define CHI_TIMINGSYSTEM_H

#include "chi-global.h"

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

#endif // CHI_TIMINGSYSTEM_H
