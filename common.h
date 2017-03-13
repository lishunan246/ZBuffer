#pragma once

#include <vector>
#include <QColor>
#include <QObject>


struct Polygon
{
	double a, b, c, d;//�����ϵ��
	int id;//����α��
	int dy;//��Խ��ɨ������Ŀ
	QColor color;//�������ɫ
};

struct Edge
{
	double x;//���϶˵��x����

	double dx;//ɨ���������ƶ�һ��ʱx������
	int dy;//�߿�Խ��ɨ������Ŀ
	int id;//�����������εı��
	bool used;//�ñ��Ƿ��Ѿ������
};

struct ActiveEdgePair
{
	/**
	 * \brief ��ǰɨ���߱߶Ե����ٽ��
	 */
	double xl;
	/**
	 * \brief 
	 */
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
