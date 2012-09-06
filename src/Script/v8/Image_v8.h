#ifndef WB_IMAGE_V8_H
#define WB_IMAGE_V8_H

#include "wb-global.h"

#include "wbv8.h"
#include "ObjectWrap.h"
#include "../../Graphics/Image.h"

namespace chi {

class Image_v8 : public ObjectWrap {

public:

	~Image_v8();

	static void Register(v8::Handle<v8::Object> target);

	static v8::Handle<v8::Object> New(Image *image);

	Image *wrappedImage();

private:

	Image_v8(v8::Handle<v8::Object> wrapper, Image *image = NULL);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> DrawBox(const v8::Arguments &args);
	static v8::Handle<v8::Value> DrawCircle(const v8::Arguments &args);
	static v8::Handle<v8::Value> DrawLine(const v8::Arguments &args);
	static v8::Handle<v8::Value> DrawRect(const v8::Arguments &args);
	static v8::Handle<v8::Value> Fill(const v8::Arguments &args);
	static v8::Handle<v8::Value> Floodfill(const v8::Arguments &args);
	static v8::Handle<v8::Value> Height(const v8::Arguments &args);
	static v8::Handle<v8::Value> PixelAt(const v8::Arguments &args);
	static v8::Handle<v8::Value> Render(const v8::Arguments &args);
	static v8::Handle<v8::Value> RenderGrayscale(const v8::Arguments &args);
	static v8::Handle<v8::Value> SetPixelAt(const v8::Arguments &args);
	static v8::Handle<v8::Value> Width(const v8::Arguments &args);
	static v8::Handle<v8::Value> Uri(const v8::Arguments &args);
	static v8::Handle<v8::Value> Load(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;

	Image *image;
	bool owns;
};

}

#endif // WB_IMAGE_V8_H
