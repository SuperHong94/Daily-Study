#pragma once
#include <Zlib/unzip.h>

class CUnzipFile :public OVERLAPPED
{

public:
	CUnzipFile();
	CUnzipFile(const char*);
	virtual ~CUnzipFile();


private:
	BYTE* _buffer;
	IO_EVENT _IOevent;
	std::string _filePath;

	std::vector<std::string> _inFileList; //�ش� ���Ͽ� ���Ե� ���ϸ���Ʈ
	unzFile _unzfile;


	//���� �Լ�
	void InitOverlapped();



public:

	bool OpenFile();
	const std::string& GetFilePath() { return _filePath; }
	const IO_EVENT IO_Event() { return _IOevent; }
	const std::vector<std::string>& GetAllFileList();
};

