#pragma once

#include <QObject>
#include <QColor>

class Config :public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
		Q_PROPERTY(int faceCount READ faceCount WRITE setFaceCount NOTIFY faceCountChanged)
		Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
public:
	static Config& getInstance();
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

	virtual ~Config();

	int width = 800;
	int height = 600;
	QColor backgroundColor = QColor(0, 0, 0);
	void setUrl(const QString& a);
	void setFaceCount(int a);
	void setTime(int a);
	QString url() const;
	int faceCount() const;
	int time() const;
signals:
	void urlChanged();
	void faceCountChanged();
	void timeChanged();
private:
	Config() = default;
	QString m_url;
	int m_faceCount = 0;
	int m_time = 0;
};
