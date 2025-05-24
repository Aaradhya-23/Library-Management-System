#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <sstream>


using namespace std;


class Book{
    public:
    string title, author, publisher, ISBN;
    int year;
    int status; // 0 - borrowed, 1- availabe , 2- reserved
    string issuedto;// - if it is available, else userid
    string issuedate;
};

class Library {
    private:
        string fname = "books_data.csv";
    
    public:
        string getFileName() const { return fname; }

        void loadBooksFromCSV() {
            ifstream file(fname);
            if (!file.is_open()) {
                cout << "Error: Could not open " << fname << "!\n";
                return;
            }
    
            string line;
            while (getline(file, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                string title, author, isbn, publisher, yearStr, statusStr, issuedTo, issuedDate;
    
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, isbn, ',');
                getline(ss, publisher, ',');
                getline(ss, yearStr, ',');
                getline(ss, statusStr, ',');
                getline(ss, issuedTo, ',');
                getline(ss, issuedDate, ',');
    
            }
            file.close();
        }
    
        void display_all_books() {
            ifstream file(fname);
            if (!file.is_open()) {
                cout << "Error opening " << fname << "!\n";
                return;
            }
    
            cout << "\n--------------BOOKS LIST--------------\n";
            string line;
            int book_number = 0;
    
            while (getline(file, line)) {
                if (line.empty()) continue;
                stringstream ss(line);
                string title, author, isbn, publisher, yearStr, statusStr, issuedTo, issuedDate;
                int year, status;
    
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, isbn, ',');
                getline(ss, publisher, ',');
                getline(ss, yearStr, ',');
                getline(ss, statusStr, ',');
                getline(ss, issuedTo, ',');
                getline(ss, issuedDate, ',');
    
                try {
                    year = stoi(yearStr);
                    status = stoi(statusStr);
                } catch (...) {
                    cerr << "Error converting numeric fields for book: " << title << "\n";
                    continue;
                }    
    
                book_number++;
                cout << "\nBook " << book_number << "\n";
                cout << "Title      : " << title << "\n";
                cout << "Author     : " << author << "\n";
                cout << "ISBN       : " << isbn << "\n";
                cout << "Publisher  : " << publisher << "\n";
                cout << "Year       : " << year << "\n";
                cout << "Status     : " << (status == 1 ? "Available" : (status == 0 ? "Borrowed" : "Reserved")) << "\n";
                if (status == 0) {
                    cout << "Issued To  : " << issuedTo << "\n";
                    cout << "Issued Date: " << issuedDate << "\n";
                }
            }
            file.close();
        }
    
        void add_books() {
            string title, author, isbn, publisher;
            int year, status;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            cout << "Enter Publisher: ";
            getline(cin, publisher);
            cout << "Enter Year: ";
            cin >> year;
            cout << "Enter Status (1=Available, 0=Borrowed, 2=Reserved): ";
            cin >> status;
    
            ofstream file(fname, ios::app);
            if (!file) {
                cerr << "Error: Unable to open " << fname << "!\n";
                return;
            }
            file << title << "," << author << "," << isbn << "," << publisher << "," << year << "," << status << ",-,-\n";
            file.close();
            cout << "Book added successfully!\n";
        }
       
        void updateBookStatus(const string& isbn, int newStatus, const string& issuedTo, const string& issuedDate) { 
            // this func changes status,issuedto, issuedate of the book after returning book or borrowing the book
            vector<string> lines;
            ifstream file(fname);
            if (!file) {
                cerr << "Error: Could not open " << fname << " for updating!\n";
                return;
            }
            
            string line;
            while (getline(file, line)) {
                if(line.empty()) continue;
                stringstream ss(line);
                string title, author, bookIsbn, publisher, yearStr, statusStr, currentIssuedTo, currentIssuedDate;
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, bookIsbn, ',');
                getline(ss, publisher, ',');
                getline(ss, yearStr, ',');
                getline(ss, statusStr, ',');
                getline(ss, currentIssuedTo, ',');
                getline(ss, currentIssuedDate, ',');
            
                if (bookIsbn == isbn) {
                    stringstream updatedLine;
                    updatedLine << title << "," << author << "," << isbn << "," << publisher << "," 
                                << yearStr << "," << newStatus << "," << issuedTo << "," << issuedDate;
                    lines.push_back(updatedLine.str());
                } else {
                    lines.push_back(line);
                }
            }
            file.close();
            
            ofstream outFile(fname);
            for (const auto& updatedLine : lines) {
                outFile << updatedLine << "\n";
            }
            outFile.close();
        }
        
        void update_books() {
            cout << "Enter ISBN of the book to update: ";
            string searchISBN;
            //cin.ignore();
            getline(cin, searchISBN);
    
            vector<string> lines;
            bool found = false;
    
            ifstream file(fname);
            if (!file.is_open()) {
                cerr << "Error: Unable to open " << fname << "!\n";
                return;
            }
    
            string line;
            while (getline(file, line)) {
                if(line.empty()) continue;
                stringstream ss(line);
                string title, author, isbn, publisher, yearStr, statusStr, issuedTo, issuedDate;
                
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, isbn, ',');
                getline(ss, publisher, ',');
                getline(ss, yearStr, ',');
                getline(ss, statusStr, ',');
                getline(ss, issuedTo, ',');
                getline(ss, issuedDate, ',');
               
                if (isbn == searchISBN) {
                    found = true;
    
                    cout << "Enter New Title: ";
                    getline(cin, title);
                    cout << "Enter New Author: ";
                    getline(cin, author);
                    cout << "Enter New Publisher: ";
                    getline(cin, publisher);
                    cout << "Enter New Year: ";
                    cin >> yearStr;
                    cout << "Enter New Status (1=Available, 0=Borrowed, 2=Reserved): ";
                    cin >> statusStr;
                    cin.ignore();
                }
    
                stringstream updatedLine;
                updatedLine << title << "," << author << "," << isbn << "," << publisher << "," << yearStr << ","
                            << statusStr << "," << issuedTo << "," << issuedDate;
                lines.push_back(updatedLine.str());
            }
    
            file.close();
    
            ofstream outFile(fname);
            for (const string& updatedLine : lines) {
                outFile << updatedLine << "\n";
            }
            outFile.close();
    
            if (found) {
                cout << "Book updated successfully.\n";
            } else {
                cout << "Book with ISBN " << searchISBN << " not found.\n";
            }
    }
        
        void remove_books() {
            cout << "Enter ISBN of the book to remove: ";
            string searchISBN;
            
            getline(cin, searchISBN);

            vector<string> lines;
            bool found = false;

            ifstream file(fname);
            if (!file.is_open()) {
                cerr << "Error: Unable to open " << fname << "!\n";
                return;
            }

            string line;
            while (getline(file, line)) {
                if(line.empty()) continue;
                stringstream ss(line);
                string title, author, isbn, publisher, yearStr, statusStr, issuedTo, issuedDate;
                int year,status;
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, isbn, ',');
                getline(ss, publisher, ',');
                getline(ss, yearStr, ',');
                getline(ss, statusStr, ',');
                getline(ss, issuedTo, ',');
                getline(ss, issuedDate, ',');
                year = stoi(yearStr);
                status = stoi(statusStr);
                if (isbn == searchISBN) {
                    found = true;
                    cout << "Book '" << title << "' removed from library.\n";
                    continue; // Skip adding this line back into file
                }

                lines.push_back(line);
            }

            file.close();

            ofstream outFile(fname);
            for (const string& updatedLine : lines) {
                outFile << updatedLine << "\n";
            }
            outFile.close();

            if (!found) {
                cout << "Book with ISBN " << searchISBN << " not found.\n";
            }
        }
    };

