#pragma once
#include "triple.h"

typedef struct nodeClassifiedPolygon {
	double a, b, c, d;//�����ϵ��
	int id;//����α��
	int dy;//��Խ��ɨ������Ŀ
	Triple<unsigned char> color;//�������ɫ
	nodeClassifiedPolygon* next;//ͬһɨ�����ϵ���һ�������
}nodeClassifiedPolygon;
