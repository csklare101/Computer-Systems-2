/*-------------------------------------------------------------------------*
 *---									---*
 *---		wordCounterHeader.h					---*
 *---									---*
 *---	    This file includes common header files and declares structs	---*
 *---	needed by .c files of the wordCounter program.			---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//---			    Common inclusions:			---//
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>


//---			    Common constants:			---//
#define		SMALL_TEXT_LEN	256


//---			      Common types:			---//
struct		TreeNode
{
  char*			wordCPtr_;
  int			count_;
  struct TreeNode*	leftPtr_;
  struct TreeNode*	rightPtr_;
};


struct		ListNode
{
  char*			wordCPtr_;
  int			count_;
  struct ListNode*	nextPtr_;
};


//---		    Declarations of global functions:			---//
//  YOUR CODE HERE!
extern int textLen;
extern char* positionHandle;	
extern void removeNewLine(char* cPtr);
extern int didGetWord(char** positionHandle, char* word);
extern struct TreeNode* buildTree(FILE* filePtr);
extern void printTree(struct TreeNode* nodePtr);
extern void freeTree(struct TreeNode* nodePtr);
extern struct ListNode* buildList(FILE* filePtr);
extern void printList(struct ListNode* firstPtr);
extern void freeList(struct ListNode* firstPtr);
