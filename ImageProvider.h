#pragma once

#include <QQuickImageProvider>
#include <QImage>

/**
 * \brief ͼ�񻺴�
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
