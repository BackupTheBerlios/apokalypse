
#include "tconfigurator.h"
#include <math.h>

#define maxfilesize 65536
#define maxlinesize 80

char* itoa(int v, char *str, int base){
  *str = 0;
  if (v == 0) {strcat(str,"0"); return str;}
  if (v < 0) {strcat(str,"-"); v *= -1;}

  int stellen = (int)log10(v);
  div_t quot;
  int q;
  char c[2]; c[1] = 0;

  for (q = stellen; q >= 0; q--){
    quot = div(v, (int)pow(10,q));
    v = v - (quot.quot * (int)pow(10,q));
    switch (quot.quot){
      case 0: c[0] = '0';break;
      case 1: c[0] = '1';break;
      case 2: c[0] = '2';break;
      case 3: c[0] = '3';break;
      case 4: c[0] = '4';break;
      case 5: c[0] = '5';break;
      case 6: c[0] = '6';break;
      case 7: c[0] = '7';break;
      case 8: c[0] = '8';break;
      case 9: c[0] = '9';break;
      default: c[0] ='#';
    };
    strcat(str, (char*)&c);
  }
  return str;
}

TLineContainer::TLineContainer(){
  line = 0;
}

TLineContainer::~TLineContainer(){
  eraseall();
}

int TLineContainer::append(char* cline){
  TLine *tmpln = line;
  int cnt = 1;

  if (line == 0){
    line= new TLine;
    tmpln= line;
  }else{
    while (tmpln->nextline != 0){
    tmpln = tmpln->nextline;
    cnt++;
    }
    tmpln->nextline = new TLine;
    tmpln = tmpln->nextline;
    cnt++;
  }
  tmpln->nextline = 0;
  tmpln->linebuf = (char*)malloc(strlen(cline)+1);
  strcpy(tmpln->linebuf, cline);

  return cnt;
}

int TLineContainer::numlines(){
  TLine* tmpline = line;
  int cnt = 0;

  while (tmpline != 0){
  tmpline = tmpline->nextline;
  cnt++;
  }
  return cnt;
}

int TLineContainer::insert(int num, char* cline){
  TLine *tmpline_prev = line, *tmpline;
  int cnt = 2;

  if (line == 0) return append(cline);
  if (num == 1){
    tmpline_prev = new TLine;
    tmpline_prev->nextline = line;
    tmpline_prev->linebuf = (char*)malloc(strlen(cline)+1);
    strcpy(tmpline_prev->linebuf, cline);
    line = tmpline_prev;
    return 1;
  }

  while ((tmpline_prev != 0) && (num > cnt)){
  tmpline_prev = tmpline_prev->nextline;
  cnt++;
  }
  if (tmpline_prev == 0) return append(cline);
     else{
     tmpline = new TLine;
     tmpline->nextline = tmpline_prev->nextline;
     tmpline->linebuf = (char*)malloc(strlen(cline)+1);
     strcpy(tmpline->linebuf, cline);
     tmpline_prev->nextline = tmpline;
     }
  return cnt;
}

int TLineContainer::erase(int num){
  TLine *tmpline_prev = line, *tmpline;
  int cnt = 2;

  if (numlines() < num) return -1;
  if (num == 1){
    tmpline = line;
    line = line->nextline;
    free(tmpline->linebuf);
    delete(tmpline);
    return 0;
  }
  tmpline = line->nextline;
  while ((tmpline != 0) && (num > cnt)){
    tmpline = tmpline->nextline;
    tmpline_prev = tmpline_prev->nextline;
    cnt++;
  }
  if (tmpline == 0) return -1;
  tmpline_prev->nextline = tmpline->nextline;
  free(tmpline->linebuf);
  delete(tmpline);
  return 0;
}

int TLineContainer::eraseall(){
  TLine* tmpln = line;

  while (line != 0){
  tmpln = line->nextline;
  free(line->linebuf);
  delete(line);
  line = tmpln;
  }
  return 0;
}

const char* TLineContainer::getline(int num){
  TLine* tmpline = line;
  int cnt = 1;
  static char strnull = 0;

  while ((tmpline != 0) && (num != cnt)){
  tmpline = tmpline->nextline;
  cnt++;
  }
  if ((tmpline == 0) || (tmpline->linebuf == 0)) return (const char*)&strnull;
     else return tmpline->linebuf;
}

int TLineContainer::setline(int num, char* cline){
  TLine* tmpline = line;
  int cnt = 1;

  while ((tmpline != 0) && (num != cnt)){
  tmpline = tmpline->nextline;
  cnt++;
  }
  if (tmpline == 0) return -1;
  if (tmpline->linebuf != 0) free(tmpline->linebuf);
  tmpline->linebuf = (char*)malloc(strlen(cline)+1);
  strcpy(tmpline->linebuf, cline);

  return 0;
}

//----------------------------------------------------------------

