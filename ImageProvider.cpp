#include "ImageProvider.h"
#include "common.h"

ImageProvider::ImageProvider(): QQuickImageProvider(QQuickImageProvider::Image)
{
	buffer = QImage(Config::getInstance().width, Config::getInstance().height, QImage::Format_RGB888);
	reset();
}

QImage ImageProvider::requestImage(const QString&, class QSize*, const class QSize&)
{
	return buffer;
}

void ImageProvider::setPixel(int x, int y, const QColor& color)
{
	buffer.setPixelColor(x, Config::getInstance().height-y-1, color);
}

void ImageProvider::reset()
{
	buffer.fill(QColor(255, 255, 255));
}
