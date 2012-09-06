#include "wb-global.h"

#include "Screen_v8.h"

#include "Image_v8.h"

using namespace v8;

namespace chi {

Screen_v8::Screen_v8(Handle<Object> wrapper)
	: screen(Screen::factory->create())
{
	Wrap(wrapper);
}

Screen_v8::~Screen_v8() {
	delete screen;
}

void Screen_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(Screen_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("Screen_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%render", Screen_v8::Render);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%set", Screen_v8::Set);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%setMouseVisibility", Screen_v8::SetMouseVisibility);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%setWindowTitle", Screen_v8::SetWindowTitle);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%size", Screen_v8::Size);

	target->Set(String::NewSymbol("Screen"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> Screen_v8::New(const Arguments &args) {
	HandleScope scope;

	new Screen_v8(args.Holder());

	return args.Holder();
}

v8::Handle<v8::Value> Screen_v8::Render(const Arguments &args) {
	HandleScope scope;

	Screen_v8 *screen_v8 = ObjectWrap::Unwrap<Screen_v8>(args.Holder());

	if (NULL == screen_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Screen::render(): NULL Holder."
		)));
	}

	Image_v8 *source = ObjectWrap::Unwrap<Image_v8>(args[0]->ToObject());

	if (NULL == source) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Screen::render(): NULL source."
		)));
	}

	screen_v8->screen->render(
		*source->wrappedImage()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Screen_v8::Set(const Arguments &args) {
	HandleScope scope;

	Screen_v8 *screen_v8 = ObjectWrap::Unwrap<Screen_v8>(args.Holder());

	if (NULL == screen_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Screen::set(): NULL Holder."
		)));
	}

	Handle<Array> dimensions = args[0].As<Array>();

	screen_v8->screen->set(
		dimensions->Get(0)->Int32Value(),
		dimensions->Get(1)->Int32Value(),
		static_cast<Screen::ScreenFlags>(args[1]->Int32Value())
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Screen_v8::SetMouseVisibility(const Arguments &args) {
	HandleScope scope;

	Screen_v8 *screen_v8 = ObjectWrap::Unwrap<Screen_v8>(args.Holder());

	if (NULL == screen_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Screen::setMouseVisibility(): NULL Holder."
		)));
	}

	screen_v8->screen->setMouseVisibility(
		args[0]->BooleanValue()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Screen_v8::SetWindowTitle(const Arguments &args) {
	HandleScope scope;

	Screen_v8 *screen_v8 = ObjectWrap::Unwrap<Screen_v8>(args.Holder());

	if (NULL == screen_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Screen::setWindowTitle(): NULL Holder."
		)));
	}

	screen_v8->screen->setWindowTitle(
		V8::StringToStdString(args[0]->ToString()),
		V8::StringToStdString(args[1]->ToString())
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Screen_v8::Size(const Arguments &args) {
	HandleScope scope;

	Screen_v8 *screen_v8 = ObjectWrap::Unwrap<Screen_v8>(args.Holder());

	if (NULL == screen_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Screen::size(): NULL Holder."
		)));
	}

	Handle<Array> size = Array::New();

	size->Set(0, Integer::New(screen_v8->screen->width()));
	size->Set(1, Integer::New(screen_v8->screen->height()));

	return scope.Close(size);
}

Persistent<FunctionTemplate> Screen_v8::constructor_template;

}

