#ifndef _DICTIONARY_H
#define _DICTIONARY_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<stdbool.h>
#include<ctype.h>
#define ASCIITABLELEN 256
typedef struct _index
{
    char ch;
	char** wordsList;
	int length;
}Index;

typedef struct _dictionary
{
	char* name;
	Index** indici;

}Dictionary;





Dictionary * create_dictionary();
int add_word_dictionary(Dictionary* dictionary,const char* word);
int is_member_dictionary(Dictionary* dictionary  ,char* word);
void free_dictionary(Dictionary* dictionary);
void print_dictionary(Dictionary* dictionary);
int init_dictionary(Dictionary* dictionary,const char* filename);


/*utility*/
char *inputString(FILE* fp, size_t size);
void fdiscardline(FILE *f) ;
#endif
