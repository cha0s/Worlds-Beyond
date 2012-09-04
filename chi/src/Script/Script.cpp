#include "chi-global.h"

#include "Script.h"

#include <deque>

#include "v8/Image_v8.h"
#include "v8/Screen_v8.h"
#include "v8/Input_v8.h"
#include "v8/Music_v8.h"
#include "v8/Sample_v8.h"
#include "v8/Counter_v8.h"

#include "v8/System_v8.h"
#include "v8/GraphicsSystem_v8.h"
#include "v8/InputSystem_v8.h"
#include "v8/SoundSystem_v8.h"
#include "v8/TimingSystem_v8.h"

#include <boost/filesystem.hpp>

#include "Exception.h"
using namespace v8;

namespace chi {

Factory<Script> *Script::factory = NULL;

Script::Script()
{
}

Script *Script::compileFile(const std::string &filename) {

	return compileCode(
		chi::System::fileToString(filename),
		filename
	);
}

Script::~Script() {
}

}