TConfigurator::TConfigurator(const char* fname){
	strength_compare = true;
  strcpy((char*)&filename, fname);
  lastfolder[0]=0;
  if (fname) load();
}

TConfigurator::TConfigurator(){
	strength_compare = true;
	filename[0] = 0;
	lastfolder[0]=0;
}

TConfigurator::~TConfigurator(){
  lc.eraseall();
}

int TConfigurator::getitemstring(const char *folder, const char *item, char *text){
  int i,startline = 1;
  char str[maxlinesize];
  char *strp, *folderstart, *folderend, *itemstart, *itemend, *textstart;
  bool folderfound = false;
  *text = 0;

	if (!strcmp(lastfolder,folder) && lastfolderline >= 0) startline = lastfolderline;

  for (i = startline; i <= lc.numlines(); i++){
    strcpy((char*)&str, lc.getline(i));
    strp = strchr((char*)&str, ';');
    if (strp != 0) *strp = 0;  //Kommentare abschneiden
    strp = (char*)&str;
    while ((((unsigned char)*strp) <= ' ') && (((unsigned char)*strp) > 0)) strp++; //fhrende Leerzeichen abschneiden
    if (strlen((char*)&str) > 0){
       if (*strp == '['){
	 if (folderfound) return -1;
	 folderstart = strp+1;
	 folderend = strchr(folderstart, ']');
	 if (folderend){
	   *folderend = 0;
			if (strength_compare)
				{if (!strcmp(folderstart,folder)){
					folderfound = true;
					strcpy(lastfolder,folder);
					lastfolderline = i;}}else
	   		{if (strstr(folderstart, folder)){
					strcpy(lastfolder,folder);
					lastfolderline = i;
					folderfound = true;}}
	 }
       }else{
	 if (folderfound){
	   itemstart = strp;
	   itemend = strchr(itemstart, '=');
	   if (itemend){
	     textstart = itemend+1;
			 while ((itemend > itemstart) && (((unsigned char)*(itemend-1)) <= ' ')) itemend--;
	     *itemend = 0;
       while (*textstart == ' ') textstart++; //Führende Leerzeichen abschneiden
			if (strength_compare){
	     if (!strcmp(itemstart, item)){
	       strcpy(text, textstart);
	       return 0;
	     }}else{
	     if (strstr(itemstart, item)){
	       strcpy(text, textstart);
	       return 0;
	     }}
	   }
	 }
       }
    }
  }
  return -1;
}

int TConfigurator::setitemstring(const char *folder, const char *item, const char *text){
  int i,startline = 1;
  char str[maxlinesize];
  char *strp, *folderstart, *folderend, *itemstart, *itemend;
  bool folderfound = false;

	if (!strcmp(lastfolder,folder) && lastfolderline >= 0) startline = lastfolderline;

  for (i = 1; i <= lc.numlines(); i++){
    strcpy((char*)&str, lc.getline(i));
    strp = strchr((char*)&str, ';');
    if (strp != 0) *strp = 0;  //Kommentare abschneiden
    strp = (char*)&str;
    while ((((unsigned char)*strp) <= ' ') && (((unsigned char)*strp) > 0)) strp++; //fhrende Leerzeichen abschneiden
    if (strlen((char*)&str) > 0){
       if (*strp == '['){
	 if (folderfound){
	   str[0] = 0;
	   strcat((char*)&str, item);
	   strcat((char*)&str, " = ");
	   strcat((char*)&str, text);
	   lc.insert(i, (char*)&str);
	   return 0;
	 }
	 folderstart = strp+1;
	 folderend = strchr(folderstart, ']');
	 if (folderend){
	   *folderend = 0;
			if (strength_compare)
				{if (!strcmp(folderstart,folder)){
					folderfound = true;
					strcpy(lastfolder,folder);
					lastfolderline = i;}}else
	   		{if (strstr(folderstart, folder)){
					strcpy(lastfolder,folder);
					lastfolderline = i;
					folderfound = true;}}
	 }
       }else{
	 if (folderfound){
	   itemstart = strp;
	   itemend = strchr(itemstart, '=');
	   if (itemend){
			 while ((itemstart < itemend) && (((unsigned char)*(itemend-1)) <= ' ')) itemend--;
	     *itemend = 0;
	     if ((strength_compare && !strcmp(itemstart, item)) || (!strength_compare && (strstr(itemstart, item) != 0))){
	       str[0] = 0;
	       strcat((char*)&str, item);
	       strcat((char*)&str, " = ");
	       strcat((char*)&str, text);
	       return lc.setline(i, (char*)&str);
	     }
	   }
	 }
       }
    }
  }
 if (!folderfound){
   str[0] = 0;
   strcat((char*)&str, "[");
   strcat((char*)&str, folder);
   strcat((char*)&str, "]");
   lc.append((char*)&str);
 }
 str[0] = 0;
 strcat((char*)&str, item);
 strcat((char*)&str, " = ");
 strcat((char*)&str, text);
 lc.append((char*)&str);
 return 0;
}

