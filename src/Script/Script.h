#ifndef WB_SCRIPT_H
#define WB_SCRIPT_H

#include "wb-global.h"

#include "../wbv8.h"
#include "Factory.h"

namespace chi {

class Script {

public:

	Script();
	virtual ~Script();

	Script *compileFile(const std::string &filename);
	virtual Script *compileCode(const std::string &code, const std::string &filename = "") = 0;
	virtual std::string preCompileCode(const std::string &code, const std::string &filename = "") = 0;

	virtual void run() = 0;

	static Factory<Script> *factory;

};

template <>
class Factory<Script> {

public:

	virtual Script *create() = 0;

};

}

#endif // WB_SCRIPT_H
