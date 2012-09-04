#ifndef CHI_RESOURCEMANAGER_H
#define CHI_RESOURCEMANAGER_H

#include "chi-global.h"

#include <cxxabi.h>
#include <map>
#include <string>

#include "Exception.h"
#include "Factory.h"
#include "System/System.h"

namespace chi {

/**
 * @addtogroup Resources
 * @{
 */

/**
 * Wrapper around each resource.
 */
template <class T>
class Resource {

public:
	T *data;
	int ref_count;
};

/**
 * Manage resources of a given type.
 */
template <class T>
class ResourceManager {

public:

	/**
	 * Shut down a ResourceManager. Destroy cached resources and
	 * metadata.
	 */
	~ResourceManager() {

		while (!resource.empty()) {
		  release(resource.begin()->first, false);
		}
	}

	/** Get the location of a resource after the base path of the content
	 *  folder is removed. */
	std::string unqualifiedResourceName(const std::string &resourceName, const std::string &suffix = "") {

		// Add any suffix.
		std::string fullLocation = System::resourceLocation() + suffix;

		/** Strip off the content folder's base path. If the file isn't within
		 *  the content folder, return a null string. */
		std::string::size_type  pos;
		if (std::string::npos != (pos = resourceName.find(fullLocation))) {
			return resourceName.substr(fullLocation.size());
		}
		else {
			return "";
		}
	}

	/**
	 * Retrieve a new resource if it hasn't already been loaded. Return
	 * a reference to the new(?) resource.
	 *
	 * @param uri
	 *   The location of the resource.
	 * @param qualify
	 *   Qualify the URI with the base path?
	 */
	T& load (const std::string &uri, bool qualify = true) {

		/** Qualify the URI with the base resource path unless explicitly
		 *  instructed not to. */
		std::string qualified = uri;
		if (qualify) qualified = System::resourceLocation() + qualified;

		/** If we don't have a record of this resource yet, try to load it. */
		if ((!contains(qualified))) {
			try {
				resource[qualified].data = T::factory->create(qualified);
			}
			catch (Exception &e) {
				int status;
				std::string name = (abi::__cxa_demangle(typeid(T).name(), 0, 0, &status));

				throw Exception(std::string(e.what()) + "(Relayed by ResourceManager<" + name + "> when trying to load " + uri + ")");
			}
		}

		resource[qualified].ref_count++;
		return *resource[qualified].data;
	}

	/**
	 * Remove a resource and its metadata.
	 *
	 * @param uri
	 *   The resource ID to remove.
	 * @param ref_check
	 *   Check reference count before releasing?
	 */
	void release(const std::string &uri, bool ref_check = true) {
		if (!contains(uri)) return;

		/** If we have a record of this resource, decrement the
		 *  references. If the references have reached 0, or
		 *  if the check has been overidden, release the resource. */
		if (--resource[uri].ref_count != 0 && ref_check) return;

		// Release the resource.
		delete resource[uri].data;
		resource.erase(uri);
	}

private:

	/** Map resource URIs to their data. */
	std::map<std::string, Resource<T> > resource;

	/**
	 * Does this manager already contain an instance of the given resource?
	 *
	 * @param uri
	 *   The location of the resource.
	 */
	bool contains(const std::string &uri) {
		return (resource.find(uri) != resource.end());
	}

};

/**
 * @}
 */

}

#endif // CHI_RESOURCEMANAGER_H
