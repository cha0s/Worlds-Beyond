#ifndef WB_COUNTER_V8_H
#define WB_COUNTER_V8_H

#include "wb-global.h"

#include "wbv8.h"
#include "ObjectWrap.h"
#include "../../Timing/Counter.h"

namespace chi {

class Counter_v8 : public ObjectWrap {

public:

	~Counter_v8();

	static void Register(v8::Handle<v8::Object> target);

	Counter *wrappedCounter();

private:

	Counter_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Current(const v8::Arguments &args);
	static v8::Handle<v8::Value> SecondsSince(const v8::Arguments &args);
	static v8::Handle<v8::Value> Since(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;

	Counter *counter;
};

}

#endif // WB_COUNTER_V8_H
