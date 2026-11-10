# Text File Analyzer

A C++ console application for reading, analyzing, processing and writing text files.

## Project Overview

The program reads text from `input.txt`, performs basic text analysis and saves the processed content to `output.txt`.

The project demonstrates file handling with C++ streams and string processing.

## Implemented Features

### 1. File Reading

- Opens `input.txt` using `std::ifstream`.
- Reads the file line by line with `std::getline()`.
- Counts the number of lines read from the input file.

### 2. Text Processing

- Searches for the longest word in the text.
- Replaces numeric characters (`0–9`) with the `*` symbol.
- Attempts to remove empty lines from the processed output.

### 3. File Writing

- Creates `output.txt` using `std::ofstream`.
- Writes the processed text to the output file.
- Appends the number of lines and the longest word as statistics.

## Output Format

The end of the output file contains statistics in the following format:

```text
Количество строк: [число]
Самое длинное слово: [слово]
```

## Project Structure

```text
cpp-text-file-analyzer/
├── README.md
├── input.txt
├── output.txt
└── src/
    └── main.cpp
```

`input.txt` is the source text file. `output.txt` is generated when the program runs.

## Technologies

- C++
- `std::ifstream`
- `std::ofstream`
- `std::string`
- `std::getline()`
- Text processing
- File input/output

## Current Limitations

The current implementation is an educational version and has several limitations:

- The program does not check whether the input file was opened successfully.
- The empty-line condition checks `line.length() == 1` instead of checking for an empty string. As a result, truly empty lines are not removed, while lines containing one character are skipped.
- The longest-word search uses only the space character as a separator. Tabs and punctuation are not handled as word boundaries.
- Punctuation remains attached to words.
- The longest word is searched after digit replacement.
- The line counter includes all lines read from the input file, including lines omitted from the output.
- The program does not report file-writing errors.

## Learning Objectives

- Working with text files in C++.
- Using input and output file streams.
- Reading files line by line.
- Processing strings and searching for words.
- Replacing characters in text.
- Collecting and displaying text statistics.

## Future Improvements

- Add checks for successful file opening and writing.
- Correct empty-line filtering.
- Handle whitespace characters as word separators.
- Improve word extraction and punctuation handling.
- Define whether the longest word should be searched in the original or processed text.
- Add command-line arguments for input and output file paths.
- Handle text encoding and Unicode characters more explicitly.
