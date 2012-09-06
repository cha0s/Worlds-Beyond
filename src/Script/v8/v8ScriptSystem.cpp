#include "wb-global.h"

#include "../Script.h"

#include "Image_v8.h"
#include "Screen_v8.h"
#include "Input_v8.h"
#include "Music_v8.h"
#include "Sample_v8.h"
#include "Counter_v8.h"

#include "System_v8.h"
#include "GraphicsSystem_v8.h"
#include "InputSystem_v8.h"
#include "SoundSystem_v8.h"
#include "TimingSystem_v8.h"

#include "v8Script.h"
#include "v8ScriptSystem.h"

using namespace v8;
using namespace std;

namespace chi {

Factory<v8ScriptSystem> *v8ScriptSystem::factory = new Factory<v8ScriptSystem>;

v8ScriptSystem::v8ScriptSystem()
	: ScriptSystem()
{

	Script::factory = v8Script::factory;

	HandleScope scope;

	Handle<ObjectTemplate> global = ObjectTemplate::New();

	chi::V8::Register(global);

	context = Context::New(NULL, global);

	context->Enter();
}

void v8ScriptSystem::bind() {
	HandleScope scope;

	Counter_v8::Register(context->Global());
	Input_v8::Register(context->Global());
	Image_v8::Register(context->Global());
	Music_v8::Register(context->Global());
	Sample_v8::Register(context->Global());
	Screen_v8::Register(context->Global());

	System_v8::Register(context->Global());
	GraphicsSystem_v8::Register(context->Global());
	InputSystem_v8::Register(context->Global());
	SoundSystem_v8::Register(context->Global());
	TimingSystem_v8::Register(context->Global());

	ScriptSystem::bind();
}

v8ScriptSystem::~v8ScriptSystem() {
	context->Exit();

	context.Dispose();
}

}
