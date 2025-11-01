package main

import (
	"bufio"
	"context"
	"fmt"
	"log"
	"os"
	"strings"
	"time"

	"github.com/joho/godotenv"
	"google.golang.org/api/docs/v1"
	"google.golang.org/api/option"
)

func main() {
	ctx := context.Background()
	service, err := docs.NewService(ctx, option.WithCredentialsFile("todo.json"))
	if err != nil {
		log.Fatal(err)
	}
	err = godotenv.Load()
	if err != nil {
		log.Fatal("Error loading .env file")
	}
	docID := os.Getenv("docID")

	fp, err := os.Open("task.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer fp.Close()
	// creating a slice contains line
	tasks := []string{}
	scanner := bufio.NewScanner(fp)
	for scanner.Scan() {
		tasks = append(tasks, scanner.Text())
	}
	if err := scanner.Err(); err != nil {
		log.Fatalf("Error reading tasks file: %v", err)
	}

	newTaskLine := time.Now().Format("02 Jan 2006")
	finalLine := newTaskLine + "\n\n" + strings.Join(tasks, "\n") + "\n"

	reqs := []*docs.Request{
		{
			InsertText: &docs.InsertTextRequest{
				Location: &docs.Location{
					Index: 1,
				},

				Text: finalLine,
			},
		},
	}

	batch := &docs.BatchUpdateDocumentRequest{
		Requests: reqs,
	}

	_, err = service.Documents.BatchUpdate(docID, batch).Do()
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("File Uploaded Successfully")
	fmt.Printf("Visit: https://docs.google.com/document/d/%s/\n", docID)
}
