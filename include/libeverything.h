#ifndef _LIB_EVERYTHING_H
#define _LIB_EVERYTHING_H

#include <nanoshell.h>
#include <fs.h>

#define printf LogMsgNoCr

typedef struct
{
	int fd;
}
FILE;

#define stdout ((FILE*)-1)
#define stderr ((FILE*)-2)
#define stdin  ((FILE*)-3)

#define EISDIR -10000000//TODO

//stdio
FILE* fopen (const char *pFileName, const char* pMode);
int fclose (FILE* pStream);
size_t fread (void* pPtr, size_t nSize, size_t nMemb, FILE* pStream);
size_t fwrite (const void* pPtr, size_t nSize, size_t nMemb, FILE* pStream);
size_t ftell (FILE* pStream);
int fseek (FILE* pStream, int offset, int whence);
int fprintf(FILE* pStream, const char* pFormat, ...);
int atox(const char* str);
double atof(const char *arr);
void sprintf(char*s, const char*format, ...);
void vsprintf(char*s, const char*format, va_list args);

//TODO
#define snprintf(b,n,c,...) sprintf(b,c,__VA_ARGS__)

//string
char* strchr (const char* s, char c);
char* strrchr(const char* s, char c);
char* strdup (const char* pStr);
char* strstr (const char *s1, const char *s2);

//stdlib
void* malloc(size_t size);
void  free(void* ptr);
void  exit(int n);
void  remove(const char* pFileName);
int   mkdir(const char* path, int mode);

//ctype
bool isalnum(char c);
bool isalpha(char c);
bool isblank(char c);
bool iscntrl(char c);
bool isdigit(char c);
bool isgraph(char c);
bool islower(char c);
bool isupper(char c);
bool isprint(char c);
bool isspace(char c);
bool isxdigit(char c);

char tolower(char c);
char toupper(char c);

int abs(int i);
double fabs(double f);
int rename(const char* old, const char* new);
int fflush(FILE* pFile);
void puts(const char* s);
void putchar(char c);
int system(const char* cmd);
int vfprintf(FILE* pStream, const char* pFormat, va_list list);

size_t strnlen(const char* ptext, size_t n);
char * strncpy (char *s1, const char *s2, size_t n);
int strncmp(const char *s1, const char *s2, register size_t n);
//doomgeneric

uint32_t DG_GetTicksMs();
void DG_SleepMs();
void DG_DrawFrame();


#endif//_LIB_EVERYTHING_H