#ifndef C_STRING_H
#define C_STRING_H

#define _STR_BUFSIZ 5


typedef struct str{
	char *str;
	//A buffer is collection of 5  byte char
	//buffer div tells how much buffer is allocated
	// eg if buffer_div==2 it means 5*2 bytes are allocated
	// add '\0' in last
	unsigned char buffer_index; //index of \0 in str pointer 0 by default
	unsigned char buffer_div;		// 1 by default
} string;

char *get_str(string *);	//returns you with new string buffer;
string *new_str(void);
int copy_str(string */*Source*/, char */*Destination*/);
int add_ch(string *, char );
int add_str(string *, char *);
int clear_str(string *);	//clears the allocated buffer;
int free_str(string *);		//frees the string struct;



#endif // C_STRING_H