class Account {
    private:
        string userID;
        string userType; // "Student" or "Faculty" or "Librarian"
    
        struct BookRecord {
            string isbn;
            time_t borrowedDate;
            time_t dueDate;
            time_t returnedDate; // 0 if not returned yet
        };
    
        vector<BookRecord> borrowedBooks; //contains currently borrowed books
        vector<BookRecord> history;       //contains books which are returned
        vector<BookRecord> reservedBooks; //contains books which are reserved
        int fineAmount;
    
    public:
        Account(string id, string type) : userID(id), userType(type), fineAmount(0) {
            loadFromFile();
            calculateOverdueFines();
        }
        
       
        void borrowBook(string isbn, Library& library) {
            calculateOverdueFines();
            bool isAvailable = false;
            if (fineAmount > 0) {
                cout << "Unpaid fine of Rs " << fineAmount << " exists. Please pay before borrowing.\n";
                return;
            }
            ifstream file(library.getFileName());
            if (!file) {
                cerr << "Error: Could not open " << library.getFileName() << "!\n";
                return;
            }
        
            string line;
            while (getline(file, line)) {
                if (line.empty()) continue;
        
                stringstream ss(line);
                string title, author, bookIsbn, publisher, yearStr, statusStr, issuedUser, issuedDate;
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, bookIsbn, ',');
                getline(ss, publisher, ',');
                getline(ss, yearStr, ',');
                getline(ss, statusStr, ',');
                getline(ss, issuedUser, ',');
                getline(ss, issuedDate, ',');
        
                if (bookIsbn == isbn) {
                    if (stoi(statusStr) == 1) { // 1 means available
                        isAvailable = true;
                    }
                    break;
                }
            }
            file.close();

