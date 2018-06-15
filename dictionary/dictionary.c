#include"dictionary.h"



Dictionary * create_dictionary();
int add_word_dictionary(Dictionary* dictionary,const char* word);
int is_member_dictionary(Dictionary* dictionary  ,char* word);
void free_dictionary(Dictionary* dictionary);
void print_dictionary(Dictionary* dictionary);
int init_dictionary(Dictionary* dictionary,const char* filename);
void shiftArray(char** dizionario,char* toAdd,int pos,int length);
void free_index(Index* index);


inline char *inputString(FILE* fp, size_t size);
void fdiscardline(FILE *f) ;
inline void stringTolower(char* string);






void fdiscardline(FILE *f) {
    fscanf(f, "%*[^\n]");
    fgetc(f);
}

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}


int add_word_dictionary(Dictionary* dizionario,const char* word)
{	

	int index=word[0];
	char* to_be_added;
	char* prev,*succ;
    to_be_added=(char*)malloc(sizeof(char)*strlen(word));
	strcpy(to_be_added,word);

	if(!is_member_dictionary(dizionario,to_be_added)) {
		dizionario->indici[index]->length++;
		dizionario->indici[index]->wordsList=(char**)realloc(dizionario->indici[index]->wordsList,sizeof(char*)*dizionario->indici[index]->length);


		if(dizionario->indici[index]->length==1){
			dizionario->indici[index]->wordsList[0]=to_be_added;
			return 1;
		}

		if(dizionario->indici[index]->length==2){
			if(strcmp(to_be_added,dizionario->indici[index]->wordsList[0])<0){
				dizionario->indici[index]->wordsList[1]=to_be_added;
			}else{
				shiftArray(dizionario->indici[index]->wordsList,to_be_added,0,dizionario->indici[index]->length);
			}
			return  1;
		}


		for (int i = 1; i < dizionario->indici[index]->length - 1; i++) {
			prev=dizionario->indici[index]->wordsList[i-1];
			succ=dizionario->indici[index]->wordsList[i];
			if(strcmp(to_be_added,prev)>0&&strcmp(to_be_added,succ)<0){
				shiftArray(dizionario->indici[index]->wordsList,to_be_added,i,dizionario->indici[index]->length);
				return 1;
			}

		}
		dizionario->indici[index]->wordsList[dizionario->indici[index]->length-1]=to_be_added;//add to the tail
		return 1;
	}

	return 0;//not addedd is already member
}





int is_member_dictionary(Dictionary* dizionario ,char* word){
	Index* curr=dizionario->indici[(int)word[0]];
	int mid;
	int l_index=0;
	int r_index=curr->length-1;
	int res;
	while(l_index<=r_index){
	    mid=l_index+((r_index-l_index)/2);
		if((res=strcmp(word,curr->wordsList[mid]))<0){
            r_index=mid-1;
		}else{
		    if(res>0){
		        l_index=mid+1;
		    }else{
		        return 1;
		    }
		}

	}
	if(curr->length>=1){//tapullo per bug :non controlla la cella in posizione 0
        if(strcmp(word,curr->wordsList[0])==0)  return 1; else return 0;
	}

return 0;
}

Dictionary * create_dictionary(){

	Dictionary* dizionario=(Dictionary*)malloc(sizeof(struct _dictionary));
	if(!dizionario){
		fprintf(stderr,"ERROR:Unable to create _dictionary\n");
		return NULL;
	}
	dizionario->indici=(Index**)malloc(sizeof(Index*)*ASCIITABLELEN);
	for(int i=0;i<ASCIITABLELEN;i++){
		dizionario->indici[i]=(Index*)malloc(sizeof(struct _index));
		dizionario->indici[i]->ch=i;
	}
return dizionario;
}




void shiftArray(char** words_list,char* toAdd,int pos,int length){
	 char *temp,*temp2;
	 temp=toAdd;
	for(int i=pos;i<length;i++){
		temp2=words_list[i];
		words_list[i]=temp;
		temp=temp2;
	}
}


void free_index(Index* index){
	for(int i=0;i<index->length;i++){
		free(index->wordsList[i]);
	}
	free(index);
}
void free_dictionary(Dictionary* dizionario){
	for(int i=0;i<ASCIITABLELEN;i++){
		free_index(dizionario->indici[i]);
	}
	free(dizionario->name);
	free(dizionario);
}

void print_index(Index* index){
	printf("<%c>-------------------------------------\n",index->ch);
	for(int i=0;i<index->length;i++){
		printf("%s\n",index->wordsList[i]);
	}

}
void print_dictionary(Dictionary* dizionario){
	printf("DICTIONARY------------------------------------------------\n");
	for(int i=0;i<ASCIITABLELEN;i++){
		print_index(dizionario->indici[i]);
	}
	printf("----------------------------------------------------------\n");
}

int nLines(FILE* fp){
	char ch;
	int lines=0;
	while(!feof(fp))
	{
  		ch = fgetc(fp);
  	if(ch == '\n')
  	{
    	lines++;
  	}
	}
	rewind(fp);
	return lines;
}
int init_dictionary(Dictionary* dizionario,const char* filename){
	FILE *fp;
	char* line;
	int lines;
	if(dizionario==NULL||filename==NULL){
		fprintf(stderr,"dizionario o filename ==NULL");
		return 0;
	}

	fp=fopen(filename,"r");
	if(!fp){
		return 0;
	}
	dizionario->name=(char*)malloc(sizeof(char)*strlen(filename));
	strcpy(dizionario->name,filename);
	lines=nLines(fp);
 	for(int i=0;i<lines;i++){
		//fdiscardline(fp);
		line = inputString(fp, 1);
		stringTolower(line);
		add_word_dictionary(dizionario,line);

	}
fclose(fp);
return 1;
}


void stringTolower(char* str){

	for(int i = 0; i<strlen(str); i++)
  		str[i] = tolower(str[i]);
}