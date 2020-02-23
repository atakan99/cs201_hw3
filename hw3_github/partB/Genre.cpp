#include "Genre.h"

Genre::Genre(const string gname)
{
	this->genreName = gname;
	head = NULL;
}

Genre::~Genre()
{
	BookNode* cur = head;
	while (cur != NULL) {
		BookNode* next = cur->next;
		delete cur;
		cur = next;
	}
	head = NULL;
}

Genre::Genre(const Genre& genreToCopy)
{
	genreName = genreToCopy.getGenreName();
	if (genreToCopy.head == NULL) {
		head = NULL;
	}
	else {
		//copy head
		head = new BookNode;
		head->b = genreToCopy.head->b;
		//copy rest
		BookNode* newPtr = head;
		for (BookNode* origPtr = genreToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new BookNode;
			newPtr = newPtr->next;
			newPtr->b= origPtr->b;
		}
		newPtr->next = NULL;
	}
}

void Genre::operator=(const Genre& right)
{
	BookNode* cur = head;
	while (head != NULL) {
		head = head->next;
		delete cur;
		cur = head;
	}

	genreName = right.getGenreName();
	if (right.head == NULL) {
		head = NULL;
	}
	else {
		//copy head
		head = new BookNode;
		head->b = right.head->b;
		//copy rest
		BookNode* newPtr = head;
		for (BookNode* origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new BookNode;
			newPtr = newPtr->next;
			newPtr->b = origPtr->b;
		}
		newPtr->next = NULL;
	}
}

string Genre::getGenreName() const
{
	return genreName;
}

void Genre::setGenreName(const string gName)
{
	genreName = gName;
}

bool Genre::addBook(const string bName)
{
	BookNode* test = findBook(bName);
	if (test != NULL) {
		cout << "Unsuccessful attempt to add book, " << bName << " already exists " << endl;
		return false;
	}
	else {
		BookNode* newPtr = new BookNode;
		newPtr->b.setName(bName);
		newPtr->next = head;
		head = newPtr;
		return true;
	}
}

bool Genre::removeBook(const string bName)
{
	BookNode* cur;
	BookNode* prev;
	BookNode* test = findBook(bName);
	if (test == NULL) {
		cout << bName << " is not exist in the list unable to remove " << endl;
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



bool Genre::addAuthor(const string bName, const int aID ,const string aName)
{
	BookNode* test = findBook(bName);
	if (test == NULL) {
		cout << "Unsuccessful attempt to add author, the book  " << bName << " does not exist in the list " << endl;
		return false;
	}
	else {
		return test->b.addAuthor(aID, aName);
	}

}

bool Genre::removeAuthor(const string bName, const int aID)
{
	BookNode* test = findBook(bName);
	if (test == NULL) {
		cout << "Unsuccessful attempt to remove author, the book  " << bName << " does not exist in the list " << endl;
		return false;
	}
	else {
		return test->b.removeAuthor(aID);
	}
}

void Genre::displayAuthor(const int aID)
{
	bool test = false;
	BookNode* displayer = head;
	while (displayer != NULL) {
		if (displayer->b.authorExists(aID)) {
			displayer->b.displayAuthor(aID);
			test = true;
		}
		if (test == true) {
			return;
		}
		displayer = displayer->next;
	}
}

void Genre::displayBook(string bName)
{
	BookNode* displayer = findBook(bName);
	
	cout<< displayer->b.getName() <<endl;
}

bool Genre::bookExists(const string bName)
{
	BookNode* test = findBook(bName);
	if (test == NULL) {
		return false;
	}
	else {
		return true;
	}
}

bool Genre::authorExists(const int aID)
{
	bool aExists = false;
	for (BookNode* a = head; a != NULL; a = a->next) {
		if (a->b.authorExists(aID)) {
			aExists = true;
		}
	}
	return aExists;
}


void Genre::displayBooks()
{
	if (head == NULL) {
		cout << "--EMPTY--" << endl;
	}
	for (BookNode* cur = head; cur != NULL; cur = cur->next)
	{
		cout << cur->b.getName() << endl;
		cur->b.displayAuthors();
	}
}


bool Genre::displayAuthorsBooks(const int aID)
{
	bool test = false;
	BookNode* displayer = head;
	while (displayer != NULL) {
		if (displayer->b.authorExists(aID)) {
			cout << "  " <<displayer->b.getName()<<endl;
			test = true;
		}
		displayer = displayer->next;
	}
	return test;
}


Genre::BookNode* Genre::findBook(string bName)
{
	BookNode* returned = NULL;
	string name = bName;
	string lowerbName = "";
	for (string::size_type i = 0; i < bName.size(); i++){
		// for not considerind the blank spaces
		if (bName[i] == ' ') {
			lowerbName = lowerbName;
		}
		else {
			lowerbName += tolower(bName[i]);
		}
	}

	for (BookNode* cur = head; cur != NULL; cur = cur->next) {
		string nameOfBook = cur->b.getName();
		string lowerBookName = "";
		for (string::size_type i = 0; i < nameOfBook.size(); i++) {
			if ( nameOfBook[i] == ' '  ) {
				lowerBookName = lowerBookName;
			}
			else {
				lowerBookName += tolower(nameOfBook[i]);
			}
		}
		if (lowerbName == lowerBookName) {
			returned = cur;
		}
	}
	return returned;
}
