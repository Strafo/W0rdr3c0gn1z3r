#include"wordrecognizer.h"

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
}* arg_t;

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

word_recognizer_t create_recognizer(int nThread,int cs,int maxl);
void destroy_recognizer(word_recognizer_t rec);
bool set_recognizer_dictionary(const word_recognizer_t rec,const char* filename);
float recognize(const word_recognizer_t rec,const char* string);

inline void rangestrncpy(char* dest,char* src,int startpos,int endpos);

Node* create_node();
void set_node(Node* node,int start,int end);
void delete_node(Node* node);
int inorder_visit_tree(word_recognizer_t wr,char* word,int start,int end,int* word_len);
int solve_function(List* lista);






float recognize(const word_recognizer_t rec,const char* payload){
	float val;
	int j=0,len=strlen(payload);

	if(!payload){return -1;}
	if(len<rec->chuncksize){return 0;}

	
	char* string=(char*)malloc(sizeof(char)*strlen(payload));
	if(!string){
		return -1;
	}
	for(int i=0;i<strlen(payload);i++){
		if(string[i]!=' '){
			string[j]=payload[i];
			j++;
		}
	}
	string[j]='\0';
	debug(stderr,"stringa:");debug(stderr,string);debug(stderr,"\n");
	debug(stderr,"chuncksize:");debugInt(stderr,rec->chuncksize);debug(stderr,"\n");
	
	val=(float)inorder_visit_tree(rec,string,0,rec->chuncksize-1,&len)/(float)strlen(string);

	free(string);
return val;
}


int inorder_visit_tree(word_recognizer_t wr,char* word,int start,int end,int* word_len){

	Stack stack;
	Node end_value;
	stack_init(&stack);
	Node* root=create_node();
	Node* left,*right;
	set_node(root,start,end);

	while(true){

		if(root!=NULL){
			stack_push(&stack,&(root->n));
			if(root->end+1>=*word_len){
				left=NULL;
			}else{
				left=create_node();set_node(left,root->start,root->end+1);
			}

			root=left;
		}else{
			if(stack_empty(&stack)){
				break;
			}
			root=stack_entry(stack_pop(&stack),struct _node,n);
			//printf("start:%d  end:%d\n",root->start,root->end);

			if(root->end+1>=*word_len||root->end+wr->chuncksize>=*word_len){
				right=NULL;
			}else{
				right=create_node();set_node(right,root->end+1,root->end+wr->chuncksize);
			}
			if(list_push_value(wr->queue,(void*)root)<0){
				debug(stderr,"ERROR pushing root_value");return -1;
			}
			root=right;
		}
	}


	end_value=create_node();
	set_node(&end_value,-1,-1);//-1=end_value
	if(list_push_value(wr->queue,(void*)end_value)<0){
		debug(stderr,"ERROR pushing end_value to work queue");return -1;
	}
	

	get_future();
	return 0;
}



void* recognizer_work(void* arg){

	linked_list_t jobs_list=((arg_t)arg)->wr->queue;

	Cell* cella;
	char* stringa;
	bool uscita=false;
	Node *first,*second,*third,*skip;
	int first_result,second_result,third_result,skip_result;
	List results;

	list_init(&results);
	


	while(!uscita){

		while((first=list_fetch_value(jobs_list,0))==NULL);
		while((second=list_fetch_value(jobs_list,0))==NULL);
		while((third=list_fetch_value(jobs_list,0))==NULL);
		while((skip=list_fetch_value(jobs_list,0))==NULL);
		if(skip->start==-1){
			uscita=true;//è arrivato il segnale per la terminazione per il prossimo giro
		}

		//check in the dictionary cache ecc...
		first_result=
		second_result=check_word
		third_result=
		if(!uscita){
			skip_result=
		}

		cella=(Cell*)malloc(sizeof(struct _cell));
		if(!cella){debug(stderr,"ERRORE malloc recognizer_work");}

		if(second_result+third_result>=first_result){
			cella->value=second_result+third_result;
			list_insert_back(&results,cella);
		}else{
			cella->value=first_result;
			list_insert_back(&result,cella);
		}

		if(!cella){
			cella=(Cell*)malloc(sizeof(struct _cell));
			cella->value=skip_result;
			list_insert_back(&result,cella);
		}
	}


	result=solve_function(&result);

	return (void*)&result;
}


int solve_function(List* lista){
	List temp_list;
	List *temp;
	list_init(&temp_list);
	temp=&temp_list;

	Cell *first,*second,*third,*curr,*skip;
 while(true){

	while(true){
		first=list_entry(list_front(lista),struct Cell,n);
		second=list_entry(list_front(lista),struct Cell,n);
		third=list_entry(list_front(lista),struct Cell,n);


		curr=(Cell*)malloc(sizeof(struct _cell));
		if(!curr){debug(stderr,"ERRORE malloc solve_function");}
		if(second->value+third->value>=first->value){
			curr->value=second->value+third->value;
			list_insert_back(temp,curr->n);
		}else{
			curr->value=first->value;
			list_insert_back(temp,curr->n);
		}


		if(list_empty(lista)){
			break;
		}else{
			curr=(Cell*)malloc(sizeof(struct _cell));
			if(!curr){debug(stderr,"ERRORE malloc solve_function");}
			skip=list_entry(list_front(lista),struct Cell,n);
			curr->value=skip->value;
			list_insert_back(temp,curr->n);

		}
	}

	if(list_size(temp)==1){break;}else{debug(stderr,"list size:");debugInt(stderr,list_size(temp));}
	lista=temp;
	temp=lista;

 }

return list_entry(list_front(temp),struct Cell,n);
}




Node* create_node(){
	return malloc(sizeof(struct _node));
}


void set_node(Node* node,int start,int end){
	if(node){
		node->start=start;
		node->end=end;
	}
}

void delete_node(Node* node){

}


bool set_recognizer_dictionary(const word_recognizer_t rec,const char* filename){
	return initList(rec->dictionary,filename);
}

void destroy_recognizer(word_recognizer_t rec){
	return;
}

void rangestrncpy(char* dest,char* src,int startpos,int endpos){
	for(int i=startpos,j=0;i<=endpos;i++,j++)
		dest[j]=src[i];
}

word_recognizer_t create_recognizer(int nThread,int cs,int maxl){
	if(maxl<=0||cs<=0||nThread<1)return NULL;//argumets check

	word_recognizer_t rec=(word_recognizer_t)malloc(sizeof(struct _word_recognizer));
	if(!rec){return NULL;}

	rec->tp=create_thread_pool(nThread);
	if(!rec->tp){
		free(rec);
		return NULL;
	}
	start_thread_pool(rec->tp);

	rec->queue=list_create();
	rec->cacheHit=list_create();
	rec->cacheMiss=list_create();
	rec->dictionary=create_dictionary();
	rec->chuncksize=cs;

	if((!rec->cacheMiss)||(!rec->dictionary)||(!rec->cacheHit)||!(rec->queue)){
		free(rec->cacheMiss);
		free(rec->cacheHit);
		free(rec->queue);
		free_dictionary(rec->dictionary);
		free(rec->dictionary);
		destroy_thread_pool(rec->tp);
		free(rec);
		return NULL;
	}
	
	return rec;
}