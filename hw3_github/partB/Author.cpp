#include "Author.h"

Author::Author()
{
	name = "";
	id = 0;
}

Author::Author(const int id, const string name)
{
	this->name = name; //(*this).
	this->id = id;
}

int Author::getID() const
{
	return this->id;
}

void Author::setID(const int id)
{
	this->id = id;
}

string Author::getName() const
{
	return name;
}

void Author::setName(const string id)
{
	this->name = id;
}
