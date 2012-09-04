#include "chi-global.h"

#include "System_v8.h"

using namespace v8;

namespace chi {

System_v8::System_v8(Handle<Object> wrapper)
	: system(System::factory->create())
{
	Wrap(wrapper);
}

System_v8::~System_v8() {
	delete system;
}

void System_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(System_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("System_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%close", System_v8::Close);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%sleep", System_v8::Sleep);

	target->Set(String::NewSymbol("System"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> System_v8::New(const Arguments &args) {
	HandleScope scope;

	new System_v8(args.Holder());

	return args.Holder();
}

v8::Handle<v8::Value> System_v8::Close(const Arguments &args) {
	HandleScope scope;

	System_v8 *system_v8 = ObjectWrap::Unwrap<System_v8>(args.Holder());

	if (NULL == system_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"System::close(): NULL Holder."
		)));
	}

	system_v8->system->close();

	return v8::Undefined();
}

v8::Handle<v8::Value> System_v8::Sleep(const Arguments &args) {
	HandleScope scope;

	System_v8 *system_v8 = ObjectWrap::Unwrap<System_v8>(args.Holder());

	if (NULL == system_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Screen::sleep(): NULL Holder."
		)));
	}

	system_v8->system->sleep(
		args[0]->Int32Value()
	);

	return v8::Undefined();
}

Persistent<FunctionTemplate> System_v8::constructor_template;

}

