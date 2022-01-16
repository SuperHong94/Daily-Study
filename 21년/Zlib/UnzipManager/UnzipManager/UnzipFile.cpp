#include "stdafx.h"

#include "UnzipFile.h"

CUnzipFile::CUnzipFile() :_buffer(nullptr), _IOevent(IO_EVENT::IO_NONE)
{
	InitOverlapped();
}

CUnzipFile::CUnzipFile(const char* path) : _buffer(nullptr), _IOevent(IO_EVENT::IO_NONE)
{
	InitOverlapped();

	_filePath = path;


}

CUnzipFile::~CUnzipFile()
{

	if (UNZ_OK != unzClose(_unzfile)) std::cout << "unzClose ����!\n";


}

void CUnzipFile::InitOverlapped()
{
	Internal = 0;
		InternalHigh = 0;
		OffsetHigh = 0;
		Offset = 0;
		Pointer = nullptr;
		hEvent = 0;
}

bool CUnzipFile::OpenFile()
{
	_unzfile = unzOpen(_filePath.c_str());

	if (NULL == _unzfile) {
		std::cout << _filePath << " ���� ���� ����!\n";
		return false;
	}
	return true;

}

const std::vector<std::string>& CUnzipFile::GetAllFileList()
{
	//  �̺κ�  _fileList�� ����������� �����ų�� ����� �� 

	int ret = unzGoToFirstFile(_unzfile);
	if (UNZ_OK != ret)std::cout << "unzGoToFirstFile  ����!\n ";

	unz_file_info info;
	const int bufSIze = 256;
	char filename[bufSIze];
	while (UNZ_OK == ret)
	{
		ret = unzGetCurrentFileInfo(_unzfile, &info, filename, bufSIze, NULL, 0, NULL, 0);
		if (UNZ_OK != ret)break;
		_inFileList.push_back(filename);
		ret = unzGoToNextFile(_unzfile);
	}
	return _inFileList;
}