            if (!isAvailable) {
                cout << "Sorry, the book with ISBN " << isbn << " is already borrowed.\n";
                return;
            }
    
            int maxBooks = (userType == "Student") ? 3 : 5;
            if (borrowedBooks.size() >= maxBooks) {
                cout << "Borrowing limit reached (" << maxBooks << " books).\n";
                return;
            }
            // **Check for overdue books exceeding 60 days for faculty**
            time_t now = time(0);

            for (const auto& book : borrowedBooks) {
                double overdueDays = difftime(now, book.dueDate) / 86400; 
                if (overdueDays > 60 && userType == "Faculty") {
                    cout << "You have an overdue book for more than 60 days. Return it before borrowing new books.\n";
                    return;
                }
            }
            
            time_t due = now + ((userType == "Student") ? (15 * 86400) : (30 * 86400));
            
            BookRecord newBook = {isbn, now, due, 0};
            borrowedBooks.push_back(newBook);
            string currentDate = string(ctime(&now));
            library.updateBookStatus(isbn,0,userID,currentDate);
            
            cout << "Book " << isbn << " borrowed. Due date: " << ctime(&due);
    
            saveToFile();
        }
    
        void returnBook(string isbn, Library& library) {
            time_t now = time(0);
            for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
                if (it->isbn == isbn) {
                    int overdueDays = (now > it->dueDate) ? (now - it->dueDate) / 86400 : 0;
                    if (userType == "Student" && overdueDays > 0) {
                        fineAmount += overdueDays * 10;
                    }
    
                    it->returnedDate = now;
                    history.push_back(*it);
                    borrowedBooks.erase(it);
                    string currentDate = string(ctime(&now));
                    library.updateBookStatus(isbn,1,"-","-");
    
                    cout << "Book " << isbn << " returned. Overdue: " << overdueDays 
                         << " days. Current fine: Rs " << fineAmount << "\n";
    
                    saveToFile();
                    return;
                }
            }
            cout << "Book " << isbn << " not found in borrowed list.\n";
        }
        
        void reserveBook(Library& library, string isbn) {
            time_t now = time(0); 
            string currentDate = string(ctime(&now));
        
         
            int bookStatus = -1; 
            string issuedTo = "-";
        
            ifstream file(library.getFileName());
            if (!file) {
                cerr << "Error: Could not open " << library.getFileName() << "!\n";
                return;
            }
        
            string line;
            while (getline(file, line)) {
                if (line.empty()) continue;
        
                stringstream ss(line);
                string title, author, bookIsbn, publisher, yearStr, statusStr, issuedUser, issuedDate;
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, bookIsbn, ',');
                getline(ss, publisher, ',');
                getline(ss, yearStr, ',');
                getline(ss, statusStr, ',');
                getline(ss, issuedUser, ',');
                getline(ss, issuedDate, ',');
        
                if (bookIsbn == isbn) {
                    bookStatus = stoi(statusStr);
                    issuedTo = issuedUser;
                    break;
                }
            }
            file.close();
        
           
            if (bookStatus == -1) {
                cout << "Book with ISBN " << isbn << " not found in the library.\n";
                return;
            }
            if (bookStatus == 1) {
                cout << "Book is available and does not need a reservation.\n";
                return;
            }
            if (bookStatus == 2) {
                cout << "Book is already reserved by another user.\n";
                return;
            }
        
            cout << "Book " << isbn << " is currently borrowed. Reserving for user " << userID << "...\n";

            BookRecord reservedBook = {isbn, now, 0, 0}; // No due date, not returned
            reservedBooks.push_back(reservedBook);

            library.updateBookStatus(isbn, 2, userID, currentDate);
            saveToFile();  
        
            cout << "Book reservation successful!\n";
        }
        
        void displayAccount() {
            time_t now = time(0);
            cout << "\n=== Account Summary for User: " << userID << " (" << userType << ") ===\n";
    
            cout << "\nCurrently Borrowed Books:\n";
            if (borrowedBooks.empty()) cout << "None\n";
            for (const auto& book : borrowedBooks) {
                int overdueDays = (now > book.dueDate) ? (now - book.dueDate) / 86400 : 0;
                cout << "  " << book.isbn << " | Borrowed: " << ctime(&book.borrowedDate) 
                     << "Due: " << ctime(&book.dueDate)
                     << "Overdue: " << overdueDays << " days\n";
            }
            
            cout <<"\nReserved Books:\n";
            if(reservedBooks.empty()) cout <<"None\n";
            for (const auto& book : reservedBooks) {
                cout << "  " << book.isbn << " | Reserved On: " << ctime(&book.borrowedDate) << "\n";
            }

            cout << "\nBorrowing History (Returned Books):\n";
            if (history.empty()) cout << "None\n";
            for (const auto& book : history) {
                cout << "  " << book.isbn << " | Borrowed: " << ctime(&book.borrowedDate)
                     << "Returned: " << ctime(&book.returnedDate) << "\n";
            }
    
            cout << "\nTotal Fine: Rs " << fineAmount << "\n";
        }
    
        void payFine() {
            calculateOverdueFines();
    
            if (fineAmount == 0) {
                cout << "No outstanding fine to pay.\n";
                return;
            }
            cout << "Paid fine of Rs " << fineAmount << "\n";
            fineAmount = 0;
            saveToFile();
        }
    
        void calculateOverdueFines() {
            time_t now = time(0);
            fineAmount = 0;
    
            for (const auto& book : borrowedBooks) {
                if (now > book.dueDate && userType == "Student") {
                    fineAmount += ((now - book.dueDate) / 86400) * 10;
                }
            }
        }
    
        void saveToFile() {
            string filename = userID + "_account.csv";
            ofstream file(filename);
            if (!file.is_open()) return;
    
            for (const auto& book : borrowedBooks) {
                file << book.isbn << "," << book.borrowedDate << "," << book.dueDate << ",0\n";
            }
            for (const auto& book : history) {
                file << book.isbn << "," << book.borrowedDate << "," << book.dueDate << "," << book.returnedDate << "\n";
            }
            file << "FineAmount," << fineAmount << "\n";
            file.close();
        }
    
        void loadFromFile() {
            string filename = userID + "_account.csv";
            ifstream file(filename);
            if (!file.is_open()) return;
    
            borrowedBooks.clear();
            history.clear();
    
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string isbn, borrowStr, dueStr, returnStr;
    
                getline(ss, isbn, ',');
                getline(ss, borrowStr, ',');
                getline(ss, dueStr, ',');
                getline(ss, returnStr, ',');
    
                if (isbn == "FineAmount") {
                    fineAmount = stoi(borrowStr);
                    continue;
                }
    
                BookRecord record = {
                    isbn,
                    static_cast<time_t>(stoll(borrowStr)),
                    static_cast<time_t>(stoll(dueStr)),
                    static_cast<time_t>(stoll(returnStr))
                };
    
                if (record.returnedDate == 0) {
                    borrowedBooks.push_back(record);
                } else {
                    history.push_back(record);
                }
            }
            file.close();
        }
    
};
  
