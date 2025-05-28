// SPDX-License-Identifier: GPL-2.0-or-later


int Exec_Xtern(int type, struct _opt *thisopt, char *arg, char **result, char *mname);
int Exec_Main(int type, char **result);
int Exec_Msg(int type, char **result, int key, char *arg, char *menuname);
int Exec_File(int type, char **result, char *menuname);
int Exec_Change(int type, char **result);
int Exec_Edit(int type, char **result, XMSG *msg, unsigned *puiFlag);
int Exec_Chat(int type, char **result);