int TConfigurator::getitemint(const char *folder, const char *item){
  char text[maxlinesize];

  if (getitemstring(folder, item, (char*)&text)) return 0;

  return atoi((char*)&text);
}

int TConfigurator::setitemint(const char *folder, const char *item, int val){
  char text[maxlinesize];
  itoa(val,(char*)&text,10);
  return setitemstring(folder, item, (char*)&text);
}

float TConfigurator::getitemfloat(const char *folder, const char *item){
  char text[maxlinesize];
  if (getitemstring(folder, item, (char*)&text)) return 0.0f;

  return atof((char*)&text);
}

int TConfigurator::setitemfloat(const char *folder, const char *item, float val){
  char text[maxlinesize];
  sprintf(text,"%.5f",val);
  return setitemstring(folder, item, text);
}

int TConfigurator::load(const char* fname){
  //int fh;
  FILE *fh;
  char buf[maxfilesize+1];
  int bytes, strt, end;

  if (fname) strcpy((char*)&filename, fname);
  lc.eraseall();

  //if ((fh = open((char*)&filename, O_RDONLY))==-1) return fail;
  //bytes = read(fh, (char*)&buf, maxfilesize);
  //close(fh);
  if( !(fh = fopen((char*)&filename, "r")) ) return fail;
  bytes = fread((char*)&buf, sizeof(char), maxfilesize, fh);
  fclose(fh);

  if (bytes == -1) return fail;
  end = 0;
  while (bytes > 0){
    strt = end;
    while ((bytes > 0) && (((unsigned char)buf[strt]) < ' ')) {strt++; bytes--;}
    end = strt;
    while ((bytes > 0) && (((unsigned char)buf[end]) >= ' ')) {end++; bytes--;}
    if (strt != end) {buf[end]=0; lc.append((char*)&buf[strt]);}
  }
  return success;
}

int TConfigurator::save(){
  //int fh;
  FILE *fh;
  int cnt;
  char line[maxlinesize+2];
  const char lineend[] = {0x0D,0x0A,0};

  if (!strlen((char*)&filename)) return -1;
  //if ((fh = open((char*)&filename, O_TRUNC|O_CREAT|O_WRONLY, 0600))==-1) return fail;
  if( !(fh = fopen((char*)&filename, "w"))) return fail;
  for (cnt = 1; cnt <= lc.numlines(); cnt++){
    line[0] = 0;
    strcat((char*)&line, lc.getline(cnt));
    strcat((char*)&line, (char*)&lineend);
    //write(fh, (char*)&line, strlen((char*)&line));
	 fwrite((char*)&line, sizeof(char), strlen((char*)&line), fh);
    }
  fclose(fh);
  return success;
}

int TConfigurator::loadshared(char *buf, long size){
  lc.eraseall();
  long end = 0, strt;
  while (size > 0){
    strt = end;
    while ((size > 0) && (((unsigned char)buf[strt]) < ' ')) {strt++; size--;}
    end = strt;
    while ((size > 0) && (((unsigned char)buf[end]) >= ' ')) {end++; size--;}
    if (strt != end) {buf[end]=0; lc.append((char*)&buf[strt]);}
  }
  return success;
}

int TConfigurator::saveshared(char *shm, long size){
	char *endshm = shm + size;
  int cnt;
  char line[maxlinesize+2];
  const char lineend[] = {0x0D,0x0A,0};
  for (cnt = 1; cnt <= lc.numlines(); cnt++){
    line[0] = 0;
    strcat((char*)&line, lc.getline(cnt));
    strcat((char*)&line, (char*)&lineend);
		strcpy(shm,(char*)&line);
		shm += strlen(line)+1;
    }
	while (shm < endshm){
		*shm = 0;
		shm++;
		}
  return success;
}
/**  */
int TConfigurator::save(const char* filename){
  //int fh;
  FILE *fh;
  int cnt;
  char line[maxlinesize+2];
  const char lineend[] = {0x0D,0x0A,0};

  if (!strlen((char*)&filename)) return -1;
  //if ((fh = open(filename, O_TRUNC|O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH))==-1) return fail;
  if( !(fh = fopen((char*)&filename, "w"))) return fail;
  for (cnt = 1; cnt <= lc.numlines(); cnt++){
    line[0] = 0;
    strcat((char*)&line, lc.getline(cnt));
    strcat((char*)&line, (char*)&lineend);
    //write(fh, (char*)&line, strlen((char*)&line));
	 fwrite((char*)&line, sizeof(char), strlen((char*)&line), fh);
    }
  fclose(fh);
  return success;
}
/**  */
bool TConfigurator::setStrengthCompare(bool sc){
	return (strength_compare = sc);
}
