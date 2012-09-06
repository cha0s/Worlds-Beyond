#ifndef WB_RESOURCECOUNTER_H
#define WB_RESOURCECOUNTER_H

#include "wb-global.h"

namespace chi {

/**
 * @addtogroup Resources
 * @{
 */

/**
 * Class to handle reference counting semantics for objects holding an
 * external resource.
 *
 * For objects without any deep copy option, this class is almost
 * completely automatic. Destroy your object's external resource only if
 * release() returns true.
 *
 * For objects with deep copying, the copyFrom() method must be called,
 * which will use different logic depending on which kind of copy is being
 * performed.
 */
class ResourceCounter {

	/** Reference count. */
	mutable int *m_count;

public:

	/**
	 * Create a new resource counter. Defaults to a count of 1.
	 */
	ResourceCounter() : m_count(new int(1)) { }

	/**
	 * Copy constructor. Handle reference counting.
	 */
	ResourceCounter(const ResourceCounter &counter) : m_count(new int(1)) {
		copyFrom(counter);
	}

	/**
	 * Destructor. If it's an orphan, delete the counter.
	 */
	~ResourceCounter() { if (0 == *m_count) delete m_count; }

	/**
	 * Copy constructor. Handle resource counting.
	 */
	ResourceCounter &operator =(const ResourceCounter &counter) {
		copyFrom(counter);

		return *this;
	}

	/** Remove one reference from the counter. */
	int removeReference() const { return --*m_count; }

	/** Add one reference to the counter. */
	int addReference() const { return ++*m_count; }

	/**
	 * Handle the reference counting between two resource counters.
	 */
	ResourceCounter &copyFrom(const ResourceCounter &counter, int deepCopy = false) {

		if (!deepCopy) {
			counter.addReference();

			if (1 == *m_count) delete m_count;
			m_count = counter.m_count;
		}
		else {
			removeReference();
			m_count = new int(1);
		}

		return *this;
	}

	/**
	 * Ask whether the resource can be released.
	 */
	bool release() { return 0 == removeReference(); }
};

/**
 * @}
 */

}

#endif // WB_RESOURCECOUNTER_H
