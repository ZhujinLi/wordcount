#include <iostream>
#include <string>
#include <hash_map>
#include <boost/filesystem.hpp>

void wc(const std::string& dir, std::hash_map<std::string, int>& dict)
{
	boost::filesystem::path path = boost::filesystem::current_path();
	for (boost::filesystem::recursive_directory_iterator iter(path);
		iter != boost::filesystem::recursive_directory_iterator();
		iter++)
	{
		std::cout << iter->path().string() << std::endl;
	}
}

int main()
{
	typedef std::hash_map<std::string, int> WordDict;
	WordDict dict;
	wc("./", dict);
	for (WordDict::iterator iter = dict.begin(); iter != dict.end(); iter++)
	{
		std::cout << iter->first << ": " << iter->second << std::endl;
	}
	return 0;
}