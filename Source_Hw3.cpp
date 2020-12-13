#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Student_grade.h"

int main() {
	BST* tree = (BST*)malloc(sizeof(BST));
	tree->root = NULL;
	//Enter New Student
	insert(tree, 100);
	insert(tree, 200);
	insert(tree, 300);
	insert(tree, 400);
	insert(tree, 500);
	insert(tree, 600);
	insert(tree, 700);
	insert(tree, 800);
	//Enter Student Midterm Grade
	updateMidtermGrade(tree, 100, 70);
	updateMidtermGrade(tree, 200, 13);
	updateMidtermGrade(tree, 300, 50);
	updateMidtermGrade(tree, 400, 60);
	updateMidtermGrade(tree, 500, 40);
	updateMidtermGrade(tree, 600, 100);
	updateMidtermGrade(tree, 700, 33);
	updateMidtermGrade(tree, 800, 72);
	//Enter Student Exam Grade
	updateExamGrade(tree, 100, 81);
	updateExamGrade(tree, 200, 54);
	updateExamGrade(tree, 300, 100);
	updateExamGrade(tree, 400, 65);
	updateExamGrade(tree, 500, 70);
	updateExamGrade(tree, 600, 100);
	updateExamGrade(tree, 700, 57);
	updateExamGrade(tree, 800, 99);
	//print data
	reportGrades(tree);
	int test = getNumOfFails(tree);
	printf(" fails: %d\n", test);
	RepostStatistics(tree);
	return 0;
}