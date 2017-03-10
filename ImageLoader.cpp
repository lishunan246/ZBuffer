#include "ObjLoader.h"



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
	QImage image;
	if (!image.load(file))
		throw "load image failed";
	
	image_provider->insertImage(url.fileName(), image);

}