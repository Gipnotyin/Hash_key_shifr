#include "Hash_def.h"

Hash_def::Hash_def()
{
    this->inputFilename = "input.txt";
    this->compressedFilename = "compressed.txt";
    this->decompressedFilename = "decompressed.txt";
    this->hashKeysFilename = "hash_keys.txt";
}

std::string Hash_def::compressString(const std::string& input)
{
    std::string compressed;
    int count = 1;

    for (int i = 1; i <= input.length(); i++) {
        if (input[i] == input[i - 1]) {
            count++;
        }
        else {
            compressed += input[i - 1];
            if (count > 1) {
                compressed += std::to_string(count);
            }
            count = 1;
        }
    }

    return compressed;
}

std::string Hash_def::decompressString(const std::string& input)
{
    std::string decompressed;
    std::string letter;
    int count = 0;

    for (char c : input) {
        if (std::isdigit(c)) {
            count = count * 10 + (c - '0');
        }
        else {
            if (count == 0) {
                decompressed += letter;
            }
            else {
                for (int i = 0; i < count; i++) {
                    decompressed += letter;
                }
            }

            letter = c;
            count = 0;
        }
    }
    if (count == 0) {
        decompressed += letter;
    }
    else {
        for (int i = 0; i < count; i++) {
            decompressed += letter;
        }
    }
    return decompressed;
}

std::pair<size_t, size_t> Hash_def::calculateHashKeys(const std::string& input)
{
    std::unordered_map<char, size_t> charOccurrences;
    std::unordered_map<size_t, size_t> occurrenceCounts;

    for (char c : input) {
        charOccurrences[c]++;
    }

    for (const auto& pair : charOccurrences) {
        occurrenceCounts[pair.second]++;
    }

    size_t hashKey1 = 0, hashKey2 = 0;

    for (const auto& pair : occurrenceCounts) {
        hashKey1 ^= pair.first;
        hashKey2 ^= pair.second;
    }

    return { hashKey1, hashKey2 };
}

bool Hash_def::Compressing_string()
{
    std::ifstream inputFile(inputFilename);
    std::string inputString;

    if (inputFile.is_open()) {
        std::getline(inputFile, inputString);
        inputFile.close();
    }
    else {
        return 0;
    }
    this->compressedString = compressString(inputString);
    return 1;
}

bool Hash_def::Read_compressing_file()
{
    std::ofstream compressedFile(this->compressedFilename);

    if (compressedFile.is_open()) {
        compressedFile << this->compressedString;
        compressedFile.close();
    }
    else {
        return 0;
    }
    return 1;
}
