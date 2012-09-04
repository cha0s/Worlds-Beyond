#ifndef CHI_QTSYSTEM_H
#define CHI_QTSYSTEM_H

#include "chi-global.h"

#include "../System.h"

namespace chi {

/**
 * @addtogroup System
 * @{
 */

/**
 * @ingroup @Qt
 */
class QtSystem : public System {

public:

	/**
	 * Delay execution.
	 *
	 * @param ms
	 *   The number of milliseconds to wait.
	 */
	void sleep(int ms);

	static Factory<QtSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<QtSystem> : public Factory<System> {

public:

	QtSystem *create() { return new QtSystem() ; }

};

/**
 * @}
 */

}

#endif // CHI_QTSYSTEM_H
