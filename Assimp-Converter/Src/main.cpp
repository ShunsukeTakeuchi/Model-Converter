
#include<memory>
#include<iostream>
#include<filesystem>
#include"ModelConverter.h"
#include"AssimpConverter.h"
#include"MMDFileRoader\PMXFile.h"
#include <windows.h>
#include <tchar.h>

#include<fstream>

int main(int argc, char **argv)
{
	std::cout << "assimp model converter\nモデルファイルをバイナリ形式に変換します。" << std::endl;

	//ModelConverter converter;
	AssimpConverter converter;

	for (int i = 1; i < argc; ++i)
	{
		std::cout << "読込ファイル名 : " << argv[i] << "\n" << std::endl;

		std::filesystem::path filepath(argv[i]);

		if (filepath.extension() == ".pmx")
		{
			std::unique_ptr<PMXFile> file = std::make_unique<PMXFile>();
			ReadPMXFile(file.get(), filepath.string());
		}
		else
		{
			// load
			if (!converter.Load(filepath.u8string())) break;
		}

		filepath = filepath.filename();
		filepath.replace_extension(".pzm");

		TCHAR path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);
		std::basic_string<TCHAR> curr_dir(path);
		curr_dir.erase(curr_dir.find_last_of("\\"), curr_dir.size());

		std::string currdir_filename(curr_dir + "\\" + filepath.u8string());

		std::cout << "保存ファイル名 : " << currdir_filename.c_str() << "\n" << std::endl;

		// save
		converter.Save(currdir_filename);

		// read sample
		converter.Read(currdir_filename);
	}

	rewind(stdin);
	getchar();

    return 0;
}