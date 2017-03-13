#include "common.h"

Point roundVertex(const std::vector<double>& v)
{//计算浮点顶点v的最近邻整点p
	Point p;
	p.x = v[0] + ((v[0] < 0) ? -0.5 : 0.5);
	p.y = v[1] + ((v[1] < 0) ? -0.5 : 0.5);
	p.z = v[2];
	return p;
}

QColor getPolygonColor(const std::vector<double>& coffs)
{
	auto t(coffs);
	//根据平面法向量与z轴（不分正反向）的夹角
	//夹角由小到大，颜色由明到暗
	if (t[0] < 0) t[0] = 0 - t[0];
	if (t[1] < 0) t[1] = 0 - t[1];
	if (t[2] < 0) t[2] = 0 - t[2];
	double costheta = t[2] / sqrt(t[0] + t[1] + t[2]);
	return QColor(255 * costheta, 255 * costheta, 255 * costheta);
}