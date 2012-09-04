#include "chi-global.h"

#include "TimingSystem_v8.h"

using namespace v8;

namespace chi {

TimingSystem_v8::TimingSystem_v8(Handle<Object> wrapper)
	: timingSystem(TimingSystem::factory->create())
{
	Wrap(wrapper);
}

TimingSystem_v8::~TimingSystem_v8() {
	delete timingSystem;
}

void TimingSystem_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(TimingSystem_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("TimingSystem_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%close", TimingSystem_v8::Close);
//	V8_SET_PROTOTYPE_METHOD(constructor_template, "%sleep", TimingSystem_v8::Sleep);

	target->Set(String::NewSymbol("TimingSystem"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> TimingSystem_v8::New(const Arguments &args) {
	HandleScope scope;

	new TimingSystem_v8(args.Holder());

	return args.Holder();
}

v8::Handle<v8::Value> TimingSystem_v8::Close(const Arguments &args) {
	HandleScope scope;

	TimingSystem_v8 *timingSystem_v8 = ObjectWrap::Unwrap<TimingSystem_v8>(args.Holder());

	if (NULL == timingSystem_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"TimingSystem::close(): NULL Holder."
		)));
	}

	timingSystem_v8->timingSystem->close();

	return v8::Undefined();
}

//v8::Handle<v8::Value> TimingSystem_v8::Sleep(const Arguments &args) {
//	HandleScope scope;
//
//	TimingSystem_v8 *timingSystem_v8 = ObjectWrap::Unwrap<TimingSystem_v8>(args.Holder());
//
//	timingSystem_v8->system->sleep(
//		args[0]->Int32Value()
//	);
//
//	return v8::Undefined();
//}

Persistent<FunctionTemplate> TimingSystem_v8::constructor_template;

}

