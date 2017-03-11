#pragma once

#include <vector>
#include <QColor>

struct nodeClassifiedPolygon {
	double a, b, c, d;//多边形系数
	int id;//多边形编号
	int dy;//跨越的扫描线数目
	QColor color;//多边形颜色
	nodeClassifiedPolygon* next;//同一扫描线上的下一个多边形
};

struct nodeClassifiedEdge {
	double x;//边上端点的x坐标

	double dx;//扫描线向下移动一次时x的增量
	int dy;//边跨越的扫描线数目
	int id;//边所在所变形的编号
	bool used;//该边是否已经处理过
	nodeClassifiedEdge* next;//具有相同x的下一条边
};

using nodeActivePolygon = nodeClassifiedPolygon;

struct nodeActiveEdgePair {
	double xl;//当前扫描线边对的左临界点
	double dxl;//相邻扫描线交点x坐标之差
	int dyl;//靠左的边跨越的扫描线数目
	double xr; //当前扫描线边对的右临界点
	double dxr;//扫描线向下移动一次时右边的xr的增量
	int dyr;//靠右的边跨越的扫描线数目
	double zl;//当前扫描线下左边的深度
	double dzx;//向右扫描一个像素时，深度的增量
	double dzy;//向下移动扫描线时深度的增量
	int id;//边对所在多边形的编号
	QColor color;//颜色
	nodeActiveEdgePair* next;//下一边对
};

struct Point{
	int x, y;
	double z;
} ;

Point roundVertex(std::vector<double> v);

QColor getPolygonColor(std::vector<double> coffs);

class Config
{
public:
	static Config& getInstance();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;
	int width = 600;
	int height = 800;
private:
	Config() = default;
};