class User {    
        protected:
            string id;
            string name,role;
            string borrowed_books,overdue_days,fine;
        
        public:
        User(string userId, string userName, string userRole, string books, string days, string f) {
            id = userId;
            name = userName;
            role = userRole;
            borrowed_books = books;
            overdue_days = days;
            fine = f;
        }
        virtual ~User() {}  // Virtual destructor for polymorphic behavior

        virtual void dummy() {}  // Dummy virtual function (if needed)
    
        string getID() { return id; }
        string getRole() { return role; }
        string getName() { return name; }

        string getBorrowedBooks() { return borrowed_books; }
        string getOverdueDays() { return overdue_days; }
        string getFine() { return fine; }
        void setBorrowedBooks(string books) { borrowed_books = books; }
        void setOverdueDays(string days) { overdue_days = days; }
        void setFine(string f) { fine = f; }

       
};

class User_db {
    private:
        string fname = "user_data.csv"; 
    public:
        vector<User*> users;
        void loadUsersFromCSV(vector<User*>& users) {
        ifstream file(fname);
        if (!file.is_open()) {
            cerr << "Error: Could not open user data file.\n";
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, role, booksStr, overdueStr, fineStr;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, role, ',');
            getline(ss, booksStr, ',');
            getline(ss, overdueStr, ',');
            getline(ss, fineStr, ',');
    
            users.push_back(new User(id, name, role, booksStr, overdueStr, fineStr));
        }
        file.close();
        }
    
        void display_users() {
            ifstream file(fname);
            if (!file) {
                cerr << "Error: Unable to open user database.\n";
                return;
            }
            cout << "\n------------ USER LIST ------------\n";
            string line;
            while (getline(file, line)) {
                cout << line << "\n";
            }
            file.close();
        }
    
        void add_user() {
            
            string id,name, role;
            string borrowed_books = "0", overdue_days = "0", fine = "0";
            cout << "Enter User ID: ";
            //cin.ignore();
            getline(cin,id);
            cout << "Enter User Name: ";
            getline(cin, name);
            cout << "Enter User Type (Student/Faculty/Librarian): ";
            getline(cin, role);
    
            ofstream file(fname, ios::app);
            if (!file) {
                cerr << "Error: Unable to open user database.\n";
                return;
            }
            file << id << "," << name << "," << role << ","
                 << borrowed_books << "," << overdue_days << "," << fine << "\n";
    
            file.close();
            cout << "User added successfully with ID: " << id << "\n";
        }
    
        void update_user() {
            string search_id;
            cout << "\nEnter User ID to update: ";
            cin >> search_id;
    
            ifstream filei(fname);
            ofstream tempFile("temp.csv");
            if (!filei || !tempFile) {
                cout << "Error: Unable to access user database.\n";
                return;
            }
    
            string id, name, type,borrowed_books,overdue_days,fine;
            bool found = false;
            string line;
            while (getline(filei, line)) {
                stringstream ss(line);
                getline(ss, id, ',');
                getline(ss, name, ',');
                getline(ss, type, ',');
                getline(ss, borrowed_books, ',');
                getline(ss, overdue_days, ',');
                getline(ss, fine, ',');
    
                if (id == search_id) {
                    found = true;
                    cout << "\nUpdating user with ID: " << id << "\n";
                    cout << "Enter New Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "\nEnter New Type (Student/Faculty): ";
                    getline(cin, type);
                    cout << "\nEnter no. of borrowed books: ";
                    getline(cin, borrowed_books);
                    cout << "\nEnter no. of overdue days: ";
                    getline(cin, overdue_days);
                    cout << "\n Enter fine amount: ";
                    getline(cin,fine);
    
                }
                tempFile << id << "," << name << "," << type << ","
                << borrowed_books << "," << overdue_days << "," << fine << "\n";
            }
    
            filei.close();
            tempFile.close();
    
            if (found) {
                remove(fname.c_str());
                rename("temp.csv", fname.c_str());
                cout << "\n User details updated successfully.\n";
            } else {
                remove("temp.csv");
                cout << "\n User ID not found. No changes made.\n";
            }
        }
    
        void delete_user() {
            string search_id;
            cout << "\nEnter User ID to delete: ";
            cin >> search_id;
        
            ifstream filei(fname);
            ofstream tempFile("temp.csv");
        
            if (!filei || !tempFile) {
                cout << "Error: Unable to access user database.\n";
                return;
            }
        
            string line;
            bool found = false;
        
            while (getline(filei, line)) {
                stringstream ss(line);
                string id, name, type, borrowed_books, overdue_days, fine;
        
                // Read CSV values
                getline(ss, id, ',');
                getline(ss, name, ',');
                getline(ss, type, ',');
                getline(ss, borrowed_books, ',');
                getline(ss, overdue_days, ',');
                getline(ss, fine, ',');
        
                if (id == search_id) {
                    found = true;
                    cout << "\nUser '" << name << "' (ID: " << id << ") has been removed.\n";
                    continue;  // Skip writing this user to the new file
                }
        
                tempFile << line << "\n";  // Write valid users back
            }
        
            filei.close();
            tempFile.close();
        
            if (found) {
                remove(fname.c_str());
                rename("temp.csv", fname.c_str());
            } else {
                remove("temp.csv");
                cout << "\nUser ID not found. No changes made.\n";
            }
        }
        
        void syncUserData() {
            for (User* user : users) {
                string accountFile = user->getID() + "_account.csv";
                ifstream file(accountFile);
                int borrowed_count = 0;
                int total_overdue_days = 0;
                int fine_amount = 0;
                time_t now = time(0);
        
                if (file.is_open()) {
                    string line;
                    while (getline(file, line)) {
                        if (line.empty()) continue;
                        // Check for the FineAmount line
                        if (line.find("FineAmount") != string::npos) {
                            size_t pos = line.find(',');
                            if (pos != string::npos) {
                                string fine_val = line.substr(pos + 1);
                                fine_amount = stoi(fine_val);
                            }
                        } else {
                            stringstream ss(line);
                            string isbn, borrowedStr, dueStr, returnedStr;
                            getline(ss, isbn, ',');
                            getline(ss, borrowedStr, ',');
                            getline(ss, dueStr, ',');
                            getline(ss, returnedStr, ',');
                            // Count only active borrowed books (returnedDate == "0")
                            if (returnedStr == "0") {
                                borrowed_count++;
                                // Calculate overdue days if the current time is past the due date.
                                time_t due = stoll(dueStr);
                                if (now > due) {
                                    int overdue_days = (now - due) / 86400; // Convert seconds to days
                                    total_overdue_days += overdue_days;
                                }
                            }
                        }
                    }
                    file.close();
                }
        
                // Update the User object with new values (converted to string).
                user->setBorrowedBooks(to_string(borrowed_count));
                user->setOverdueDays(to_string(total_overdue_days));
                user->setFine(to_string(fine_amount));
            }
        
            // Rewrite the entire user_data.csv file with updated user information.
            ofstream outfile(fname);
            if (!outfile.is_open()) {
                cerr << "Error: Could not open " << fname << " for writing.\n";
                return;
            }
            for (User* user : users) {
                outfile << user->getID() << "," << user->getName() << "," << user->getRole()
                        << "," << user->getBorrowedBooks() << "," 
                        << user->getOverdueDays() << "," 
                        << user->getFine() << "\n";
            }
            outfile.close();
            cout << "User data synchronized successfully.\n";
        }
    };
    
