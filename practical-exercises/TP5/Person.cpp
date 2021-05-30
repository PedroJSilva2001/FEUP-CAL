/*
 * Person.cpp
 */

#include "Person.h"

Person::Person(std::string n, int a): name(n), age(a) {}
Person::Person(){}

std::string Person::getName() const {
	return name;
}

bool Person::operator == (const Person &p2) const {
	return (name==p2.name && age==p2.age);
}

std::ostream & operator << (std::ostream &os, Person &p) {
   os << p.getName();
   return os;
}

void createNetwork(Graph<Person> & net1) {
    Person p1("Ana",19);
    Person p2("Carlos",33);
    Person p3("Filipe", 20);
    Person p4("Ines", 18);
    Person p5("Maria", 24);
    Person p6("Rui",21);
    Person p7("Vasco",28);
    net1.addVertex(p1); net1.addVertex(p2);
    net1.addVertex(p3); net1.addVertex(p4);
    net1.addVertex(p5); net1.addVertex(p6); net1.addVertex(p7);
    net1.addEdge(p1,p2,0);
    net1.addEdge(p1,p3,0);
    net1.addEdge(p1,p4,0);
    net1.addEdge(p2,p5,0);
    net1.addEdge(p5,p6,0);
    net1.addEdge(p5,p1,0);
    net1.addEdge(p3,p6,0);
    net1.addEdge(p3,p7,0);
    net1.addEdge(p6,p2,0);
}
