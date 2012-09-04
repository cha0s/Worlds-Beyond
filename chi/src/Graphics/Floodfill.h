#ifndef CHI_FLOODFILL_H
#define CHI_FLOODFILL_H

#include "chi-global.h"

#include <stack>

namespace chi {
	
/**
 * @addtogroup Math
 * @{
 */

/** Flood an abstract surface with a value of type T. */
template <class T>
class Floodfill {

private:

	/** One node of a surface to be filled. */
	struct FloodfillNode {

		/** X location. */
		int x;

		/** Y location. */
		int y;

		/** Constructor. */
		FloodfillNode(int x = 0, int y = 0)
		: x(x),
		  y(y) {

		}
	};

public:

	/** Constructor for abstract flood filler. */
	Floodfill(int width, int height, int stepX = 1, int stepY = 1)
	: m_width(width),
	  m_height(height),
	  m_valueWidth(stepX),
	  m_valueHeight(stepY) {

	}

	/**
	 * Flood fill the surface.
	 *
	 * @param x
	 *   The x coordinate to start filling from.
	 *
	 * @param y
	 *   The y coordinate to start filling from.
	 *
	 * @param fillValue
	 *   The value to fill the surface.
	 */
	void fillAt(int x, int y, T fillValue) {
		T startValue = value(x, y);

		// Early out if the starting value is the same as the fill value.
		if (startValue == fillValue) return;

		int spanLeft = 0;
		int spanRight = 0;

		int y1 = 0;

		nodeToBeVisited(x, y);
		while( visitNextNode(x, y) ) {

			y1 = y;
			while ((y1 >= 0) && (value(x, y1) == startValue)) {
				y1 -= m_valueHeight;
			}

			y1 += m_valueHeight;

			spanLeft = 0;
			spanRight = 0;

			while((y1 <= (m_height - m_valueHeight)) && (value(x, y1) == startValue)) {

				setValue(x, y1, fillValue);

				if (x > (m_valueWidth - 1)) {

					if ((0 == spanLeft) && (value(x - m_valueWidth, y1) == startValue)) {

						nodeToBeVisited(x - m_valueWidth, y1);
						spanLeft = 1;
					}
					else if ((spanLeft != 0) && !(value(x - m_valueWidth, y1) == startValue)) {

						spanLeft = 0;
					}
				}

				if (x < (m_width - m_valueWidth)) {

					if((0 == spanRight) && (value(x + m_valueWidth, y1) == startValue)) {

						nodeToBeVisited(x + m_valueWidth, y1);
						spanRight = 1;
					}
					else if ((spanRight != 0) && !(value(x + m_valueWidth, y1) == startValue)) {

						spanRight = 0;
					}
				}

				y1 += m_valueHeight;
			}
		}
	}

	/** Mark a node to be visited. */
	void nodeToBeVisited(int x, int y) {
		m_stack.push(FloodfillNode(x, y));
	}

	/** Visit the next node on the stack. */
	bool visitNextNode(int &x, int &y) {
		if (m_stack.empty()) return false;

		FloodfillNode node;
		node = m_stack.top();
		m_stack.pop();

		x = node.x; y = node.y;

		return true;
	}

protected:

	/** Get a value from x, y coordinates. */
	virtual T value(int x, int y) = 0;

	/** Set a value using x, y coordinates. */
	virtual void setValue(int x, int y, const T value) = 0;

private:

	/** The width of the surface. */
	int m_width;

	/** The height of the surface. */
	int m_height;

	/** The width of the value. */
	int m_valueWidth;

	/** The height of the value. */
	int m_valueHeight;

	/** A stack of nodes to visit. */
	std::stack<FloodfillNode> m_stack;
};

/**
 * @}
 */

}

#endif // CHI_FLOODFILL_H
