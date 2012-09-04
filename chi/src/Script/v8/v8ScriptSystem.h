#ifndef CHI_V8SCRIPTSYSTEM_H
#define CHI_V8SCRIPTSYSTEM_H

#include "chi-global.h"

#include "chiv8.h"

#include "../ScriptSystem.h"

namespace chi {

/**
 * @addtogroup Script
 * @{
 */

class v8ScriptSystem : public ScriptSystem {

public:

	v8ScriptSystem();
	virtual ~v8ScriptSystem();

	void bind();

	static Factory<v8ScriptSystem> *factory;

private:

	v8::Persistent<v8::Context> context;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<v8ScriptSystem> : public Factory<ScriptSystem> {

public:

	v8ScriptSystem *create() { return new v8ScriptSystem(); }

};

/**
 * @}
 */

}

#endif // CHI_V8SCRIPTSYSTEM_H
