#pragma once

/*
UnzipMgr�� ���� 



Worker���� �۾� ���� ����ϱ� 

worker�� ���� 

�۾����� ó���ϱ�

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
	HANDLE _hIocp;  //IOCP�� ���� �ڵ�
	std::vector<std::thread> _workers; //�۾��ϴ� ������ Ǯ
	std::unordered_map<std::string, CUnzipFile*> _FileContainer; //���� �����ϴ� �����̳�

	std::mutex _fileLock;
	void FLock() { _fileLock.lock(); }
	void FUnlock() { _fileLock.unlock(); }
	void RunThread(int threadNum);
	void Worker();//Worker ������
public:
	bool RequestOpenFile(const char* path);
};

