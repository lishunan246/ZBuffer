#pragma once

#include <QQuickImageProvider>
#include <QImage>

class ImageProvider: public QQuickImageProvider
{
public:
	ImageProvider();
	QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
	void setPixel(int x, int y,const QColor& color);
private:
	QImage buffer;
};