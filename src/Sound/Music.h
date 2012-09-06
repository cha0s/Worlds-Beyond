#ifndef WB_MUSIC_H
#define WB_MUSIC_H

#include "wb-global.h"

#include <string>

#include "Factory.h"
#include "ResourceCounter.h"
#include "ResourceManager.h"

namespace chi {

/**
 * @addtogroup Sounds
 * @{
 */

/**
 * %Music class.
 */
class Music {

public:

	enum MusicProperties {

		/** %Sound should loop forever. */
		LoopForever = -1

		/** Any free channel is suitable for playing. */
		, AnyChannel = -1
	};

	/**
	 * Create an empty music resource.
	 */
	Music();

	Music(const Music &music);
	virtual Music &operator =(const Music &music);
	virtual Music *clone() const = 0;
	Music &copyFrom(const Music &image, bool deepCopy = false);

	/**
	 * Load music from a resource location.
	 *
	 * @param uri
	 *   The location of the music resource to load.
	 */
	Music(const std::string &uri);

	/**
	 * Release a music resource.
	 */
	virtual ~Music();

	/**
	 * Play music.
	 *
	 * @param loops
	 *   Number of times to loop the music.
	 */
	virtual int play(int loops = LoopForever) = 0;

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
	virtual void fadeIn(int loops = LoopForever, int ms = 3000, int position = 0) = 0;

	/**
	 * Stop music playing after a fadeout.
	 *
	 * @param ms
	 *   Milliseconds to fade the music out.
	 * @param block
	 *   Non-zero value blocks until the fadeout is complete.
	 */
	virtual void fadeOut(int ms = 3000, bool block = false) =0;

	/**
	 * Query whether there is music currently playing.
	 */
	virtual int isPlaying() = 0;

	/**
	 * Get the current music volume.
	 */
	virtual int volume() = 0;

	/**
	 * Set the global music volume.
	 *
	 * @param volume
	 *   New volume level (0-128).
	 */
	virtual void setVolume(int volume) = 0;

	/**
	 * Stop music playing.
	 */
	virtual  void stop() = 0;

	static ResourceManager<Music> manager;
	static Factory<Music> *factory;

protected:

	/** URI (for free'ing) */
	std::string m_uri;

	ResourceCounter m_musicCounter;
};

/**
 * @ingroup Resources
 */
template <>
class Factory<Music> {

public:

	virtual Music *create() = 0;
	virtual Music *create(const std::string &uri) = 0;

};

/**
 * @}
 */

}

#endif // WB_MUSIC_H
