#pragma once

/*
UnzipMgr�� ���� 



Worker���� �۾� ���� ����ϱ� 

worker�� ���� 
�۾����� ó���ϱ�

*/


class CUnzipMgr
{

private:
	HANDLE _hIocp;  //IOCP�� ���� �ڵ�
	std::vector<std::thread> _workers; //�۾��ϴ� ������ Ǯ

	static void Worker(CUnzipMgr*);//Worker ������
public:
	CUnzipMgr();
	~CUnzipMgr();


};

