#ifndef CHI_FACTORY_H
#define CHI_FACTORY_H

#include "chi-global.h"

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

#endif // CHI_FACTORY_H
