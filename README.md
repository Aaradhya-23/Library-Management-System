# Library-Management-System
Overview

This is a Library Management System developed in C++ as part of my CS253 coursework during the fourth semester. The entire application is contained within a single file, Library_system.cpp. The system supports basic library operations, such as managing books and users, borrowing/returning books, and updating user accounts with borrowed book counts, overdue days, and fines.

Features
User Management:
    User login based on User ID.
    Different user types: Student, Faculty, and Librarian.
Book Management:
    Add, update, remove, and view books.
    Borrow ,return and reserve books.
Account Management:
    Maintain an account file for each user (e.g., 101_account.csv) that stores detailed transaction history.
    user_data.csv that stores user information and counters (borrowed books, overdue days, and fine amounts).

File structure
Library_system.cpp:
    Contains the complete source code for the Library Management System. This file includes all the classes and functions needed for managing books, user accounts, and the overall system logic.
CSV Data Files:
    user_data.csv: A master file containing user information in form id,name,usertype,no of borrowed books, no of overdues days,fine .
    books.csv: A file that holds the library's book inventory.
    Individual account files: Files named <UserID>_account.csv that store each user's borrowing history and fine details.

Note-
- Temporary Files:  
  The file `temp.csv` is used internally during certain operations (like updating or deleting user data).
- User Account Files:  
  Files such as `101_account.csv` are generated automatically at runtime when a user logs in or performs an operation.

Requirements
A C++ compiler supporting C++11 or later (e.g., g++, clang++).
Standard C++ libraries (iostream, fstream, sstream, vector, etc.).
CSV files for data storage (ensure that user_data.csv and books.csv exist in the same directory as the executable).

Compilation
To compile the project, run the following command from the terminal:
```sh
    g++ -o Library_system Library_system.cpp
```
Running:
   ```sh
 ./Library_system
```


Workflow
User Login:
    When the program starts, we'll be prompted to enter User ID to log in. After entering correct user id , we have to enter password which is saved as username in user_data.csv.
Role-Specific Menus:
    Student/Faculty:
    Access options to see all the books,borrow books , return books , reserve books, view your account, and pay fines.
    Librarian:
    Manage the library’s book inventory and update user records.
Data Synchronization:
    After each operation (such as borrowing or returning a book), the system updates the master user database (user_data.csv) by reading the individual account files.
