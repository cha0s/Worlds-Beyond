#ifndef CHI_INPUTSYSTEM_H
#define CHI_INPUTSYSTEM_H

#include "chi-global.h"

#include "Factory.h"

namespace chi {

/**
 * @addtogroup Input
 * @{
 */

class InputSystem {

public:

	InputSystem();
	virtual ~InputSystem();

	virtual void close() { }

	static Factory<InputSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<InputSystem> {

public:

	virtual InputSystem *create() = 0;

};

/**
 * @}
 */

}

#endif // CHI_INPUTSYSTEM_H
