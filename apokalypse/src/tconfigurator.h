
#ifndef __TCONFIGURATOR_H
#define __TCONFIGURATOR_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define maxpath 1024
char* itoa(int v, char *str, int base = 10);

struct TLine{
  char* linebuf;
  TLine* nextline;
};

class TLineContainer
{
protected:
  TLine* line;

public:
  TLineContainer();
  ~TLineContainer();
  int append(char* cline);
  int insert(int num, char* cline);
  int erase(int num);
  int eraseall();
  const char* getline(int num);
  int setline(int num, char* cline);
  int numlines();
};

class TConfigurator
{
public:
  enum {fail=-1, success=0, notfound, accessdenied};

  TConfigurator(const char* fname);
  TConfigurator();
  ~TConfigurator();

	int load(const char* filename = 0);
	int save();
	int getitemstring(const char *folder, const char *item, char *text);
	int setitemstring(const char *folder, const char *item, const char *text);
	int getitemint(const char *folder, const char *item);
	int setitemint(const char *folder, const char *item, int val);
	float getitemfloat(const char *folder, const char *item);
	int setitemfloat(const char *folder, const char *item, float val);
	TLineContainer *getcontainer(){return &lc;};
	int loadshared(char* shm, long size);
	int saveshared(char* shm, long size);

	int save(const char* filename);
protected:
	bool setStrengthCompare(bool sc);
	TLineContainer lc;
	char filename[maxpath];

	bool strength_compare;
	char lastfolder[256];
	int lastfolderline;
};

#endif
