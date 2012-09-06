#include "wb-global.h"

#include "System.h"

#include <algorithm>

#include <fstream>
#include <iostream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <io.h>
#endif

#include <stdlib.h>

#include <boost/filesystem.hpp>

#include <boost/regex.hpp>

#include "boost/filesystem/operations.hpp"


using namespace boost::filesystem;

namespace chi {

double System::m_elapsed = 0;
std::string System::m_resourceLocation = "./content";

void System::setResourceLocation(const std::string &resourceLocation) {
	std::string resourceLocationPreferred = resourceLocation;
	std::replace(resourceLocationPreferred.begin(), resourceLocationPreferred.end(), '\\', '/');

	m_resourceLocation = resourceLocationPreferred;
}


/** Get the location of a resource after the base path of the content
 *  folder is removed. */
std::string System::unqualifiedResourceName(const std::string &resourceName, const std::string &suffix) {

	std::string resourceNamePreferred = resourceName;
	std::replace(resourceNamePreferred.begin(), resourceNamePreferred.end(), '\\', '/');

	// Add any suffix.
	std::string fullLocation = System::resourceLocation() + suffix;
	std::replace(fullLocation.begin(), fullLocation.end(), '\\', '/');

	/** Strip off the content folder's base path. If the file isn't within
	 *  the content folder, return a null string. */
	std::string::size_type  pos;
	if (std::string::npos != (pos = resourceNamePreferred.find(fullLocation))) {
		return resourceNamePreferred.substr(fullLocation.size());
	}
	else {
		return "";
	}
}

Factory<System> *System::factory = NULL;

std::vector<std::string> System::gatherFiles(const std::string &pathname, const std::string &pattern) {

	std::string pathnamePreferred = pathname;
	std::replace(pathnamePreferred.begin(), pathnamePreferred.end(), '\\', '/');

	std::vector<std::string> matches;
	boost::regex reg(pattern);
	for (recursive_directory_iterator it(pathnamePreferred); it != recursive_directory_iterator(); ++it) {
		if (boost::regex_search(it->path().string(), reg)) {
			matches.push_back(it->path().string());
		}
	}

	return matches;
}

std::string System::fileToString(const std::string &filename) {

	std::string filenamePreferred = filename;
	std::replace(filenamePreferred.begin(), filenamePreferred.end(), '\\', '/');

	std::ifstream file(filenamePreferred.c_str());
	std::stringstream buffer;

	if (file) {
		buffer << file.rdbuf();

		file.close();
	}

	return buffer.str();
}

void System::stringToFile(const std::string s, const std::string &filename) {

	std::ofstream file(filename.c_str());
	std::istringstream buffer(s);

	if (file) {
		buffer >> file.rdbuf();

		file.close();
	}
}

void System::log(const std::string &message) {

	std::cerr << message;
}

}
