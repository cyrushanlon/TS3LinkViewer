#pragma once
#include <QObject>
#include <QSharedMemory>

class MemoryManager : public QObject 
{
	Q_OBJECT

public:
	MemoryManager(QObject * parent = Q_NULLPTR);
	~MemoryManager();

	void LoadTextIntoSharedMemory(std::string URL);
	void OpenConfig();

private:
	QSharedMemory SharedMemory;
	QSharedMemory ConfigMemory;
};
