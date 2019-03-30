#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH_LEN 128
#define MAX_WORD_LEN 128
#define MAX_WORD_COUNT 16384

typedef struct {
	char _words[MAX_WORD_COUNT][MAX_WORD_LEN];
	int _counts[MAX_WORD_COUNT];
} WordRecords;

typedef int WordRecordIterator;

void WordRecords_init(WordRecords* o) {
	memset(o, 0, sizeof *o);
}

void WordRecords_addWordCount(WordRecords* o, const char* word) {
	int hash = 5381;
	for (const char* c = word; *c; c++)
		hash = (((hash << 5) + hash) + *c) % MAX_WORD_COUNT;

	int index = -1, found = 0;
	for (int i = hash; index == -1; i = (i + 1) % MAX_WORD_COUNT)
		if (o->_words[i][0] == 0 || (found = (strcmp(o->_words[i], word) == 0)))
			index = i;

	if (!found)
		strcpy(o->_words[index], word);
	o->_counts[index]++;
}

WordRecordIterator WordRecords_getIterator(WordRecords* o) {
	return -1;
}

const char* WordRecords_nextWordAndCount(WordRecords* o, WordRecordIterator* iter, int* count) {
	for ((*iter)++; *iter < MAX_WORD_COUNT; (*iter)++)
		if (o->_words[*iter][0]) {
			*count = o->_counts[*iter];
			return o->_words[*iter];
		}
	return NULL;
}

void processFile(const char* path, WordRecords* records) {
	FILE* f = fopen(path, "r");
	if (f) {
		char word[MAX_WORD_LEN];
		while (fscanf(f, "%s", word) == 1)
			WordRecords_addWordCount(records, word);
		fclose(f);
	}
}

void wc(const char* root, WordRecords* records) {
	DIR* dir = opendir(root);
	if (dir) {
		for (struct dirent* de; (de = readdir(dir)); )
			if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
				char path[MAX_PATH_LEN];
				sprintf(path, "%s/%s", root, de->d_name);
				if (de->d_type == DT_DIR)
					wc(path, records);
				else if (de->d_type == DT_REG)
					processFile(path, records);
			}
		closedir(dir);
	}
}

int main() {
	WordRecords records;
	WordRecords_init(&records);
	wc("./testdata", &records);

	const char* word = NULL;
	int count = 0;
	WordRecordIterator iter = WordRecords_getIterator(&records);
	while ((word = WordRecords_nextWordAndCount(&records, &iter, &count)))
		printf("%s: %d\n", word, count);
	return 0;
}
