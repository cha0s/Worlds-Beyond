#ifndef WB_GRAPHICSSYSTEM_H
#define WB_GRAPHICSSYSTEM_H

#include "wb-global.h"

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

#endif // WB_GRAPHICSSYSTEM_H
