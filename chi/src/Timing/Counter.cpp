#include "chi-global.h"

#include "Counter.h"

namespace chi {

Factory<Counter> *Counter::factory = NULL;

Counter::Counter()
	: m_current(0)
{
}

Counter::Counter (const Counter &counter)
{
	copyFrom(counter);
}

Counter &Counter::operator =(const Counter &counter) {
	return copyFrom(counter);
}

Counter &Counter::copyFrom(const Counter &counter) {
	m_current = counter.m_current;

	return *this;
}

double Counter::since() {

	/** Get the difference between current ticks and previous. */
	int now = current();
	int result = now - m_current;

	/** Update the current ticks. */
	m_current = now;

	/** Return the difference (delta). */
	return result;
}

}
