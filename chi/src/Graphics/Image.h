#ifndef CHI_IMAGE_H
#define CHI_IMAGE_H

#include "chi-global.h"

#include "ResourceCounter.h"
#include "ResourceManager.h"

namespace chi {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Abstraction layer to be implemented by the selected graphics
 * subsystem.
 */
class Image {

public:

	/** List of drawing modes available by rendering functions. */
	enum DrawMode {

		/** Replace the destination pixels with the source pixels. */
		DrawMode_Replace = 0

		/** Blend the destination pixels into the source pixels. */
		, DrawMode_Blend = 1
	};

	/**
	 * Image constructor.
	 */
	Image();

	Image(const Image &image);
	virtual Image &operator =(const Image &image);
	virtual Image *clone() const = 0;
	Image &copyFrom(const Image &image, bool deepCopy = false);

	/**
	 * Image constructor. @todo Document better.
	 *
	 * @param uri
	 *   Resource location.
	 */
	Image(const std::string &uri);

	/**
	 * Image constructor.
	 * @param size
	 *   A 2D vector specifying the image's dimensions.
	 */
	Image(int width, int height);

	/**
	 * Image destructor.
	 */
	virtual ~Image() { }

	/** Equivalence operator. If the two images have the same data,
	 *  the operator will return true. */
	virtual bool operator ==(const Image &image) const = 0;

	/**
	 * URI of the current image resource.
	 */
	const std::string &uri() const { return m_uri; }

	/**
	 * Get the pixel color at a given x, y coordinate.
	 */
	virtual int &pixelAt(int x, int y) const = 0;

	/**
	 * Set the pixel color at a given x, y coordinate.
	 */
	void setPixelAt(int x, int y, int pixel) { pixelAt(x, y) = pixel; }

	/**
	 * Get the width of the image.
	 */
	virtual int width() const = 0;

	/**
	 * Get the height of the image.
	 */
	virtual int height() const = 0;

	/**
	 * Extremely naive, but better than nothing.
	 */
	int sizeInBytes() {
		return width() * height() * 4 + sizeof(Image);
	}

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
	virtual void fill(int r, int g, int b, int a = 255) = 0;

	virtual void drawBox(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend) = 0;
	virtual void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend) = 0;
	virtual void drawRect(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend) = 0;

	virtual void drawCircle(int x, int y, int radius, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend) = 0;

	void floodfill(int x, int y, unsigned int color);

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
	virtual void render(int x, int y, Image &destination, int alpha = 255, DrawMode mode = DrawMode_Blend, int sx = 0, int sy = 0, int sw = 0, int sh = 0) const = 0;
	void renderGrayscale(Image &destination, float amount = 1, float darken = 1) const;

	/**
	 * Scale an image to a given percent.
	 *
	 * @param image
	 *   The source image.
	 *
	 * @param percent
	 *   The percentage of the original dimensions. e.g. 100 will return
	 *   the same image, 200 twice as big, etc.
	 *
	 * @return
	 *   A new Image, scaled to the correct size.
	 */
	void scaleFrom(Image &image, int percent);

	/**
	 * Scale an image to a given set of dimensions.
	 */
	virtual void scaleFrom(Image &image, int width, int height) = 0;

	void setAutoFree(bool autoFree) { m_autoFree = autoFree; }
	bool autoFree() { return m_autoFree; }

	virtual void setInternalImage(void *image) = 0;
	virtual void *internalImage() = 0;

	static inline unsigned int blendPixel(unsigned int src, unsigned int dst, int alpha = 255) {

		unsigned char *sc = reinterpret_cast<unsigned char *>(&src);
		if (0 == sc[3]) return dst;

		unsigned char *dc = reinterpret_cast<unsigned char *>(&dst);

		int pAlpha = sc[3] * (alpha / 255.0);
		dc[0] = (sc[0] * pAlpha + dc[0] * (255 - pAlpha)) / 256;
		dc[1] = (sc[1] * pAlpha + dc[1] * (255 - pAlpha)) / 256;
		dc[2] = (sc[2] * pAlpha + dc[2] * (255 - pAlpha)) / 256;

		// ???
		dc[3] = pAlpha;

		return dst;
	}

	static ResourceManager<Image> manager;
	static Factory<Image> *factory;

protected:

	/** Release the surface [meta]data automatically. */
	bool m_autoFree;

	/** URI (for free'ing) */
	std::string m_uri;

	ResourceCounter m_imageCounter;

};

/**
 * @ingroup Resources
 */
template <>
class Factory<Image> {

public:

	virtual Image *create() = 0;
	virtual Image *create(int width, int height) = 0;
	virtual Image *create(const std::string &uri) = 0;

};

/**
 * @}
 */

}

#endif // CHI_IMAGE_H
