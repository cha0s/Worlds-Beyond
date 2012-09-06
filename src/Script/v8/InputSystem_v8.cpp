#include "wb-global.h"

#include "InputSystem_v8.h"

using namespace v8;

namespace chi {

InputSystem_v8::InputSystem_v8(Handle<Object> wrapper)
	: inputSystem(InputSystem::factory->create())
{
	Wrap(wrapper);
}

InputSystem_v8::~InputSystem_v8() {
	delete inputSystem;
}

void InputSystem_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(InputSystem_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("InputSystem_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%close", InputSystem_v8::Close);

	target->Set(String::NewSymbol("InputSystem"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> InputSystem_v8::New(const Arguments &args) {
	HandleScope scope;

	new InputSystem_v8(args.Holder());

	return args.Holder();
}

v8::Handle<v8::Value> InputSystem_v8::Close(const Arguments &args) {
	HandleScope scope;

	InputSystem_v8 *inputSystem_v8 = ObjectWrap::Unwrap<InputSystem_v8>(args.Holder());

	if (NULL == inputSystem_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"InputSystem::close(): NULL Holder."
		)));
	}

	inputSystem_v8->inputSystem->close();

	return v8::Undefined();
}

Persistent<FunctionTemplate> InputSystem_v8::constructor_template;

}

