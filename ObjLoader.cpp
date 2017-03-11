#include <algorithm>

#include <QFile>
#include <ObjLoader.h>
#include <common.h>


objLoader::objLoader(ImageProvider* image_provider)
{
	objLoader::image_provider = image_provider;
	g_bgColor = QColor(0, 0, 0);
	g_renderColor = QColor(255, 255, 255);
	g_zbuffer.resize(Config::getInstance().width);
}


objLoader::~objLoader()
{
}

void objLoader::loadObj(QUrl url)
{
	auto file = url.toLocalFile();
	Obj o;
	o.readFromFile(file);
	o.translate(1, 3, 200);
	o.scale(10, 10, 10);
	//image_provider->insertImage(url.fileName(), image);
	auto&& vface = o.getObj();
	constructDS(vface);
	zbuffer();
}

void objLoader::constructDS(Obj::Faces& vfaces)
{
	int g_ploygon_id = 0;
	tClassifiedEdge.assign(Config::getInstance().height, std::list<nodeClassifiedEdge>());
	tClassifiedPolygon.assign(Config::getInstance().height, std::list<nodeClassifiedPolygon>());
	for (auto&& face:vfaces)
	{
		++g_ploygon_id;
		auto&& coffs = solveFaceCoffs(face);

		if (std::abs(coffs[2]) < 1e-8)
			continue;

		auto polygon_maxy = std::max(0, static_cast<int>(face[0].y));
		auto polygon_miny(polygon_maxy);

		for (int i = 0; i < face.size(); ++i)
		{
			auto a = roundVertex(face[i]);
			auto b = roundVertex(face[(i + 1) % face.size()]);
			if (a.y < b.y)
				std::swap(a, b);

			if (a.y < 0)
				continue;

			if (std::abs(a.y - b.y) < 1e-8)
				continue;

			nodeClassifiedEdge ce;
			ce.x = a.x;
			ce.dx = (b.x - a.x + 0.0) / (a.y - b.y);
			ce.dy = a.y - b.y + 1;
			ce.id = g_ploygon_id;
			ce.used = false;
			if (a.y >= tClassifiedEdge.size())
				continue;

			tClassifiedEdge[a.y].push_back(std::move(ce));

			polygon_maxy = std::max(polygon_maxy, a.y);
			polygon_miny = std::min(polygon_miny, b.y);
		}
		nodeClassifiedPolygon cp;

		cp.a = coffs[0];
		cp.b = coffs[1];
		cp.c = coffs[2];
		cp.d = coffs[3];
		cp.dy = polygon_maxy - polygon_miny + 1;
		cp.id = g_ploygon_id;
		cp.color = getPolygonColor(coffs);
		if (polygon_maxy >= tClassifiedPolygon.size())
			continue;

		tClassifiedPolygon[polygon_maxy].push_back(std::move(cp));
	}
}

std::vector<double> objLoader::solveFaceCoffs(std::vector<Triple<double>> f)
{
	std::vector<double> coffs(4);
	//solve the coefficient of the plane specified by icoords and store the answer in coffs
	Triple<double> vec1;
	vec1 = f[2] - f[1];
	Triple<double> vec2;
	vec2 = f[0] - f[1];
	//计算系数
	coffs[0] = vec1.y * vec2.z - vec1.z * vec2.y;
	coffs[1] = vec1.z * vec2.x - vec1.x * vec2.z;
	coffs[2] = vec1.x * vec2.y - vec1.y * vec2.x;
	//系数归一
	float coffs_abssum = abs(coffs[0]) + abs(coffs[1]) + abs(coffs[2]);
	//_ASSERT(coffs_abssum != 0.0);
	if (coffs_abssum == 0.0)
	{
#ifdef DEBUGGER
		cout << "normal vector is 0." << endl;
#endif
		coffs_abssum = 1.0;
	}
	coffs[0] = coffs[0] / coffs_abssum;
	coffs[1] = coffs[1] / coffs_abssum;
	coffs[2] = coffs[2] / coffs_abssum;
	//计算截距
	coffs[3] = 0.0 - coffs[0] * f[0].x - coffs[1] * f[0].y - coffs[2] * f[0].z;
	return coffs;
}

void objLoader::zbuffer()
{
	for (int y = Config::getInstance().height - 1; y >= 0; --y)
	{
		g_zbuffer.clear();
		g_zbuffer.resize(Config::getInstance().width);
		activeNewPolygon(y);
		depthUpdate(y);
		activeEdgeTableUpdate(y);
		activePolygonTableUpdate();
	}
}

std::vector<nodeClassifiedEdge> objLoader::findEdge(int id, int y)
{
	std::vector<nodeClassifiedEdge> edges;

	for (auto&& edge : tClassifiedEdge[y])
	{
		if (!edge.used && edge.id == id)
		{
			edge.used = true;
			edges.push_back(edge);
		}
	}
	return edges;
}

