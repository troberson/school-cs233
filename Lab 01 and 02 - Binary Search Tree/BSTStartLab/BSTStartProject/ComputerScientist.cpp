#include "stdafx.h"
#include "ComputerScientist.h"
#include <string> 


ostream& operator<< (ostream &out, const ComputerScientist &ComputerScientist)
{
	// Since operator<< is a friend of the ComputerScientist class, we can access
	// ComputerScientist's members directly.
	out << "(" << ComputerScientist.firstName << " " << ComputerScientist.lastName;
	out << ", id: " << ComputerScientist.id;
	out << ", speciality: " << ComputerScientist.speciality;
	out << ")";
	return out;
}

//Initialize class members from constructor arguments 
//by using a member initializer list.
//This method uses direct initialization, which is more
//efficient than using assignment operators inside the constructor body.
ComputerScientist::ComputerScientist(const ComputerScientist& rhs)
	: firstName{ rhs.firstName }, lastName{ rhs.lastName }, speciality{ rhs.speciality }, id{ rhs.id }
{
}

//Initialize class members from constructor arguments 
//by using a member initializer list.
//This method uses direct initialization, which is more
//efficient than using assignment operators inside the constructor body.
ComputerScientist::ComputerScientist(string firstName, string lastName, string speciality, int id)
	: firstName{ firstName }, lastName{ lastName }, speciality{ speciality }, id{ id }
{
}

//Initialize class members from constructor arguments 
//by using a member initializer list.
//This method uses direct initialization, which is more
//efficient than using assignment operators inside the constructor body.
ComputerScientist::ComputerScientist()
	: firstName{ "" }, lastName{ "" }, speciality{ "" }, id{ -1 }
{
}

ComputerScientist::~ComputerScientist()
{
}
bool ComputerScientist::operator==( const ComputerScientist& rhs) const
{	
	return this->id == rhs.id;
}

bool  ComputerScientist::operator<( const ComputerScientist& rhs) const
{
	return this->id < rhs.id;	
}

ComputerScientist & ComputerScientist::operator=(const ComputerScientist & rhs)
{
	this->firstName = rhs.firstName;
	this->lastName = rhs.lastName;
	this->speciality = rhs.speciality;
	this->id = rhs.id;
	return *this;
}

 string ComputerScientist::getFirstName()
{
	return this->firstName;
}

 string ComputerScientist::getLastName()
{
	return this->lastName;
}

 string ComputerScientist::getSpeciality()
{
	return this->speciality;
}

 int ComputerScientist::getID()
{
	return this->id;
}