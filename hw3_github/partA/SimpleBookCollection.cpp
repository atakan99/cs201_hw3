
#include "SimpleBookCollection.h"
#include <iostream>

BookCollection::BookCollection()
{
	name = "";
	head = NULL;
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
	name = bcToCopy.getName();
	if (bcToCopy.head == NULL)
		head = NULL;
	else {
		//first node copy
		head = new GenreNode;
		head->g = bcToCopy.head->g;
		//copy the rest
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
	name = right.getName();
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

void BookCollection::displayGenres() const
{
	if (head == NULL) {
		cout<< "--EMPTY--" <<endl;
	}
	for (GenreNode* cur = head; cur != NULL; cur = cur->next)
	{
		cout << cur->g.getGenreName() << endl;
	}
}

bool BookCollection::addGenre(const string genreName)
{
	GenreNode* test = findGenre(genreName);
	if (test != NULL) {
		cout << "Unsuccessful attempt to add genre, "<< genreName << " already exists " << endl;
		return false;
	}
	else {
		//always adding to the head
		GenreNode* newPtr = new GenreNode;
		genreCount++;
		newPtr->g.setGenreName(genreName);
		newPtr->next = head;
		head = newPtr;
		return true;
	}
}

bool BookCollection::removeGenre(const string genreName)
{
	GenreNode* cur;
	GenreNode* prev;
	GenreNode* test = findGenre(genreName);
	if (test == NULL) {
		cout << genreName << " is not exist in the list unable to remove " << endl;
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

string BookCollection::getName() const
{
	return name;
}

void BookCollection::setName(const string bcName)
{
	name = bcName;
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName)
{
	// make all characters lowercase for search
	string name = genreName ;
	string lowerName = "";
	for (string::size_type i = 0; i < name.size(); ++i) {
		//for not considering the blank spaces
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
			else {
				lowerNameGenre += tolower(nameOfGenre[i]);
			}
		}
		if (lowerName == lowerNameGenre) {
			return cur;
		}
	}
	return NULL;
}
