#pragma once
#include <string>
#include <unordered_map>
#include <fstream>

class Hash_def
{
private:
	std::string inputFilename;
	std::string compressedFilename;
	std::string decompressedFilename;
	std::string hashKeysFilename;
	std::string compressedString;
	std::string compressString(const std::string& input);
	std::string decompressString(const std::string& input);
	std::pair<size_t, size_t> calculateHashKeys(const std::string& input);
public:
	Hash_def();
	bool Compressing_string();
	bool Read_compressing_file();
};

