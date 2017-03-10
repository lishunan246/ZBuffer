#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QFileDialog>
#include <QQmlContext>
#include <QDebug>
#include <ObjLoader.h>

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	auto image_provider = new ImageProvider; //will be deleted by engine
	objLoader obj_loader(image_provider);
	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("obj_loader", &obj_loader);
	engine.addImageProvider("ip", image_provider);
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	return app.exec();
}
