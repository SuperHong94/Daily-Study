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

	std::vector<std::string> _inFileList; //해당 파일에 포함된 파일리스트
	unzFile _unzfile;


	//내부 함수
	void InitOverlapped();



public:

	bool OpenFile();
	const std::string& GetFilePath() { return _filePath; }
	const IO_EVENT IO_Event() { return _IOevent; }
	const std::vector<std::string>& GetAllFileList();
};

