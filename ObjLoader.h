#pragma once
#include <QObject>
#include <QUrl>
#include <QDebug>
#include "ImageProvider.h"

class objLoader :
	public QObject
{
	Q_OBJECT
public:
	objLoader(ImageProvider* image_provider);
	virtual ~objLoader();

	Q_INVOKABLE void loadObj(QUrl url);
	
private:
	ImageProvider* image_provider;
};

