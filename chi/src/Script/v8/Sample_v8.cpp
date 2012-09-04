#include "chi-global.h"

#include "Sample_v8.h"

using namespace v8;

namespace chi {

Sample_v8::Sample_v8(Handle<Object> wrapper, Sample *sample)
	: sample(sample)
	, owns(false)
{
	Wrap(wrapper);

	if (NULL == this->sample) {
		this->sample = Sample::factory->create();
		owns = true;
	}
}

Sample_v8::~Sample_v8() {
//	delete sample;
}

void Sample_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(Sample_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("Sample_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%play", Sample_v8::Play);

	V8_SET_METHOD(constructor_template->GetFunction(), "%load", Sample_v8::Load);

	target->Set(String::NewSymbol("Sample"), constructor_template->GetFunction());
}

Sample *Sample_v8::wrappedSample() {
	return sample;
}

v8::Handle<v8::Value> Sample_v8::New(const Arguments &args) {
	HandleScope scope;

	new Sample_v8(args.Holder());

	return args.This();
}

Handle<Object> Sample_v8::New(Sample *sample) {
	HandleScope scope;

	Handle<Object> instance = constructor_template->GetFunction()->NewInstance();

	Sample_v8 *sample_v8 = ObjectWrap::Unwrap<Sample_v8>(instance);

	sample_v8->owns = false;

	delete sample_v8->sample;
	sample_v8->sample = sample;

	return scope.Close(instance);
}

v8::Handle<v8::Value> Sample_v8::Play(const Arguments &args) {
	HandleScope scope;

	Sample_v8 *sample_v8 = ObjectWrap::Unwrap<Sample_v8>(args.Holder());

	if (NULL == sample_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Sample::play(): NULL Holder."
		)));
	}

	sample_v8->sample->play(
		args[0]->Int32Value(),
		args[1]->Int32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Sample_v8::Load(const Arguments &args) {
	HandleScope scope;

	Handle<Object> when_ = Context::GetCurrent()->Global()->Get(
		String::NewSymbol("when_")
	).As<Object>();

	Handle<Object> defer = when_->Get(
		String::NewSymbol("defer")
	).As<Function>()->Call(when_, 0, NULL).As<Object>();

	try {

		Handle<Object> sample;

		sample = Sample_v8::New(

			&Sample::manager.load(
				V8::StringToStdString(args[0]->ToString()),
				args[1]->BooleanValue()
			)
		);

		Handle<Value> resolveArgs[] = {
			sample
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

Persistent<FunctionTemplate> Sample_v8::constructor_template;

}

