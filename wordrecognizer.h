#ifndef WORDRECOGNIZER_H
#define WORDRECOGNIZER_H
#include<stdio.h>
#include<stdlib.h>
#include"ThreadPool/threadPool.h"
#include"ThreadPool/libhl/linklist.h"
#include"lista.h"
#include<string.h>
#include<math.h>
#include"cdsa-master/src/stack.h"
#include"cdsa-master/src/list.h"
#define WORDLEN 2

typedef struct  _word_recognizer * word_recognizer_t;

float recognize(const word_recognizer_t rec,const char* string);
word_recognizer_t create_recognizer(int nThread,int cs,int maxl);
void destroy_recognizer(word_recognizer_t rec);
bool set_recognizer_dictionary(const word_recognizer_t rec,const char* filename);






#endif