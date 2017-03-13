#include "Config.h"

Config& Config::getInstance()
{
	static Config c;
	return c;
}

Config::~Config()
{
}

void Config::setUrl(const QString& a)
{
	if (a != m_url)
	{
		m_url = a;
		emit urlChanged();
	}
}

void Config::setFaceCount(int a)
{
	if (a != m_faceCount)
	{
		m_faceCount = a;
		emit faceCountChanged();
	}
}

void Config::setTime(int a)
{
	if (a != m_time)
	{
		m_time = a;
		emit timeChanged();
	}
}

QString Config::url() const
{
	return m_url;
}

int Config::faceCount() const
{
	return m_faceCount;
}

int Config::time() const
{
	return m_time;
}
