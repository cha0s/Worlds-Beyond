#include "chi-global.h"

#include "Input_v8.h"

using namespace v8;

namespace chi {

Input_v8::Input_v8(Handle<Object> wrapper)
	: input(Input::factory->create())
{
	Wrap(wrapper);
}

Input_v8::~Input_v8() {
	delete input;
}

void Input_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(Input_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("Input_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "poll", Input_v8::Poll);

	target->Set(String::NewSymbol("Input"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> Input_v8::New(const Arguments &args) {
	HandleScope scope;

	new Input_v8(args.Holder());

	Handle<Function> Mixin = Context::GetCurrent()->Global()->Get(
		String::New("Mixin")
	).As<Function>();

	Handle<Function> EventEmitter = Context::GetCurrent()->Global()->Get(
		String::New("EventEmitter")
	).As<Function>();

	Handle<Value> argv[] = {args.Holder(), EventEmitter};
	Mixin->Call(Context::GetCurrent()->Global(), 2, argv);

	return args.Holder();
}

v8::Handle<v8::Value> Input_v8::Poll(const v8::Arguments &args) {
	HandleScope scope;

	Handle<Object> holder = args.Holder();
	Input_v8 *input_v8 = ObjectWrap::Unwrap<Input_v8>(holder);

	if (NULL == input_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Input::poll(): NULL Holder."
		)));
	}

	bool anyResults = input_v8->input->poll();
	if (anyResults) {
		Input::PollResults &results = input_v8->input->results;

		Handle<Function> emitFunction = args.Holder()->Get(
			String::New("emit")
		).As<Function>();

		Handle<Value> argv[2];

		if (results.keyDown.size() > 0) {
			argv[0] = String::New("keyDown");
			for (unsigned int i = 0; i < results.keyDown.size(); i++) {

				argv[1] = Integer::New(results.keyDown[i].code);
				emitFunction->Call(holder, 2, argv);
			}
		}

		if (results.keyUp.size() > 0) {
			argv[0] = String::New("keyUp");
			for (unsigned int i = 0; i < results.keyUp.size(); i++) {

				argv[1] = Integer::New(results.keyUp[i].code);
				emitFunction->Call(holder, 2, argv);
			}
		}

		// TODO: Joystick

		if (results.resize.width && results.resize.height) {
			argv[0] = String::New("resize");

			Handle<Array> resize = Array::New(2);
			resize->Set(0, Integer::New(results.resize.width));
			resize->Set(1, Integer::New(results.resize.height));

			argv[1] = resize;
			emitFunction->Call(holder, 2, argv);
		}

		if (results.quit) {
			argv[0] = String::New("quit");

			argv[1] = Boolean::New(true);
			emitFunction->Call(holder, 2, argv);
		}
	}

	return scope.Close(Boolean::New(anyResults));
}

Persistent<FunctionTemplate> Input_v8::constructor_template;

}

