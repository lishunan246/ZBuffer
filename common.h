#pragma once

#include <vector>
#include "Config.h"

/**
 * \brief �����
 */
struct Polygon
{
	/**
	* \brief ���������ƽ��ķ���ϵ�� ax+by+cz+d=0;
	*/
	double a, b, c, d;
	/**
	 * \brief ����εı��
	 */
	int id;
	/**
	 * \brief ����ο�Խ��ɨ������Ŀ
	 */
	int dy;
	/**
	 * \brief ����ε���ɫ
	 */
	QColor color;
};

struct Edge
{
	/**
	 * \brief �ߵ��϶����x����
	 */
	double x;

	/**
	 * \brief ��������ɨ���߽����x�����
	 */
	double dx;
	/**
	 * \brief �߿�Խ��ɨ������Ŀ
	 */
	int dy;
	/**
	 * \brief ����������εı��
	 */
	int id;

	bool used;
};

/**
 * \brief �����
 */
struct ActiveEdgePair
{
	/**
	 * \brief �󽻵��x����
	 */
	double xl;
	/**
	 * \brief (�󽻵����)������ɨ���߽����x����֮��
	 */
	double dxl;
	/**
	 * \brief �Ժ���߽������ڱ��ཻ��ɨ����Ϊ��ֵ,�Ժ�ÿ����һ��ɨ���߼�1
	 */
	int dyl;
	/**
	 * \brief �ҽ����x����
	 */
	double xr;
	/**
	 * \brief (�ҽ������)������ɨ���߽����x����֮��
	 */
	double dxr;
	/**
	 * \brief �Ժ��ұ߽������ڱ��ཻ��ɨ����Ϊ��ֵ,�Ժ�ÿ����һ��ɨ���߼�1
	 */
	int dyr;
	/**
	 * \brief �󽻵㴦���������ƽ������ֵ
	 */
	double zl;
	/**
	 * \brief ��ɨ���������߹�һ������ʱ,���������ƽ����������. ����ƽ�淽��.dzx=-a/c (c!=0);
	 */
	double dzx;
	/**
	 * \brief ��y���������ƹ�һ��ɨ����ʱ�����������ƽ������������
	 * ����ƽ�淽�̣� dzy=b/c (c!=0)
	 */
	double dzy;
	/**
	 * \brief ��������ڶ���εı�� 
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
