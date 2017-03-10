#include <QFile>
#include <ObjLoader.h>
#include <iostream>
#include "obj.h"

objLoader::objLoader(ImageProvider* image_provider)
{
	objLoader::image_provider = image_provider;
}


objLoader::~objLoader()
{
}

void objLoader::loadObj(QUrl url)
{
	auto file = url.toLocalFile();
	obj o;
	o.readFromFile(file);
	o.translate(1, 3, 2);
	//image_provider->insertImage(url.fileName(), image);

}


