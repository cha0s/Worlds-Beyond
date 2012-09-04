#include "chi-global.h"

#include "SoundSystem_v8.h"

using namespace v8;

namespace chi {

SoundSystem_v8::SoundSystem_v8(Handle<Object> wrapper)
	: soundSystem(SoundSystem::factory->create())
{
	Wrap(wrapper);
}

SoundSystem_v8::~SoundSystem_v8() {
	delete soundSystem;
}

void SoundSystem_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(SoundSystem_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("SoundSystem_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%close", SoundSystem_v8::Close);

	target->Set(String::NewSymbol("SoundSystem"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> SoundSystem_v8::New(const Arguments &args) {
	HandleScope scope;

	new SoundSystem_v8(args.Holder());

	return args.Holder();
}

v8::Handle<v8::Value> SoundSystem_v8::Close(const Arguments &args) {
	HandleScope scope;

	SoundSystem_v8 *soundSystem_v8 = ObjectWrap::Unwrap<SoundSystem_v8>(args.Holder());

	if (NULL == soundSystem_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"SoundSystem::close(): NULL Holder."
		)));
	}

	soundSystem_v8->soundSystem->close();

	return v8::Undefined();
}

Persistent<FunctionTemplate> SoundSystem_v8::constructor_template;

}

