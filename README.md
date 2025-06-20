# Binary Search Tree (BST) Student Record Management System

This project is a C++ application developed for the UCCD1024 Data Structures and Algorithmic Problem Solving course. It demonstrates the implementation and manipulation of Binary Search Trees (BSTs) for efficient storage and retrieval of student records. 

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Error Handling](#error-handling)
- [Known Errors and Bugs](#known-errors-and-bugs)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Features

This application handles student records stored in a Binary Search Tree, with the student ID as the key for the BST.  The following functionalities are implemented:

* **Read Data to BST**: Reads student records from a text file (`student.txt`) and stores them in a BST.  It prints the number of successfully read records and returns `false` if the file cannot be opened. 
* **Print Deepest Nodes**: Finds and prints the student IDs of all nodes at the deepest level of the BST. 
* **Display Student Information**: Traverses the BST recursively and prints all student information (name, ID, address, DOB, phone number, course, and CGPA).  It supports both ascending (order = 1) and descending (order = 2) order based on student ID, and output can be directed to the screen (source = 1) or a file named "student-info.txt" (source = 2). 
* **Clone Subtree**: Clones a subtree from an existing BST (`t1`) where the root of the subtree matches a specified student ID (`item`).  The original tree (`t1`) remains unchanged, and the cloned subtree (`t2`) must be empty before the cloning operation.  It prints both `t1` and `t2` using `preOrderPrint()` after the operation, and handles cases where `t1` is empty or the item is not found. 
* **Print Level Nodes**: Prints the student IDs of nodes level by level within the BST. 
* **Print Path**: Prints all external paths (paths from the root to leaf nodes) in the BST, showing the student IDs along each path. 
* **Interactive Menu**: Provides a command-line menu for users to interact with the application and select various functions. 

## Getting Started

### Prerequisites

* Microsoft Visual Studio 2022 

### Installation

1.  Clone the repository:
    ```bash
    git clone <repository_url>
    ```
2.  Open the project in Microsoft Visual Studio 2022. 
3.  Build the solution.

## Usage

Run the compiled executable. A menu will be displayed, allowing you to choose from various operations: 

1.  Read data to BST 
2.  Print deepest nodes 
3.  Display student 
4.  Clone Subtree 
5.  Print Level Nodes 
6.  Print Path 
7.  Exit 

A sample input text file `student.txt` is provided in the `sample textfile` folder. 

## Project Structure

The project will typically include:

* `main.cpp`: Contains the `readFile` function and the `menu` function, orchestrating the application flow. 
* `BST.h` / `BST.cpp`: Defines the `BST` class and implements its member functions such as `deepestNodes()`, `display()`, `CloneSubtree()`, `printLevelNodes()`, and `printPath()`. 
* `Student.h` / `Student.cpp`: Defines the `Student` class/struct to hold individual student records, including attributes like `id`, `name`, `address`, `DOB`, `phone number`, `course`, and `cgpa`. 

## Contributing

This project was developed as a university assignment. While direct contributions are not expected, any feedback or suggestions are welcome.

## License

This project is not publicly licensed as it is a university assignment.

## Acknowledgments

* Universiti Tunku Abdul Rahman Data Structure and Algorithmic Problem Solving Course Material 
* Microsoft Visual Studio 

---
**Group Members:**

* Stanley Chew Jun Xian
* Chong Jian Yi
* Fun Yong Qi
* Aiden Ting Sing Soon