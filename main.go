package main

import (
	"fmt"
	"io"
	"log"
	"os"
)

func main() {
	fp, err := os.Open("task.txt")
	if err != nil {
		log.Fatal(err)
	}
	readerbytes, err := io.ReadAll(fp)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(string(readerbytes))
}