class Student : public User {
    private:
        Account studentAccount;
        Library& library; 
        User_db &userDb;
    
    public:
        Student(string id, string name, string role, string books, string days, string fine, Library& lib, User_db& udb)
            : User(id, name, role, books, days, fine), studentAccount(id, "Student"), library(lib), userDb(udb) {}
    
        void menu() {
            int choice = 0;
            while (true) {
                cout << "\n\n------------- STUDENT MENU ------------\n\n";
                cout << "1. See all books\n";
                cout << "2. Request (Borrow) a book\n";
                cout << "3. Reserve a book\n";
                cout << "4. Return book\n";
                cout << "5. View borrowing history\n";
                cout << "6. Pay fine\n";
                cout << "7. Logout\n";
                cout << "Enter choice: ";
                cin >> choice;
    
                if (choice == 1) {
                    library.display_all_books();
                } 
                else if (choice == 2) {
                    borrowBook();
                } 
                else if (choice == 3) {
                    reserveBook();
                } 
                else if (choice == 4) {
                    returnBook();
                } 
                else if (choice == 5) {
                    viewHistory();
                } 
                else if (choice == 6) {
                    payFine();
                } 
                else if (choice == 7) {
                    cout << "Logging out...\n";
                    break;
                } 
                else {
                    cout << "Invalid choice! Try again.\n";
                }
            }
        }
    
