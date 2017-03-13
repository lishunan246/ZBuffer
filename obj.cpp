#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <limits>

#include "obj.h"
#include "common.h"


void Obj::readFromFile(const QString& path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	QString line = in.readLine();
	vertices.clear();
	indices_of_faces.clear();
	vertices.push_back(matrix<double>(1, 4, 0));

	x_max = y_max =z_max= std::numeric_limits<double>::min();
	x_min = y_min =z_min= std::numeric_limits<double>::max();

	while (!line.isNull())
	{
		auto string_list = line.split(" ");

		if (string_list.front() == "v")
		{
			matrix<double> vertex(1, 4, 1);
			for (int i = 1; i < 4; ++i)
			{
				auto t = string_list[i];
				vertex(0, i - 1) = t.toDouble();
			}
			x_max = std::max(x_max, vertex(0, 0));
			x_min = std::min(x_min, vertex(0, 0));
			y_max = std::max(y_max, vertex(0, 1));
			y_min = std::min(y_min, vertex(0, 1));
			z_max = std::max(z_max, vertex(0, 2));
			z_min = std::min(z_min, vertex(0, 2));

			vertices.push_back(vertex);
		}
		else if (string_list.front() == "f")
		{
			std::vector<int> ele;
			for (int i = 1; i < string_list.size(); ++i)
			{
				auto str = string_list[i];
				if (str.contains('/'))
				{
					str = str.split('/')[0];
				}
				auto index = str.toInt();
				if (index < 0)
					index = vertices.size() + index;
				ele.push_back(index);
			}
			indices_of_faces.push_back(ele);
		}
		else
		{
			//std::cout << "can not read line: " << line.toStdString() << std::endl;
		}

		line = in.readLine();
	}
	Config::getInstance().setFaceCount(indices_of_faces.size());
}

void Obj::translate(double x, double y, double z)
{
	x_max += x;
	y_max += y;
	x_min += x;
	y_min += y;
	z_max += z;
	z_min += z;
	matrix<double> translate_matrix(4, 4, 0);
	translate_matrix(0, 0) = 1;
	translate_matrix(1, 1) = 1;
	translate_matrix(2, 2) = 1;
	translate_matrix(3, 3) = 1;
	translate_matrix(3, 0) = x;
	translate_matrix(3, 1) = y;
	translate_matrix(3, 2) = z;

	for (auto&& v:vertices)
	{
		v = prod(v, translate_matrix);
	}
}

void Obj::scale(double x, double y, double z)
{
	x_max *= x;
	y_max *= y;
	x_min *= x;
	y_min *= y;
	z_max *= z;
	z_min *= z;
	matrix<double> translate_matrix(4, 4, 0);
	translate_matrix(0, 0) = x;
	translate_matrix(1, 1) = y;
	translate_matrix(2, 2) = z;
	translate_matrix(3, 3) = 1;

	for (auto&& v : vertices)
	{
		v = prod(v, translate_matrix);
	}
}

void Obj::rotateY(double theta)
{
	matrix<double> mat(4, 4, 0);
	mat(0, 0) = std::cos(theta);
	mat(0, 2) = std::sin(theta);
	mat(1, 1) = 1;
	mat(2, 0) = -std::sin(theta);
	mat(2, 2) = std::cos(theta);
	mat(3, 3) = 1;

	for (auto&& v : vertices)
	{
		v = prod(v, mat);
	}
}


Obj::Faces& Obj::getFaces()
{
	vertices_of_faces.resize(indices_of_faces.size());
	for (int i = 0; i < vertices_of_faces.size(); ++i)
	{
		for (int j = 0; j < indices_of_faces[i].size(); ++j)
		{
			Face vec;
			for (auto&& t:indices_of_faces[i])
			{

					auto v = vertices[t];
					vec.push_back({v(0, 0), v(0, 1), v(0, 2)});
				
			}
			vertices_of_faces[i] = vec;
		}
	}
	return vertices_of_faces;
}

void Obj::rotateX(double x)
{
	matrix<double> mat(4, 4, 0);
	mat(0, 0) = 1;
	mat(1, 1) = std::cos(x);
	mat(1, 2) = -std::sin(x);
	mat(2, 1) = std::sin(x);
	mat(2, 2) = std::cos(x);
	mat(3, 3) = 1;

	for (auto&& v : vertices)
	{
		v = prod(v, mat);
	}
}
