#include <algorithm>
#include <QTime>

#include "ObjLoader.h"
#include "common.h"
#include <unordered_map>


ObjLoader::ObjLoader(ImageProvider* image_provider)
{
	ObjLoader::image_provider = image_provider;
	zbuffer.resize(Config::getInstance().width);
}


ObjLoader::~ObjLoader()
{
}

void ObjLoader::refresh()
{
	image_provider->reset();
	QTime timer;
	timer.start();
	auto&& vface = o.getFaces();
	tableInit(vface);
	scan();
	auto ms = timer.elapsed();
	Config::getInstance().setTime(ms);
}

void ObjLoader::loadObj(QUrl url)
{
	Config::getInstance().setUrl(url.toLocalFile());

	o.readFromFile(Config::getInstance().url());
	auto s = Config::getInstance().height / (2 * (o.y_max - o.y_min));
	o.scale(s, s, s);
	auto x = 1.0 * Config::getInstance().width / 2 - 1.0 * (o.x_max + o.x_min) / 2;
	auto y = 1.0 * Config::getInstance().height / 2 - 1.0 * (o.y_max + o.y_min) / 2;
	auto z = 1.0*(o.z_max + o.z_min) / 2;
	o.translate(x, y, -z+1000);

	refresh();
}

void ObjLoader::moveUp()
{
	o.translate(0, 10, 0);
	refresh();
}

void ObjLoader::moveLeft()
{
	o.translate(-10, 0, 0);
	refresh();
}

void ObjLoader::rotateUp()
{
	auto x = 1.0*(o.x_max + o.x_min) / 2;
	auto y = 1.0*(o.y_max + o.y_min) / 2;
	auto z = 1.0*(o.z_max + o.z_min) / 2;
	o.translate(-x, -y, -z);
	o.rotateX(0.1);
	o.translate(x, y, z);
	refresh();
}

void ObjLoader::rotateDown()
{
	auto x = 1.0*(o.x_max + o.x_min) / 2;
	auto y = 1.0*(o.y_max + o.y_min) / 2;
	auto z = 1.0*(o.z_max + o.z_min) / 2;
	o.translate(-x, -y, -z);
	o.rotateX(-0.1);
	o.translate(x, y, z);
	refresh();
}

void ObjLoader::rotateLeft()
{
	auto x = 1.0*(o.x_max + o.x_min) / 2;
	auto y = 1.0*(o.y_max + o.y_min) / 2;
	auto z = 1.0*(o.z_max + o.z_min) / 2;
	o.translate(-x, -y, -z);
	o.rotateY(0.1);
	o.translate(x, y, z);
	refresh();
}

void ObjLoader::rotateRight()
{
	auto x = 1.0*(o.x_max + o.x_min) / 2;
	auto y = 1.0*(o.y_max + o.y_min) / 2;
	auto z = 1.0*(o.z_max + o.z_min) / 2;
	o.translate(-x, -y, -z);
	o.rotateY(-0.1);
	o.translate(x, y, z);
	refresh();
}

void ObjLoader::moveDown()
{
	o.translate(0, -10, 0);
	refresh();
}

void ObjLoader::moveRight()
{
	o.translate(10, 0, 0);
	refresh();
}