        void borrowBook() {
            string isbn;
            cout << "Enter ISBN to borrow: ";
            cin >> isbn;
            studentAccount.borrowBook(isbn, library);
            userDb.syncUserData();
        }
    
        void returnBook() {
            string isbn;
            cout << "Enter ISBN to return: ";
            cin >> isbn;
            studentAccount.returnBook(isbn, library);
            userDb.syncUserData();
        }
    
        void reserveBook(){
            string isbn;
            cout << "Enter ISBN to reserve: ";
            cin >> isbn;
            studentAccount.reserveBook(library,isbn);
        }

        void viewHistory() {
            studentAccount.displayAccount();
        }
     
        void payFine() {
            studentAccount.payFine();
            userDb.syncUserData();
        }
    };
    
class Faculty : public User {
        private:
            Account facultyAccount;
            Library& library; 
            User_db &userDb;
        
        public:
            Faculty(string id, string name, string role, string books, string days, string fine, Library& lib,User_db& udb)
                : User(id, name, role, books, days, fine), facultyAccount(id, "Faculty"), library(lib), userDb(udb) {}
        
            void menu() {
                int choice = 0;
                while (true) {
                    cout << "\n\n-------- FACULTY MENU --------\n";
                    cout << "1. See all books\n";
                    cout << "2. Request (Borrow) a book\n";
                    cout << "3. Reserve a book\n";
                    cout << "4. Return book\n";
                    cout << "5. View borrowing history\n";
                    cout << "6. Logout\n";
                    cout << "Enter choice: ";
                    cin >> choice;

                    if(choice == 1){
                        library.display_all_books();
                    }
                    else if (choice == 2) {
                        borrowBook();
                    } 
                    else if (choice == 3) {
                        reserveBook();
                    } 
                    else if (choice == 4) {
                        returnBook();
                    } 
                    else if (choice == 5) {
                        viewHistory();
                    } 
                    else if (choice == 6) {
                        cout << "Logging out...\n";
                        break;  
                    } 
                    else {
                        cout << "Invalid choice! Try again.\n";
                    }
                }
            }
        
