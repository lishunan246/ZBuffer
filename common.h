#pragma once

#include <vector>
#include "Config.h"

/**
 * \brief 多边形
 */
struct Polygon
{
	/**
	* \brief 多边形所在平面的方程系数 ax+by+cz+d=0;
	*/
	double a, b, c, d;
	/**
	 * \brief 多边形的编号
	 */
	int id;
	/**
	 * \brief 多变形跨越的扫描线数目
	 */
	int dy;
	/**
	 * \brief 多边形的颜色
	 */
	QColor color;
};

struct Edge
{
	/**
	 * \brief 边的上顶点的x坐标
	 */
	double x;

	/**
	 * \brief 相邻两条扫描线交点的x坐标差
	 */
	double dx;
	/**
	 * \brief 边跨越的扫描线数目
	 */
	int dy;
	/**
	 * \brief 边所属多边形的编号
	 */
	int id;

	bool used;
};

/**
 * \brief 交点对
 */
struct ActiveEdgePair
{
	/**
	 * \brief 左交点的x坐标
	 */
	double xl;
	/**
	 * \brief (左交点边上)两相邻扫描线交点的x坐标之差
	 */
	double dxl;
	/**
	 * \brief 以和左边交点所在边相交的扫描线为初值,以后每处理一条扫描线减1
	 */
	int dyl;
	/**
	 * \brief 右交点的x坐标
	 */
	double xr;
	/**
	 * \brief (右交点边上)两相邻扫描线交点的x坐标之差
	 */
	double dxr;
	/**
	 * \brief 以和右边交点所在边相交的扫描线为初值,以后每处理一条扫描线减1
	 */
	int dyr;
	/**
	 * \brief 左交点处多边形所在平面的深度值
	 */
	double zl;
	/**
	 * \brief 沿扫描线向右走过一个像素时,多边形所在平面的深度增量. 对于平面方程.dzx=-a/c (c!=0);
	 */
	double dzx;
	/**
	 * \brief 沿y方向向下移过一根扫描线时，多边形所在平面的深度增量。
	 * 对于平面方程， dzy=b/c (c!=0)
	 */
	double dzy;
	/**
	 * \brief 交点对所在多边形的编号 
	 */
	int id;
	QColor color;
};

struct Point
{
	int x, y;
	double z;
};

Point roundVertex(const std::vector<double>& v);

QColor getPolygonColor(const std::vector<double>& coffs);
