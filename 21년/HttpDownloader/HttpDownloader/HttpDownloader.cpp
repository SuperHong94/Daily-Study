#include "pch.h"

#include "HttpDownloader.h"

HttpDownloader::FileDownloader::FileDownloader()
{
	_internet_handle = nullptr;
	initialize();

}

HttpDownloader::FileDownloader::~FileDownloader()
{
	if (nullptr != _internet_handle) {
		InternetCloseHandle(_internet_handle);
		_internet_handle = nullptr;
	}

}

bool HttpDownloader::FileDownloader::download(System::String^ sUrl, System::String^ sSave_path, System::String^ sSave_file_name)
{
	std::wstring url = msclr::interop::marshal_as<std::wstring>(sUrl);
	std::wstring save_path = msclr::interop::marshal_as<std::wstring>(sSave_path);
	std::wstring save_file_name = msclr::interop::marshal_as<std::wstring>(sSave_file_name);
	bool result = false;
	do {
		/*
		넘어온 parameter는 verify check를 해주어야겠죠? 필수 입력값이기때문에
		셋중에 하나라도 미입력시 정상적으로 파일을 다운로드하지 못하거나 저장하지 못할 수 있습니다.
		*/
		if (nullptr == _internet_handle) {
			Console::WriteLine("_internet_handle nullptr.");
			break;
		}
		if (url.empty()) {
			Console::WriteLine("empty url.");
			break;
		}
		if (save_path.empty()) {
			Console::WriteLine("empty save_path.");
			break;
		}
		if (save_file_name.empty()) {
			Console::WriteLine("save_file_name save_path.");
			break;
		}
		/*
		InternetOpenUrl API를 이용하여 실제 접속이 시작됩니다.
		캐시가 아닌 원본파일을 항상 다운로드받기위해 Flag는 INTERNET_FLAG_RELOAD를 주었습니다.
		다른 Flag를 설정하고싶은경우 MSDN을 참조하시면 됩니다.
		*/
		const HINTERNET open_url_handle = InternetOpenUrl(
			_internet_handle,
			url.c_str(),
			nullptr,
			0,
			INTERNET_FLAG_RELOAD,
			0
		);
		if (nullptr == open_url_handle) {
			Console::WriteLine("_open_url_handle nullptr.");
			break;
		}
		/*
		해당 URL에 404, 500 등 http error가 넘어오더라도 정상적인 URL정보이기때문에 InternetOpenUrl의 HINTERNET Handle이 넘어오게 됩니다.
		그렇기때문에 NULL 또는 INVALID_HANDLE 정보로는 에러 여부를 확인할 수 없으므로
		HttpQueryInfo API를 이용하여 HTTP_QUERY_STATUS_CODE를 확인합니다.
		HTTP_STATUS_OK가 넘어왔다면 접속이 성공한것이니 이제 파일로 저장하기만 하면 됩니다.
		*/
		DWORD status_code = 0;
		DWORD status_code_size = sizeof(status_code);
		if (FALSE == HttpQueryInfo(
			open_url_handle,
			HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
			&status_code,
			&status_code_size,
			nullptr
		)) {
			Console::WriteLine("HttpQueryInfo failed (%d)", ::GetLastError());
			break;
		}
		if (sizeof(status_code) != status_code_size) {
			Console::WriteLine("status_code != status_code_size failed.");
			break;
		}
		if (HTTP_STATUS_OK != status_code) {
			Console::WriteLine("error status_code (%d).", status_code);
			break;
		}
		//
		// make save file name.
		//
		std::wstring file_name;
		file_name.assign(save_path);
		file_name.append(L"\\");
		file_name.append(save_file_name);
		const int max_buffer_size = 2014;
		char buffer[max_buffer_size] = {};
		std::ofstream save_file;
		save_file.open(file_name.c_str(), std::ios::binary);
		if (save_file.is_open()) {
			//
			// set result.
			//
			result = true;
			DWORD number_of_bytes_read = 0;
			do {
				/*
				여기가 가장 중요한 부분인데요 네트워크 통신이라는게 패킷단위로 왔다갔다 하다보니 한번의 통신으로 파일을 받을 수 없습니다.
				용량이 아주 작은 통신 패킷이라면 한번에 받기도 하겠지만 지정된 버퍼보다 큰 사이즈 또는 네트워크 상태에 따라 정해지지 않은 크기를 주고받기때문에
				InternetQueryDataAvailable API를 통해 현재 얼마만큼의 데이터를 읽을 수 있는지 확인하도록 합니다.
				*/
				DWORD read_available = 0;
				if (FALSE == InternetQueryDataAvailable(
					open_url_handle,
					&read_available,
					0,
					0
				)) {
					result = false;
					Console::WriteLine("InternetQueryDataAvailable failed.");
					break;
				}
				// resize buffer.
				if (read_available > max_buffer_size) {
					read_available = max_buffer_size;
				}
				//
				// internet read file.
				//
				if (FALSE == InternetReadFile(
					open_url_handle,
					buffer,
					read_available,
					&number_of_bytes_read
				)) {
					result = false;
					Console::WriteLine("InternetReadFile failed.");
					break;
				}
				if (0 < number_of_bytes_read) {
					//
					// write file.
					//
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

void HttpDownloader::FileDownloader::initialize()
{
	_internet_handle = InternetOpen(
		L"file_donwload",
		INTERNET_OPEN_TYPE_DIRECT,
		nullptr,
		nullptr,
		0
	);
	if (nullptr == _internet_handle) {
		Console::WriteLine("InternetOpen failed.");
	}


}
