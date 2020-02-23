#include "Book.h"
#include <iostream>

Book::Book()
{
	head = NULL;
	name = "";
}

Book::Book(const string name)
{
	head = NULL;
	this->name = name;
}

Book::~Book()
{
	AuthorNode* cur = head;
	while (cur != NULL) {
		AuthorNode* next = cur->next;
		delete cur;
		cur = next;
	}
	head = NULL;
}

Book::Book(const Book& bookToCopy)
{
	name = bookToCopy.name;
	if(bookToCopy.head == NULL){
		head = NULL;
	}
	else {
		//copy head
		head = new AuthorNode;
		head->a = bookToCopy.head->a;
		//copy rest
		AuthorNode* newPtr = head;
		for (AuthorNode* origPtr = bookToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new AuthorNode;
			newPtr = newPtr->next;
			newPtr->a = origPtr->a;
		}
		newPtr->next = NULL;
	}
}

void Book::operator=(const Book& right)
{
	//if it is full delete all nodes
	AuthorNode* cur = head;
	while (head != NULL) {
		head = head->next;
		delete cur;
		cur = head;
	}

	name = right.name;
	if (right.head == NULL) {
		head = NULL;
	}
	else {
		//copy head
		head = new AuthorNode;
		head->a = right.head->a;
		//copy rest
		AuthorNode* newPtr = head;
		for (AuthorNode* origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new AuthorNode;
			newPtr = newPtr->next;
			newPtr->a = origPtr->a;
		}
		newPtr->next = NULL;
	}
}

string Book::getName() const
{
	return name;
}

void Book::setName(const string bookName)
{
	this->name = bookName;
}

bool Book::addAuthor(const int id, const string name)
{
	AuthorNode* test = findAuthor(id);
	if (test != NULL) {
		cout << "Author with the id: "<< id << " already exists, unable to add" <<endl;
		return false;
	}
	else {
		//always adding to the head
		AuthorNode* newPtr = new AuthorNode;
		newPtr->a.setName(name);
		newPtr->a.setID(id);
		newPtr->next = head;
		head = newPtr;
		return true;
	}
}

bool Book::removeAuthor(const int id)
{
	AuthorNode* cur;
	AuthorNode* prev;
	AuthorNode* test;
	test = findAuthor(id);
	if (test == NULL) {
		cout << "Author with id: "<< id << " is not exist in the list, unable to remove"  <<endl;
		return false;
	}
	else if (test == head) {
		cur = head;
		head = head->next;
	}
	else {
		prev = NULL;
		cur = head;
		while (cur != test) {
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur->next;
	}
	cur->next = NULL;
	delete cur;
	cur = NULL;
	return true;
}

void Book::displayAuthors() const
{
	AuthorNode* displayer = head;
	if (displayer == NULL)
		cout << "  --EMPTY--" << endl;
	else {
		while (displayer != NULL) {
			cout << "   " << displayer->a.getID() << ", " << displayer->a.getName() << endl;
			displayer = displayer->next;
		}
	}
}

void Book::displayAuthor(const int aID) 
{
	AuthorNode* test = this->findAuthor(aID);
	if (test == NULL)
		return;
	else {
		cout<< test->a.getID() <<", " << test->a.getName() <<endl;
		return;
	}
}



bool Book::authorExists(const int aID) 
{
	AuthorNode* test = findAuthor(aID);
	if (test == NULL) {
		return false;
	}
	else {
		return true;
	}
}




Book::AuthorNode* Book::findAuthor(int id)
{
	for (AuthorNode* cur = head; cur != NULL; cur = cur->next) {
		if (cur->a.getID() == id) {
			return cur;
		}
	}
	return NULL;

}







