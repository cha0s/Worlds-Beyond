#include "wb-global.h"

#include "GraphicsSystem_v8.h"

using namespace v8;

namespace chi {

GraphicsSystem_v8::GraphicsSystem_v8(Handle<Object> wrapper)
	: graphicsSystem(GraphicsSystem::factory->create())
{
	Wrap(wrapper);
}

GraphicsSystem_v8::~GraphicsSystem_v8() {
	delete graphicsSystem;
}

void GraphicsSystem_v8::Register(Handle<Object> target) {
	HandleScope scope;

	constructor_template = Persistent<FunctionTemplate>::New(
		FunctionTemplate::New(GraphicsSystem_v8::New)
	);
	constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
	constructor_template->SetClassName(String::NewSymbol("GraphicsSystem_v8"));

	V8_SET_PROTOTYPE_METHOD(constructor_template, "%close", GraphicsSystem_v8::Close);

	target->Set(String::NewSymbol("GraphicsSystem"), constructor_template->GetFunction());
}

v8::Handle<v8::Value> GraphicsSystem_v8::New(const Arguments &args) {
	HandleScope scope;

	new GraphicsSystem_v8(args.Holder());

	return args.Holder();
}

v8::Handle<v8::Value> GraphicsSystem_v8::Close(const Arguments &args) {
	HandleScope scope;

	GraphicsSystem_v8 *graphicsSystem_v8 = ObjectWrap::Unwrap<GraphicsSystem_v8>(args.Holder());

	if (NULL == graphicsSystem_v8) {
		return ThrowException(v8::Exception::ReferenceError(String::NewSymbol(
			"GraphicsSystem::close(): NULL Holder."
		)));
	}

	graphicsSystem_v8->graphicsSystem->close();

	return v8::Undefined();
}

Persistent<FunctionTemplate> GraphicsSystem_v8::constructor_template;

}

