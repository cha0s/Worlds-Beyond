#include "wb-global.h"

#include "SdlInput.h"

#include "SDL/SDL.h"

#include <algorithm>
#include "math.h"

using namespace std;

namespace chi {

Factory<SdlInput> *SdlInput::factory = new Factory<SdlInput>;

SdlInput::SdlInput()
	: Input()
//	, numJoysticks(0)
//	, joystick(NULL)
{
//
//	numJoysticks = SDL_NumJoysticks();
//
//	if (numJoysticks > 0) {
//	    SDL_JoystickEventState(SDL_ENABLE);
//	    joystick = SDL_JoystickOpen(0);
//	}
}

bool SdlInput::poll() {
	bool anyResults = Input::poll();

	static SDL_Event event;
	while (SDL_PollEvent(&event)) {

		switch (event.type) {

		case SDL_QUIT: {
			anyResults = true;

			results.quit = true;
			break;

		}

		case SDL_KEYDOWN: {
			anyResults = true;

			KeyDown keyDown = {event.key.keysym.sym};
			deque<KeyDown>::iterator i = find(
				results.keyDown.begin(),
				results.keyDown.end(),
				keyDown
			);

			if (results.keyDown.end() == i) {
				results.keyDown.push_back(keyDown);
			}

			break;
		}

		case SDL_KEYUP: {
			anyResults = true;

			KeyUp keyUp = {event.key.keysym.sym};
			deque<KeyUp>::iterator i = find(
				results.keyUp.begin(),
				results.keyUp.end(),
				keyUp
			);

			if (results.keyUp.end() == i) {
				results.keyUp.push_back(keyUp);
			}

			break;
		}

		case SDL_VIDEORESIZE: {
			anyResults = true;

			results.resize.width = event.resize.w;
			results.resize.height = event.resize.h;

			break;
		}

		default: {
			break;

		}

		}
	}

	return anyResults;
}

//bool SdlInput::fetch() {
//	static SDL_Event event;
//
//	screen_resize = Size(0, 0);
//
//	cancel = false;
//	confirm = false;
//	menu = 0;
//
//	pressState[UP] = false;
//	pressState[DOWN] = false;
//	pressState[RIGHT] = false;
//	pressState[LEFT] = false;
//
//	/** Retrieve an SDL event from the queue. */
//	if (SDL_PollEvent(&event)) {
//
//		// Handle events.
//		switch (event.type) {
//
//			/** If the user clicked the X or hit alt-f4 (i.e. if the
//			 *  window manager is saying to shut down), then set the
//			 *  exit flag. */
//			case SDL_QUIT:
//				exit = true;
//				break;
//
//			case SDL_JOYAXISMOTION:
//
//				if ((event.jaxis.value < -3200) || (event.jaxis.value > 3200)) {
//					if (event.jaxis.axis == 0) {
//
//						if (event.jaxis.value < 0) {
//							state[LEFT] = 1;
//						}
//						else {
//							state[RIGHT] = 1;
//						}
//					}
//					if (event.jaxis.axis == 1) {
//						if (event.jaxis.value < 0) {
//							state[UP] = 1;
//						}
//						else {
//							state[DOWN] = 1;
//						}
//					}
//				}
//				else {
//					if (event.jaxis.axis == 0) {
//						state[RIGHT] = state[LEFT] = 0;
//					}
//					if (event.jaxis.axis == 1) {
//						state[UP] = state[DOWN] = 0;
//					}
//				}
//				break;
//
//			case SDL_JOYBUTTONDOWN:
//
////				std::cerr << event.jbutton.which << std::endl;
////				std::cerr << event.jbutton.button << std::endl;
////				std::cerr << event.jbutton.state << std::endl;
//
//				break;
//
//
//			/** Check keyboard presses. */
//			case SDL_KEYDOWN:
//				switch(event.key.keysym.sym) {
//					case SDLK_UP:
//						state[UP] = 1;
//						break;
//
//					case SDLK_RIGHT:
//						state[RIGHT] = 1;
//						break;
//
//					case SDLK_DOWN:
//						state[DOWN] = 1;
//						break;
//
//					case SDLK_LEFT:
//						state[LEFT] = 1;
//						break;
//
//					case SDLK_BACKSPACE:
//						cancel = true;
//						break;
//
//					case SDLK_RETURN:
//						confirm = true;
//						break;
//
//					case SDLK_ESCAPE:
//						menu = true;
//						break;
//
//					default:
//						break;
//				}
//				break;
//
//			/** Check keyboard releases. */
//			case SDL_KEYUP:
//				switch(event.key.keysym.sym) {
//					case SDLK_UP:
//						state[UP] = 0;
//						break;
//
//					case SDLK_RIGHT:
//						state[RIGHT] = 0;
//						break;
//
//					case SDLK_DOWN:
//						state[DOWN] = 0;
//						break;
//
//					case SDLK_LEFT:
//						state[LEFT] = 0;
//						break;
//
//					default:
//						break;
//				}
//				break;
//
//			/** Check requests for screen size update. */
//			case SDL_VIDEORESIZE:
//				screen_resize = Size(event.resize.w, event.resize.h);
//				break;
//		}
//
//		/** Pre-calculate the movement vector. */
//		movement = Eigen::Vector2f(state[RIGHT] - state[LEFT], state[DOWN] - state[UP]);
//	}
//}
//
}
