#pragma once
#include <QObject>
#include <vector>
#include <list>

#include "ImageProvider.h"
#include "obj.h"
#include "common.h"


class ObjLoader :public QObject
{
	Q_OBJECT
public:
	ObjLoader(ImageProvider* image_provider);
	virtual ~ObjLoader();
	void refresh();

	Q_INVOKABLE void loadObj(QUrl url);
	Q_INVOKABLE void moveUp();
	Q_INVOKABLE void moveDown();
	Q_INVOKABLE void moveRight();
	Q_INVOKABLE void moveLeft();
	Q_INVOKABLE void rotateUp();
	Q_INVOKABLE void rotateDown();
	Q_INVOKABLE void rotateLeft();
	Q_INVOKABLE void rotateRight();
	Q_INVOKABLE void zoomIn();
	Q_INVOKABLE void zoomOut();
private:
	/**
	 * \brief ��������Ķ���α�ͱ߱�
	 * \param vfaces ����ȫ������ε�vector
	 */
	void tableInit(const Obj::Faces& vfaces);
	/**
	 * \brief ����ƽ�淽��ϵ��
	 * \param f vertices in the plane
	 * \return {a,b,c,b} in the equation of plane ax+by+cz+d=0
	 */
	std::vector<double> solveFaceCoffs(const Obj::Face& f) const;
	/**
	 * \brief ���д���ÿ��ɨ����
	 */
	void scan();
	std::vector<Edge> findEdge(int id,int y);
	/**
	 * \brief ������Ķ���α�����µĶ���κͱ�
	 */
	void activeNewPolygons();
	void setPixel(int x, int y,const QColor& color) const;
	/**
	 * \brief ����ʽ����ȸ���
	 */
	void depthUpdate();
	/**
	 * \brief �޸Ļ�߱��е�Ԫ��
	 */
	void activeEdgeTableUpdate();
	/**
	 * \brief �޸Ļ������е�Ԫ��
	 */
	void activePolygonTableUpdate();

	ImageProvider* image_provider;
	Obj o;
	int currentY=0;
	/**
	 * \brief ��ǰɨ���ߵ�z������
	 */
	std::vector<double> zbuffer;
	/**
	 * \brief ����߱�
	 * ����ymax(�ߵ��϶˵�y����)���߷�����Ӧ������
	 */
	std::vector<std::list<Edge>> edgeTable;
	/**
	 * \brief �������α�
	 * ����ymax(����ε����y����)������η�����Ӧ������
	 */
	std::vector<std::list<Polygon>> polygonTable;
	/**
	 * \brief �����α�
	 * ��¼�˵�ǰɨ������������oxyͶӰ����ͶӰ�ཻ�Ķ����
	 */
	std::list<Polygon> activePolygonTable;
	/**
	 * \brief ��߱�
	 * ���ͶӰ����α߽���ɨ�����ཻ�ı߶�
	 */
	std::list<ActiveEdgePair> activeEdgePairTable;
};