            void borrowBook() {
                string isbn;
                cout << "Enter ISBN to borrow: ";
                cin >> isbn;
                facultyAccount.borrowBook(isbn, library);
                userDb.syncUserData();
            }
        
            void returnBook() {
                string isbn;
                cout << "Enter ISBN to return: ";
                cin >> isbn;
                facultyAccount.returnBook(isbn, library);
                userDb.syncUserData();
            }
            
            void reserveBook(){
                string isbn;
                cout << "Enter ISBN to reserve: ";
                cin >> isbn;
                facultyAccount.reserveBook(library,isbn);
            }

            void viewHistory() {
                facultyAccount.displayAccount();
            }
        };

class Librarian : public User {
    private:
        Library &library;
        User_db &userDb;
    
    public:
        Librarian(string id, string name,Library &lib, User_db &udb)
            : User(id, name, "Librarian", "0", "0", "0"), library(lib), userDb(udb) {}
    
        void menu() {
            while (true) {
                cout << "\n\n------------ LIBRARIAN MENU ------------\n\n";
                cout << "1. See all books\n";
                cout << "2. See User List\n";
                cout << "3. Add Book\n";
                cout << "4. Update Existing Book\n";
                cout << "5. Remove Book\n";
                cout << "6. Add User\n";
                cout << "7. Delete User\n";
                cout << "8. Update Existing User\n";
                cout << "9. Logout\n";
                cout << "Enter choice: ";
                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    library.display_all_books();
                } 
                else if (choice == 2) {
                    userDb.display_users();
                } 
                else if (choice == 3) {
                    library.add_books();
                } 
                else if (choice == 4) {
                    library.update_books();
                } 
                else if (choice == 5) {
                    library.remove_books();
                } 
                else if (choice == 6) {
                    userDb.add_user();
                } 
                else if (choice == 7) {
                    userDb.delete_user();
                } 
                else if (choice == 8) {
                    userDb.update_user();
                } 
                else if (choice == 9) {
                    cout << "Logging out...\n";
                    break;  
                } 
                else {
                    cout << "Invalid choice! Try again.\n";
                }
            }
        }
    
};  

