#include "Classroom.h"
#include <iostream>

Classroom::Classroom(Student* students, int studentCount)
{
	this->studentCount = studentCount;

	this->students = new Student[this->studentCount];
	for (int i = 0; i < this->studentCount; i++) {
		this->students[i] = students[i];
	}
}

Classroom::~Classroom()
{	
	delete[] students;
	students = nullptr;
}

void Classroom::printStudentsWithScholarship()
{
	bool skip = false;
	for (int i = 0; i < this->studentCount; i++) {
		for (int j = 0; j < students[i].getSubjectCount(); j++) {
			if (students[i].getGrade(j) > 2) {
				skip = true;
			}
		}
		if (skip) {
			skip = false;
			continue;
		}
		if (students[i].getAverageGrade() < 1.7) {
			std::cout << students[i].getFirstName() << " " << students[i].getLastName() << std::endl;
		}
	}
}
