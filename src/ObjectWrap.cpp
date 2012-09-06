#include "wb-global.h"

#include "ObjectWrap.h"

namespace chi {

ObjectWrap::~ObjectWrap() {
	if (!handle_.IsEmpty()) {
		assert(handle_.IsNearDeath());
		handle_.ClearWeak();
		handle_->SetInternalField(0, v8::Undefined());
		handle_.Dispose();
		handle_.Clear();
	}
}

void ObjectWrap::WeakCallback(v8::Persistent<v8::Value> value, void *data) {
	ObjectWrap *obj = static_cast<ObjectWrap*>(data);
	assert(value == obj->handle_);
	assert(value.IsNearDeath());
	delete obj;
}

}
