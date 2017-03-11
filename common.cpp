#include "common.h"

Point roundVertex(std::vector<double> v)
{//���㸡�㶥��v�����������p
	Point p;
	p.x = v[0] + ((v[0] < 0) ? -0.5 : 0.5);
	p.y = v[1] + ((v[1] < 0) ? -0.5 : 0.5);
	p.z = v[2];
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
