#pragma once

/*
UnzipMgr이 할일 



Worker에게 작업 내용 명령하기 

worker가 할일 
작업내용 처리하기

*/


class CUnzipMgr
{

private:
	HANDLE _hIocp;  //IOCP를 위한 핸들
	std::vector<std::thread> _workers; //작업하는 쓰레드 풀

	static void Worker(CUnzipMgr*);//Worker 쓰레드
public:
	CUnzipMgr();
	~CUnzipMgr();


};

