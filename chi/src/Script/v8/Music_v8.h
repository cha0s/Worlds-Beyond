#ifndef CHI_MUSIC_V8_H
#define CHI_MUSIC_V8_H

#include "chi-global.h"

#include "../../Sound/Music.h"
#include "ObjectWrap.h"
#include "chiv8.h"

namespace chi {

class Music_v8 : public ObjectWrap {

public:

	~Music_v8();

	static void Register(v8::Handle<v8::Object> target);

	static v8::Handle<v8::Object> New(Music *music);

private:

	Music_v8(v8::Handle<v8::Object> wrapper, Music *music = NULL);

	static v8::Handle<v8::Value> New(const v8::Arguments &args);

	static v8::Handle<v8::Value> FadeIn(const v8::Arguments &args);
	static v8::Handle<v8::Value> FadeOut(const v8::Arguments &args);
	static v8::Handle<v8::Value> Load(const v8::Arguments &args);
	static v8::Handle<v8::Value> Play(const v8::Arguments &args);
	static v8::Handle<v8::Value> Stop(const v8::Arguments &args);

	static v8::Persistent<v8::FunctionTemplate> constructor_template;

	Music *music;
	bool owns;
};

}

#endif // CHI_MUSIC_V8_H

