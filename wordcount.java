import java.util.*;
import java.io.*;
import java.nio.file.*;

class WordCount {
	public static void main(String[] args) throws IOException {
		HashMap<String, Integer> records = new HashMap<String, Integer>();

		Files.walk(Paths.get("./testdata")).filter(Files::isRegularFile).forEach((f) -> {
			try {
				Scanner sc = new Scanner(new File(f.toString()));
				while (sc.hasNext()) {
					for (String word : sc.nextLine().split("\\s")) {
						records.putIfAbsent(word, 0);
						records.put(word, records.get(word) + 1);
					}
				}
				sc.close();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		});

		records.forEach((k, v) -> System.out.println(k + ": " + v));
	}
}