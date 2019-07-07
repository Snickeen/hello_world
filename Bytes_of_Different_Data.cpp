#include<stdio.h>
#include<stdint.h>
#include<stdbool.h> 

int main()
{
    printf("some kinds of data && their bytes\n");

    printf("char        : %d Bytes\n",sizeof(char));
    printf("short       : %d Bytes\n",sizeof(short));
    printf("int         : %d Bytes\n",sizeof(int));
    printf("long        : %d Bytes\n",sizeof(long));
    printf("long long   : %d Bytes\n",sizeof(long long));
    printf("float       : %d Bytes\n",sizeof(float));
    printf("double      : %d Bytes\n",sizeof(double));
    printf("long double : %d Bytes\n",sizeof(long double));

	printf("bool        : %d Bytes\n",sizeof(bool));
	
	
    
    printf("int8_t      : %d Bytes\n",sizeof(int8_t));
    printf("int16_t     : %d Bytes\n",sizeof(int16_t));
//    printf("int32       : %d Bytes\n",sizeof(int32));
    printf("int32_t     : %d Bytes\n",sizeof(int32_t));
//    printf("int64       : %d Bytes\n",sizeof(int64));
    printf("int64_t     : %d Bytes\n",sizeof(int64_t));
//    printf("int128      : %d Bytes\n",sizeof(int128));
//    printf("int128_t    : %d Bytes\n",sizeof(int128_t));
    printf("__int128    : %d Bytes\n",sizeof(__int128)); 


    printf("char*        : %d Bytes\n",sizeof(char*));
    printf("short*       : %d Bytes\n",sizeof(short*));
    printf("int*         : %d Bytes\n",sizeof(int*));
    printf("long*        : %d Bytes\n",sizeof(long*));
    printf("long long*   : %d Bytes\n",sizeof(long long*));
    printf("float*       : %d Bytes\n",sizeof(float*));
    printf("double*      : %d Bytes\n",sizeof(double*));
    printf("long double* : %d Bytes\n",sizeof(long double*));


    return 0;
}



/*

F:\github\hello_world>g++ -m32  Bytes_of_Different_Data.cpp

F:\github\hello_world>a.exe
some kinds of data && their bytes
char        : 1 Bytes
short       : 2 Bytes
int         : 4 Bytes
long        : 4 Bytes
long long   : 8 Bytes
float       : 4 Bytes
double      : 8 Bytes
long double : 12 Bytes
char*        : 4 Bytes
short*       : 4 Bytes
int*         : 4 Bytes
long*        : 4 Bytes
long long*   : 4 Bytes
float*       : 4 Bytes
double*      : 4 Bytes
long double* : 4 Bytes

F:\github\hello_world>g++ -m64  Bytes_of_Different_Data.cpp -std=gnu++11 -o c.exe

F:\github\hello_world>c.exe
some kinds of data && their bytes
char        : 1 Bytes
short       : 2 Bytes
int         : 4 Bytes
long        : 4 Bytes
long long   : 8 Bytes
float       : 4 Bytes
double      : 8 Bytes
long double : 16 Bytes
bool        : 1 Bytes
int8_t      : 1 Bytes
int16_t     : 2 Bytes
int32_t     : 4 Bytes
int64_t     : 8 Bytes
__int128    : 16 Bytes
char*        : 8 Bytes
short*       : 8 Bytes
int*         : 8 Bytes
long*        : 8 Bytes
long long*   : 8 Bytes
float*       : 8 Bytes
double*      : 8 Bytes
long double* : 8 Bytes

*/
