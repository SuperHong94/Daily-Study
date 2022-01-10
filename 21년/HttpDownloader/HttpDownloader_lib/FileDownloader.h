#pragma once


#define HFD_DECLSPEC __declspec(dllexport)


class CFileDownloader
{

public:
	CFileDownloader(const std::wstring& url, const std::wstring& save_path, const std::wstring& file_name);
	~CFileDownloader();
public:
	bool download();
private:
	void initialize();
private:
	HINTERNET _internet_handle;
	std::wstring _url, _save_path, _save_file_name;


};


extern "C"{
	HFD_DECLSPEC CFileDownloader* CreateFileDownloader(const std::wstring& url, const std::wstring& save_path, const std::wstring& file_name);

	HFD_DECLSPEC bool Download(CFileDownloader& fd);
	HFD_DECLSPEC void DeleteFD(CFileDownloader* fd);
}