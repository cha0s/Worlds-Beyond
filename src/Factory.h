#ifndef WB_FACTORY_H
#define WB_FACTORY_H

#include "wb-global.h"

namespace chi {

/**
 * @addtogroup Resources
 * @{
 */

/**
 * Factory is the absraction use to instantiate all the instances of objects
 * requiring different backends, possibly configured as late as run-time.
 */
template<class T>
class Factory {

public:

	virtual T *create() = 0;

};

/**
 * @}
 */

}

#endif // WB_FACTORY_H
