#include "common.h"

Point roundVertex(Triple<double> v)
{//���㸡�㶥��v�����������p
	Point p;
	p.x = v.x + ((v.x < 0) ? -0.5 : 0.5);
	p.y = v.y + ((v.y < 0) ? -0.5 : 0.5);
	p.z = v.z;
	return p;
}

QColor getPolygonColor(std::vector<double> coffs)
{
	//����ƽ�淨������z�ᣨ���������򣩵ļн�
	//�н���С������ɫ��������
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
