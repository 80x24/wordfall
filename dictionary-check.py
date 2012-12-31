#!/usr/bin/python
import argparse

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("word", help="Check if it is a word")
	args = parser.parse_args()
	words = word_reader("/usr/share/dict/words")
	checkWord = args.word.lower()
	isWord = False
	for word in words:
		if checkWord == word:
			print "is a word"
			isWord = True
			break
	if isWord == False:
		print "Not a word"

def word_reader(filename):
	return (word.strip() for word in open(filename))

if __name__=="__main__":
	main()