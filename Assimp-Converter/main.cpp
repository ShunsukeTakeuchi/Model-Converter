
#include<iostream>
#include<filesystem>
#include"ModelConverter.h"

int main(int argc, char **argv)
{
	std::cout << "assimp model converter\nモデルファイルをバイナリ形式に変換します。" << std::endl;

	ModelConverter converter;

	for (int i = 1; i < argc; ++i)
	{
		std::cout << argv[i] << "\n" << std::endl;

		std::filesystem::path filepath(argv[i]);

		// load
		converter.Load(filepath.u8string());

		filepath = filepath.filename();
		filepath.replace_extension(".pzm");

		// save
		converter.Save(filepath.u8string());
	}

	rewind(stdin);
	getchar();

    return 0;
}