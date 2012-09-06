#ifndef WB_INPUTSYSTEM_V8_H
#define WB_INPUTSYSTEM_V8_H

#include "wb-global.h"

#include "wbv8.h"
#include "ObjectWrap.h"
#include "../../Input/InputSystem.h"

namespace chi {

class InputSystem_v8 : public ObjectWrap {

public:

	~InputSystem_v8();

	static void Register(v8::Handle<v8::Object> target);

	InputSystem *inputSystem;

private:

	InputSystem_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Close(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;
};

}

#endif // WB_INPUTSYSTEM_V8_H
