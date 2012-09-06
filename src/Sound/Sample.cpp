#include "wb-global.h"

#include "Sample.h"

namespace chi {

ResourceManager<Sample> Sample::manager;
Factory<Sample> *Sample::factory = NULL;

Sample::Sample()
{
}

Sample::Sample(const Sample &sample)
{
	copyFrom(sample);
}

Sample::~Sample() {
}

Sample &Sample::operator =(const Sample &sample) {
	return copyFrom(sample);
}

Sample &Sample::copyFrom(const Sample &sample) {

	m_uri = sample.m_uri;
	m_sampleCounter = sample.m_sampleCounter;

	return *this;
}

}

