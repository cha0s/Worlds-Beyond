#include "chi-global.h"

#include "QtCounter.h"

#include "Exception.h"

const chi::QtCounter *superCast(const chi::Counter &counter) {
	const chi::QtCounter *qtCounter = dynamic_cast<const chi::QtCounter *>(&counter);

	if (!qtCounter) {
		throw chi::Exception("You can only assign a QtCounter from another QtCounter.");
	}

	return qtCounter;
}

namespace chi {

Factory<QtCounter> *QtCounter::factory = new Factory<QtCounter>();

QtCounter::QtCounter()
	: Counter()
	, time(QTime())
{

	time.start();
	m_current = time.elapsed();
}

QtCounter::QtCounter(const QtCounter &counter)
	: Counter(counter)
{
	copyFrom(counter);
}

QtCounter::QtCounter(const Counter &counter)
	: Counter(counter)
{
	copyFrom(*superCast(counter));
}

QtCounter::~QtCounter() {
}

QtCounter &QtCounter::operator =(const QtCounter &counter) {
	Counter::copyFrom(counter);

	return copyFrom(counter);
}

Counter &QtCounter::operator =(const Counter &counter) {
	Counter::copyFrom(counter);

	return *this = *superCast(counter);
}

QtCounter &QtCounter::copyFrom(const QtCounter &counter) {

	time = counter.time;

	return *this;
}

double QtCounter::current() {

	/** Get the difference between current ticks and previous. */
	return time.elapsed();
}

}
