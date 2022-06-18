#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "customstring.h"
#include "common.h"

int is_bigend() {
	unsigned short test=0xAAFF;
	unsigned char first_byte=*((unsigned char*)&test);
	if (first_byte==0xFF) {
		return 0;    //little endian
	}
	return 1;	//big endian
}


char *get_str(string *str) {
	return str->str;
}

int copy_str(string *str, char *ptr) {
	strcpy(ptr, str->str);
	return 1; //no use
}
int add_ch(string *str, char ch) {
	uint8_t space_left=((5+str->buffer_index)%5)-1; //space left in the 5 byte buffer;
	uint8_t *buf_ind=&(str->buffer_index);
	if(space_left>0) {
		//add char to last and shift the terminating char at last
		str->str[*buf_ind]=ch;
		*buf_ind+=1;
		str->str[*buf_ind]='\0';

	} else {
		// when no space is left
		//alocate new div
		str->str=(char *)realloc(str->str, *buf_ind*5);

		str->str[*buf_ind]=ch;
		str->str[*buf_ind+1]='\0';
		*buf_ind+=1;
		str->buffer_div+=1;

	}
	return EXIT_SUCCESS;
}
int add_str(string *str, char *buffer) {

	char *chr=buffer;

	while(*chr!='\0') {

		add_ch(str, *chr);
		chr+=1;
	}

}

int clear_str(string *str) {
	free(str->str);
	str->buffer_div=0;
	str->buffer_index=0;
	return 1;
}

int free_str(string *str) {
	free(str->str);
	free(str);
	return 1;
}
string *new_str() {
	string *s=LigMalloc(string, 1);
	s->str=LigMalloc(char, _STR_BUFSIZ);
	s->str[0]='\0';
	s->buffer_index=0;
	s->buffer_div=1;
	return s;
}
