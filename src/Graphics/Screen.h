#ifndef WB_SCREEN_H
#define WB_SCREEN_H

#include "wb-global.h"

#include <string>

#include "Image.h"

namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Represents the screen buffers and operations.
 */
class Screen {

public:

	enum ScreenFlags {
		Flags_Default    = 0,
		Flags_Fullscreen = 1
	};

	virtual ~Screen() { }

	virtual void set(int width, int height, ScreenFlags f = Flags_Default);
	virtual void render(Image &working) = 0;

	virtual void setMouseVisibility(bool visible) = 0;
	virtual void setWindowTitle(const std::string &window, const std::string &iconified = "") = 0;

	int width() const;
	int height() const;

	static Factory<Screen> *factory;

private:

	int m_width;
	int m_height;
};

/**
 * @ingroup Resources
 */
template <>
class Factory<Screen> {

public:

	virtual Screen *create() = 0;

};

/**
 * @}
 */

}

#endif // WB_SCREEN_H
