#ifndef _GENRE_H 
#define _GENRE_H 

#include <string> 
#include <iostream>
#include "Book.h"
using namespace std;


class Genre{
public:
	Genre(const string gname = "");
	~Genre();
	Genre(const Genre& genreToCopy);
	void operator=(const Genre& right);
	string getGenreName() const;
	void setGenreName(const string gName);
	bool addBook(const string bName);
	bool removeBook(const string bName);
	bool addAuthor(const string bName,  const int aID , const string aName );
	bool removeAuthor(const string bName, const int aID);
	
	void displayAuthor(const int aID);
	void displayBook(string bName);
	bool bookExists(const string bName);
	bool authorExists(const int aID);
	void displayBooks();
	bool displayAuthorsBooks(const int aID);
	
	
private:
	struct BookNode {
		Book b;
		BookNode* next;
	};
	BookNode* head;
	string genreName;

	BookNode* findBook(string bName);
};
#endif 

