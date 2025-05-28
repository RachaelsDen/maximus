// SPDX-License-Identifier: GPL-2.0-or-later


void Initialize_Menu(struct _amenu *menu);
sword Read_Menu(struct _amenu *menu, char *mname);
void Free_Menu(struct _amenu *menu);
char *RunOption(struct _amenu *menu, struct _opt *thisopt, int ch, XMSG *msg, unsigned *puiFlag,
                char *menuname);
int OptionOkay(struct _amenu *menu, struct _opt *popt, int displaying, char *barricade, PMAH pmah,
               PFAH pfah, char *menuname);
int DoDspFile(byte help, word flag);