void ObjLoader::tableInit(const Obj::Faces& vfaces)
{
	int id = 0;
	edgeTable.assign(Config::getInstance().height, std::list<Edge>());
	polygonTable.assign(Config::getInstance().height, std::list<Polygon>());
	for (auto&& face:vfaces)
	{
		++id;
		auto&& coffs = solveFaceCoffs(face);

		if (std::abs(coffs[2]) < 1e-8)
			continue;

		auto y_max = -1;
		auto y_min = Config::getInstance().height+1;
		std::unordered_multimap<int,Edge> edges;
		for (int i = 0; i < face.size(); ++i)
		{
			Point a(face[i]);
			Point b(face[(i + 1) % face.size()]);
			if (a.y < b.y)
				std::swap(a, b);

			if (a.y < 0||a.y>edgeTable.size())
				continue;

			if (a.y == b.y)
				continue;

			Edge ce;
			ce.x = a.x;
			ce.dx = (b.x - a.x + 0.0) / (a.y - b.y);
			ce.dy = a.y - b.y + 1;
			ce.id = id;
			ce.used = false;

			edges.insert({ a.y,std::move(ce) });

			y_max = std::max(y_max, a.y);
			y_min = std::min(y_min, b.y);
		}
		Polygon cp;

		cp.a = coffs[0];
		cp.b = coffs[1];
		cp.c = coffs[2];
		cp.d = coffs[3];
		cp.dy = y_max - y_min + 1;
		cp.id = id;
		cp.color = getPolygonColor(coffs);
		if (y_max >= polygonTable.size())
			continue;

		for(auto&& p:edges)
		{
			edgeTable[p.first].push_back(p.second);
		}
		polygonTable[y_max].push_back(std::move(cp));
	}
}

