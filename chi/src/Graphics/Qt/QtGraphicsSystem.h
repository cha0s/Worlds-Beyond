#ifndef CHI_QTGRAPHICSSYSTEM_H
#define CHI_QTGRAPHICSSYSTEM_H

#include "chi-global.h"

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

#endif // CHI_QTGRAPHICSSYSTEM_H
