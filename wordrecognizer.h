#ifndef WORDRECOGNIZER_H
#define WORDRECOGNIZER_H
#include<stdio.h>
#include<stdlib.h>
#include"Thread-Pool-C/threadPool.h"
#include"Thread-Pool-C/libhl/linklist.h"
#include"dictionary/dictionary.h"
#include<string.h>
#include<math.h>
#include"cdsa-master/stack.h"
#include"cdsa-master/list.h"
#define WORDLEN 2

typedef struct  _word_recognizer  word_recognizer_t;

float recognize(const word_recognizer_t* rec,const char* string);
word_recognizer_t* create_recognizer(int nThread,int cs,int maxlength);
void destroy_recognizer(word_recognizer_t* rec);
bool set_recognizer_dictionary(const word_recognizer_t* rec,const char* filename);






#endif

/*
struct _word_recognizer
{
	thread_pool_t tp;
	linked_list_t* queue;
	linked_list_t* cacheHit;//mutable
	linked_list_t* cacheMiss;//mutable
	Dictionary dictionary;//immutable object
	int chuncksize;
};

typedef struct _arg
{
	word_recognizer_t wr;
	char* string;
} arg_t;

typedef struct _node
{
	int start;
	int end;
	StackNode n;
}Node;

typedef struct _cell
{
	int value;
	ListNode n;
}Cell;

*/