#include "BookCollection.h"

BookCollection::BookCollection()
{
	this->head = NULL;
	genreCount = 0;
}

BookCollection::~BookCollection()
{
	GenreNode* cur = head;
	while (cur != NULL) {
		GenreNode* next = cur->next;
		delete cur;
		cur = next;
	}
	head = NULL;
}

BookCollection::BookCollection(const BookCollection& bcToCopy)
{
	genreCount = bcToCopy.genreCount;
	if (bcToCopy.head == NULL)
		head = NULL;
	else {
		//copy first node  
		head = new GenreNode;
		head->g = bcToCopy.head->g;
		//copy rest
		GenreNode* newPtr = head;
		for (GenreNode* origPtr = bcToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new GenreNode;
			newPtr = newPtr->next;
			newPtr->g = origPtr->g;
		}
		newPtr->next = NULL;
	}
}

void BookCollection::operator=(const BookCollection& right)
{
	//What if the list has items, remove them!
	GenreNode* dummy;
	dummy = head;
	while (!genreCount && head != NULL) {
		head = head->next;
		delete dummy;
		dummy = head;
	}

	genreCount = right.genreCount;
	if (right.head == NULL)
		head = NULL;
	else {
		//first node copy
		head = new GenreNode;
		head->g = right.head->g;
		//copy the rest
		GenreNode* newPtr = head;
		for (GenreNode* origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new GenreNode;
			newPtr = newPtr->next;
			newPtr->g = origPtr->g;
		}
		newPtr->next = NULL;
	}

}

void BookCollection::addGenre(string genreName)
{
	GenreNode* test = findGenre(genreName);
	if (test != NULL) {
		cout << "Unsuccessful attempt to add genre, " << genreName << " already exists " << endl;
		return;
	}
	else {
		//always adding to the head
		GenreNode* newPtr = new GenreNode;
		genreCount++;
		newPtr->g.setGenreName(genreName);
		newPtr->next = head;
		head = newPtr;
		genreCount++;
		return;
	}
}

void BookCollection::removeGenre(string genreName)
{
	GenreNode* cur;
	GenreNode* prev;
	GenreNode* test = findGenre(genreName);
	if (test == NULL) {
		cout << genreName << " is not exist in the list unable to remove " << endl;
		return;
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
	genreCount--;
	cur->next = NULL;
	delete cur;
	cur = NULL;
	return;
}

void BookCollection::displayAllGenres() const
{
	GenreNode* displayer = head;
	if (displayer == NULL) {
		cout << "--EMPTY--" <<endl;
	}
	while (displayer != NULL) {
		cout << displayer->g.getGenreName() << endl;
		displayer = displayer->next;
	}
}

void BookCollection::addBook(string genreName, string bookName)
{
	GenreNode* test = findGenre(genreName);
	
	if (test == NULL) {
		cout << "Unsuccessful attempt to add the book, the genre  " << genreName << " does not exist in the list " << endl;
		return;
	}
	else {
		 test->g.addBook(bookName);
		 return;
	}

}

void BookCollection::removeBook(string genreName, string bookName)
{
	GenreNode* test = findGenre(genreName);
	if (test == NULL) {
		cout << "Unsuccessful attempt to remove the book, the genre  " << genreName << " does not exist in the list " << endl;
		return;
	}
	else {
		test->g.removeBook(bookName);
		return;
	}
}

void BookCollection::addAuthor(string genreName, string bookName, int authorID, string authorName)
{
	GenreNode* test = findGenre(genreName);
	if (test == NULL) {
		cout << "Unsuccessful attempt to add the author, the genre  " << genreName << " does not exist in the list " << endl;
		return;
	}
	else {
		if (!test->g.bookExists(bookName)) {
			cout << "Unsuccessful attempt to add the author, the book  " << bookName << " does not exist in the list " << endl;
			return;
		}
		else {
			test->g.addAuthor(bookName, authorID, authorName);
			return;
		}
	}
}

void BookCollection::removeAuthor(string genreName, string bookName, int authorID)
{
	GenreNode* test = findGenre(genreName);
	if (test == NULL) {
		cout << "Unsuccessful attempt to remove the author, the genre  " << genreName << " does not exist in the list " << endl;
		return;
	}
	else {
		if (!test->g.bookExists(bookName)) {
			cout << "Unsuccessful attempt to remove the author, the book  " << bookName << " does not exist in the list " << endl;
			return;
		}
		else {
			test->g.removeAuthor(bookName, authorID);
		}
	}
}

void BookCollection::displayGenre(string genreName)
{
	GenreNode* test = findGenre(genreName);
	if (test == NULL) {
		cout << "--EMPTY--" << endl;
	}
	else {
		cout << test->g.getGenreName() << endl;
		test->g.displayBooks();
	}
}

void BookCollection::displayAuthor(int authorID)
{
	bool flag1 = false;
	bool flag2 = false;
	for (GenreNode* test = head; test != NULL; test = test->next) {
		if (test->g.authorExists(authorID)) {
			if (!flag1) {
				test->g.displayAuthor(authorID);
				flag1 = true;
			}
			cout << test->g.getGenreName() << endl;
		    test->g.displayAuthorsBooks(authorID);
			flag2 = true;
		}
	}
	if (!flag2) {
		cout << " --Empty-- " << endl;
	}
}



BookCollection::GenreNode* BookCollection::findGenre(string genreName)
{
	// make all characters lowercase for search
	GenreNode* returned = NULL;
	string name = genreName;
	string lowerName = "";
	for (string::size_type i = 0; i < name.size(); ++i) {
		// for not considerind the blank spaces
		if (name[i] == ' ') {
			lowerName = lowerName;
		}
		else {
			lowerName += tolower(name[i]);
		}
	}

	for (GenreNode* cur = head; cur != NULL; cur = cur->next) {
		string nameOfGenre = cur->g.getGenreName();
		string lowerNameGenre = "";
		for (string::size_type i = 0; i < nameOfGenre.size(); ++i) {
			if (nameOfGenre[i] == ' ') {
				lowerNameGenre = lowerNameGenre;
			}
			else{
			lowerNameGenre += tolower(nameOfGenre[i]);
			}
		}
		if (lowerName == lowerNameGenre) {
			returned = cur;
		}
	}
	return returned;
}
