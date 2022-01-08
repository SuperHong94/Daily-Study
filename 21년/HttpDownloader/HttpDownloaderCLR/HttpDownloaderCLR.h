#pragma once

using namespace System;

namespace HttpDownloader {
	public ref class FileDownloader
	{
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	public:
		FileDownloader();
		~FileDownloader();
	public:
		bool download(System::String^ sUrl, System::String^ sSave_path, System::String^ sSave_file_name);
	private:
		void initialize();
	private:
		HINTERNET _internet_handle;

	};
}
