#include "wb-global.h"

#include "SdlMusic.h"

namespace chi {

const chi::SdlMusic *superCast(const chi::Music &image) {
	const chi::SdlMusic *sdlMusic = dynamic_cast<const chi::SdlMusic *>(&image);

	if (!sdlMusic) {
		throw chi::Exception("You can only assign an SdlMusic from another SdlMusic.");
	}

	return sdlMusic;
}

Factory<SdlMusic> *SdlMusic::factory = new Factory<SdlMusic>;

SdlMusic::SdlMusic()
	: music(NULL)
{
}

SdlMusic::SdlMusic(const Music &music)
	: Music(music)
{
	copyFrom(*superCast(music));
}

SdlMusic::SdlMusic(const SdlMusic &music)
	: Music(music)
{
	copyFrom(music);
}

Music &SdlMusic::operator =(const Music &music) {
	Music::operator =(music);

	return copyFrom(*superCast(music));
}

SdlMusic *SdlMusic::clone() const {
	return new SdlMusic(*this);
}

SdlMusic &SdlMusic::copyFrom(const SdlMusic &music, bool deepCopy) {

	if (!deepCopy) {
		this->music = music.music;
	}
	else {
		this->music = Mix_LoadMUS(m_uri.c_str());
	}

	return *this;
}

SdlMusic::SdlMusic(const std::string &uri)
	: music(Mix_LoadMUS((m_uri = uri).c_str()))
{

	if (!music) {
		throw Exception("Mix_LoadMUS failed! SDL says, \"" + std::string(SDL_GetError()) + "\".");
	}
}

SdlMusic::~SdlMusic() {
	if (!m_musicCounter.release()) return;

	if (!music) return;

	Mix_FreeMusic(music);
}

int SdlMusic::play(int loops) {
	return Mix_PlayMusic(music, loops);
}

void SdlMusic::fadeIn(int loops, int ms, int position) {
	WB_UNUSED(position);

	Mix_FadeInMusic(music, loops, ms);
}

void SdlMusic::fadeOut(int ms, bool block) {
	WB_UNUSED(block);

	Mix_FadeOutMusic(ms);
//	while (!Mix_FadeOutMusic(ms) && block && isPlaying()) {
//		SDL_Delay(100);
//	}
}

void SdlMusic::setVolume(int volume) {
	Mix_VolumeMusic(volume);
}

int SdlMusic::volume() {
	return Mix_VolumeMusic(-1);
}

void SdlMusic::stop() {
	Mix_HaltMusic();
}

int SdlMusic::isPlaying() {
	return Mix_PlayingMusic();
}

}
