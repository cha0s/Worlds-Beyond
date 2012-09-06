#ifndef WB_SDLIMAGE_H
#define WB_SDLIMAGE_H

#include "wb-global.h"

#include "SDL/SDL.h"

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
 * @ingroup SDL
 */
class SdlImage : public Image {

public:

	/** Screen needs access so it can do things like use an Image as
	 *  a screen surface. */
	friend class Screen;

	/**
	 * Image constructor.
	 */
	SdlImage();

	/**
	 * Image copy constructor. Shallow copies the resource.
	 */
	SdlImage(const Image &image);

	/**
	 * Image copy constructor. Shallow copies the resource.
	 */
	SdlImage(const SdlImage &image);

	Image &operator =(const Image &image);
	SdlImage *clone() const;
	SdlImage &copyFrom(const SdlImage &image, bool deepCopy = false);

	/**
	 * Image constructor. @todo Document better.
	 *
	 * @param uri
	 *   Resource location.
	 */
	SdlImage(const std::string &uri);

	/**
	 * Image constructor.
	 * @param size
	 *   A 2D vector specifying the image's dimensions.
	 */
	SdlImage(int width, int height);

	/**
	 * Image destructor.
	 */
	~SdlImage();

	/** Equivalence operator. If the two images have the same data,
	 *  the operator will return true. */
	bool operator ==(const Image &image) const;

	/**
	 * URI of the current image resource.
	 */
	const std::string &uri() const { return m_uri; }

	/**
	 * Get the pixel color at a given x, y coordinate.
	 */
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
	void render(int x, int y, Image &destination, int alpha = 255, DrawMode mode = DrawMode_Blend, int sx = 0, int sy = 0, int sw = 0, int sh = 0) const;

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

	void setInternalImage(void *image) { surface = static_cast<SDL_Surface *>(image); }
	void *internalImage() { return static_cast<void *>(surface); }

	static Factory<SdlImage> *factory;

private:

	SDL_Surface *surface;

};

/**
 * @ingroup Resources
 * @ingroup SDL
 */
template <>
class Factory<SdlImage> : public Factory<Image> {

	SdlImage *create(const std::string &uri) { return new SdlImage(uri); }
	SdlImage *create(int width, int height) { return new SdlImage(width, height); }
	SdlImage *create() { return new SdlImage(); }

};

/**
 * @}
 */

}

#endif // WB_SDLIMAGE_H
