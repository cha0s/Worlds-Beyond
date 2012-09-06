#include "wb-global.h"

#include "SdlImage.h"

#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"

static const chi::SdlImage *superCast(const chi::Image &image) {
	const chi::SdlImage *sdlImage = dynamic_cast<const chi::SdlImage *>(&image);

	if (!sdlImage) {
		throw chi::Exception("You can only assign an SdlImage from another SdlImage.");
	}

	return sdlImage;
}

enum SDL_ColorMask {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	SDL_ColorMaskRed = 0xff000000,
	SDL_ColorMaskGreen = 0x00ff0000,
	SDL_ColorMaskBlue = 0x0000ff00,
	SDL_ColorMaskAlpha = 0x000000ff
#else
	SDL_ColorMaskRed = 0x000000ff,
	SDL_ColorMaskGreen = 0x0000ff00,
	SDL_ColorMaskBlue = 0x00ff0000,
	SDL_ColorMaskAlpha = 0xff000000
#endif
};

SDL_Surface *SDL_SurfaceDeepCopy(const SDL_Surface *surface) {

	return SDL_CreateRGBSurfaceFrom(
		surface->pixels,
		surface->w,
		surface->h,
		32,
		surface->pitch,
		SDL_ColorMaskBlue, SDL_ColorMaskGreen, SDL_ColorMaskRed, SDL_ColorMaskAlpha
	);
}

namespace chi {

Factory<SdlImage> *SdlImage::factory = new Factory<SdlImage>;

SdlImage::SdlImage()
	: Image()
	, surface(NULL)
{
}

SdlImage::SdlImage(const Image &image)
	: Image(image)
{
	copyFrom(*superCast(image));
}

SdlImage::SdlImage(const SdlImage &image)
	: Image(image)
{
	copyFrom(image);
}

Image &SdlImage::operator =(const Image &image) {
	Image::operator =(image);

	return copyFrom(image);
}

SdlImage *SdlImage::clone() const {
	return new SdlImage(*this);
}

SdlImage &SdlImage::copyFrom(const SdlImage &image, bool deepCopy) {

	if (!deepCopy) {
		surface = image.surface;
	}
	else {
		surface = SDL_SurfaceDeepCopy(image.surface);
	}

	return *this;
}

SdlImage::SdlImage(int width, int height)
	: Image()
{

	surface = SDL_DisplayFormatAlpha(
		SDL_CreateRGBSurface(
			SDL_SRCALPHA,
			width,
			height,
			32,
			SDL_ColorMaskRed,
			SDL_ColorMaskGreen,
			SDL_ColorMaskBlue,
			SDL_ColorMaskAlpha
		)
	);
}

SdlImage::SdlImage(const std::string &uri)
	: Image()
	, surface(NULL)
{
	// Load the filename into raw_image.
	SDL_Surface* raw_image = IMG_Load((this->m_uri = uri).c_str());

	// Optimize it before returning it.
	if (raw_image) {
		surface = SDL_DisplayFormatAlpha(raw_image);

		// And kill the original.
		SDL_FreeSurface(raw_image);
	}
	else {
		throw Exception("IMG_Load failed. SDL says, \"" + std::string(SDL_GetError()) + "\"");
	}

	if (!surface) throw Exception("SDL_DisplayFormatAlpha failed. SDL says, \"" + std::string(SDL_GetError()) + "\"");
}

SdlImage::~SdlImage() {
	if (!m_imageCounter.release()) return;

	if (!surface) return;

	// If automatic free'ing is enabled, free the surface.
	if (m_autoFree) SDL_FreeSurface(surface);
}

int &SdlImage::pixelAt(int x, int y) const {

	static int i = 0;
	if (x < 0 || y < 0 || x >= width() || y >= height()) {
		return i;
	}
	return ((int*)surface->pixels)[y * width() + x];
}

int SdlImage::width() const {
	return surface ? surface->w : 0;
}

int SdlImage::height() const {
	return surface ? surface->h : 0;
}

void SdlImage::fill(int r, int g, int b, int a) {
	SDL_Rect rect = {0, 0, width(), height()};
	SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, r, g, b, a));
}

