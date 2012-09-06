#include "wb-global.h"

#include "wbv8.h"
#include "Exception.h"
#include "System/System.h"
#include "v8Script.h"

using namespace v8;

namespace chi {

Factory<v8Script> *v8Script::factory = new Factory<v8Script>;

v8Script::v8Script()
	: Script()
{
}

std::string v8Script::preCompileCode(const std::string &code, const std::string &filename) {
	HandleScope scope;

	// Compile coffeescript to JS.
	if (std::string::npos != filename.find(".coffee")) {

		Handle<Object> CoffeeScript = Context::GetCurrent()->Global()->Get(String::New("CoffeeScript")).As<Object>();
		Handle<Function> compile = CoffeeScript->Get(String::New("compile")).As<Function>();

		Handle<Object> options = Object::New();

		options->Set(String::New("filename"), String::New(
			chi::System::unqualifiedResourceName(filename).c_str()
		));

		Handle<Value> args[] = {
			String::New(code.c_str()),
			options
		};

		TryCatch exception;

		Handle<Value> result = compile->Call(compile, 2, args);

		if (exception.HasCaught()) {
			throw chi::Exception(chi::V8::ReportException(exception, true));
		}

		return chi::V8::StringToStdString(result->ToString());
	}
	else {

		return code;
	}
}

Script *v8Script::compileCode(const std::string &code, const std::string &filename) {
	HandleScope scope;

	TryCatch exception;

	script = Persistent<v8::Script>::New(v8::Script::New(
		String::New(preCompileCode(code, filename).c_str()),
		String::New(System::unqualifiedResourceName(filename).c_str())
	));

	if (exception.HasCaught()) {
		throw chi::Exception(chi::V8::ReportException(exception));
	}

	return this;
}

void v8Script::run() {
	HandleScope scope;

	TryCatch exception;

	script->Run();

	if (exception.HasCaught()) {
		throw chi::Exception(chi::V8::ReportException(exception));
	}
}

v8Script::~v8Script() {
	script.Dispose();
}

}
