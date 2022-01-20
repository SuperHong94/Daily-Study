#include <iostream>
#include <fstream>
#include <string>
#include "zip.h"
#include "unzip.h"
using namespace std;


int main()
{
	zipFile _zipFile = zipOpen("test.zip", APPEND_STATUS_CREATE);
	zip_fileinfo zipinfo;
	memset(&zipinfo, 0, sizeof(zip_fileinfo));
	zipOpenNewFileInZip(_zipFile, "test.txt", &zipinfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

	ifstream  fp;
	fp.open("test.txt", ios::binary);
	if (!fp)
		cout << "¿À·ù!\n";
	const int BUF = 16;
	Bytef in[BUF];
	do {
		fp.read((char*)in, BUF);
		int readsize = (int)fp.gcount();
		zipWriteInFileInZip(_zipFile, in, sizeof(readsize));
	} while (!fp.eof());
	fp.close();
	zipCloseFileInZip(_zipFile);
	zipClose(_zipFile, "");

}