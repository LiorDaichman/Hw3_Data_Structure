#include "Student_grade.h"

//This function introduces a new student with an ID. A midterm score and test score will be set to be 0.
void insert(BST* tree, int ID) {
	StudentNode* node = tree->root;
	StudentNode* parent = NULL;
	if (tree->root == NULL) {
		tree->root = (StudentNode*)malloc(sizeof(StudentNode));
		tree->root->ID = ID;
		tree->root->Mid_year_test = 0;
		tree->root->End_year_test = 0;
		tree->root->right = NULL;
		tree->root->left = NULL;
		tree->root->parent = parent;
	}
	else {
		while (node != NULL) {
			parent = node;
			if (ID == node->ID)
				return;
			else if (ID < node->ID)
				node = node->left;
			else if (ID > node->ID)
				node = node->right;
		}
		node = (StudentNode*)malloc(sizeof(StudentNode));
		node->ID = ID;
		node->Mid_year_test = 0;
		node->End_year_test = 0;
		node->right = NULL;
		node->left = NULL;
		node->parent = parent;
		if (ID < parent->ID)
			parent->left = node;
		else if (ID > parent->ID)
			parent->right = node;
	}
}

//Updates a grade in the mid-quiz of a student with an ID number.
void updateMidtermGrade(BST* tree, int ID, int newGrade) {
	StudentNode* node = tree->root;
	while (node != NULL) {
		if (ID == node->ID) {
			node->Mid_year_test = newGrade;
			return;
		}
		else if (ID < node->ID)
			node = node->left;
		else if (ID > node->ID)
			node = node->right;
	}
}

//Updates a exam in the mid-quiz of a student with an ID number.
void updateExamGrade(BST* tree, int ID, int newGrade) {
	StudentNode* node = tree->root;
	while (node != NULL) {
		if (ID == node->ID) {
			node->End_year_test = newGrade;
			return;
		}
		else if (ID < node->ID)
			node = node->left;
		else if (ID > node->ID)
			node = node->right;
	}
}

//Returns the final score of a student with an ID number.
int getFinalGrade(BST* tree, int ID) {
	StudentNode* node = tree->root;
	float grade = 0;
	while (node != NULL) {
		if (ID == node->ID) {
			grade = (float)((node->Mid_year_test) * 0.3 + (node->End_year_test) * 0.7);
			if (grade < (int)grade + 0.5)
				return (int)grade;
			return (int)grade + 1;
		}
		else if (ID < node->ID)
			node = node->left;
		else if (ID > node->ID)
			node = node->right;
	}
	return 0;
}

//Returns the average in the final grades in the course.
double getAverageGrade(BST* tree) {
	double gradeSum = 0;
	StudentNode* node = tree->root;
	gradeSum = Proper(node, tree);
	return gradeSum / Size_of_tree(tree->root);
}

//Proper order data in tree
int Proper(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return Proper(node->right, tree) + Proper(node->left, tree) + getFinalGrade(tree, node->ID);
}

//Change Size of tree
int Size_of_tree(StudentNode* node) {
	if (node == NULL)
		return 0;
	return Size_of_tree(node->right) + Size_of_tree(node->left) + 1;
}

//Print data funcation
void PrintData(StudentNode* node, BST* tree) {
	if (node != NULL) {
		PrintData(node->left, tree);
		printf("%d\t%d\t%d\t%d\n", node->ID, node->Mid_year_test, node->End_year_test, getFinalGrade(tree, node->ID));
		PrintData(node->right, tree);
	}
}

//Prints student information on the screen and is sorted by ID.
void reportGrades(BST* tree) {
	StudentNode* node = tree->root;
	printf("\nID\tQuiz\tExam\tFinall\n");
	PrintData(node, tree);
}

//Checking if the student fails
int IsFail(int grade) {
	if (grade < 56)
		return 1;
	else
		return 0;
}

//Counter fail grade between
int postOrderFails(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return postOrderFails(node->left, tree) + postOrderFails(node->right, tree) + IsFail(getFinalGrade(tree, node->ID));
}

//Returns the number of students fail course
int getNumOfFails(BST* tree) {
	StudentNode* node = tree->root;
	int num_of_fails = postOrderFails(node, tree);
	return num_of_fails;
}

//Checking if the student get between 56 to 75
int IsGood(int grade) {
	if (56 <= grade && grade <= 75)
		return 1;
	else
		return 0;
}

//Checking if the student get between 76 to 94
int IsVeryGood(int grade) {
	if (76 <= grade && grade <= 94)
		return 1;
	else
		return 0;
}

//Checking if the student get between 95 to 100
int IsXLent(int grade) {
	if (95 <= grade && grade <= 100)
		return 1;
	else
		return 0;
}

//Counter grade between 56 to 75
int GoodCounter(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return GoodCounter(node->left, tree) + GoodCounter(node->right, tree) + IsGood(getFinalGrade(tree, node->ID));
}

//Counter grade between 76 to 94
int VeryGoodCounter(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return VeryGoodCounter(node->left, tree) + VeryGoodCounter(node->right, tree) + IsVeryGood(getFinalGrade(tree, node->ID));
}

//Counter grade between 95 to 100
int ExcellentCounter(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return ExcellentCounter(node->left, tree) + ExcellentCounter(node->right, tree) + IsXLent(getFinalGrade(tree, node->ID));
}

//Prints the number of students in the three grade grades represented
void RepostStatistics(BST* tree) {
	StudentNode* node = tree->root;
	int good = GoodCounter(node, tree), veryGood = VeryGoodCounter(node, tree), excellent = ExcellentCounter(node, tree);
	printf("\t  Degree\t final grade\n");
	printf("Good\t  (56-75)\t %d\nVery good (76-94)\t %d\nExcellent (95-100)\t %d\n", good, veryGood, excellent);
}