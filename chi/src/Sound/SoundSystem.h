#ifndef CHI_SOUNDSYSTEM_H
#define CHI_SOUNDSYSTEM_H

#include "chi-global.h"

#include "Factory.h"

namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

class SoundSystem {

public:

	SoundSystem();
	virtual ~SoundSystem();

	virtual void close() { }

	static Factory<SoundSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<SoundSystem> {

public:

	virtual SoundSystem *create() = 0;

};

/**
 * @}
 */

}

#endif // CHI_SOUNDSYSTEM_H
