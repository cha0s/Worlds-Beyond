#ifndef WB_SCRIPTSYSTEM_H
#define WB_SCRIPTSYSTEM_H

#include "wb-global.h"

#include <string>
#include <vector>

#include "Factory.h"

namespace chi {

/**
 * @addtogroup Script
 * @{
 */

class ScriptSystem {

public:

	ScriptSystem();
	virtual ~ScriptSystem();

	virtual void bind();

	std::vector<std::string> load();

	static Factory<ScriptSystem> *factory;

private:

	std::vector<std::string> m_scriptFilenames;

};

template <>
class Factory<ScriptSystem> {

public:

	virtual ScriptSystem *create() = 0;

};

}

#endif // WB_SCRIPTSYSTEM_H
