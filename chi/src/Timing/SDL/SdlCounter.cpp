#include "chi-global.h"

#include "SdlCounter.h"

#include "SDL/SDL.h"

#include "Exception.h"

const chi::SdlCounter *superCast(const chi::Counter &counter) {
	const chi::SdlCounter *sdlCounter = dynamic_cast<const chi::SdlCounter *>(&counter);

	if (!sdlCounter) {
		throw chi::Exception("You can only assign an SdlCounter from another SdlCounter.");
	}

	return sdlCounter;
}

namespace chi {

Factory<SdlCounter> *SdlCounter::factory = new Factory<SdlCounter>();

SdlCounter::SdlCounter()
	: Counter()
{
	m_current = SDL_GetTicks();
}

SdlCounter::SdlCounter(const SdlCounter &counter)
	: Counter()
{
	copyFrom(counter);
}


SdlCounter::SdlCounter(const Counter &counter)
	: Counter()
{
	copyFrom(*superCast(counter));
}

SdlCounter::~SdlCounter() {

}

SdlCounter &SdlCounter::operator =(const SdlCounter &counter) {
	Counter::copyFrom(counter);

	return copyFrom(counter);
}

Counter &SdlCounter::operator =(const Counter &counter) {
	Counter::copyFrom(counter);

	return *this = *superCast(counter);
}

SdlCounter &SdlCounter::copyFrom(const SdlCounter &counter) {
	CHI_UNUSED(counter);

	return *this;
}

double SdlCounter::current() {

	/** Get the difference between current ticks and previous. */
	return SDL_GetTicks();
}

}
