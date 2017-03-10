#pragma once
#include "triple.h"

typedef struct nodeClassifiedPolygon {
	double a, b, c, d;//多边形系数
	int id;//多边形编号
	int dy;//跨越的扫描线数目
	Triple<unsigned char> color;//多边形颜色
	nodeClassifiedPolygon* next;//同一扫描线上的下一个多边形
}nodeClassifiedPolygon;
