// At the time of writing the "walking directory" feature has not been included in (stable) Rust standard library.
// Here I'm using a third-party crate "walkdir" for such functionality.

use std::collections::HashMap;
use std::fs::File;
use std::io::Read;
use walkdir::WalkDir;

fn main() -> Result<(), std::io::Error> {
    let mut records: HashMap<String, u32> = HashMap::new();

    for entry in WalkDir::new("testdata") {
        let entry = entry?;
        if entry.metadata()?.is_file() {
            let mut file = File::open(entry.path())?;
            let mut content = String::new();
            file.read_to_string(&mut content)?;
            for word in content.split_whitespace() {
                records
                    .entry(word.to_string())
                    .and_modify(|count| *count += 1)
                    .or_insert(1);
            }
        }
    }

    for (word, count) in &records {
        println!("{} : {}", word, count);
    }

    Ok(())
}
