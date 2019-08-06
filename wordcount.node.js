const fs = require('fs');
const path = require('path');

function walk(dir, records) {
    records = records || {};

    fs.readdirSync(dir).forEach((f) => {
        let entry = path.join(dir, f);
        let stat = fs.statSync(entry);
        if (stat && stat.isDirectory()) {
            walk(entry, records);
        } else {
            let content = fs.readFileSync(entry, 'utf8');
            let words = content.replace(/\n/g, ' ').split(' ');
            words.forEach((word) => {
                if (!records.hasOwnProperty(word))
                    records[word] = 0;
                records[word]++;
            });
        }
    });

    return records;
}

console.log(walk('./testdata'));
