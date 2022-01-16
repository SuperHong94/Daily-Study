#include "stdafx.h"
#include "UnzipMgr.h"
#include "UnzipFile.h"




CUnzipMgr::CUnzipMgr(int threadNum)
{

	_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, threadNum);

	std::thread CUnzipMgrThread{ &CUnzipMgr::RunThread ,this,threadNum };


	CUnzipMgrThread.join();



}

CUnzipMgr::~CUnzipMgr()
{
}



void CUnzipMgr::RunThread(int threadNum)
{
	for (int i = 0; i < threadNum; ++i)
	{

		_workers.emplace_back(&CUnzipMgr::Worker, this);
	}


	for (auto& th : _workers)
		th.join();
}

void CUnzipMgr::Worker()
{
	while (true)
	{
		DWORD numbytes = 0;
		uLong key = 0;
		OVERLAPPED* over;
		GetQueuedCompletionStatus(_hIocp, &numbytes, &key, &over, INFINITE);

		CUnzipFile* unzipFile = static_cast<CUnzipFile*>(over);

		switch (unzipFile->IO_Event())
		{
		case IO_EVENT::IO_NONE:
			break;
		case IO_EVENT::IO_FILE_OPEN:
			if (true == unzipFile->OpenFile())
			{
				FLock();
				_FileContainer.emplace(unzipFile->GetFilePath(), unzipFile);
				FUnlock();
			}
			break;
		default:
			break;
		}
	}
}

bool CUnzipMgr::RequestOpenFile(const char* path)
{
	std::string reqPath = path;
	if (_FileContainer.count(path) != 0) {
		std::cout << "이미 열려있는 파일입니다.\n";
		return false;
	}

	CUnzipFile* newCUnzipFile = new CUnzipFile(path);
	PostQueuedCompletionStatus(_hIocp, 0, 0, static_cast<OVERLAPPED*>(newCUnzipFile));
	return true;
}
