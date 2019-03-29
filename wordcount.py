import os

result = dict()

for _, _, filenames in os.walk('./testdata'):
    for filename in filenames:
        with open(filename) as f:
            for word in f.read().split():
                if word in result:
                    result[word] += 1
                else:
                    result[word] = 1

print(result)
