#pragma once
#include <string>

using namespace std;

class ComputerScientist {
  public:
	
	string getFirstName();
	string getLastName();
	string getSpeciality();
	int getID();
	friend ostream& operator<< (ostream &out,const ComputerScientist &computerScientist);
	bool operator==(const  ComputerScientist& rhs) const;
	bool operator<(const ComputerScientist& rhs) const;
	ComputerScientist & operator=(const  ComputerScientist& rhs) ;
	ComputerScientist(const ComputerScientist& rhs);
	ComputerScientist();
	ComputerScientist(string firstName, string lastName, string speciality, int id);
	~ComputerScientist();

  private:
	string firstName;
	string lastName;
	string speciality;
	int id;
};

