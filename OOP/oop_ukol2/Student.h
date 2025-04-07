#pragma once
#include <string>

class Student {
public:
	Student();
	Student(std::string firstName, std::string lastName, int* grades, int subjectCount);
	~Student();

	std::string getFirstName();
	std::string getLastName();
	int getGrade(int index);
	int getSubjectCount();
	double getAverageGrade();

private:
	std::string firstName;
	std::string lastName;
	int* grades;
	int subjectCount;
};