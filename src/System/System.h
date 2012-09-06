#ifndef WB_SYSTEM_H
#define WB_SYSTEM_H

#include "wb-global.h"

#include <string>
#include <vector>

#include "Factory.h"

namespace chi {

/**
 * @addtogroup System
 * @{
 */

class System {

public:

	virtual ~System() { }

	virtual void close() { }

	/**
	 * Delay execution.
	 *
	 * @param ms
	 *   The number of milliseconds to wait.
	 */
	virtual void sleep(int ms) = 0;

	static const std::string &resourceLocation() { return m_resourceLocation; }
	static void setResourceLocation(const std::string &resourceLocation);

	static std::vector<std::string> gatherFiles(const std::string &pathname, const std::string &pattern);
	static std::string fileToString(const std::string &filename);
	static void stringToFile(const std::string s, const std::string &filename);

	static std::string unqualifiedResourceName(const std::string &resourceName, const std::string &suffix = "");

	static void log(const std::string &message);

	static Factory<System> *factory;

private:

	static double m_elapsed;
	static std::string m_resourceLocation;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<System> {

public:

	virtual System *create() = 0;

};

/**
 * @}
 */

}

#endif // WB_SYSTEM_H
