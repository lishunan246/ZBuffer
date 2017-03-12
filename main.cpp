#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <ObjLoader.h>
#include "common.h"

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	auto image_provider = new ImageProvider; //will be deleted by engine
	ObjLoader obj_loader(image_provider);
	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("obj_loader", &obj_loader);
	engine.rootContext()->setContextProperty("config", &Config::getInstance());
	engine.addImageProvider("ip", image_provider);
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}
