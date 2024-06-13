#C Header Analyzer

This repository contains code for a C program that analyzes header file inclusions encoded in assignment.c file.

    Identifies header files within the given directory structure.
    Parses #include directives in source code files.
    Reports included header files for each source file processed.

Usage

    Clone this repository to your local machine.
    Build the program using a C compiler (e.g., gcc header_analyzer.c -o header_analyzer).
    Run the program by providing the directory path as an argument:

Bash 
./header_analyzer src/

This will analyze header file inclusions within the src directory and its subdirectories.
Code Structure

The code consists of the following functions:

    isHeaderFile: Checks if the provided filename has the .h extension.
    analyzeSourceFile: Opens a source file, reads line by line, and identifies any #include directives, reporting the included header files.
    traverseDirectory: Recursively iterates through a directory, processing source code files and subdirectories.
    main: Parses command-line arguments, validates input, and initiates the directory traversal process.

Optimization Note

This implementation prioritizes clarity and readability over potential micro-optimizations. However, it ensures safe bounds checking by using sizeof(line) within fgets.
