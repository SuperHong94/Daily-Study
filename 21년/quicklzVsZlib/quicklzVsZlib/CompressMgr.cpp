#include "CompressMgr.h"
#include "zip.h"
#include <fstream>
#include <iostream>
#include <vector>
void CZlibCompress::Compress(const char* filename)
{


	zipFile zf = zipOpen("c.zip", APPEND_STATUS_CREATE);
	if (NULL == zf)
		return;
	zip_fileinfo info;
	memset(&info, 0, sizeof(zip_fileinfo));

	zipOpenNewFileInZip(zf, filename, &info, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

	std::ifstream fp;
	fp.open(filename, std::ios_base::binary);
	if (!fp) return;

	fp.seekg(0, fp.end);
	size_t fileLength = fp.tellg();
	fp.seekg(0, fp.beg);

	//unsigned char* buf = new unsigned char[fileLength];

	//fp.read((char*)buf, fileLength);
	//std::vector<unsigned char> buf{ std::istream_iterator<unsigned char>{fp},{} };//whitespaceÀÚ¸£¸é ¾ÈµÊ

	fp.close();


	zipCloseFileInZip(zf);

	zipClose(zf, "");



}

CCompressMgr::CCompressMgr()
{
	zlibCompress = new CZlibCompress;
}

CCompressMgr::~CCompressMgr()
{
	if (nullptr != zlibCompress)
		delete zlibCompress;
}

void CCompressMgr::Compress(char c, const char* filename)
{
	switch (c)
	{
	case 'z':
		zlibCompress->Compress(filename);
		break;
	case 'q':
		quickLZCompress->Compress(filename);
		break;
	default:
		break;
	}
}
