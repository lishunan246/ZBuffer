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

	Faces vfs;
	std::vector<std::vector<int>> ifaces;

	void readFromFile(QString path);
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateY(double theta);
	Faces& getObj();;
};
