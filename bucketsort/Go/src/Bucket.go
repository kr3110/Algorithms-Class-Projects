package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

type bucketsort struct {
	size    int
	buckets []int
	values  []int
}

func (b *bucketsort) sort() {
	b.buckets = make([]int, b.size)
	for i := 0; i < len(b.values); i++ {
		b.buckets[b.values[i]]++
	}
}
func (b *bucketsort) print() {
	file, err := os.Create(os.Args[2])
	if err != nil {
		fmt.Println("error opening output file")
		return
	}
	defer file.Close()
	for i := 0; i < b.size; i++ {
		for b.buckets[i] > 0 {
			if b.buckets[i] != 0 {
				file.WriteString(strconv.Itoa(i))
				file.WriteString("\n")
			}
			b.buckets[i]--
		}
	}
}

func loadFile() (arr []int, max int, err error) {
	file, err := os.Open(os.Args[1])
	max = -1
	if err != nil {
		fmt.Println("error loading")
		fmt.Println(err)
		return arr, max, err
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanWords)

	for success := scanner.Scan(); success == true; success = scanner.Scan() {
		err = scanner.Err()
		if err != nil {
			fmt.Println(err)
		}
		x, _ := strconv.ParseInt(scanner.Text(), 10, 32)
		if max < int(x) {
			max = int(x)
		}
		arr = append(arr, int(x))
	}
	return arr, max, err
}

func main() {
	arr, max, err := loadFile()
	if err != nil {
		fmt.Println("error")
		fmt.Println(err)
		return
	}
	bucket := bucketsort{values: arr, size: max + 1}
	bucket.sort()
	bucket.print()
}
