
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
int getNumOfFails(BST*);
void RepostStatistics(BST*);

int main() {
	BST* tree = (BST*)malloc(sizeof(BST));
	tree->root = NULL;
	//Enter New Student
	insert(tree, 300);
	insert(tree, 100);
	insert(tree, 200);
	insert(tree, 700);
	insert(tree, 600);
	insert(tree, 800);
	//Enter Student Midterm Grade
	updateMidtermGrade(tree, 300, 50);
	updateMidtermGrade(tree, 100, 70);
	updateMidtermGrade(tree, 200, 13);
	updateMidtermGrade(tree, 700, 33);
	updateMidtermGrade(tree, 600, 100);
	updateMidtermGrade(tree, 800, 72);
	//Enter Student Exam Grade
	updateExamGrade(tree, 300, 100);
	updateExamGrade(tree, 100, 70);
	updateExamGrade(tree, 200, 54);
	updateExamGrade(tree, 700, 57);
	updateExamGrade(tree, 600, 100);
	updateExamGrade(tree, 800, 99);

	reportGrades(tree);
	int test=getNumOfFails(tree);
	printf(" fails: %d\n", test);

	RepostStatistics(tree);

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
	if (node == NULL) 
		return 0;
	return inorder(node->left, tree) + getFinalGrade(tree, node->ID) + inorder(node->right, tree);
}

int treeSize(StudentNode* node) {	//need to change
	if (node == NULL)
		return 0;
	return 1 + treeSize(node->left) + treeSize(node->right);
}



void PrintData(StudentNode* node,BST* tree) {
	if (node != NULL) {
		PrintData(node->left,tree);
		printf("%d\t%d\t%d\t%d\n", node->ID, node->midTestGrade, node->testGrade, getFinalGrade(tree, node->ID));
		PrintData(node->right,tree);
		
	}
}

void reportGrades(BST* tree) {

	StudentNode* node = tree->root;
	printf("\nID\tQuiz\tExam\tFinall\n");
	PrintData(node,tree);
}

int IsFail(int grade) {
	if (grade < 56)
		return 1;
	else
		return 0;
}


int postOrderFails(StudentNode* node, BST* tree) {
		if (node == NULL)
			return 0;
		return postOrderFails(node->left, tree) + postOrderFails(node->right, tree) + IsFail(getFinalGrade(tree, node->ID));

}

int getNumOfFails(BST* tree) {
	StudentNode* node = tree->root;
	int num_of_fails = postOrderFails(node, tree);
	return num_of_fails;
}

int IsGood(int grade) {
	if (56<= grade && grade <=75)
		return 1;
	else
		return 0;
}

int IsVeryGood(int grade) {
	if (76 <= grade && grade <= 94)
		return 1;
	else
		return 0;
}

int IsXLent(int grade) {
	if (95 <= grade && grade <= 100)
		return 1;
	else
		return 0;
}

int GoodCounter(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return GoodCounter(node->left, tree) + GoodCounter(node->right, tree) + IsGood(getFinalGrade(tree, node->ID));
}

int VeryGoodCounter(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return VeryGoodCounter(node->left, tree) + VeryGoodCounter(node->right, tree) + IsVeryGood(getFinalGrade(tree, node->ID));
}

int ExcellentCounter(StudentNode* node, BST* tree) {
	if (node == NULL)
		return 0;
	return ExcellentCounter(node->left, tree) + ExcellentCounter(node->right, tree) + IsXLent(getFinalGrade(tree, node->ID));
}



void checkstatus(StudentNode* node, BST* tree,int* G,int*V,int*E) {

	if (node != NULL) {
		checkstatus(node->left, tree,G,V,E);
		int tempgrade = getFinalGrade(tree, node->ID);
		if (56 <= tempgrade && tempgrade <= 75)
			G += 1;
		else if (76 <= tempgrade && tempgrade <= 94)
			V++;
		else if (95 <= tempgrade && tempgrade <= 100)
			E++;
		checkstatus(node->right, tree,G,V,E);
	}
	
}



//
//void PrintData(StudentNode* node, BST* tree) {
//	if (node != NULL) {
//		PrintData(node->left, tree);
//		printf("%d\t%d\t%d\t%d\n", node->ID, node->midTestGrade, node->testGrade, getFinalGrade(tree, node->ID));
//		PrintData(node->right, tree);
//
//	}
//}




void RepostStatistics(BST* tree) {

	StudentNode* node = tree->root;
	int good = GoodCounter(node,tree), veryGood = VeryGoodCounter(node,tree), excellent = ExcellentCounter(node,tree);
	int* ptrgood = &good;
	checkstatus(node, tree,ptrgood,&veryGood,&excellent);
	printf("\t  Degree\t final grade\n");
	printf("Good\t  (56-75)\t %d\nVery good (76-94)\t %d\nExcellent (95-100)\t %d\n", good, veryGood, excellent);

}