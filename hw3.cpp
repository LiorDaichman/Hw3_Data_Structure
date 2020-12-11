#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct StudentNode {
	int ID;
	int midTestGrade;
	int testGrade;
	struct StudentNode* left;
	struct StudentNode* right;
	struct StudentNode* parent;

} StudentNode;

typedef struct BST {
	struct StudentNode* root;
} BST;

void insert(BST*, int);
void updateMidtermGrade(BST*, int, int);
void updateExamGrade(BST*, int, int);
int getFinalGrade(BST*, int);
double getAverageGrade(BST*);
int inorder(StudentNode*, BST*); //need to change
int treeSize(StudentNode*);	//need to change
void reportGrades(BST*);


int main() {
	BST* tree = (BST*)malloc(sizeof(BST));
	tree->root = NULL;
	//Enter New Student
	insert(tree, 123456);
	insert(tree, 882211);
	insert(tree, 128832);
	insert(tree, 992212);
	insert(tree, 122121);
	insert(tree, 122111);
	//Enter Student Midterm Grade
	updateMidtermGrade(tree, 123456, 50);
	updateMidtermGrade(tree, 882211, 90);
	updateMidtermGrade(tree, 128832, 13);
	updateMidtermGrade(tree, 992212, 33);
	updateMidtermGrade(tree, 122121, 100);
	updateMidtermGrade(tree, 122111, 72);
	//Enter Student Exam Grade
	updateExamGrade(tree, 123456, 100);
	updateExamGrade(tree, 882211, 87);
	updateExamGrade(tree, 128832, 54);
	updateExamGrade(tree, 992212, 98);
	updateExamGrade(tree, 122121, 100);
	updateExamGrade(tree, 122111, 99);

	return 0;
}

//This function introduces a new student with an ID. A midterm score and test score will be set to be 0.
void insert(BST* tree, int ID) {
	StudentNode* node = tree->root, * parent = NULL;
	if (tree->root == NULL) {
		tree->root = (StudentNode*)malloc(sizeof(StudentNode));
		tree->root->ID = ID;
		tree->root->midTestGrade = 0;
		tree->root->testGrade = 0;
		tree->root->left = NULL;
		tree->root->right = NULL;
		tree->root->parent = parent;
	}
	else {
		while (node != NULL) {
			parent = node;
			if (ID == node->ID) return;
			else if (ID < node->ID) node = node->left;
			else if (ID > node->ID) node = node->right;
		}
		node = (StudentNode*)malloc(sizeof(StudentNode));
		node->ID = ID;
		node->midTestGrade = 0;
		node->testGrade = 0;
		node->left = NULL;
		node->right = NULL;
		node->parent = parent;
		if (ID < parent->ID) parent->left = node;
		else if (ID > parent->ID) parent->right = node;
	}
}

//Updates a grade in the mid-quiz of a student with an ID number.
void updateMidtermGrade(BST* tree, int ID, int newGrade) {
	StudentNode* node = tree->root;
	while (node != NULL) {
		if (ID == node->ID) {
			node->midTestGrade = newGrade;
			return;
		}
		else if (ID < node->ID) node = node->left;
		else if (ID > node->ID) node = node->right;
	}
}

//Updates a exam in the mid-quiz of a student with an ID number.
void updateExamGrade(BST* tree, int ID, int newGrade) {
	StudentNode* node = tree->root;
	while (node != NULL) {
		if (ID == node->ID) {
			node->testGrade = newGrade;
			return;
		}
		else if (ID < node->ID) node = node->left;
		else if (ID > node->ID) node = node->right;
	}
}

//Returns the final score of a student with an ID number.
int getFinalGrade(BST* tree, int ID) {
	StudentNode* node = tree->root;
	float grade = 0;
	while (node != NULL) {
		if (ID == node->ID) {
			grade = (float)((node->midTestGrade) * 0.3 + (node->testGrade) * 0.7);
			if (grade < (int)grade + 0.5) {
				return (int)grade;
			}
			return (int)grade + 1;
		}
		else if (ID < node->ID) node = node->left;
		else if (ID > node->ID) node = node->right;
	}
	return 0;
}

//Returns the average in the final grades in the course.
double getAverageGrade(BST* tree) {
	double gradeSum = 0;
	StudentNode* node = tree->root;
	gradeSum = inorder(node, tree);
	return gradeSum / treeSize(tree->root);
}

int inorder(StudentNode* node, BST* tree) { //need to change
	if (node == NULL) return 0;
	return inorder(node->left, tree) + getFinalGrade(tree, node->ID) + inorder(node->right, tree);
}

int treeSize(StudentNode* node) {	//need to change
	if (node == NULL) return 0;
	return 1 + treeSize(node->left) + treeSize(node->right);
}
