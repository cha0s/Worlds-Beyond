#include "chi-global.h"

#include "Music_v8.h"

using namespace v8;

namespace chi {

Music_v8::Music_v8(Handle<Object> wrapper, Music *music)
	: music(music)
	, owns(false)
{
	Wrap(wrapper);

	if (NULL == this->music) {
		this->music = Music::factory->create();
		owns = true;
	}
}

Music_v8::~Music_v8() {
	if (owns) delete music;
}

void Music_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(Music_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("Music_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%fadeIn", Music_v8::FadeIn);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%fadeOut", Music_v8::FadeOut);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%play", Music_v8::Play);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%stop", Music_v8::Stop);

	V8_SET_METHOD(constructor_template->GetFunction(), "%load", Music_v8::Load);

	target->Set(String::NewSymbol("Music"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> Music_v8::New(const Arguments &args) {
	HandleScope scope;

	new Music_v8(args.Holder());

	return args.This();
}

Handle<Object> Music_v8::New(Music *music) {
	HandleScope scope;

	Handle<Object> instance = constructor_template->GetFunction()->NewInstance();

	Music_v8 *music_v8 = ObjectWrap::Unwrap<Music_v8>(instance);

	music_v8->owns = false;

	delete music_v8->music;
	music_v8->music = music;

	return scope.Close(instance);
}

v8::Handle<v8::Value> Music_v8::Load(const Arguments &args) {
	HandleScope scope;

	Handle<Object> when_ = Context::GetCurrent()->Global()->Get(
		String::NewSymbol("when_")
	).As<Object>();

	Handle<Object> defer = when_->Get(
		String::NewSymbol("defer")
	).As<Function>()->Call(when_, 0, NULL).As<Object>();

	try {

		Handle<Object> music;

		music = Music_v8::New(

			&Music::manager.load(
				V8::StringToStdString(args[0]->ToString()),
				args[1]->BooleanValue()
			)
		);

		Handle<Value> resolveArgs[] = {
			music
		};
		defer->Get(
			String::NewSymbol("resolve")
		).As<Function>()->Call(defer, 1, resolveArgs);
	}
	catch (std::exception &e) {

		return ThrowException(
			v8::Exception::Error(String::New(e.what()))
		);
	}

	return scope.Close(defer->Get(String::NewSymbol("promise")));
}

v8::Handle<v8::Value> Music_v8::FadeIn(const Arguments &args) {
	HandleScope scope;

	Music_v8 *music_v8 = ObjectWrap::Unwrap<Music_v8>(args.Holder());

	if (NULL == music_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Music::fadeIn(): NULL Holder."
		)));
	}

	music_v8->music->fadeIn(
		args[0]->Int32Value(),
		args[1]->Int32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Music_v8::FadeOut(const Arguments &args) {
	HandleScope scope;

	Music_v8 *music_v8 = ObjectWrap::Unwrap<Music_v8>(args.Holder());

	if (NULL == music_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Music::fadeOut(): NULL Holder."
		)));
	}

	music_v8->music->fadeOut(
		args[0]->Int32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Music_v8::Play(const Arguments &args) {
	HandleScope scope;

	Music_v8 *music_v8 = ObjectWrap::Unwrap<Music_v8>(args.Holder());

	if (NULL == music_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Music::play(): NULL Holder."
		)));
	}

	music_v8->music->play(
		args[0]->Int32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Music_v8::Stop(const Arguments &args) {
	HandleScope scope;

	Music_v8 *music_v8 = ObjectWrap::Unwrap<Music_v8>(args.Holder());

	if (NULL == music_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Music::stop(): NULL Holder."
		)));
	}

	music_v8->music->stop();

	return v8::Undefined();
}

Persistent<FunctionTemplate> Music_v8::constructor_template;

}
