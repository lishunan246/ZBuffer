#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

class Obj
{
public:
	using Face = std::vector<std::vector<double>>;
	using Faces = std::vector<Face>;

	void readFromFile(const QString& path);
	void translate(double x, double y, double z);
	void scale(double x, double y, double z);
	void rotateY(double theta);
	Faces& getFaces();
private:
	std::vector<matrix<double>> vertices;
	std::vector<std::vector<int>> indices_of_faces;
	Faces vertices_of_faces;
};
