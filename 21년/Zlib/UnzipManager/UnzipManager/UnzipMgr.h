#pragma once

/*
UnzipMgr이 할일 



Worker에게 작업 내용 명령하기 

worker가 할일 

작업내용 처리하기

*/
#include <thread>
#include <unordered_map>
#include <mutex>
class CUnzipFile;


class CUnzipMgr
{
public:



	CUnzipMgr(int threadNum);
	~CUnzipMgr();




private:
	HANDLE _hIocp;  //IOCP를 위한 핸들
	std::vector<std::thread> _workers; //작업하는 쓰레드 풀
	std::unordered_map<std::string, CUnzipFile*> _FileContainer; //파일 관리하는 컨테이너

	std::mutex _fileLock;
	void FLock() { _fileLock.lock(); }
	void FUnlock() { _fileLock.unlock(); }
	void RunThread(int threadNum);
	void Worker();//Worker 쓰레드
public:
	bool RequestOpenFile(const char* path);
};

