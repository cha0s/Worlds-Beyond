#include "chi-global.h"

#include "Counter_v8.h"

using namespace v8;

namespace chi {

Counter_v8::Counter_v8(Handle<Object> wrapper)
	: counter(Counter::factory->create())
{
	Wrap(wrapper);
}

Counter_v8::~Counter_v8() {
	delete counter;
}

void Counter_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(Counter_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("Counter_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%current", Counter_v8::Current);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%secondsSince", Counter_v8::SecondsSince);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%since", Counter_v8::Since);

	target->Set(String::NewSymbol("Counter"), constructor_template->GetFunction());
}

Counter *Counter_v8::wrappedCounter() {
	return counter;
}

v8::Handle<v8::Value> Counter_v8::New(const Arguments &args) {
	HandleScope scope;

	new Counter_v8(args.Holder());

	return args.This();
}

v8::Handle<v8::Value> Counter_v8::Current(const Arguments &args) {
	HandleScope scope;

	Counter_v8 *counter_v8 = ObjectWrap::Unwrap<Counter_v8>(args.Holder());

	if (NULL == counter_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Counter::current(): NULL Holder."
		)));
	}

	return scope.Close(Number::New(counter_v8->counter->current()));
}

v8::Handle<v8::Value> Counter_v8::SecondsSince(const Arguments &args) {
	HandleScope scope;

	Counter_v8 *counter_v8 = ObjectWrap::Unwrap<Counter_v8>(args.Holder());

	if (NULL == counter_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Counter::secondsSince(): NULL Holder."
		)));
	}

	return scope.Close(Number::New(counter_v8->counter->secondsSince()));
}

v8::Handle<v8::Value> Counter_v8::Since(const Arguments &args) {
	HandleScope scope;

	Counter_v8 *counter_v8 = ObjectWrap::Unwrap<Counter_v8>(args.Holder());

	if (NULL == counter_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Counter::since(): NULL Holder."
		)));
	}

	return scope.Close(Number::New(counter_v8->counter->since()));
}

Persistent<FunctionTemplate> Counter_v8::constructor_template;

}

