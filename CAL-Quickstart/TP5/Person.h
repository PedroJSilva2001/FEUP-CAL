/*
 * Person.h
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <ostream>

class Person {
	std::string name;
	int age;
public:
	Person();
	Person (std::string n, int a);
    std::string getName() const;
	bool operator == (const Person &p2) const;
	friend std::ostream & operator << (std::ostream &os, Person &p);
};

#include "Graph.h"
void createNetwork(Graph<Person> & net1);

#endif /* PERSON_H_ */
