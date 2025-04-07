#pragma once
#include "Student.h"

class Classroom {
public:
	Classroom(Student* students, int studentCount);
	~Classroom();
	void printStudentsWithScholarship();

private:
	Student* students;
	int studentCount;
};