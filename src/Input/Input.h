#ifndef WB_INPUT_H
#define WB_INPUT_H

#include "wb-global.h"

#include "Factory.h"

#include <deque>

namespace chi {

/**
 * @addtogroup IO
 * @{
 */

/**
 * Library-agnostic representation/gathering of user input.
 */
class Input {

public:

	Input();
	virtual ~Input() {}

	enum Type {
		Type_KeyDown,
		Type_KeyUp,
		Type_JoyAxis,
		Type_JoyButtonDown,
		Type_JoyButtonUp,
		Type_Resize,
		Type_Quit
	};

	struct KeyDown {
		int code;

		bool operator == (const KeyDown &other) { return other.code == code; }
	};

	struct KeyUp {
		int code;

		bool operator == (const KeyUp &other) { return other.code == code; }
	};

	struct JoyAxis {
		int stick;
		int axis;
		int value;
	};

	struct JoyButtonDown {
		int stick;
		int button;
	};

	struct JoyButtonUp {
		int stick;
		int button;
	};

	struct Resize {
		int width;
		int height;
	};

	struct PollResults {

		std::deque<KeyDown> keyDown;

		std::deque<KeyUp> keyUp;

		std::deque<JoyAxis> joyAxis;

		std::deque<JoyButtonDown> joyButtonDown;

		std::deque<JoyButtonUp> joyButtonUp;

		Resize resize;

		bool quit;

		PollResults()
		{
			resize.width = resize.height = 0;
			quit = false;
		}

		void reset() {

			keyDown.clear();
			keyUp.clear();

			joyAxis.clear();
			joyButtonDown.clear();
			joyButtonUp.clear();

			resize.width = resize.height = 0;
			quit = false;
		}
	};

	PollResults results;

	/**
	 * Get input from the concrete Input implementation.
	 */
	virtual bool poll();

	static Factory<Input> *factory;
};

/**
 * @ingroup Resources
 */
template <>
class Factory<Input> {

public:

	virtual ~Factory<Input>() {}

	virtual Input *create() = 0;

};

/**
 * @}
 */

}

#endif // WB_INPUT_H
