#ifndef WB_SAMPLE_H
#define WB_SAMPLE_H

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
 * %Sample (sound effect) class.
 */
class Sample {

public:

	enum PlaybackProperties {

		/** %Sound should loop forever. */
		LoopForever = -1

		/** Any free channel is suitable for playing. */
		, AnyChannel = -1
	};

	Sample();
	Sample(const Sample &sample);

	/**
	 * Load a sample from a resource location.
	 *
	 * @param uri
	 *   The location of the sample resource to load.
	 */
	Sample(const std::string &uri);

	virtual Sample &operator =(const Sample &sample);

	Sample &copyFrom(const Sample &sample);

	/**
	 * Release a sample resource.
	 */
	virtual ~Sample();

	const std::string &uri() const { return m_uri; }

	/**
	 * Play a sample.
	 *
	 * @param loops
	 *   Number of times to repeat.
	 * @param channel
	 *   %Sound channel to play the sample on.
	 */
	virtual int play(int loops = 0, int channel = AnyChannel) = 0;

	static ResourceManager<Sample> manager;
	static Factory<Sample> *factory;

protected:

	/** URI (for free'ing) */
	std::string m_uri;

	ResourceCounter m_sampleCounter;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<Sample> {

public:

	virtual Sample *create() = 0;
	virtual Sample *create(const std::string &uri) = 0;

};

/**
 * @}
 */

}

#endif // WB_SAMPLE_H
