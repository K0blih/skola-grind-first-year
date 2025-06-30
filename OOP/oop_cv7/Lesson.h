#pragma once
#include "Teacher.h"
#include "Student.h"
class Lesson
{
private:
	Teacher* teacher;
	Student** students;
	int studentCount;

public:
	Lesson(Teacher* teacher, Student** student, int studentCount);
	void passedStudents();
};

