#ifndef WB_OBJECTWRAP_H
#define WB_OBJECTWRAP_H

#include "wb-global.h"

#include "../lib/v8/include/v8.h"
#include <assert.h>

namespace chi {

/**
 * Wrap an object for ease going in/out of v8. Lovingly stolen with highest
 * respect from NodeJS.
 */
class ObjectWrap {

public:

	ObjectWrap ( ) {
	}

	virtual ~ObjectWrap();

	template <class T>
	static inline T* Unwrap(v8::Handle<v8::Object> handle) {
		if (handle.IsEmpty() || 0 == handle->InternalFieldCount()) {
			return NULL;
		}
		return static_cast<T*>(handle->GetPointerFromInternalField(0));
	}

	v8::Persistent<v8::Object> handle_;

protected:

	inline void Wrap(v8::Handle<v8::Object> handle) {
		assert(handle_.IsEmpty());
		assert(handle->InternalFieldCount() > 0);
		handle_ = v8::Persistent<v8::Object>::New(handle);
		handle_->SetPointerInInternalField(0, this);
		MakeWeak();
	}


	inline void MakeWeak(void) {
		handle_.MakeWeak(this, WeakCallback);
		handle_.MarkIndependent();
	}

private:

	static void WeakCallback(v8::Persistent<v8::Value> value, void *data);
};

}

#endif // WB_OBJECTWRAP_H
