#include"wordrecognizer.h"

int main()
{
	word_recognizer_t* wr=create_recognizer(4,1,45);
	if(!set_recognizer_dictionary(wr,"dictionary2.txt")){
	perror("ERR INIT");
	}
	printf("\n\n\n\n\nStarting:\n");
	printf("result:%f",recognize(wr,"abibl\0"));
}

/*abandonedly*/