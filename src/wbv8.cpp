#include "wb-global.h"

#include "wbv8.h"

#include "Exception.h"

#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "System/System.h"

using namespace v8;

namespace chi {

/**
 * v8 way to write to stderr.
 */
Handle<Value> log(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 1) return v8::Undefined();

	for (int i = 0; i < args.Length(); i++) {
		v8::String::Utf8Value value(V8::toJson(args[i]));

		std::cerr << *value << std::endl;
	}

	return v8::Undefined();
}

v8::Handle<v8::String> V8::toJson(v8::Handle<v8::Value> value) {
	HandleScope scope;

	Handle<Context> context = Context::GetCurrent();
	Handle<Object> global = context->Global();

	Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
	Handle<Function> JSON_stringify = Handle<Function>::Cast(JSON->Get(String::New("stringify")));

	TryCatch exception;

	Handle<Value> argv[] = {
		value,
		v8::Null(),
		v8::String::New("\t")
	};

	if (exception.HasCaught()) {
		throw chi::Exception(chi::V8::ReportException(exception));
	}

	Handle<Value> stringified = JSON_stringify->Call(JSON_stringify, 3, argv);

	if (exception.HasCaught()) {
		throw chi::Exception(chi::V8::ReportException(exception));
	}

	return scope.Close(stringified.As<String>());
}

std::string V8::toJsonString(v8::Handle<v8::Value> value) {
	return StringToStdString(toJson(value));
}

Handle<Value> resourceExists(const Arguments &args) {

	bool exists;
	if (args.Length() < 1) {

		exists = false;
	}
	else {

		exists = boost::filesystem::exists(
			System::resourceLocation() + V8::StringToStdString(args[0]->ToString())
		);
	}

	Handle<Value> callbackArgs[] = {
		Boolean::New(exists)
	};

	Handle<Function> callback = args[1].As<Function>();

	callback->Call(Context::GetCurrent()->Global(), 1, callbackArgs);

	return Undefined();
}

void V8::Register(v8::Handle<v8::ObjectTemplate> target) {

	target->Set(
		v8::String::New("log"),
		FunctionTemplate::New(log)
	);

	target->Set(
		v8::String::New("resourceExists"),
		FunctionTemplate::New(resourceExists)
	);

	target->Set(
		v8::String::New("parseJsonConfigurationFile"),
		FunctionTemplate::New(V8::parseJsonConfigurationFile)
	);
}

v8::Handle<v8::Value> V8::parseJsonConfigurationFile(const v8::Arguments &args) {
	if (args.Length() < 1) return v8::Undefined();

	HandleScope scope;

	std::string filename = System::resourceLocation() + V8::StringToStdString(
		args[0]->ToString()
	);
	if (!boost::filesystem::exists(boost::filesystem3::path(filename))) {

		return ThrowException(
			String::New(("parseJsonConfigurationFile(): " + filename + " doesn't exist!").c_str())
		);
	}

	Handle<Value> callbackArgs[] = {
		parseJson(v8::String::New(System::fileToString(filename).c_str()))
	};

	Handle<Function> callback = args[1].As<Function>();

	callback->Call(Context::GetCurrent()->Global(), 1, callbackArgs);

	return Undefined();
}

Handle<Value> V8::parseJson(Handle<String> jsonString) {
	HandleScope scope;

	Handle<Context> context = Context::GetCurrent();
	Handle<Object> global = context->Global();

	Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
	Handle<Function> JSON_parse = Handle<Function>::Cast(JSON->Get(String::New("parse")));

	// return JSON.parse.apply(JSON, jsonString);
	Handle<Value> args[] = {
		jsonString
	};
	return scope.Close(JSON_parse->Call(JSON, 1, args));
}

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

std::string V8::StringToStdString(v8::Handle<v8::String> value) {
  v8::String::Utf8Value utf8_value(value);

  return ToCString(utf8_value);
}

std::string V8::ReportException(const v8::TryCatch& try_catch, bool suppressBacktrace) {
	v8::HandleScope handle_scope;
	std::string output = "";

	std::string exception_string = V8::StringToStdString(try_catch.Exception().As<String>());
	v8::Handle<v8::Message> message = try_catch.Message();

	if (suppressBacktrace || message.IsEmpty()) {

		// V8 didn't provide any extra information about this error; just
		// print the exception.
		output += exception_string;
		output += "\n";

	} else {

		output += V8::StringToStdString(
			message->GetScriptResourceName().As<String>()
		) + ":" + boost::lexical_cast<std::string>(
			message->GetLineNumber()
		) + "\n";

		output += exception_string + "\n";

		// Print line of source code.
		output += V8::StringToStdString(message->GetSourceLine()) + "\n";

		// Print wavy underline (GetUnderline is deprecated).
		int start = message->GetStartColumn();
		for (int i = 0; i < start; i++) {
			output += " ";
		}
		int end = message->GetEndColumn();
		for (int i = start; i < end; i++) {
			output += "^";
		}
		output += "\n";

		std::string stackTrace = V8::StringToStdString(try_catch.StackTrace().As<String>());
		if (stackTrace.length() > 0) {
			output += stackTrace + "\n";
		}
	}

	return output;
}

}
