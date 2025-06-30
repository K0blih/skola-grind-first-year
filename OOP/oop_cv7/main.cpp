#include <iostream>
#include "Square.h"
#include "Teacher.h"
#include "Student.h"
#include "Lesson.h"

int main() 
{
	Rectangle r(5, 4);
	Square sq(4);
	Shape* s = new Rectangle(2, 4);

	std::cout << r.getArea() << std::endl;
	std::cout << sq.getArea() << std::endl;
	std::cout << s->getArea() << std::endl;

	/*Teacher* teacher = new Teacher("Ing.", "Richard", "Chovanec");
	Student* student1 = new Student(10 , 55, "Pepa", "asdasds");
	Student* student2 = new Student(9, 49, "Franta", "asdasdas");
	Student* students[] = {student1, student2};

	Lesson lesson(teacher, students, 2);
	lesson.passedStudents();


	delete teacher;
	delete student1;
	delete student2;*/
	return 0;
}