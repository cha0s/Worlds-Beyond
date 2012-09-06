#include "wb-global.h"

#include "Image_v8.h"

using namespace v8;

namespace chi {

Image_v8::Image_v8(Handle<Object> wrapper, Image *image)
	: image(image)
	, owns(false)
{
	Wrap(wrapper);

	if (NULL == this->image) {
		this->image = Image::factory->create();
		owns = true;
	}
}

Image_v8::~Image_v8() {
	if (owns) delete image;
}

void Image_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(Image_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("Image_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%drawBox", Image_v8::DrawBox);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%drawCircle", Image_v8::DrawCircle);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%drawRect", Image_v8::DrawRect);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%drawLine", Image_v8::DrawLine);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%fill", Image_v8::Fill);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%floodfill", Image_v8::Floodfill);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%height", Image_v8::Height);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%pixelAt", Image_v8::PixelAt);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%render", Image_v8::Render);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%renderGrayscale", Image_v8::RenderGrayscale);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%setPixelAt", Image_v8::SetPixelAt);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%uri", Image_v8::Uri);
	V8_SET_PROTOTYPE_METHOD(constructor_template, "%width", Image_v8::Width);

	V8_SET_METHOD(constructor_template->GetFunction(), "%load", Image_v8::Load);

	target->Set(v8::String::NewSymbol("Image"), constructor_template->GetFunction());
}

Image *Image_v8::wrappedImage() {
	return image;
}

v8::Handle<v8::Value> Image_v8::New(const Arguments &args) {
	HandleScope scope;

	Image *image = NULL;

	if (2 == args.Length()) {

		image = Image::factory->create(
			args[0]->Uint32Value(),
			args[1]->Uint32Value()
		);
	}

	new Image_v8(args.Holder(), image);

	return args.This();
}

Handle<Object> Image_v8::New(Image *image) {
	HandleScope scope;

	Handle<Object> instance = constructor_template->GetFunction()->NewInstance();

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(instance);

	image_v8->owns = false;

	delete image_v8->image;
	image_v8->image = image;

	return scope.Close(instance);
}

v8::Handle<v8::Value> Image_v8::Load(const Arguments &args) {
	HandleScope scope;

	Handle<Object> when_ = Context::GetCurrent()->Global()->Get(
		String::NewSymbol("when_")
	).As<Object>();

	Handle<Object> defer = when_->Get(
		String::NewSymbol("defer")
	).As<Function>()->Call(when_, 0, NULL).As<Object>();

	try {

		Handle<Object> image;

		image = Image_v8::New(

			&Image::manager.load(
				V8::StringToStdString(args[0]->ToString()),
				args[1]->BooleanValue()
			)
		);

		Handle<Value> resolveArgs[] = {
			image
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

v8::Handle<v8::Value> Image_v8::DrawBox(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::drawBox(): NULL Holder."
		)));
	}

	Handle<Array> dimensions = args[0].As<Array>();

	image_v8->image->drawBox(
		dimensions->Get(0)->Int32Value(),
		dimensions->Get(1)->Int32Value(),
		dimensions->Get(2)->Int32Value(),
		dimensions->Get(3)->Int32Value(),
		args[1]->Uint32Value(),
		args[2]->Uint32Value(),
		args[3]->Uint32Value(),
		args[4]->Uint32Value(),
		static_cast<Image::DrawMode>(args[5]->Uint32Value())
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::DrawCircle(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::drawCircle(): NULL Holder."
		)));
	}

	Handle<Array> position = args[0].As<Array>();

	image_v8->image->drawCircle(
		position->Get(0)->Int32Value(),
		position->Get(1)->Int32Value(),
		args[1]->Uint32Value(),
		args[2]->Uint32Value(),
		args[3]->Uint32Value(),
		args[4]->Uint32Value(),
		args[5]->Uint32Value(),
		static_cast<Image::DrawMode>(args[6]->Uint32Value())
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::DrawRect(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::drawRect(): NULL Holder."
		)));
	}

	Handle<Array> dimensions = args[0].As<Array>();

	image_v8->image->drawRect(
		dimensions->Get(0)->Int32Value(),
		dimensions->Get(1)->Int32Value(),
		dimensions->Get(2)->Int32Value(),
		dimensions->Get(3)->Int32Value(),
		args[1]->Uint32Value(),
		args[2]->Uint32Value(),
		args[3]->Uint32Value(),
		args[4]->Uint32Value(),
		static_cast<Image::DrawMode>(args[5]->Uint32Value())
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::DrawLine(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::drawLine(): NULL Holder."
		)));
	}

	Handle<Array> dimensions = args[0].As<Array>();

	image_v8->image->drawLine(
		dimensions->Get(0)->Int32Value(),
		dimensions->Get(1)->Int32Value(),
		dimensions->Get(2)->Int32Value(),
		dimensions->Get(3)->Int32Value(),
		args[1]->Uint32Value(),
		args[2]->Uint32Value(),
		args[3]->Uint32Value(),
		args[4]->Uint32Value(),
		static_cast<Image::DrawMode>(args[5]->Uint32Value())
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::Fill(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::fill(): NULL Holder."
		)));
	}

	image_v8->image->fill(
		args[0]->Uint32Value(),
		args[1]->Uint32Value(),
		args[2]->Uint32Value(),
		args[3]->Uint32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::Floodfill(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::floodfill(): NULL Holder."
		)));
	}

	Handle<Array> position = args[0].As<Array>();

	image_v8->image->floodfill(
		position->Get(0)->Int32Value(),
		position->Get(1)->Int32Value(),
		args[1]->Uint32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::Height(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::height(): NULL Holder."
		)));
	}

	return scope.Close(
		Integer::New(image_v8->image->height())
	);
}

