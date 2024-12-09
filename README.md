# DSA Learning and Coding Workspace

Welcome to my DSA (Data Structures and Algorithms) learning and coding workspace! This repository serves as a hub for my coursework, including homework assignments (HW), Programming Assignments (PAs), and Labs (LABs). Below is an overview of the files and folders included in this workspace, along with their purposes.

## Repository Structure

```
/
├── 2024-fall-dsa/
│   ├── LAB1/
│   ├── LAB2/
│   ├── LAB3/
│   ├── LAB4/
│   ├── PA1/
│   ├── PA2/
│   ├── PA3/
│   └── PA4/
├── Sketch2View/
│   ├── [Code and Learning Materials for SRT Project]
├── .gitignore
├── bash.sh
├── compare.sh
├── delete.sh
├── gen.cpp
├── main.cpp
├── Makefile
└── test.cpp
```

### Files

- **`.gitignore`**: A configuration file used to specify files and directories that should be ignored by Git.

- **`bash.sh`**: A shell script for any custom commands or scripts I need to execute during my coding workflow.

- **`compare.sh`**: A script that automates the testing process. It runs `gen.cpp` to generate input, executes `main.cpp` and `test.cpp`, and compares their outputs, stopping when discrepancies are found.

- **`delete.sh`**: A script designed to clean up and delete specific files and `.Zone.Identifier` files that are created when copying files from Windows to my WSL (Windows Subsystem for Linux).

- **`gen.cpp`**: A utility to generate input files for testing purposes, ensuring a wide range of scenarios for my programs.

- **`main.cpp`**: The main file for my C++ coding exercises, serving as the entry point for my programs.

- **`Makefile`**: A Makefile specifically configured for building `main.cpp`. It simplifies the compilation process and manages dependencies.

- **`test.cpp`**: This file contains the correct implementation for a Programming Assignment (PA), used for comparison with my solutions.

- **`2024-fall-dsa/`**: This directory serves as my primary DSA repository, containing all relevant LABs and PAs (LAB 1-4 and PA 1-4).

- **`Sketch2View/`**: This folder is dedicated to my SRT (Sketch to View) project and includes associated code and learning materials.

## Usage

To use this workspace effectively:

1. Clone the repository to your local machine.
2. Navigate to the appropriate folder for the specific exercise (e.g., LABs or PAs).
3. Use the provided scripts (`compare.sh`, `delete.sh`, etc.) to automate processes as needed.
4. Modify and test your code in `main.cpp` and compare with `test.cpp`.
5. Use `gen.cpp` to generate various test inputs and ensure comprehensive testing.

## Additional Notes

While this workspace is primarily for my DSA studies, it is also flexible enough to accommodate other C++ programming projects by adjusting the Makefile and other scripts accordingly.

Feel free to explore and use any of the resources included here to enhance your learning experience in data structures and algorithms!
