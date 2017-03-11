#include "common.h"

Point roundVertex(Triple<double> v)
{//计算浮点顶点v的最近邻整点p
	Point p;
	p.x = v.x + ((v.x < 0) ? -0.5 : 0.5);
	p.y = v.y + ((v.y < 0) ? -0.5 : 0.5);
	p.z = v.z;
	return p;
}

QColor getPolygonColor(std::vector<double> coffs)
{
	//根据平面法向量与z轴（不分正反向）的夹角
	//夹角由小到大，颜色由明到暗
	if (coffs[0] < 0) coffs[0] = 0 - coffs[0];
	if (coffs[1] < 0) coffs[1] = 0 - coffs[1];
	if (coffs[2] < 0) coffs[2] = 0 - coffs[2];
	double costheta = coffs[2] / sqrt(coffs[0] + coffs[1] + coffs[2]);
	return QColor(255 * costheta, 255 * costheta, 255 * costheta);
}

Config& Config::getInstance()
{
	static Config c;
	return c;
}