void SdlImage::drawBox(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {
	WB_UNUSED(drawMode);

	boxRGBA(
		surface,
		x, y, x + w - 1, y + h - 1,
		r, g, b, a
	);
}

void SdlImage::drawRect(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {
	WB_UNUSED(drawMode);

	rectangleRGBA(
		surface,
		x, y, x + w - 1, y + h - 1,
		r, g, b, a
	);
}

void SdlImage::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a, DrawMode drawMode) {
	WB_UNUSED(drawMode);

	lineRGBA(
		surface,
		x1, y1, x2, y2,
		r, g, b, a
	);
}

void SdlImage::drawCircle(int x, int y, int radius, int r, int g, int b, int a, DrawMode drawMode) {
	WB_UNUSED(drawMode);

	circleRGBA(
		surface,
		x, y,
		radius,
		r, g, b, a
	);
}

void SdlImage::render(int x, int y, Image &destination, int alpha, DrawMode mode, int sx, int sy, int sw, int sh) const {

	SDL_Surface *otherSurface = superCast(destination)->surface;

	/** If src_rect doesn't have a valid width or height, set them
	 *  to this Image object's dimensions. */
	if (0 == sw || 0 == sh) {
		sw = width();
		sh = height();
	}

	// SDL's blitting sucks ass. I need to fucking learn OpenGL already! Damn
	// it!!!
	if (0 == alpha) {

		// Woohoo!
		return;
	}
	else {

		int sIdx = sy * surface->w + sx;

		if (sy < 0) {
			sh += sy;
			sIdx -= sy * surface->w;
			sy = 0;
		}
		if (sx < 0) {
			sw += sx;
			sIdx -= sx;
			sx = 0;
		}

		if (sx + sw > surface->w) {
			sw = surface->w - sx;
		}
		if (sy + sh > surface->h) {
			sh = surface->h - sy;
		}

		int dx = x;
		int dy = y;
		int dw = otherSurface->w;
		int dh = otherSurface->h;

		if (dy < 0) {
			sh += dy;
			sIdx -= dy * surface->w;
			dy = 0;
		}
		if (dx < 0) {
			sw += dx;
			sIdx -= dx;
			dx = 0;
		}

		if (dx + sw > dw) {
			sw = dw - dx;
		}
		if (dy + sh > dh) {
			sh = dh - dy;
		}

		int dIdx = dy * otherSurface->w + dx;

		// 32-bit implied; we ain't fucking around with no bullshit!
		SDL_LockSurface(surface);
		SDL_LockSurface(otherSurface);

		/** Take addresses of the first pixel of the source and destination. */
		unsigned int *src = (unsigned int *)surface->pixels, *dst = (unsigned int *)otherSurface->pixels;
		unsigned char *sc;

		src += sIdx;
		dst += dIdx;
		unsigned int colorKey = surface->format->colorkey;

		/** For each pixel from the source image, make it a
		 *  2 x 2 block in the destination. */
		for (int y = 0; y < sh; ++y) {
			for (int x = 0; x < sw; ++x) {

				if (colorKey != *src) {

					sc = reinterpret_cast<unsigned char *>(src);

					if (DrawMode_Replace == mode || (255 == alpha && 255 == sc[3])) {

						*dst = *src;
					}
					else {

						*dst = blendPixel(*src, *dst, alpha);
					}
				}

				src++;
				dst++;
			}
			dst -= sw;
			dst += otherSurface->w;
			src -= sw;
			src += surface->w;
		}

		SDL_UnlockSurface(otherSurface);
		SDL_UnlockSurface(surface);
	}
}

void SdlImage::scaleFrom(Image &image, int width, int height) {
	WB_UNUSED(width);
	WB_UNUSED(height);

	copyFrom(*superCast(image), true);
}

bool SdlImage::operator ==(const Image &image) const {
	WB_UNUSED(image);

	// TODO for realsies?
	return false;
}

}

