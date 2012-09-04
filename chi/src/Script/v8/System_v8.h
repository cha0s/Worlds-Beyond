#ifndef CHI_SYSTEM_V8_H
#define CHI_SYSTEM_V8_H

#include "chi-global.h"

#include "chiv8.h"
#include "ObjectWrap.h"
#include "../../System/System.h"

namespace chi {

class System_v8 : public ObjectWrap {

public:

	~System_v8();

	static void Register(v8::Handle<v8::Object> target);

	System *system;

private:

	System_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Close(const v8::Arguments &args);
	static v8::Handle<v8::Value> Sleep(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;
};

}

#endif // CHI_SYSTEM_V8_H
