/* File I/O (C) 2022 iProgramInCpp*/
#include <stdio.h>
#include <fs.h>

#define TOLOWER(a) tolower(a)//(((a)>='A'&&(a)<='Z')?((a)+0x20):(a))

//taken from https://code.woboq.org/userspace/glibc/string/strcasecmp.c.html

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
int strcasecmp (const char *s1, const char *s2)
{
	const unsigned char *p1 = (const unsigned char *) s1;
	const unsigned char *p2 = (const unsigned char *) s2;
	int result;
	
	if (p1 == p2)
		return 0;
	
	while ((result = tolower (*p1) - tolower (*p2++)) == 0)
		if (*p1++ == '\0')
			break;
	return result;
}
/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
int strncasecmp (const char *s1, const char *s2, size_t n)
{
	const unsigned char *p1 = (const unsigned char *) s1;
	const unsigned char *p2 = (const unsigned char *) s2;
	int result;
	if (p1 == p2 || n == 0)
		return 0;
	while ((result = tolower (*p1) - tolower (*p2++)) == 0)
		if (*p1++ == '\0' || --n == 0)
			break;
	return result;
}

bool isalnum(char c)
{
	return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9');
}
bool isalpha(char c)
{
	return (c>='a'&&c<='z')||(c>='A'&&c<='Z');
}
bool isblank(char c)
{
	return (c==' '||c=='\n'||c=='\0');
}
bool iscntrl(char c)
{
	return (c>=0&&c<=0x1F);
}
bool isdigit(char c)
{
	return (c>='0'&&c<='9');
}
bool isgraph(char c)
{
	return (c>='!'&&c<=0x7E);
}
bool islower(char c)
{
	return (c>='a'&&c<='z');
}
bool isprint(char c)
{
	return (c>=' '&&c<=0x7E);
}
bool isspace(char c)
{
	return (c==' '||c=='\n');
}
bool isupper(char c)
{
	return (c>='A'&&c<='Z');
}
bool isxdigit(char c)
{
	return (c>='a'&&c<='f')||(c>='A'&&c<='F')||(c>='0'&&c<='9');
}
char tolower (char c)
{
	if (isupper(c)) return c+0x20; else return c;
}
char toupper (char c)
{
	if (islower(c)) return c-0x20; else return c;
}
char* strdup (const char* pStr)
{
	int ln = strlen(pStr)+1;
	char* buf = malloc(ln + 1);
	strcpy(buf, pStr);
	return buf;
}

void* g_allocations[10000];

void* malloc(size_t size)
{
	int spot = -1;
	for (int i = 0; i < 10000; i++)
	{
		if (g_allocations[i] == NULL)
		{
			spot = i; break;
		}
	}
	if (spot == -1)
		LogMsg("No spot found! The program can go crazy!!");
	
	void* pReturn = Allocate(size);
	if (spot != -1)
		g_allocations[spot] = pReturn;
	return pReturn;
}
void free(void* ptr)
{
	for (int i = 0; i < 10000; i++)
	{
		if (g_allocations[i] == ptr)
		{
			g_allocations[i] =  NULL;
			break;
		}
	}
	return Free(ptr);
}
void ns$FreeEverything(void)
{
	for (int i = 0; i < 10000; i++)
	{
		if (g_allocations[i] != NULL)
		{
			Free(g_allocations[i]);
			g_allocations[i] = NULL;
		}
	}
}
char* strchr(const char* s, char c)
{
	//demote a pointer from const? isn't that bad?
	while (*s)
	{
		if (*s == c) return (char*)s;
		s++;
	}
	return NULL;
}
char* strrchr(const char* s, char c)
{
	char* sr = (char*)s;
	while (*sr) sr++;
	//TODO demote a pointer from const? isn't that bad?
	while (sr != s)
	{
		sr--;
		if (*sr == c) return sr;
	}
	return NULL;
}

int abs(int i)
{
	return i>0?i:-i;
}
double fabs(double f)
{
	return f>0?f:-f;
}

