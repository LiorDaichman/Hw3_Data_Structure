#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef struct StudentNode {
	int ID;
	int Mid_year_test;
	int End_year_test;
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
int Proper(StudentNode*, BST*);
int Size_of_tree(StudentNode*);
void reportGrades(BST*);
int getNumOfFails(BST*);
void RepostStatistics(BST*);