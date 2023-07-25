#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Book {
    string title;
    string author;
    int copies;
};

vector<Book> bookList;

void addNewBook() {
    Book newBook;
    cout << "Enter the title of the book: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter the author of the book: ";
    getline(cin, newBook.author);
    cout << "Enter the number of copies: ";
    cin >> newBook.copies;

    bookList.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

void deleteBook() {
    string searchTitle;
    cout << "Enter the title of the book to delete: ";
    cin.ignore();
    getline(cin, searchTitle);

    auto it = find_if(bookList.begin(), bookList.end(), [&](const Book& book) {
        return book.title == searchTitle;
    });

    if (it != bookList.end()) {
        bookList.erase(it);
        cout << "Book deleted successfully!" << endl;
    } else {
        cout << "Book not found!" << endl;
    }
}

void addBookCopy() {
    string searchTitle;
    cout << "Enter the title of the book to add a copy: ";
    cin.ignore();
    getline(cin, searchTitle);

    auto it = find_if(bookList.begin(), bookList.end(), [&](const Book& book) {
        return book.title == searchTitle;
    });

    if (it != bookList.end()) {
        it->copies++;
        cout << "Book copy added successfully!" << endl;
    } else {
        cout << "Book not found!" << endl;
    }
}

void setBookList() {
    bookList.clear();
    int numBooks;
    cout << "Enter the number of books: ";
    cin >> numBooks;

    for (int i = 0; i < numBooks; i++) {
        Book book;
        cout << "Enter the title of book " << i + 1 << ": ";
        cin.ignore();
        getline(cin, book.title);
        cout << "Enter the author of book " << i + 1 << ": ";
        getline(cin, book.author);
        cout << "Enter the number of copies of book " << i + 1 << ": ";
        cin >> book.copies;

        bookList.push_back(book);
    }

    cout << "Book list set successfully!" << endl;
}

void searchBook() {
    string searchTitle;
    cout << "Enter the title of the book to search: ";
    cin.ignore();
    getline(cin, searchTitle);

    auto it = find_if(bookList.begin(), bookList.end(), [&](const Book& book) {
        return book.title == searchTitle;
    });

    if (it != bookList.end()) {
        cout << "Book found!" << endl;
        cout << "Title: " << it->title << endl;
        cout << "Author: " << it->author << endl;
        cout << "Copies available: " << it->copies << endl;
    } else {
        cout << "Book not found!" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Delete a Copy of Book" << endl;
        cout << "3. Add a Copy of Book" << endl;
        cout << "4. Set the Book List" << endl;
        cout << "5. Search a Book from List" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                addBookCopy();
                break;
            case 4:
                setBookList();
                break;
            case 5:
                searchBook();
                break;
            case 6:
                cout << "Exiting... Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