void objLoader::activeNewPolygon(int y)
{
	auto&& polygon_list = tClassifiedPolygon[y];

	tActivePolygon.assign(polygon_list.cbegin(), polygon_list.cend());
	auto it = tActivePolygon.begin();
	while (it!=tActivePolygon.end())
	{
		auto polygon = *it;
		auto&& edges = findEdge(polygon.id, y);

		if(edges.size()==0)
		{
			tActivePolygon.erase(it++);
			continue;
		}
		//assert(edges.size() == 2);
		auto l = edges[0];
		auto r = edges[1];
		if (l.x > r.x || (l.x == r.x && l.dx > r.dx))
		{
			std::swap(l, r);
		}

		nodeActiveEdgePair aep;
		aep.xl = l.x;
		aep.dxl = l.dx;
		aep.dyl = l.dy;
		aep.xr = r.x;
		aep.dxr = r.dx;
		aep.dyr = r.dy;
		aep.zl = (-polygon.d - l.x * polygon.a - y * polygon.b) / polygon.c;
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
			if (x < g_zbuffer.size() && zx > g_zbuffer[x])
			{
				g_zbuffer[x] = zx;
				setPixel(x, y, g_bgColor);
			}
			zx += aep.dzx;
			++x;
		}


		tActiveEdgePair.push_back(std::move(aep));
		++it;
	}
}

void objLoader::setPixel(int x, int y, const QColor& color)
{
	image_provider->setPixel(x, y, color);
}

void objLoader::depthUpdate(int y)
{
	for (auto&& aep:tActiveEdgePair)
	{
		auto zx = aep.zl;
		auto x = aep.xl;

		while (x < 0)
		{
			zx += aep.dzx;
			++x;
		}

		if (x < g_zbuffer.size() && zx > g_zbuffer[x])
		{
			g_zbuffer[x] = zx;
			setPixel(x, y, g_bgColor);
		}

		zx += aep.dzx;
		++x;

		while (x < g_zbuffer.size() && x < aep.xr)
		{
			if (zx > g_zbuffer[x])
			{
				g_zbuffer[x] = zx;
				setPixel(x, y, aep.color);
			}
			zx += aep.dzx;
			++x;
		}
	}
}

void objLoader::activeEdgeTableUpdate(int y)
{
	auto it = tActiveEdgePair.begin();
	while (it != tActiveEdgePair.end())
	{
		it->dyl--;
		it->dyr--;
		if (it->dyl <= 0 && it->dyr <= 0)
		{
			auto&& edges = findEdge(it->id, y);
			if (edges.empty())
			{
				tActiveEdgePair.erase(it++);
			}
			else
			{
				assert(edges.size() == 2);
				auto&& l = edges[0];
				auto&& r = edges[1];

				if (l.x > r.x || (l.x == r.x && l.dx > r.dx))
				{
					std::swap(l, r);
				}

				auto ap = std::find_if(tActivePolygon.cbegin(), tActivePolygon.cend(), [id=it->id](const nodeActivePolygon& t)
				                       {
					                       return t.id == id;
				                       });

				it->xl = l.x;
				it->dxl = l.dx;
				it->dyl = l.dy;
				it->xr = r.x;
				it->dxr = r.dx;
				it->dyr = r.dy;
				it->zl = (-ap->d - l.x * ap->a - y * ap->b) / ap->c;
				it->dzx = (-ap->a) / ap->c;
				it->dzy = ap->b / ap->c;

				++it;
			}
		}
		else
		{
			if (it->dyl <= 0)
			{
				auto&& edges = findEdge(it->id, y);
				if (edges.empty())
				{
					tActiveEdgePair.erase(it++);
				}
				else
				{
					auto&& l = edges.front();
					it->xl = l.x;
					it->dxl = l.dx;
					it->dyl = l.dy;
				}
			}
			else
			{
				it->xl += it->dxl;
				it->zl = it->zl + it->dxl * it->dzx + it->dzy;
			}
			if (it->dyr <= 0)
			{
				auto&& edges = findEdge(it->id, y);
				if (edges.empty())
				{
					tActiveEdgePair.erase(it++);
				}
				else
				{
					auto&& l = edges.front();
					it->xr = l.x;
					it->dxr = l.dx;
					it->dyr = l.dy;
				}
			}
			else
			{
				it->xr += it->dxr;
			}
		}
	}
}

void objLoader::activePolygonTableUpdate()
{
	auto it = tActivePolygon.begin();
	while (it != tActivePolygon.end())
	{
		it->dy--;
		if (it->dy < 0)
			tActivePolygon.erase(it++);
		else
			++it;
	}
}
