#include "wb-global.h"

#include "QtImage.h"

static const chi::QtImage *superCast(const chi::Image &image) {
	const chi::QtImage *qtImage = dynamic_cast<const chi::QtImage *>(&image);

	if (!qtImage) {
		throw chi::Exception("You can only assign a QtImage from another QtImage.");
	}

	return qtImage;
}

namespace chi {

Factory<QtImage> *QtImage::factory = new Factory<QtImage>;

QPainter::CompositionMode QtImage::mapCompositionMode(Image::DrawMode drawMode) {

	switch (drawMode) {
	default:
	case Image::DrawMode_Blend:
		return QPainter::CompositionMode_SourceOver;

	case Image::DrawMode_Replace:
		return QPainter::CompositionMode_Source;
	}
}


QtImage::QtImage()
	: Image()
	, qImage(NULL)
{
}

QtImage::QtImage(const Image &image)
	: Image(image)
{
	copyFrom(*superCast(image));
}

QtImage::QtImage(const QtImage &image)
	: Image(image)
{
	copyFrom(image);
}

QtImage::QtImage(int width, int height)
	: Image()
{
	qImage = new QImage(width, height, QImage::Format_ARGB32);
}

QtImage::QtImage(const std::string &uri)
	: Image()
{
	qImage = new QImage(QString((m_uri = uri).c_str()));
	if (!qImage || qImage->isNull()) throw Exception(
		"Qt couldn't load the image."
	);
}

QtImage::~QtImage() {
	if (!m_imageCounter.release()) return;

	if (!qImage) return;

	// If automatic free'ing is enabled, free the surface.
	if (m_autoFree) delete qImage;
}

Image &QtImage::operator =(const Image &image) {
	Image::operator =(image);

	return copyFrom(image);
}

QtImage *QtImage::clone() const {
	return new QtImage(*this);
}

QtImage &QtImage::copyFrom(const QtImage &image, bool deepCopy) {

	if (!deepCopy) {
		qImage = image.qImage;
	}
	else {
		qImage = new QImage(image.qImage->copy());
	}

	return *this;
}

int &QtImage::pixelAt(int x, int y) const {

	return reinterpret_cast<int *>(qImage->scanLine(y))[x];
}

int QtImage::width() const {
	return qImage ? qImage->width() : 0;
}

int QtImage::height() const {
	return qImage ? qImage->height() : 0;
}

void QtImage::fill(int r, int g, int b, int a) {

	/** @todo Should we allow blending? */
	drawBox(
		0, 0, width(), height(),
		r, g, b, a,
		DrawMode_Replace
	);
}

void QtImage::drawBox(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {

	QPainter painter(qImage);

	/** Translate the rendering mode to Qt's composition mode. */
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.fillRect(QRect(x, y, w, h), QColor(r, g, b, a));
}

void QtImage::drawRect(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {
	QPainter painter(qImage);

	/** Translate the rendering mode to Qt's composition mode. */
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.setPen(QPen(QColor(r, g, b, a)));
	painter.drawRect(QRect(x, y, w, h));
}

void QtImage::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a, DrawMode drawMode) {
	QPainter painter(qImage);

	/** Translate the rendering mode to Qt's composition mode. */
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.setPen(QPen(QColor(r, g, b, a)));
	painter.drawLine(QLine(x1, y1, x2, y2));
}

void QtImage::drawCircle(int x, int y, int radius, int r, int g, int b, int a, DrawMode drawMode) {

	QPainter painter(qImage);

	/** Translate the rendering mode to Qt's composition mode. */
	painter.setCompositionMode(mapCompositionMode(drawMode));

	painter.setPen(QPen(QColor(r, g, b, a)));
	painter.drawEllipse(QRect(x, y, radius * 2, radius * 2));
}

void QtImage::resize(int width, int height) {
	m_imageCounter.copyFrom(m_imageCounter, true);

	if (!qImage || qImage->isNull()) {
		qImage = new QImage(width, height, QImage::Format_ARGB32);
		fill(0, 0, 0, 0);
	}
	else {
		*qImage = qImage->copy(0, 0, width, height);
	}
}

void QtImage::render(int x, int y, Image &destination, int alpha, DrawMode mode, int sx, int sy, int sw, int sh) const {

	QPainter painter(superCast(destination)->qImage);

	if (DrawMode_Blend == mode) painter.setOpacity((float)alpha / 255);

	/** Translate the rendering mode to Qt's composition mode. */
	painter.setCompositionMode(mapCompositionMode(mode));

	/** If src_rect doesn't have a valid width or height, set them
	 *  to this Image object's dimensions. Not sure if Qt needs this
	 *  actually... */
	if (0 == sw || 0 == sh) {
		sw = width();
		sh = height();
	}

	painter.drawImage(
		QPoint(x, y),
		*qImage,
		QRect(sx, sy, sw, sh)
	);
}

void QtImage::scaleFrom(Image &image, int width, int height) {

	if (qImage) delete qImage;

	qImage = new QImage();
	*qImage = superCast(image)->qImage->scaled(width, height);
}

bool QtImage::operator ==(const Image &image) const {
	return *qImage == *superCast(image)->qImage;
}

}