int rename(const char* old, const char* new)
{
	LogMsg("NS: Rename attempt ('%s'->'%s')", old, new);
	return -1;
}
int mkdir(const char* path, int mode)
{
	LogMsg("NS: MKDIR attempt ('%s' mode %d)", path, mode);
	return -1;
}
int fflush(__attribute__((unused)) FILE* pFile)
{
	return 0;//stub
}
void puts(const char* s)
{
	LogMsg ("%s", s);
}
void putchar(char c)
{
	LogMsgNoCr("%c", c);
}
int atox(const char* str) 
{
	int f = 0;
	int s = 1;
	int i = 0;
	if (str[0] == '-')
	{
		i++;
		s = -1;
	}
	for (; str[i] != '\0'; i++)
	{
		f = f * 16;
		if (str[i] >= 'a' && str[i] <= 'f')
			f += str[i] - 'a' + 0xa;
		else if (str[i] >= 'A' && str[i] <= 'F')
			f += str[i] - 'A' + 0xA;
		else f += str[i] - '0';
	}
	
	return s * f;
}
int system(const char* cmd)
{
	LogMsg("NS: Shell command attempt ('%s')", cmd);
	return -1;
}
size_t strnlen(const char* ptext, size_t n)
{
	size_t k = 0;
	while (*ptext)
	{
		k++;
		if (k == n) return n;
		ptext++;
	}
	return k;
}
char * strncpy (char *s1, const char *s2, size_t n)
{
	size_t size = strnlen (s2, n);
	if (size != n)
		memset (s1 + size, '\0', n - size);
	return memcpy (s1, s2, size);
}
int strncmp(const char *s1, const char *s2, register size_t n)
{
	unsigned char u1, u2;
	while (n-- > 0)
	{
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (u1 != u2)
			return u1 - u2;
		if (u1 == '\0')
			return 0;
	}
	return 0;
}
char * strstr (const char *s1, const char *s2)
{
	const char *p = s1;
	const size_t len = strlen (s2);
	for (; (p = strchr (p, *s2)) != 0; p++)
	{
		if (strncmp (p, s2, len) == 0)
			return (char *)p;
	}
	return (0);
}
//stolen from https://stackoverflow.com/questions/52391330/create-a-precise-atof-implementation-in-c
double atof(const char *arr)
{
	float val = 0;
	int afterdot=0;
	float scale=1;
	int neg = 0; 
	
	if (*arr == '-') {
		arr++;
		neg = 1;
	}
	while (*arr) {
		if (afterdot) {
			scale = scale/10;
			val = val + (*arr-'0')*scale;
		} else {
			if (*arr == '.') 
				afterdot++;
			else
				val = val * 10.0 + (*arr - '0');
		}
		arr++;
	}
	if(neg) return -val;
	else    return  val;
}
void vsprintf(char* memory, const char* format, va_list list);
int vfprintf(FILE* pStream, const char* pFormat, va_list list)
{
	char buff[8192];
	vsprintf(buff, pFormat, list);
	if (pStream == stdout || pStream == stderr || pStream == stdin)
	{
		PutString(buff);
	}
	else
	{
		FiWrite(pStream->fd, buff, strlen(buff));
	}
	return strlen(buff);
}
int fprintf(FILE* pStream, const char* pFormat, ...)
{
	va_list list;
	va_start(list, pFormat);
	char buff[8192];
	vsprintf(buff, pFormat, list);
	va_end(list);
	if (pStream == stdout || pStream == stderr || pStream == stdin)
	{
		PutString(buff);
	}
	else
	{
		FiWrite(pStream->fd, buff, strlen(buff));
	}
	return strlen(buff);
}



FILE* fopen (const char *pFileName, const char* pMode)
{
	int posix = 0;
	while (*pMode)
	{
		switch (*pMode)
		{
			case 'r':
				posix |= O_RDONLY;
				break;
			case 'w':
				posix |= O_WRONLY;
				break;
			case 'b':
				break;
		}
		pMode++;
	}
	int fd = FiOpen (pFileName, posix);
	if (fd < 0)
	{
		LogMsg("ERROR: Could not open file '%s' with mode parms '%s' (got error %d)", pFileName, pMode, fd);
		return NULL;
	}
	
	FILE* pFile = malloc(sizeof(FILE));
	pFile->fd = fd;
	
	return pFile;
}
int fclose (FILE* pStream)
{
	if (!pStream) return -1;
	
	FiClose(pStream->fd);
	
	Free(pStream);
	return 0;
}
__attribute__((noreturn)) void exit1(int n);
__attribute__((noreturn)) void exit(int n)
{
	LogMsg("NS:Exiting! Error code : %d", n);
	//while (1) __asm__ volatile("hlt\n\t");
	exit1(n);
}
void remove(const char* pFileName)
{
	LogMsg("NS:Remove attempt (%s)", pFileName);
}

size_t fread (void* pPtr, size_t nSize, size_t nMemb, FILE* pStream)
{
	if (!pStream) return 0;
	return FiRead(pStream->fd, pPtr, nSize * nMemb);
}
size_t fwrite (const void* pPtr, size_t nSize, size_t nMemb, FILE* pStream)
{
	LogMsg("NS:fwrite not implemented. TODO! (Parms: %x %d %d %x(%d))", pPtr, nSize, nMemb, pStream, pStream->fd);
	return 0;
}
size_t ftell (FILE* pStream)
{
	if (!pStream) return 0;
	return FiTell (pStream->fd);
}
int fseek (FILE* pStream, int offset, int whence)
{
	if (!pStream) return 0;
	return FiSeek (pStream->fd, offset, whence);
}
