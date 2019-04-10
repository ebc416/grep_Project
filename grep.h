//EFrain Bonilla Caudillo 223C MW 2pm-3:50pm
// https://github.com/ebc416/grep_Project
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

const int BLKSIZE = 4096;  const int NBLK = 2047;  const int FNSIZE = 128;  const int LBSIZE = 4096;
const int ESIZE = 256; const int GBSIZE = 256;  const int NBRA = 5;
const int CBRA = 1; const int CCHR = 2;  const int CDOT = 4;  const int CCL = 6;  const int NCCL = 8;  const int CDOL = 10;
const int CEOF = 11;  const int CKET = 12;  const int CBACK = 14;  const int CCIRC = 15;  const int STAR = 01;
const int READ = 0;  const int WRITE = 1;

int  peekc, lastc, given, ninbuf, io, pflag;
int oflag, listf, listn, col, tfile  = -1, tline, iblock  = -1, oblock  = -1, ichanged, nleft;
int  names[26], nbra, fchange;
unsigned nlall = 128;
unsigned int  *addr1, *addr2, *dot, *dol, *zero;

char  Q[] = "", T[] = "TMP", savedfile[FNSIZE], file[FNSIZE], linebuf[LBSIZE], expbuf[ESIZE+4];
char  genbuf[LBSIZE], *nextip, *globp, *mkdtemp(char *), tmpXXXXX[50] = "/tmp/eXXXXX";
char  *tfname, *loc1, *loc2, ibuff[BLKSIZE], obuff[BLKSIZE], WRERR[]  = "WRITE ERROR", *braslist[NBRA], *braelist[NBRA];
char  line[70];  char  *linp  = line;

void commands(void); unsigned int *address(void);  int advance(char *lp, char *ep);
int append(int (*f)(void), unsigned int *a);  int backref(int i, char *lp);
void blkio(int b, char *buf, long (*iofcn)(int, void*, unsigned long));
void defchar(char *ep, int c);
void cerror(void);
int star(char *lp, char *ep, char *curlp);
int cclass(char *set, int c, int af);  void compile(int eof);
void error(char *s);  int execute(unsigned int *addr);  void exfile(void);
void filename(const char *file_name); char *getblock(unsigned int atl, int iof); int getchr(void);
int getfile(void);  int getnum(void);
void global(int k);  void init(void);
void newline(void);  void nonzero(void);
void print(void);  void putchr_(int ac);
int putline(void);  void puts_(char *sp);
void setwide(void);  void setnoaddr(void);  void squeeze(int);
char grepbuf[GBSIZE];

typedef void (*SIG_TYP)(int);
SIG_TYP  oldhup, oldquit;  //const int SIGHUP = 1;  /* hangup */   const int SIGQUIT = 3;  /* quit (ASCII FS) */
