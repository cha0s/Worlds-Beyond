#include "wb-global.h"

#include "Image.h"

#include "Floodfill.h"

namespace chi {

ResourceManager<Image> Image::manager;
Factory<Image> *Image::factory = NULL;

Image::Image()
	: m_autoFree(true)
{
}

Image::Image(const Image &image)
	: m_autoFree(true)
{
	copyFrom(image);
}

Image &Image::operator =(const Image &image) {
	return copyFrom(image);
}

Image &Image::copyFrom(const Image &image, bool deepCopy) {

	m_autoFree = image.m_autoFree;
	m_uri = image.m_uri;

	m_imageCounter.copyFrom(image.m_imageCounter, deepCopy);

	return *this;
}

void Image::scaleFrom(Image &image, int percent) {

	double p = percent / 100.0;

	scaleFrom(image, width() * p, height() * p);
}

void Image::renderGrayscale(Image &destination, float amount, float darken) const {

	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {

			int c, r, g, b;
			int gc, grgb;
			c = pixelAt(x, y);

			b = c & 255;
			g = (c >> 8) & 255;
			r = (c >> 16) & 255;

			grgb = std::min(255.0, r * .3 + g * .59 + b * .11) * darken;

			b -= (b - grgb) * amount;
			g -= (g - grgb) * amount;
			r -= (r - grgb) * amount;

			gc = b;
			gc = gc | (g << 8);
			gc = gc | (r << 16);
			gc = gc | (255 << 24);

			destination.setPixelAt(x, y, gc);
		}
	}
}


class FloodfillPixel : public Floodfill<int> {

	Image &image;

public:

	/**
	 * Construct a tile flood filler.
	 */
	FloodfillPixel(Image &image)
		: Floodfill<int>(
			image.width(),
			image.height()
		)
		, image(image)
	{
	}

	/**
	 * Get a matrix for the current location in the layer.
	 */
	int value(int x, int y) {
		return image.pixelAt(x, y);
	}

	/**
	 * Set tiles in the layer based on a location and a tile value matrix.
	 */
	void setValue(int x, int y, int value) {

		unsigned int dst = image.pixelAt(x, y);

		image.setPixelAt(x, y, Image::blendPixel(value, dst));
	}
};

void Image::floodfill(int x, int y, unsigned int color) {

	unsigned int black = 0xFF000000;

	// Don't do anything if the blend will do nothing.
	if (black == Image::blendPixel(color, black)) return;

	FloodfillPixel(*this).fillAt(x, y, color);
}

}

