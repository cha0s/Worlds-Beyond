#ifndef WB_TIMINGSYSTEM_V8_H
#define WB_TIMINGSYSTEM_V8_H

#include "wb-global.h"

#include "wbv8.h"
#include "ObjectWrap.h"
#include "../../Timing/TimingSystem.h"

namespace chi {

class TimingSystem_v8 : public ObjectWrap {

public:

	~TimingSystem_v8();

	static void Register(v8::Handle<v8::Object> target);

	TimingSystem *timingSystem;

private:

	TimingSystem_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Close(const v8::Arguments &args);
//	static v8::Handle<v8::Value> Sleep(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;
};

}

#endif // WB_TIMINGSYSTEM_V8_H
