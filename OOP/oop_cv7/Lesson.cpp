#include "Lesson.h"

Lesson::Lesson(Teacher* teacher, Student** students, int studentCount)
	: teacher(teacher), students(students), studentCount(studentCount)
{
}

void Lesson::passedStudents()
{
	for (int i = 0; i < studentCount; i++) {
		if (students[i]->getPoints() > 51 && students[i]->getAttendance() > 8) {
			students[i]->printStatus();
		}
	}
}
