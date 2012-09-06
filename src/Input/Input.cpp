#include "wb-global.h"

#include "Input.h"
namespace chi {

Factory<Input> *Input::factory = NULL;

Input::Input()
{
}

bool Input::poll() {
	results.reset();

	return false;
}

}
