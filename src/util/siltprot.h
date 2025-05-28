// SPDX-License-Identifier: GPL-2.0-or-later


#include "areadat.h"

int Make_Strng(char *value, int type);
int Make_Pth(char *value);
void Strip_Comment(char *l);
int Parse_Ctlfile(char *ctlname);
void Initialize_Prm(void);
int Parse_System(FILE *ctlfile);
int Parse_Equipment(FILE *ctlfile);
int Parse_Matrix(FILE *ctlfile);
int Parse_Session(FILE *ctlfile);
int Parse_Reader(FILE *ctlfile);
int Parse_Area(FILE *ctlfile, char *name);
int Deduce_Priv(char *p);
int Deduce_Attribute(char *a);
int Deduce_Class(int priv);
void Unknown_Ctl(int linenum, char *p);
int Compiling(char type, char *string, char *name);
void Blank_Sys(struct _sys *sys, int mode);
int Add_Backslash(char *s);
int Remove_Backslash(char *s);
int Parse_Weekday(char *s);
int Parse_Menu(FILE *ctlfile, char *name);
dword Deduce_Lock(char *p);
void Attrib_Or(int clnum, int attr, struct _area *area);
void Attrib_And(int clnum, int attr, struct _area *area);
void Add_Path(char *s, int warn);
void Add_Filename(char *s);
char *fchar(char *str, char *delim, int wordno);
int Add_To_Heap(char *s, int fancy);
void Blank_Area(struct _area *area);
