#include "wb-global.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "Exception.h"
#include "Script.h"
#include "ScriptSystem.h"
#include "System/System.h"

#include "wbv8.h"

using namespace std;
using namespace v8;

namespace chi {

map<string, Script *> scripts;

Factory<ScriptSystem> *ScriptSystem::factory = NULL;

ScriptSystem::ScriptSystem()
{
}

void ScriptSystem::bind() {

	chi::Script *coffeeCompiler = chi::Script::factory->create();
	coffeeCompiler->compileFile(
		System::resourceLocation() + "/script/CoffeeScript.js"
	)->run();
}

std::vector<std::string> ScriptSystem::load() {

	std::vector<std::string> filenames;

	static const string types[] = {
		"config", "global", "extensions",
		"classes", "states", "ui"
	};
	for (unsigned int i = 0; i < sizeof(types) / sizeof(types[0]); i++) {

		std::vector<std::string> gathered = chi::System::gatherFiles(
			System::resourceLocation() + "/script/" + types[i],
			"(.*\\.js|.*\\.coffee)"
		);

		for (unsigned int j = 0; j < gathered.size(); j++) {
			filenames.push_back(gathered[j]);
		}
	}

	sort(filenames.begin(), filenames.end());

	HandleScope scope;

	for (unsigned int i = 0; i < filenames.size(); i++) {

		Script *script = Script::factory->create();
		scripts[filenames[i]] = script->compileFile(filenames[i]);
	}

	std::vector<std::string> loadedFilenames;

	while (scripts.size() > 0) {

		unsigned int size = scripts.size();

		vector<string>::iterator i = filenames.begin();
		while (i != filenames.end()) {

			try {
				scripts[*i]->run();

				loadedFilenames.push_back(*i);

				delete scripts[*i];

				scripts.erase(*i);
				i = filenames.erase(i);
			}
			catch (std::exception &e) {

				++i;
			}
		}

		if (size == scripts.size()) {

			std::string text;

			map<string, Script *>::iterator i = scripts.begin();
			while (i != scripts.end()) {

				try {
					(i->second)->run();
				}
				catch (std::exception &e) {
					text += e.what();
				}

				delete i->second;
				scripts.erase(i++);
			}

			throw chi::Exception(text);
		}
	}

	return loadedFilenames;
}

ScriptSystem::~ScriptSystem() {
}

}