int main() {
        Library library;
        User_db userDb;
    
        library.loadBooksFromCSV();
    
        userDb.loadUsersFromCSV(userDb.users);
    
        cout << "\n----- Welcome to Library Management System -----\n";
        string enteredID, enteredPassword;
        cout << "Enter User ID to login: ";
        cin >> enteredID;
    
        User* loggedInUser = nullptr;
        for (User* user : userDb.users) {
            if (user->getID() == enteredID) {
                loggedInUser = user;
                break;
            }
        }

    if (!loggedInUser) {
        cout << "User not found! Exiting...\n";
        return 0;
    }
    cout << "Enter Password: ";
    cin >> enteredPassword;

    if (enteredPassword != loggedInUser->getName()) {  
        cout << "Incorrect password! Exiting...\n";
        return 0;
    }
    cout << "\n****** Welcome "<< loggedInUser->getName() <<" ******\n";

    if (loggedInUser->getRole() == "Student") {
        Student student(loggedInUser->getID(), loggedInUser->getName(), "Student",
                        loggedInUser->getBorrowedBooks(), loggedInUser->getOverdueDays(),
                        loggedInUser->getFine(), library,userDb);
        
        student.menu();
    } 
    else if (loggedInUser->getRole() == "Faculty") {
        Faculty faculty(loggedInUser->getID(), loggedInUser->getName(), "Faculty",
                        loggedInUser->getBorrowedBooks(), loggedInUser->getOverdueDays(),
                        loggedInUser->getFine(), library,userDb);
        faculty.menu();
    } 
    else if (loggedInUser->getRole() == "Librarian") {
        Librarian librarian(loggedInUser->getID(), loggedInUser->getName(), library, userDb);
        librarian.menu();
    }

    for (User* user : userDb.users) {
        delete user;  // Clean up memory
    }
    
        cout << "\n-------- Thank you for using the Library Management System. Goodbye! ----------\n";
    
    return 0;
}
    
