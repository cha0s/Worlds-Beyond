#ifndef CHI_V8SCRIPT_H
#define CHI_V8SCRIPT_H

#include "chi-global.h"

#include "chiv8.h"
#include "../Script.h"

namespace chi {

class v8Script : public Script{

public:

	v8Script();
	virtual ~v8Script();

	std::string preCompileCode(const std::string &code, const std::string &filename = "");
	Script *compileCode(const std::string &code, const std::string &filename = "");
	void run();

	static Factory<v8Script> *factory;

private:

	v8::Persistent<v8::Script> script;
};

template <>
class Factory<v8Script> : public Factory<Script> {

public:

	v8Script *create() { return new v8Script(); }

};

}

#endif // CHI_V8SCRIPT_H
