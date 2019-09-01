const fs = require('fs');
const path = require('path');

function walk(dir, records) {
    records = records || {};

    fs.readdirSync(dir).forEach((f) => {
        const entry = path.join(dir, f);
        const stat = fs.statSync(entry);
        if (stat && stat.isDirectory()) {
            walk(entry, records);
        } else {
            const content = fs.readFileSync(entry, 'utf8');
            const words = content.replace(/\n/g, ' ').split(' ');
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
