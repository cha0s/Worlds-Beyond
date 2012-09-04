#ifndef CHI_SDLMUSIC_H
#define CHI_SDLMUSIC_H

#include "chi-global.h"

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "../Music.h"

namespace chi {

/**
 * @addtogroup Sounds
 * @{
 */

class SdlMusic;

/**
 * @ingroup Resources
 */
template<>
class ResourceManager<SdlMusic> : public ResourceManager<Music> {

public:



};

/**
 * @ingroup @SDL
 */
class SdlMusic : public Music {

public:

	/**
	 * Create an empty music resource.
	 */
	SdlMusic();

	SdlMusic(const Music &music);
	SdlMusic(const SdlMusic &music);
	Music &operator =(const Music &music);
	SdlMusic *clone() const;
	SdlMusic &copyFrom(const SdlMusic &music, bool deepCopy = false);

	/**
	 * Load music from a resource location.
	 *
	 * @param uri
	 *   The location of the music resource to load.
	 */
	SdlMusic(const std::string &uri);

	/**
	 * Release a music resource.
	 */
	~SdlMusic();

	/**
	 * Play music.
	 *
	 * @param loops
	 *   Number of times to loop the music.
	 */
	int play(int loops = LoopForever);

	/**
	 * Play music, fading it in.
	 *
	 * @param loops
	 *   Number of times to loop the music.
	 * @param ms
	 *   Milliseconds to fade the music in.
	 * @param position
	 *   Position to start playing the music.
	 */
	void fadeIn(int loops = LoopForever, int ms = 3000, int position = 0);

	/**
	 * Stop music playing after a fadeout.
	 *
	 * @param ms
	 *   Milliseconds to fade the music out.
	 * @param block
	 *   Non-zero value blocks until the fadeout is complete.
	 */
	void fadeOut(int ms = 3000, bool block = false);

	/**
	 * Query whether there is music currently playing.
	 */
	int isPlaying();

	/**
	 * Get the current music volume.
	 */
	int volume();

	/**
	 * Set the global music volume.
	 *
	 * @param volume
	 *   New volume level (0-128).
	 */
	void setVolume(int volume);

	/**
	 * Stop music playing.
	 */
	void stop();

	static Factory<SdlMusic> *factory;

private:

	Mix_Music *music;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<SdlMusic> : public Factory<Music> {

public:

	SdlMusic *create() { return new SdlMusic(); }
	SdlMusic *create(const std::string &uri) { return new SdlMusic(uri); }

};

/**
 * @}
 */

}

#endif // CHI_SDLMUSIC_H
