package main

import "os"
import "fmt"
import "strings"
import "io/ioutil"
import "path/filepath"

func main() {
    records := make(map[string]int)

    filepath.Walk("./testdata",
        func(path string, info os.FileInfo, e error) error {
            if info.Mode().IsRegular() {
                buf, _ := ioutil.ReadFile(path)
                words := strings.Fields(string(buf))
                for _, word := range words {
                    records[word]++
                }
            }
            return nil
        })

    for word, count := range records {
        fmt.Printf("%s: %d\n", word, count)
    }
}
