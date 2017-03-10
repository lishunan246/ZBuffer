#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QString>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "obj.h"

using namespace boost::numeric::ublas;

void obj::readFromFile(QString path)
{
	QFile file(path);
	objpath = path;
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	QString line = in.readLine();

	double min_x = std::numeric_limits<double>::max();
	double min_y = min_x;
	double max_x = std::numeric_limits<double>::min();
	double max_y = std::numeric_limits<double>::min();

	vVertex.push_back(Triple<double>(0, 0, 0));
	while (!line.isNull())
	{
		//std::cout << line.toStdString() << std::endl;
		auto string_list = line.split(" ");

		if (string_list.front() == "v")
		{
			double vertex[3];
			for (int i = 1; i < 4; ++i)
			{
				auto t = string_list[i];
				vertex[i - 1] = t.toDouble();
			}
			min_x = std::min(min_x, vertex[0]);
			max_x = std::max(max_x, vertex[0]);
			min_y = std::min(min_y, vertex[1]);
			max_y = std::max(max_y, vertex[1]);

			vVertex.push_back(Triple<double>(vertex));
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

	auto spanx = max_x - min_x;
	auto spany = max_y - min_y;

	if (spanx <= 1 || spany <= 1)
		m_scaleFactor = 1000;

	else if (spanx < 5 || spany < 5)
		m_scaleFactor = 80;

	else if (spanx < 10 || spany < 10)
		m_scaleFactor = 40;

	else if (spanx < 20 || spany < 20)
		m_scaleFactor = 20;

	else if (spanx < 40 || spany < 40)
		m_scaleFactor = 10;

	else
		m_scaleFactor = 1;

	m_offsetX = (m_winWidth >> 1) - ((max_x + min_x) * m_scaleFactor / 2);//abs(min_x) + 0.5;
	m_offsetY = (m_winHeight >> 1) - ((max_y + min_y) * m_scaleFactor / 2);
	nVertex = vVertex.size() - 1;
	nFace = ifaces.size();
}

void obj::translate(double x, double y, double z)
{
	matrix<double> translate_matrix(4, 4,0);
	translate_matrix(0, 0) = x;
	translate_matrix(1, 1) = y;
	translate_matrix(2, 2) = z;
	translate_matrix(3, 3) = 1;
	std::cout << translate_matrix << std::endl;
}
