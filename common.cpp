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
	//����ƽ�淨������z�ᣨ���������򣩵ļн�
	//�н���С������ɫ��������
	if (t[0] < 0) t[0] = 0 - t[0];
	if (t[1] < 0) t[1] = 0 - t[1];
	if (t[2] < 0) t[2] = 0 - t[2];
	double costheta = t[2] / sqrt(t[0] + t[1] + t[2]);
	return QColor(255 * costheta, 255 * costheta, 255 * costheta);
}
