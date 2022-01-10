#include "pch.h"
#include "FileDownloader.h"

CFileDownloader::CFileDownloader(const std::wstring& url, const std::wstring& save_path, const std::wstring& file_name) :_url(url), _save_path(save_path), _save_file_name(file_name)
{
	_internet_handle = nullptr;
	initialize();
}

CFileDownloader::~CFileDownloader()
{
	if (nullptr != _internet_handle) {
		InternetCloseHandle(_internet_handle);
		_internet_handle = nullptr;
	}
}

bool CFileDownloader::download()
{
	bool result = false;
	do {

		if (nullptr == _internet_handle) {
			//Console::WriteLine("_internet_handle nullptr.");
			break;
		}
		if (_url.empty()) {
			//Console::WriteLine("empty url.");
			break;
		}
		if (_save_path.empty()) {
			//Console::WriteLine("empty save_path.");
			break;
		}
		if (_save_file_name.empty()) {
			//Console::WriteLine("save_file_name save_path.");
			break;
		}

		const HINTERNET open_url_handle = InternetOpenUrl(
			_internet_handle,
			_url.c_str(),
			nullptr,
			0,
			INTERNET_FLAG_RELOAD,
			0
		);
		if (nullptr == open_url_handle) {
			//Console::WriteLine("_open_url_handle nullptr.");
			break;
		}

		DWORD status_code = 0;
		DWORD status_code_size = sizeof(status_code);
		if (FALSE == HttpQueryInfo(
			open_url_handle,
			HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
			&status_code,
			&status_code_size,
			nullptr
		)) {

			break;
		}
		if (sizeof(status_code) != status_code_size) {

			break;
		}
		if (HTTP_STATUS_OK != status_code) {

			break;
		}

		std::wstring file_name;
		file_name.assign(_save_path);
		file_name.append(L"\\");
		file_name.append(_save_file_name);
		const int max_buffer_size = 2014;
		char buffer[max_buffer_size] = {};
		std::ofstream save_file;
		save_file.open(file_name.c_str(), std::ios::binary);
		if (save_file.is_open()) {

			result = true;
			DWORD number_of_bytes_read = 0;
			do {

				DWORD read_available = 0;
				if (FALSE == InternetQueryDataAvailable(
					open_url_handle,
					&read_available,
					0,
					0
				)) {
					result = false;
					//Console::WriteLine("InternetQueryDataAvailable failed.");
					break;
				}
				// resize buffer.
				if (read_available > max_buffer_size) {
					read_available = max_buffer_size;
				}

				if (FALSE == InternetReadFile(
					open_url_handle,
					buffer,
					read_available,
					&number_of_bytes_read
				)) {
					result = false;
					//Console::WriteLine("InternetReadFile failed.");
					break;
				}
				if (0 < number_of_bytes_read) {

					save_file.write(buffer, number_of_bytes_read);
					memset(buffer, 0x00, number_of_bytes_read);
				}
			} while (0 != number_of_bytes_read);
			save_file.close();
		}
		InternetCloseHandle(open_url_handle);
	} while (false);
	return result;
}

void CFileDownloader::initialize()
{
	_internet_handle = InternetOpen(
		L"file_donwload",
		INTERNET_OPEN_TYPE_DIRECT,
		nullptr,
		nullptr,
		0
	);
	if (nullptr == _internet_handle) {
		//Console::WriteLine("InternetOpen failed.");
	}
}

HFD_DECLSPEC CFileDownloader* CreateFileDownloader(const std::wstring& url, const std::wstring& save_path, const std::wstring& file_name)
{
	return new CFileDownloader(url, save_path, file_name);
}

HFD_DECLSPEC bool Download(CFileDownloader& fd)
{
	return fd.download();
}

HFD_DECLSPEC void DeleteFD(CFileDownloader* fd)
{
	if (fd == nullptr) {
		delete fd;
		fd = nullptr;
	}
}
