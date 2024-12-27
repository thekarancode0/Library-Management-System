#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
using namespace std;

//structure
struct Book {
    int id;
    string title;
    string author;
    int copies;
};

// Function 
void addBook(vector<Book>& library);
void displayBooks(const vector<Book>& library);
void searchBook(const vector<Book>& library);
void loadLibraryFromFile(vector<Book>& library);
void saveLibraryToFile(const vector<Book>& library);
void clearScreen();

const string FILE_NAME = "library.txt"; 

int main() {
    vector<Book> library;
    //Load all the book at the starting
    loadLibraryFromFile(library);

    int choice;
    do {
        clearScreen(); 
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        clearScreen(); 
        switch (choice) {
            case 1:
                addBook(library);
                saveLibraryToFile(library); 
                break;
            case 2:
                displayBooks(library);
                break;
            case 3:
                searchBook(library);
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

        if (choice != 4) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get(); // Wait for the user to press Enter
        }

    } while (choice != 4);

    return 0;
}

void addBook(vector<Book>& library) {
    Book newBook;
    cout << "\nEnter Book ID: ";
    cin >> newBook.id;
    cin.ignore(); // Clear buffer
    cout << "Enter Book Title: ";
    getline(cin, newBook.title);
    cout << "Enter Author Name: ";
    getline(cin, newBook.author);
    cout << "Enter Number of Copies: ";
    cin >> newBook.copies;

    library.push_back(newBook);
    cout << "Book added successfully!\n";
}

// Function to display all books 
void displayBooks(const vector<Book>& library) {
    if (library.empty()) {
        cout << "\nNo books available in the library.\n";
        return;
    }

    cout << "\n--- Library Books ---\n";
    for (const auto& book : library) {
        cout << "Book ID: " << book.id << "\n";
        cout << "Title: " << book.title << "\n";
        cout << "Author: " << book.author << "\n";
        cout << "Copies: " << book.copies << "\n";
        cout << "--------------------------\n";
    }
}

// Function to search
void searchBook(const vector<Book>& library) {
    if (library.empty()) {
        cout << "\nNo books available in the library.\n";
        return;
    }

    string searchTitle;
    cin.ignore(); // Clear the input buffer
    cout << "\nEnter the title of the book to search: ";
    getline(cin, searchTitle);

    bool found = false;
    for (const auto& book : library) {
        if (book.title == searchTitle) {
            cout << "\nBook Found:\n";
            cout << "Book ID: " << book.id << "\n";
            cout << "Title: " << book.title << "\n";
            cout << "Author: " << book.author << "\n";
            cout << "Copies: " << book.copies << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book with title '" << searchTitle << "' not found.\n";
    }
}


// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/macOS
#endif
}

// Function to load library data from a file
void loadLibraryFromFile(vector<Book>& library) {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "No existing library data found. Starting fresh.\n";
        return;
    }

    Book book;
    while (inFile >> book.id) {
        inFile.ignore();
        getline(inFile, book.title);
        getline(inFile, book.author);
        inFile >> book.copies;
        inFile.ignore(); 
        library.push_back(book);
    }
    inFile.close();
    cout << "Library data loaded successfully.\n";
}

// Function to save library data to a file
void saveLibraryToFile(const vector<Book>& library) {
    ofstream outFile(FILE_NAME);
    for (const auto& book : library) {
        outFile <<"\n";
        outFile << book.id << "\n";
        outFile << book.title << "\n";
        outFile << book.author << "\n";
        outFile << book.copies << "\n";
    }
    outFile.close();
    cout << "Library data saved successfully.\n";
}
