#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QString>

#include "obj.h"


void Obj::readFromFile(QString path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	QString line = in.readLine();

	vVertex.push_back(matrix<double>(1, 4, 0));
	while (!line.isNull())
	{
		auto string_list = line.split(" ");

		if (string_list.front() == "v")
		{
			matrix<double> vertex(1, 4, 1);
			for (int i = 1; i < 4; ++i)
			{
				auto t = string_list[i];
				vertex(0,i-1) = t.toDouble();
			}

			vVertex.push_back(vertex);
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
				ele.push_back(str.toInt());
			}
			ifaces.push_back(ele);
		}
		else
		{
			std::cout << "can not read line: " << line.toStdString() << std::endl;
		}

		line = in.readLine();
	}
}

void Obj::translate(double x, double y, double z)
{
	matrix<double> translate_matrix(4, 4,0);
	translate_matrix(0, 0) = 1;
	translate_matrix(1, 1) = 1;
	translate_matrix(2, 2) = 1;
	translate_matrix(3, 3) = 1;
	translate_matrix(3, 0) = x;
	translate_matrix(3, 1) = y;
	translate_matrix(3, 2) = z;
	
	for(auto&& v:vVertex)
	{
		v = prod(v, translate_matrix);
	}
}

void Obj::scale(double x, double y, double z)
{
	matrix<double> translate_matrix(4, 4, 0);
	translate_matrix(0, 0) = x;
	translate_matrix(1, 1) = y;
	translate_matrix(2, 2) = z;
	translate_matrix(3, 3) = 1;

	for (auto&& v : vVertex)
	{
		v = prod(v, translate_matrix);
	}
}

void Obj::rotateY(double theta)
{
	
}


Obj::Faces& Obj::getObj()
{
	vfs.resize(ifaces.size());
	for(int i=0;i<vfs.size();++i)
	{
		for(int j=0;j<ifaces[i].size();++j)
		{
			Face vec;
			for(auto&& t:ifaces[i])
			{
				auto v = vVertex[t];
				vec.push_back({ v(0, 0), v(0, 1), v(0, 2) });
			}
			vfs[i] = vec;
		}
	}
	return vfs;
}
