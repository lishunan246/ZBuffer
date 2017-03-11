#pragma once
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QColor>
#include <vector>
#include <list>

#include "ImageProvider.h"
#include "obj.h"
#include <common.h>


class objLoader :
	public QObject
{
	Q_OBJECT
public:
	objLoader(ImageProvider* image_provider);
	virtual ~objLoader();

	Q_INVOKABLE void loadObj(QUrl url);
	void constructDS(Obj::Faces& vfaces);
	std::vector<double> solveFaceCoffs(const Obj::Face& f);

	QColor g_renderColor;
	QColor g_bgColor;
	std::vector<float> g_zbuffer;

	std::vector<std::list<nodeClassifiedEdge>> tClassifiedEdge;
	std::vector<std::list<nodeClassifiedPolygon>> tClassifiedPolygon;
	std::list<nodeActivePolygon> tActivePolygon;
	std::list<nodeActiveEdgePair> tActiveEdgePair;
	void zbuffer();
	std::vector<nodeClassifiedEdge> findEdge(int id,int y);
	void activeNewPolygon(int y);
	void setPixel(int x, int y,const QColor& color);
	void depthUpdate(int y);
	void activeEdgeTableUpdate(int y);
	void activePolygonTableUpdate();
private:
	ImageProvider* image_provider;
};

