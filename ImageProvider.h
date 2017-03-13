#pragma once

#include <QQuickImageProvider>
#include <QImage>

/**
 * \brief Í¼Ïñ»º´æ
 */
class ImageProvider: public QQuickImageProvider
{
public:
	ImageProvider();
	QImage requestImage(const QString&, QSize*, const QSize&) override;
	void setPixel(int x, int y, const QColor& color);
	void reset();
private:
	QImage buffer;
};