v8::Handle<v8::Value> Image_v8::PixelAt(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::pixelAt(): NULL Holder."
		)));
	}

	return scope.Close(Integer::New(
		image_v8->image->pixelAt(
			args[0]->Uint32Value(),
			args[1]->Uint32Value()
		)
	));
}

v8::Handle<v8::Value> Image_v8::Render(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::render(): NULL Holder."
		)));
	}

	Handle<Array> dimensions = args[4].As<Array>();
	Handle<Array> position = args[0].As<Array>();

	Image_v8 *destination = ObjectWrap::Unwrap<Image_v8>(args[1]->ToObject());

	if (NULL == destination) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::render(): NULL destination."
		)));
	}

	image_v8->image->render(
		position->Get(0)->Int32Value(),
		position->Get(1)->Int32Value(),
		*destination->image,
		args[2]->Int32Value(),
		static_cast<Image::DrawMode>(args[3]->Int32Value()),
		dimensions->Get(0)->Int32Value(),
		dimensions->Get(1)->Int32Value(),
		dimensions->Get(2)->Int32Value(),
		dimensions->Get(3)->Int32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::RenderGrayscale(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::renderGrayscale(): NULL Holder."
		)));
	}

	image_v8->image->renderGrayscale(
		*ObjectWrap::Unwrap<Image_v8>(args[0]->ToObject())->image,
		args[1]->NumberValue(),
		args[2]->NumberValue()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::SetPixelAt(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::setPixelAt(): NULL Holder."
		)));
	}

	image_v8->image->setPixelAt(
		args[0]->Uint32Value(),
		args[1]->Uint32Value(),
		args[2]->Uint32Value()
	);

	return v8::Undefined();
}

v8::Handle<v8::Value> Image_v8::Uri(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::uri(): NULL Holder."
		)));
	}

	return scope.Close(v8::String::New(
		chi::System::unqualifiedResourceName(image_v8->image->uri()).c_str()
	));
}

v8::Handle<v8::Value> Image_v8::Width(const Arguments &args) {
	HandleScope scope;

	Image_v8 *image_v8 = ObjectWrap::Unwrap<Image_v8>(args.Holder());

	if (NULL == image_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"Image::width(): NULL Holder."
		)));
	}

	return scope.Close(Integer::New(image_v8->image->width()));
}

Persistent<FunctionTemplate> Image_v8::constructor_template;

}

