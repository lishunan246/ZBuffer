#include "common.h"


Point::Point(const std::vector<double>& v)
{
	x = round(v[0]);
	y = round(v[1]);
	z = round(v[2]);
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
