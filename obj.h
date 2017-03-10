#pragma once
#include <vector>
#include <QString>
#include <triple.h>

class obj
{
public:
	std::vector<Triple<double>> vVertex;
	double m_offsetX, m_offsetY, m_offset;
	double m_scaleFactor;
	std::vector<std::vector<Triple<double>>> vfs;
	std::vector<std::vector<int>> ifaces;
	QString objpath;
	int nVertex;
	int nFace;
	int m_winWidth=1600, m_winHeight=900;

	void readFromFile(QString path);
	void translate(double x, double y, double z);
};
