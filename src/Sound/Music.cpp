#include "wb-global.h"

#include "Music.h"

namespace chi {

/** Global music factory. */
ResourceManager<Music> Music::manager;
Factory<Music> *Music::factory = NULL;

Music::Music()
{
}

Music::Music(const Music &music) {
	copyFrom(music);
}

Music &Music::operator =(const Music &music) {
	return copyFrom(music);
}

Music &Music::copyFrom(const Music &music, bool deepCopy) {

	m_uri = music.m_uri;

	m_musicCounter.copyFrom(music.m_musicCounter, deepCopy);

	return *this;
}

Music::Music(const std::string &uri)
{
	WB_UNUSED(uri);
}

Music::~Music() {
}

}

