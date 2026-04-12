package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	fin, err := os.Open("input.txt")
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error: cannot open input.txt\n")
		os.Exit(1)
	}
	defer fin.Close()

	fout, err := os.Create("output.txt")
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error: cannot create output.txt\n")
		os.Exit(1)
	}
	defer fout.Close()

	q, err := NewQueue()
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error: cannot create queue\n")
		os.Exit(1)
	}
	defer q.Close()

	scanner := bufio.NewScanner(fin)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}

		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}

		cmd := parts[0]

		switch cmd {
		case "push":
			val, _ := strconv.Atoi(parts[1])
			if err := q.Push(val); err == nil {
				fmt.Fprintf(fout, "push %d done\n", val)
			} else {
				fmt.Fprintf(fout, "push failed\n")
			}

		case "pop":
			val, err := q.Pop()
			if err == nil {
				fmt.Fprintf(fout, "pop = %d\n", val)
			} else {
				fmt.Fprintf(fout, "pop: queue is empty\n")
			}

		case "peek":
			val, err := q.Peek()
			if err == nil {
				fmt.Fprintf(fout, "peek = %d\n", val)
			} else {
				fmt.Fprintf(fout, "peek: queue is empty\n")
			}

		case "size":
			fmt.Fprintf(fout, "size = %d\n", q.Size())

		case "empty":
			if q.IsEmpty() {
				fmt.Fprintf(fout, "empty = yes\n")
			} else {
				fmt.Fprintf(fout, "empty = no\n")
			}

		case "clear":
			q.Clear()
			fmt.Fprintf(fout, "clear done\n")

		case "print":
			fmt.Fprintf(fout, "%s\n", q.String())

		case "destroy":
			q.Clear()
			fmt.Fprintf(fout, "destroy done\n")

		default:
			fmt.Fprintf(fout, "Unknown command: %s\n", cmd)
		}
	}
}
