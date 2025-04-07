#include <iostream>
#include "Student.h"
#include "Classroom.h"

int main() {

    int grades1[5] = { 5, 5, 5, 5, 5 };
    int grades2[5] = { 2, 2, 2, 2, 2 };
    int grades3[5] = { 1, 1, 1, 1, 3 };
    int grades4[5] = { 1, 2, 3, 4, 5 };
    int grades5[5] = { 1, 1, 1, 1, 2 };

    Student student1("Richard", "Chovanec", grades1, 5);
    Student student2("Petr", "Chovanec", grades2, 5);
    Student student3("Ondrej", "Chovanec", grades3, 5);
    Student student4("Samuel", "Chovanec", grades4, 5);
    Student student5("Ales", "Chovanec", grades5, 5);
    Student students[5] = {student1, student2, student3, student4, student5};

    Classroom classroom1(students, 5);
    classroom1.printStudentsWithScholarship();
	return 0;
}