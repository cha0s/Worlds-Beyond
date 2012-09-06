#ifndef WB_QTGRAPHICSSYSTEM_H
#define WB_QTGRAPHICSSYSTEM_H

#include "wb-global.h"

#include "../GraphicsSystem.h"

namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * @ingroup @QT
 */
class QtGraphicsSystem : public GraphicsSystem {

public:

	QtGraphicsSystem();
	~QtGraphicsSystem();

	static Factory<QtGraphicsSystem> *factory;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<QtGraphicsSystem> : public Factory<GraphicsSystem> {

public:

	QtGraphicsSystem *create() { return new QtGraphicsSystem(); }

};

/**
 * @}
 */

}

#endif // WB_QTGRAPHICSSYSTEM_H
