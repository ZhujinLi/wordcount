#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <boost/filesystem.hpp>

typedef std::unordered_map<std::string, int> WordDict;

static void wc(const std::string& dir, WordDict& dict)
{
	for (auto& dirIter : boost::filesystem::recursive_directory_iterator(dir))
	{
		if (boost::filesystem::is_regular_file(dirIter.status()))
		{
			std::ifstream f(dirIter.path().string());
			for (std::istream_iterator<std::string> wordIter(f), end; wordIter != end; wordIter++)
				if (dict.find(*wordIter) != dict.end())
					dict[*wordIter]++;
				else
					dict[*wordIter] = 1;
		}
	}
}

int main()
{
	WordDict dict;
	wc("./testdata", dict);
	for (auto& iter : dict)
		std::cout << iter.first << ": " << iter.second << std::endl;
	return 0;
}
