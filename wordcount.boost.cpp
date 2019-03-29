#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <experimental/filesystem>

int main() {
	std::unordered_map<std::string, int> records;
	for (auto& dirIter : std::filesystem::recursive_directory_iterator("./testdata")) {
		if (std::filesystem::is_regular_file(dirIter.status())) {
			std::ifstream f(dirIter.path().string());
			for (std::istream_iterator<std::string> wordIter(f), end; wordIter != end; wordIter++)
				records[*wordIter]++;
		}
	}
	for (auto& iter : records)
		std::cout << iter.first << ": " << iter.second << std::endl;
	return 0;
}
