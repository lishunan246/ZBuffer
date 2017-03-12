#pragma once
#include <QObject>
#include <vector>
#include <list>

#include "ImageProvider.h"
#include "obj.h"
#include "common.h"


class ObjLoader :public QObject
{
	Q_OBJECT
public:
	ObjLoader(ImageProvider* image_provider);
	virtual ~ObjLoader();
	void refresh();

	Q_INVOKABLE void loadObj(QUrl url);
	Q_INVOKABLE void moveUp();
	Q_INVOKABLE void moveDown();
	Q_INVOKABLE void moveRight();
	Q_INVOKABLE void moveLeft();
private:
	void constructDS(Obj::Faces& vfaces);
	std::vector<double> solveFaceCoffs(const Obj::Face& f);
	void scan();
	std::vector<Edge> findEdge(int id,int y);
	void activeNewPolygon(int y);
	void setPixel(int x, int y,const QColor& color);
	void depthUpdate(int y);
	void activeEdgeTableUpdate(int y);
	void activePolygonTableUpdate();

	ImageProvider* image_provider;
	Obj o;
	std::vector<float> zbuffer;
	std::vector<std::list<Edge>> edgeTable;
	std::vector<std::list<Polygon>> polygonTable;
	std::list<Polygon> activePolygonTable;
	std::list<ActiveEdgePair> activeEdgeTable;
};

