#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "customstring.h"
#include "common.h"
//Token definations
//@A.K
#define MAX_TOKEN 105

#define	_LEFT_PAREN '('
#define _RIGHT_PAREN ')'
#define _ADD '+'
#define _SUB '-'
#define _MUL '*'
#define _DIV '/'
#define _POWER '^'
#define _NUM 'N' // n for num

//Enm defination to make it clean

/*Precedence (())>(*,/)>(+, -)

*/
#define LIGINT uint_32 //Integer for lexer

typedef struct tkn {
	uint8_t token_type;
	int16_t token; /*This variable wastes space for single token and also contributes
					for less space for integers, two different struct can be used to
					define tokens one for singleton token and other for numbers but
					for now, this is not bad*/
	struct tkn *left;
	struct tkn	*right;

} Token;

#define OPERATOR_LIST_LENGTH 7
/*List of operators*/
char *OPERATORS[OPERATOR_LIST_LENGTH]={_LEFT_PAREN,
									_RIGHT_PAREN,
									_POWER, _ADD,
									_DIV, _MUL, _SUB};	//Global stuffs for something


/*Checks whether the op is in list of operators.*/
int in_op_list(char ch) {
	for(int j=0;j<OPERATOR_LIST_LENGTH;j++) {
		if(OPERATORS[j]==ch)
			return 1;
	}
	return 0;
}


#define is_int(ch) ((ch>=48 && ch<=57) ? 1:0)

Token *NEW_TOKEN() {
	Token *tkn=LigMalloc(Token, 1);
	tkn->left=NULL;
	tkn->right=NULL;
	return tkn;
}
static uint32_t LEX_POINTER;

char text[]="2-2^2+3+5";
static char *pointer=&text;
static char prev_char_type=0;


Token *get_next_token() {
	string *buffer;
	Token *tkn=NULL;

	while(*pointer==' ') {
		pointer+=1;	//skip the spaces
	}

	if(*pointer=='\0') {
		return 0;
	} else if(is_int(*pointer)) {
		buffer=new_str();
		while(is_int(*pointer)) {
			add_ch(buffer, *pointer);
			pointer+=1;
		}
		tkn=NEW_TOKEN();
		tkn->token_type=_NUM;
		tkn->token=(int16_t)atoi(buffer->str);
		prev_char_type=_NUM;
		return tkn;
	} else if(in_op_list(*pointer)) {
		buffer=new_str();
		tkn=NEW_TOKEN();
		char current=*pointer;
		if((*pointer==_ADD || *pointer==_SUB) && prev_char_type!=_NUM && is_int(*(pointer+1))) {
			//For unary operations
			pointer+=1;
			while(is_int(*pointer)) {
				add_ch(buffer, *pointer);
				pointer+=1;
			}

			tkn->token_type=_NUM;
			if(current==_ADD) {
				tkn->token=(int16_t)atoi(buffer->str);
			} else if(current==_SUB) {
				tkn->token=-1*(int16_t)atoi(buffer->str);
			}
			prev_char_type=_NUM;
			return tkn;

		} else {
			tkn->token=*pointer;
			tkn->token_type=*pointer;
			pointer+=1;
			prev_char_type=*pointer;
			return tkn;
		}
	}
	return 0;
}
int precedence(Token *a, Token *b) {
	/*
		order of precedence for binary operators
			^, (*,/), (+,-)

	*/
	if(b->token==_POWER) {return 1;}
	else if((b->token==_MUL || b->token==_DIV) && (a->token==_ADD || a->token==_SUB)){return 1;}
	else if((a->token==_ADD || a->token==_SUB) && (b->token==_ADD || b->token==_SUB)){return 1;}
	else if((a->token==_MUL || a->token==_DIV) && (b->token==_MUL || b->token==_DIV)){return 1;}
	else {return 0;}
}

Token *make_ast() {
	//Token can be used as node;
	Token *parent=NULL;
	Token *current=NULL;
	Token *prev=NULL;
	Token *prevPrev_ptr=NULL;
	Token *num=NULL, *op=NULL;
	//To DO follows precedence

}
void *evaluate(Token *ast) {
	//to do recursively execute ast
}

int main()
{

    getch();
    return 0;
}
