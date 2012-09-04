#ifndef CHI_GRAPHICSSYSTEM_H
#define CHI_GRAPHICSSYSTEM_H

#include "chi-global.h"

#include "Factory.h"

namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

class GraphicsSystem {

public:

	GraphicsSystem();
	virtual ~GraphicsSystem();

	virtual void close() { }

	static Factory<GraphicsSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<GraphicsSystem> {

public:

	virtual GraphicsSystem *create() = 0;

};

/**
 * @}
 */

}

#endif // CHI_GRAPHICSSYSTEM_H
