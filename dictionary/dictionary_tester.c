/*list_tester*/

#include"dictionary.h"



int main(){
	
	Dictionary* dizionario=create_dictionary();
	char *m;int scelta;
	bool loop=true;


	if(!init_dictionary(dizionario,"dictionary2.txt")){
			perror("ERRORE inserimento dizionario D;\n");
			return 1;
	}
	
	while(loop){
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("Cosa vuoi fare \n1:addword\n2:isMember\n3:stampa dizionario\n4:exit\n");
		scanf("%d",&scelta);
		switch(scelta){
			case 1:
				fdiscardline(stdin);
				m = inputString(stdin, 10);
				if( !add_word_dictionary(dizionario,m)){
					perror("ERRORE inserimento dizionario D;\n");
					return 1;
				}	
			break;
			case 2:
				fdiscardline(stdin);
				m = inputString(stdin, 10);
				if( is_member_dictionary(dizionario,m)){
					printf("Membro!\n");
				}else{printf("Non Membro\n");}
			break;
			case 3:
			print_dictionary(dizionario);
			break;
			case 4:
            default:
				loop=false;
			break;
		}
	}

	printf("Libero la memoria\n");
	free_dictionary(dizionario);

}

