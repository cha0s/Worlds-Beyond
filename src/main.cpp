#include <string>
#include <vector>

#include "boost/filesystem/operations.hpp"

#include "Exception.h"
#include "Script/Script.h"

#include "Graphics/SDL/SdlGraphicsSystem.h"
#include "Input/SDL/SdlInputSystem.h"
#include "Script/v8/v8ScriptSystem.h"
#include "Sound/SDL/SdlSoundSystem.h"
#include "System/SDL/SdlSystem.h"
#include "Timing/SDL/SdlTimingSystem.h"

using namespace chi;
using namespace v8;
using namespace std;

std::string contentRoot(char **argv);

chi::Script *enginePhase(const std::string &filename);

int main(int argc, char **argv) {
	CHI_UNUSED(argc);

	System::setResourceLocation(contentRoot(argv) + "/content");

	// Set up the concrete implementations.
	System::factory = SdlSystem::factory;
	GraphicsSystem::factory = SdlGraphicsSystem::factory;
	InputSystem::factory = SdlInputSystem::factory;
	ScriptSystem::factory = v8ScriptSystem::factory;
	SoundSystem::factory = SdlSoundSystem::factory;
	TimingSystem::factory = SdlTimingSystem::factory;

	ScriptSystem *scriptSystem = ScriptSystem::factory->create();

	chi::Script *bindings;
	chi::Script *initialize;
	chi::Script *main;
	chi::Script *finish;

	try {

		scriptSystem->bind();

		bindings = enginePhase("/script/BindingsCpp.coffee");

		initialize = enginePhase("/script/InitializeCpp.coffee");

		scriptSystem->load();

		main = enginePhase("/script/MainCpp.coffee");

		finish = enginePhase("/script/FinishCpp.coffee");

		delete finish;
		delete main;
		delete initialize;
		delete bindings;
	}
	catch (std::exception &e) {

		std::cerr << e.what() << std::endl;
	}

	delete scriptSystem;

	return 0;
}

std::string contentRoot(char **argv) {

	using namespace boost::filesystem;

    path fullPath(initial_path<path>());

    fullPath = system_complete(path(argv[0]));

    fullPath.normalize();

    return fullPath.branch_path().string();
}

chi::Script *enginePhase(const std::string &filename) {

	chi::Script *phase = chi::Script::factory->create();
	phase->compileFile(System::resourceLocation() + filename)->run();
	return phase;
}
