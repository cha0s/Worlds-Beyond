#ifndef WB_QTIMAGE_H
#define WB_QTIMAGE_H

#include "wb-global.h"

#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QSlider>

#include "../Image.h"
namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Abstraction layer to be implemented by the selected graphics
 * subsystem.
 *
 * @ingroup Qt
 */
class QtImage : public Image {

public:

	/** Screen needs access so it can do things like use an Image as
	 *  a screen surface. */
	friend class Screen;

	/**
	 * Image constructor.
	 */
	QtImage();

	/**
	 * Image copy constructor. Shallow copies the resource.
	 */
	QtImage(const Image &image);

	/**
	 * Image copy constructor. Shallow copies the resource.
	 */
	QtImage(const QtImage &image);

	/**
	 * Image constructor. @todo Document better.
	 *
	 * @param uri
	 *   Resource location.
	 */
	QtImage(const std::string &uri);

	/**
	 * Image constructor.
	 * @param size
	 *   A 2D vector specifying the image's dimensions.
	 */
	QtImage(int width, int height);

	/**
	 * Image destructor.
	 */
	~QtImage();

	/**
	 * Image assignment operator. Does a shallow copy of the rhs.
	 */
	Image &operator =(const Image &image);

	/** Equivalence operator. If the two images have the same data,
	 *  the operator will return true. */
	bool operator ==(const Image &image) const;

	QtImage *clone() const;

	/**
	 * Generic image copier. Does a deep or shallow copy and updates the
	 * reference counter.
	 *
	 * @param image
	 *   The source image.
	 *
	 * @param deepCopy
	 *   Do a deep copy?
	 *
	 * @return
	 *   A reference to the lhs.
	 */
	QtImage &copyFrom(const QtImage &image, bool deepCopy = false);

	/**
	 * URI of the current image resource.
	 */
	const std::string &uri() const { return m_uri; }

	int &pixelAt(int x, int y) const;

	/**
	 * Get the width of the image.
	 */
	int width() const;

	/**
	 * Get the height of the image.
	 */
	int height() const;

	bool isValid() const { return width() != 0 && height() != 0; }

	/**
	 * Fill an image with a specified color.
	 *
	 * @param r
	 *   Red value of the fill color.
	 *
	 * @param g
	 *   Green value of the fill color.
	 *
	 * @param b
	 *   Blue value of the fill color.
	 *
	 * @param a
	 *   Alpha value of the fill color.
	 */
	void fill(int r, int g, int b, int a = 255);

	void drawBox(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);
	void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);
	void drawRect(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void drawCircle(int x, int y, int radius, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void resize(int width, int height);

	/**
	 * Render this Image to another Image.
	 *
	 * @param location
	 *   2D vector representing the x, y coordinate location to render the
	 *   image.
	 *
	 * @param destination
	 *   The image to render to.
	 *
	 * @param src_rect (optional)
	 *   A 2x2 matrix describing the rectangle area of the source image to
	 *   render.
	 *
	 * @param mode (optional)
	 * 	 The DrawMode to use when rendering.
	 *
	 * @param alpha (optional)
	 * 	 The alpha value to use. 0(transparent)-255(opaque)
	 */
	void render(int x, int y, Image &destination, int alpha = 255, DrawMode mode = DrawMode_Blend, int sx = 0, int sy = 0, int sw = 0, int sh = 0) const WB_ENSURE_STACK_ALIGNED_FOR_SSE;

	/**
	 * Scale an image to a given set of dimensions.
	 *
	 * @param image
	 *   The source image.
	 *
	 * @param size
	 *   The vector specifying the desired size.
	 *
	 * @return
	 *   A new image, scaled to the correct size.
	 */
	void scaleFrom(Image &image, int width, int height);

	void setInternalImage(void *image) { qImage = static_cast<QImage *>(image); }
	void *internalImage() { return static_cast<void *>(qImage); }

	static Factory<QtImage> *factory;

	static QPainter::CompositionMode mapCompositionMode(Image::DrawMode drawMode);

private:

	QImage *qImage;

};

/**
 * @ingroup Resources
 * @ingroup Qt
 */
template <>
class Factory<QtImage> : public Factory<Image> {

public:

	QtImage *create(const std::string &uri) { return new QtImage(uri); }
	QtImage *create(int width, int height) { return new QtImage(width, height); }
	QtImage *create() { return new QtImage(); }

};

/**
 * @}
 */

}

#endif // WB_QTIMAGE_H
