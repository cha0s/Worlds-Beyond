#ifndef CHI_GRAHPICSSYSTEM_V8_H
#define CHI_GRAHPICSSYSTEM_V8_H

#include "chi-global.h"

#include "chiv8.h"
#include "ObjectWrap.h"
#include "../../Graphics/GraphicsSystem.h"

namespace chi {

class GraphicsSystem_v8 : public ObjectWrap {

public:

	~GraphicsSystem_v8();

	static void Register(v8::Handle<v8::Object> target);

	GraphicsSystem *graphicsSystem;

private:

	GraphicsSystem_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Close(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;
};

}

#endif // CHI_GRAHPICSSYSTEM_V8_H
