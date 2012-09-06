#ifndef WB_CHIV8_H
#define WB_CHIV8_H

#include "wb-global.h"

#include <assert.h>
#include <string>

#include "../lib/v8/include/v8.h"

namespace chi {


class V8 {

public:

	static std::string ReportException(const v8::TryCatch &try_catch, bool suppressBacktrace = false);

	static void Register(v8::Handle<v8::ObjectTemplate> target);

	static v8::Handle<v8::Value> parseJsonConfigurationFile(const v8::Arguments& args);
	static v8::Handle<v8::Value> parseJson(v8::Handle<v8::String> jsonString);
	static v8::Handle<v8::String> toJson(v8::Handle<v8::Value> value);
	static std::string toJsonString(v8::Handle<v8::Value> value);

	// Convert a JavaScript string to a std::string.  To not bother too
	// much with string encodings we just use ascii.
	static std::string StringToStdString(v8::Handle<v8::String> value);
};

#define V8_SET_METHOD(obj, name, callback)                    \
  obj->Set(v8::String::NewSymbol(name),                        \
           v8::FunctionTemplate::New(callback)->GetFunction())

#define V8_SET_PROTOTYPE_METHOD(templ, name, callback)                   \
do {                                                                      \
  v8::Local<v8::Signature> __callback##_SIG = v8::Signature::New(templ);  \
  v8::Local<v8::FunctionTemplate> __callback##_TEM =                      \
    v8::FunctionTemplate::New(callback, v8::Handle<v8::Value>(),          \
                          __callback##_SIG);                              \
  templ->PrototypeTemplate()->Set(v8::String::NewSymbol(name),            \
                                  __callback##_TEM);                      \
} while (0)

#define V8_SET_PROPERTY(obj, name, getter, setter)             \
  obj->SetAccessor(v8::String::NewSymbol(name), getter, setter)

#define V8_SET_INTERCEPTOR(obj, getter, setter)             \
  obj->SetNamedPropertyHandler(getter, setter)

}

#endif // WB_CHIV8_H
