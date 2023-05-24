#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

enum Choice {
    SEE_ALL_NOTES = 1,
    TO_WRITE,
    COMPRESS,
    HASH_KEY,
    DECOMPRESS,
    CLEAR,
    EXIT
};

void show_menu();
void data_file();
void add_note_one(const std::string& new_note_one);
void add_note_two(const std::string& new_note_two);
std::string compressString(const std::string& input);
std::string decompressString(const std::string& input);
std::pair<size_t, size_t> calculateHashKeys(const std::string& input);
bool clear_file();

int main() {
    setlocale(LC_ALL, "rus");
    std::string inputFilename = "input.txt";
    std::string compressedFilename = "compressed.txt";
    std::string decompressedFilename = "decompressed.txt";
    std::string hashKeysFilename = "hash_keys.txt";
    std::ifstream inputFile;
    std::string inputString;
    std::string compressedString;
    std::ofstream compressedFile;
    std::string decompressedString;
    std::ofstream hashKeysFile;
    std::ofstream decompressedFile;
    std::pair<size_t, size_t> hashKeys;
    while (true) {
        show_menu();
        std::cout << "Ваш выбор: ";
        int choice;
        std::cin >> choice;
        system("cls");
        switch (choice)
        {
        case SEE_ALL_NOTES:
            system("cls");
            data_file();
            break;
        case TO_WRITE:
            system("cls");
            std::cout << "[1] Дописать\n" <<
                "[2] Написать с нуля\n" <<
                "[3] Назад\n";
            int edit;
            std::cin >> edit;
            if (edit == 1) {
                system("cls");
                std::cout << "Введите текст\n";
                std::string new_note_one;
                getline(std::cin, new_note_one);
                std::cout << "Примечание для добавления: ";
                getline(std::cin, new_note_one);
                add_note_one(new_note_one);
            }
            else if (edit == 2) {
                system("cls");
                std::cout << "Введите текст\n";
                std::string new_note_two;
                getline(std::cin, new_note_two);
                std::cout << "Примечание для добавления: ";
                getline(std::cin, new_note_two);
                add_note_two(new_note_two);
            }
            else if (edit == 3) {
                system("pause");
            }
            break;
        case COMPRESS:
            system("cls");
            // Сжатие строки из файла
            inputFile.open(inputFilename);
            if (inputFile.is_open()) {
                std::getline(inputFile, inputString);
                inputFile.close();
            }
            else {
                std::cout << "Не удалось открыть файл " << inputFilename << std::endl;
                return 1;
            }
            compressedFile.open(compressedFilename);
            compressedString = compressString(inputString);
            //Запись в файл зашифрованного текста
            if (compressedFile.is_open()) {
                compressedFile << compressedString;
                compressedFile.close();
            }
            else {
                std::cout << "Не удалось создать файл " << compressedFilename << std::endl;
                return 1;
            }
            break;
        case HASH_KEY:
            // Вычисление и вывод хэш-ключей
            hashKeysFile.open(hashKeysFilename);
            hashKeys = calculateHashKeys(inputString);

            if (hashKeysFile.is_open()) {
                hashKeysFile << "hash-key one: " << hashKeys.first << std::endl;
                hashKeysFile << "hash-key two: " << hashKeys.second << std::endl;
                hashKeysFile.close();
            }
            else {
                std::cout << "Не удалось создать файл " << hashKeysFilename << std::endl;
                return 1;
            }
            break;
        case DECOMPRESS:
            // Разархивация строки из файла
            decompressedFile.open(decompressedFilename);
            decompressedString = decompressString(compressedString);

            // Запись разархивированной строки в файл
            if (decompressedFile.is_open()) {
                decompressedFile << decompressedString;
                decompressedFile.close();
            }
            else {
                std::cout << "Не удалось создать файл " << decompressedFilename << std::endl;
                return 1;
            }
            break;
        case CLEAR:
            system("cls");
            clear_file();
            system("pause");
            break;
        default:
            exit(EXIT_SUCCESS);
            break;
        }
    }
    return 0;
}

void show_menu()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "[1] Посмотреть содержимое файла " << std::endl;
    std::cout << "[2] Вести текст " << std::endl;
    std::cout << "[3] Сжать файл" << std::endl;
    std::cout << "[4] Получить хэш-ключи" << std::endl;
    std::cout << "[5] Расшифровать содержимое зашифрованного файла" << std::endl;
    std::cout << "[6] Очистить файл " << std::endl;
    std::cout << "[7] Выход " << std::endl;
}

//Посмотреть содержимое файла
void data_file()
{
    std::ifstream file("input.txt");
    if (!file.is_open())
    {
        std::cout << "Никаких заметок! Добавь их!" << std::endl;
        return;
    }
    std::string one_note;
    std::cout << "Все примечания: " << std::endl;
    std::cout << std::endl;
    while (!file.eof()) {
        getline(file, one_note);
        std::cout << one_note << '\n' << std::endl;
    }
    file.close();
}

//Вести текст
void add_note_one(const std::string& new_note_one)
{
    std::cout << new_note_one;
    std::ofstream file("input.txt", std::ios::app);
    if (!file.is_open()) {
        std::cout << "[-] Файл не открывается! ";
        exit(EXIT_FAILURE);
    }
    file << new_note_one << " ";

    file.close();
    std::cout << "\nДобавлено примечание! " << std::endl;
}

//Вести текст
void add_note_two(const std::string& new_note_two)
{
    std::cout << new_note_two;
    std::ofstream file("input.txt", std::ios::out);
    if (!file.is_open()) {
        std::cout << "[-] Файл не открывается! ";
        exit(EXIT_FAILURE);
    }
    file << new_note_two << " ";

    file.close();

    std::cout << "\nДобавлено примечание! " << std::endl;
}

// Функция для сжатия строки
std::string compressString(const std::string& input) {
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

// Функция для разархивации строки
std::string decompressString(const std::string& input) {
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

// Функция для вычисления хэш-ключей
std::pair<size_t, size_t> calculateHashKeys(const std::string& input) {
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

bool clear_file() {
    std::ofstream file("input.txt", std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "[-] Файл не открывается!";
        exit(EXIT_FAILURE);
    }
    file.close();
    std::cout << "Файл очищен\n";
    return 1;
}