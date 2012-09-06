#ifndef WB_INPUT_V8_H
#define WB_INPUT_V8_H

#include "wb-global.h"

#include "wbv8.h"
#include "ObjectWrap.h"
#include "../../Input/Input.h"

namespace chi {

class Input_v8 : public ObjectWrap {

public:

	~Input_v8();

	static void Register(v8::Handle<v8::Object> target);

	Input *input;

private:

	Input_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Poll(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;
};

}

#endif // WB_INPUT_V8_H