std::vector<double> ObjLoader::solveFaceCoffs(const Obj::Face& f) const
{
	std::vector<vector<double>> vv;
	for (auto&& p:f)
	{
		vector<double> v(p.size());
		for (int i = 0; i < p.size(); ++i)
		{
			v(i) = p[i];
		}
		vv.push_back(v);
	}
	std::vector<double> coffs(4);

	auto vec1 = vv[2] - vv[1];
	auto vec2 = vv[0] - vv[1];

	coffs[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	coffs[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	coffs[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

	auto coffs_abssum = abs(coffs[0]) + abs(coffs[1]) + abs(coffs[2]);

	if (coffs_abssum == 0.0)
	{
		coffs_abssum = 1.0;
	}

	coffs[0] = coffs[0] / coffs_abssum;
	coffs[1] = coffs[1] / coffs_abssum;
	coffs[2] = coffs[2] / coffs_abssum;
	coffs[3] = 0.0 - coffs[0] * f[0][0] - coffs[1] * f[0][1] - coffs[2] * f[0][2];
	return coffs;
}

void ObjLoader::scan()
{
	for (currentY = (Config::getInstance().height) - 1; currentY >= 0; --currentY)
	{
		zbuffer=std::vector<double>(Config::getInstance().width,std::numeric_limits<double>::min());
		//zbuffer.resize(Config::getInstance().width);
		activeNewPolygons();
		depthUpdate();
		activeEdgeTableUpdate();
		activePolygonTableUpdate();
	}
}

std::vector<Edge> ObjLoader::findEdge(int id, int y)
{
	std::vector<Edge> edges;

	for (auto&& edge : edgeTable[y])
	{
		if (!edge.used && edge.id == id)
		{
			edge.used = true;
			edges.push_back(edge);
		}
	}
	return edges;
}

void ObjLoader::activeNewPolygons()
{
	auto&& polygon_list = polygonTable[currentY];

	activePolygonTable.assign(polygon_list.cbegin(), polygon_list.cend());
	auto it = activePolygonTable.begin();
	while (it != activePolygonTable.end())
	{
		auto polygon = *it;
		auto&& edges = findEdge(polygon.id, currentY);

		if (edges.size() < 2)
		{
			activePolygonTable.erase(it++);
			continue;
		}
		//assert(edges.size() == 2);
		//由于舍弃了平行的边,所以不一定能找到两条边
		auto l = edges[0];
		auto r = edges[1];
		if (l.x > r.x || (l.x == r.x && l.dx > r.dx))
		{
			std::swap(l, r);
		}

		ActiveEdgePair aep;
		aep.xl = l.x;
		aep.dxl = l.dx;
		aep.dyl = l.dy;
		aep.xr = r.x;
		aep.dxr = r.dx;
		aep.dyr = r.dy;
		aep.zl = (-polygon.d - l.x * polygon.a - currentY * polygon.b) / polygon.c;
		aep.dzx = (-polygon.a) / polygon.c;
		aep.dzy = polygon.b / polygon.c;
		aep.id = polygon.id;
		aep.color = polygon.color;

		auto zx = aep.zl;
		auto x = aep.xl;
		while (x < 0)
		{
			zx += aep.dzx;
			++x;
		}
		while (x < aep.xr)
		{
			if (x < zbuffer.size() && zx > zbuffer[x])
			{
				zbuffer[x] = zx;
				setPixel(x, currentY, Config::getInstance().backgroundColor);
			}
			zx += aep.dzx;
			++x;
		}


		activeEdgePairTable.push_back(std::move(aep));
		++it;
	}
}

void ObjLoader::setPixel(int x, int y, const QColor& color) const
{
	image_provider->setPixel(x, y, color);
}

void ObjLoader::depthUpdate()
{
	for (auto&& aep:activeEdgePairTable)
	{
		auto zx = aep.zl;
		auto x = aep.xl;

		while (x < 0)
		{
			zx += aep.dzx;
			++x;
		}

		if (x < zbuffer.size() && zx > zbuffer[x])
		{
			zbuffer[x] = zx;
			setPixel(x, currentY, Config::getInstance().backgroundColor);
		}

		zx += aep.dzx;
		++x;

		while (x < zbuffer.size() && x < aep.xr)
		{
			if (zx > zbuffer[x])
			{
				zbuffer[x] = zx;
				setPixel(x, currentY, aep.color);
			}
			zx += aep.dzx;
			++x;
		}
	}
}

void ObjLoader::activeEdgeTableUpdate()
{
	auto it = activeEdgePairTable.begin();
	while (it != activeEdgePairTable.end())
	{
		it->dyl--;
		it->dyr--;
		if (it->dyl <= 0 && it->dyr <= 0)
		{
			auto&& edges = findEdge(it->id, currentY);
			if (edges.empty())
			{
				activeEdgePairTable.erase(it++);
				continue;
			}
			assert(edges.size() == 2);
			auto&& l = edges[0];
			auto&& r = edges[1];

			if (l.x > r.x || (l.x == r.x && l.dx > r.dx))
			{
				std::swap(l, r);
			}

			auto ap = std::find_if(activePolygonTable.cbegin(), activePolygonTable.cend(), [id=it->id](const Polygon& t)
			                       {
				                       return t.id == id;
			                       });

			it->xl = l.x;
			it->dxl = l.dx;
			it->dyl = l.dy;
			it->xr = r.x;
			it->dxr = r.dx;
			it->dyr = r.dy;
			it->zl = (-ap->d - l.x * ap->a - currentY * ap->b) / ap->c;
			it->dzx = (-ap->a) / ap->c;
			it->dzy = ap->b / ap->c;

			++it;
		}
		else
		{
			if (it->dyl <= 0)
			{
				auto&& edges = findEdge(it->id, currentY);
				if (edges.empty())
				{
					activeEdgePairTable.erase(it++);
					continue;
				}
				auto&& l = edges.front();
				it->xl = l.x;
				it->dxl = l.dx;
				it->dyl = l.dy;
			}
			else
			{
				it->xl += it->dxl;
				it->zl = it->zl + it->dxl * it->dzx + it->dzy;
			}
			if (it->dyr <= 0)
			{
				auto&& edges = findEdge(it->id, currentY);
				if (edges.empty())
				{
					activeEdgePairTable.erase(it++);
					continue;
				}
				auto&& l = edges.front();
				it->xr = l.x;
				it->dxr = l.dx;
				it->dyr = l.dy;
			}
			else
			{
				it->xr += it->dxr;
			}
			++it;
		}
	}
}

void ObjLoader::activePolygonTableUpdate()
{
	auto it = activePolygonTable.begin();
	while (it != activePolygonTable.end())
	{
		it->dy--;
		if (it->dy < 0)
			activePolygonTable.erase(it++);
		else
			++it;
	}
}
