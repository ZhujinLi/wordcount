#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH_LEN 128
#define MAX_WORD_LEN 128
#define MAX_WORD_COUNT 16384

typedef struct {
	char _words[MAX_WORD_COUNT][MAX_WORD_LEN];
	int _counts[MAX_WORD_COUNT];
	int _size;
} WordRecords;

void WordRecords_init(WordRecords* o) {
	o->_size = 0;
}

void WordRecords_addWordCount(WordRecords* o, const char* word) {
	int index = -1;
	for (int i = 0; index == -1 && i < o->_size; i++)
		if (strcmp(o->_words[i], word) == 0)
			index = i;
	if (index == -1) {
		o->_counts[o->_size] = 1;
		strcpy(o->_words[o->_size], word);
		o->_size++;
	} else {
		o->_counts[index]++;
	}
}

int WordRecords_getSize(WordRecords* o) {
	return o->_size;
}

const char* WordRecords_getWordAndCountAtIndex(WordRecords* o, int index, int* count) {
	*count = o->_counts[index];
	return o->_words[index];
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
				strcpy(path, root);
				strcat(path, "/");
				strcat(path, de->d_name);

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
	for (int i = 0; i < WordRecords_getSize(&records); i++) {
		int count = 0;
		const char* word = WordRecords_getWordAndCountAtIndex(&records, i, &count);
		printf("%s: %d\n", word, count);
	}
	return 0;
}