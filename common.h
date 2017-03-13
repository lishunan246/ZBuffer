#pragma once

#include <vector>
#include <QColor>
#include <QObject>


struct Polygon
{
	double a, b, c, d;//多边形系数
	int id;//多边形编号
	int dy;//跨越的扫描线数目
	QColor color;//多边形颜色
};

struct Edge
{
	double x;//边上端点的x坐标

	double dx;//扫描线向下移动一次时x的增量
	int dy;//边跨越的扫描线数目
	int id;//边所在所变形的编号
	bool used;//该边是否已经处理过
};

struct ActiveEdgePair
{
	/**
	 * \brief 当前扫描线边对的左临界点
	 */
	double xl;
	/**
	 * \brief 
	 */
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
};

struct Point
{
	int x, y;
	double z;
};

Point roundVertex(const std::vector<double>& v);


QColor getPolygonColor(const std::vector<double>& coffs);

class Config:public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
	Q_PROPERTY(int faceCount READ faceCount WRITE setFaceCount NOTIFY faceCountChanged)
	Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
public:
	static Config& getInstance();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

	virtual ~Config();

	int width = 800;
	int height = 600;
	QColor backgroundColor = QColor(0, 0, 0);
	void setUrl(const QString& a);
	void setFaceCount(int a);
	void setTime(int a);
	QString url() const;
	int faceCount() const;
	int time() const;
	signals :
	void urlChanged();
	void faceCountChanged();
	void timeChanged();
private:
	Config() = default;
	QString m_url;
	int m_faceCount = 0;
	int m_time = 0;
};
