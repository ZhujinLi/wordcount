#include <iostream>
#include <string>
#include <hash_map>
#include <fstream>
#include <boost/filesystem.hpp>

typedef std::hash_map<std::string, int> WordDict;

static void wc(const std::string& dir, std::hash_map<std::string, int>& dict)
{
	for (auto& dirIter : boost::filesystem::recursive_directory_iterator(dir))
	{
		if (dirIter.status().type() == boost::filesystem::regular_file)
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
