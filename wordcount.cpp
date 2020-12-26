// C++17 or higher is required

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> records;
    std::string word;

    for (auto &f : std::filesystem::recursive_directory_iterator("./testdata"))
        if (f.is_regular_file())
            for (std::ifstream s(f); s >> word;)
                records[word]++;

    for (auto &iter : records)
        std::cout << iter.first << ": " << iter.second << std::endl;

    return 0;
}
