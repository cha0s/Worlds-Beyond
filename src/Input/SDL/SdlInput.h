#ifndef WB_SDLINPUT_H
#define WB_SDLINPUT_H

#include "wb-global.h"

#include "SDL/SDL.h"

#include "../Input.h"

namespace chi {

/**
 * @addtogroup IO
 * @{
 */

/**
 * SDL representation/gathering of user input.
 *
 * @ingroup SDL
 */
class SdlInput : public Input {

public:

	SdlInput();

	/**
	 * Get input from the concrete Input implementation.
	 */
//	bool fetch();

	bool poll();

	static Factory<SdlInput> *factory;

//	int numJoysticks;
//	SDL_Joystick *joystick;
};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlInput> : public Factory<Input> {

public:

	virtual ~Factory<SdlInput>() {}

	virtual SdlInput *create() { return new SdlInput(); }

};

/**
 * @}
 */

}

#endif // WB_SDLINPUT_H
