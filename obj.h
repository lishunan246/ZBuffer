#pragma once

#include <vector>
#include <QString>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

class Obj
{
public:
	using Face = std::vector<std::vector<double>>;
	using Faces = std::vector<Face>;

	std::vector<matrix<double>> vVertex;
	double m_offsetX, m_offsetY, m_offset;
	double m_scaleFactor;
	Faces vfs;
	std::vector<std::vector<int>> ifaces;
	QString objpath;
	size_t nVertex;
	size_t nFace;
	int m_winWidth=1600, m_winHeight=900;

	void readFromFile(QString path);
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateY(double theta);
	Faces& getObj();;
};
