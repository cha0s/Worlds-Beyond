#ifndef CHI_SOUNDSYSTEM_V8_H
#define CHI_SOUNDSYSTEM_V8_H

#include "chi-global.h"

#include "chiv8.h"
#include "ObjectWrap.h"
#include "../../Sound/SoundSystem.h"

namespace chi {

class SoundSystem_v8 : public ObjectWrap {

public:

	~SoundSystem_v8();

	static void Register(v8::Handle<v8::Object> target);

	SoundSystem *soundSystem;

private:

	SoundSystem_v8(v8::Handle<v8::Object> wrapper);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> Close(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;
};

}

#endif // CHI_SOUNDSYSTEM_V8_H
