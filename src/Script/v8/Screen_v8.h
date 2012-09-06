#ifndef WB_SCREEN_V8_H
#define WB_SCREEN_V8_H

#include "wb-global.h"

#include "wbv8.h"
#include "ObjectWrap.h"
#include "../../Graphics/Screen.h"

namespace chi {

class Screen_v8 : public ObjectWrap {

public:

	~Screen_v8();

	static void Register(v8::Handle<v8::Object> target);

	Screen *screen;

private:

	Screen_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Render(const v8::Arguments &args);
	static v8::Handle<v8::Value> Set(const v8::Arguments &args);
	static v8::Handle<v8::Value> SetMouseVisibility(const v8::Arguments &args);
	static v8::Handle<v8::Value> SetWindowTitle(const v8::Arguments &args);
	static v8::Handle<v8::Value> Size(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;
};

}

#endif // WB_SCREEN_V8_H
