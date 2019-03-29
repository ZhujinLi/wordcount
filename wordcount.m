records = containers.Map;
wc('./testdata', records);
words = records.keys();
counts = records.values();
for i = 1:length(words)
    fprintf('%s: %d\n', words{i}, counts{i});
end

function wc(root, records)
    for d = dir(root)'
        fullpath = [d.folder '/' d.name];
        if d.isdir
            if d.name ~= "." && d.name ~= ".."
                wc(fullpath, records);
            end
        else
            f = fopen(fullpath);
            content = textscan(f, '%s');
            fclose(f);
            for word_ = content{:}'
                word = word_{:};
                if records.isKey(word)
                    records(word) = records(word) + 1;
                else
                    records(word) = 1;
                end
            end
        end
    end
end