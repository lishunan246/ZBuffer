#pragma once

#include <QObject>
#include <QColor>

/**
 * \brief 保存一些全局数据
 */
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
	/**
	 * \brief 文件地址
	 */
	QString m_url;
	/**
	 * \brief 面片数量
	 */
	int m_faceCount = 0;
	/**
	 * \brief 扫描一帧的时间(毫秒)
	 */
	int m_time = 0;
};
