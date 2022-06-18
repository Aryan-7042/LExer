#ifndef _COMMON_H
#define _COMMON_H


#define LigMalloc(type, numb) \
		((type*)malloc(numb*sizeof(type)))

#define LigFree(ptr) \
		(free(ptr))

#endif // _COMMON_H
