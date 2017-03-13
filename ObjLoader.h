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
	Q_INVOKABLE void rotateUp();
	Q_INVOKABLE void rotateDown();
	Q_INVOKABLE void rotateLeft();
	Q_INVOKABLE void rotateRight();
	Q_INVOKABLE void zoomIn();
	Q_INVOKABLE void zoomOut();
private:
	/**
	 * \brief 建立分类的多边形表和边表
	 * \param vfaces 包含全部多边形的vector
	 */
	void tableInit(const Obj::Faces& vfaces);
	/**
	 * \brief 计算平面方程系数
	 * \param f vertices in the plane
	 * \return {a,b,c,b} in the equation of plane ax+by+cz+d=0
	 */
	std::vector<double> solveFaceCoffs(const Obj::Face& f) const;
	/**
	 * \brief 逐行处理每条扫描线
	 */
	void scan();
	std::vector<Edge> findEdge(int id,int y);
	/**
	 * \brief 检查分类的多边形表，添加新的多边形和边
	 */
	void activeNewPolygons();
	void setPixel(int x, int y,const QColor& color) const;
	/**
	 * \brief 增量式的深度更新
	 */
	void depthUpdate();
	/**
	 * \brief 修改活化边表中的元素
	 */
	void activeEdgeTableUpdate();
	/**
	 * \brief 修改活化多边形中的元素
	 */
	void activePolygonTableUpdate();

	ImageProvider* image_provider;
	Obj o;
	int currentY=0;
	/**
	 * \brief 当前扫描线的z缓冲器
	 */
	std::vector<double> zbuffer;
	/**
	 * \brief 分类边表
	 * 根据ymax(边的上端点y坐标)将边放入相应的类中
	 */
	std::vector<std::list<Edge>> edgeTable;
	/**
	 * \brief 分类多边形表
	 * 根据ymax(多边形的最大y坐标)将多边形放入相应的类中
	 */
	std::vector<std::list<Polygon>> polygonTable;
	/**
	 * \brief 活化多边形表
	 * 记录了当前扫描线与多边形在oxy投影面上投影相交的多边形
	 */
	std::list<Polygon> activePolygonTable;
	/**
	 * \brief 活化边表
	 * 存放投影多边形边界与扫描线相交的边对
	 */
	std::list<ActiveEdgePair> activeEdgePairTable;
};

