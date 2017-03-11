#pragma once

#include <vector>
#include <QColor>


struct nodeClassifiedPolygon
{
	double a, b, c, d;//�����ϵ��
	int id;//����α��
	int dy;//��Խ��ɨ������Ŀ
	QColor color;//�������ɫ
};

struct nodeClassifiedEdge
{
	double x;//���϶˵��x����

	double dx;//ɨ���������ƶ�һ��ʱx������
	int dy;//�߿�Խ��ɨ������Ŀ
	int id;//�����������εı��
	bool used;//�ñ��Ƿ��Ѿ������
};

using nodeActivePolygon = nodeClassifiedPolygon;

struct nodeActiveEdgePair
{
	double xl;//��ǰɨ���߱߶Ե����ٽ��
	double dxl;//����ɨ���߽���x����֮��
	int dyl;//����ı߿�Խ��ɨ������Ŀ
	double xr; //��ǰɨ���߱߶Ե����ٽ��
	double dxr;//ɨ���������ƶ�һ��ʱ�ұߵ�xr������
	int dyr;//���ҵı߿�Խ��ɨ������Ŀ
	double zl;//��ǰɨ��������ߵ����
	double dzx;//����ɨ��һ������ʱ����ȵ�����
	double dzy;//�����ƶ�ɨ����ʱ��ȵ�����
	int id;//�߶����ڶ���εı��
	QColor color;//��ɫ
};

struct Point
{
	int x, y;
	double z;
};

Point roundVertex(const std::vector<double>& v);


QColor getPolygonColor(const std::vector<double>& coffs);

class Config
{
public:
	static Config& getInstance();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;
	int width = 800;
	int height = 600;
private:
	Config() = default;
};
