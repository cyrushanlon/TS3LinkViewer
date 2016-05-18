#include "memorymanager.hpp"
#include <QBuffer>
#include <QDataStream>

MemoryManager::MemoryManager(QObject * parent) : QObject(parent) 
{
	SharedMemory.setKey("CyrillTS3AutoLinkOpenerThingy");
	ConfigMemory.setKey("CyrillTS3AutoLinkOpenerMessage");

	if (SharedMemory.isAttached())
		SharedMemory.detach();

	if (ConfigMemory.isAttached())
		ConfigMemory.detach();
}

MemoryManager::~MemoryManager() 
{

}

void MemoryManager::LoadTextIntoSharedMemory(std::string URL)
{
	if (SharedMemory.isAttached())
		SharedMemory.detach();

	QBuffer Buf;
	Buf.open(QBuffer::ReadWrite);
	QDataStream Out(&Buf);

	Out << QString::fromStdString(URL);

	int Size = Buf.size();

	if (!SharedMemory.create(Size))
	{
		return;
	}

	SharedMemory.lock();
	char *to = (char*)SharedMemory.data();
	const char *from = Buf.data().data();
	memcpy(to, from, qMin(SharedMemory.size(), Size));
	SharedMemory.unlock();

}

void MemoryManager::OpenConfig()
{
	if (ConfigMemory.isAttached())
		ConfigMemory.detach();

	QBuffer Buf;
	Buf.open(QBuffer::ReadWrite);
	QDataStream Out(&Buf);

	Out << QString::fromStdString("OpenConfig");

	int Size = Buf.size();

	if (!ConfigMemory.create(Size))
	{
		return;
	}

	ConfigMemory.lock();
	char *to = (char*)ConfigMemory.data();
	const char *from = Buf.data().data();
	memcpy(to, from, qMin(ConfigMemory.size(), Size));
	ConfigMemory.unlock();
}