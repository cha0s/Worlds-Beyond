#ifndef WB_SDLSCREEN_H
#define WB_SDLSCREEN_H

#include "wb-global.h"

#include <string>

#include "Factory.h"

#include "../Screen.h"

#include "SdlImage.h"

namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Represents the screen buffers and operations.
 *
 * @ingroup SDL
 */
class SdlScreen : public Screen {

public:

	SdlScreen();
	~SdlScreen();

	void set(int width, int height, ScreenFlags f = Flags_Default);
	void render(Image &working);

	void setMouseVisibility(bool visible);

	void setWindowTitle(const std::string &window, const std::string &iconified = "");

	static Factory<SdlScreen> *factory;

private:

	SdlImage *image;
};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlScreen> : public Factory<Screen> {

public:

	SdlScreen *create() { return new SdlScreen(); }

};

/**
 * @}
 */

}

#endif // WB_SDLSCREEN_H
