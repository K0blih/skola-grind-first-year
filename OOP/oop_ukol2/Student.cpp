#include "Student.h"

Student::Student()
{
	this->firstName = "";
	this->lastName = "";
	this->subjectCount = 5;
	this->grades = new int[this->subjectCount];
	for (int i = 0; i < this->subjectCount; i++) {
		this->grades[i] = 5;
	}
}

Student::Student(std::string firstName, std::string lastName, int* grades, int subjectCount)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->subjectCount = subjectCount;
	
	this->grades = new int[this->subjectCount];
	for (int i = 0; i < this->subjectCount; i++) {
		this->grades[i] = grades[i];
	}
}

Student::~Student()
{
	grades = nullptr;
}

std::string Student::getFirstName()
{
	return this->firstName;
}

std::string Student::getLastName()
{
	return this->lastName;
}

int Student::getGrade(int index)
{
	return this->grades[index];
}

int Student::getSubjectCount()
{
	return this->subjectCount;
}

double Student::getAverageGrade()
{
	double sum = 0.0;
	for (int i = 0; i < this->subjectCount; i++) {
		sum += grades[i];
	}
	return sum / this->subjectCount;
}
