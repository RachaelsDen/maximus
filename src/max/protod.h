// SPDX-License-Identifier: GPL-2.0-or-later


#include "m_reply.h"

cpp_begin()

    void Update_User(void);
int TrackNeedToInsertRemoteMsg(PMAH pmah, XMSG *pxmsg, char *kludges);
void CLIMax(void);
void FinishUp2(int hangup);
unsigned int Decimal_Baud_To_Mask(unsigned int bd);
int System_Restart(char *restart_name);
void Fossil_Install(int fInitVideo);
void Got_A_Null_Pointer(char *type, char *where);
int _stdc yellchk(void);
int UserList(void);
void Statistics(void);
void Chg_Username(void);
void Chg_City(void);
void Chg_Alias(void);
void Chg_Phone(void);
int _stdc Display_File(word type, char *o_nonstop, char *fname, ...);
int Parse_Outside_Cmd(char *parm, char *outparm);
void File_Raw(void);
void Get_File_Description(char *filename, long fsize, char *dsc);
char *Remove_Files_Entry(char *filename, char *description);
void File_Hurl(void);
void File_Override_Path(void);
sword Get_New_Date(union stamp_combo *new_date, union stamp_combo *last, char *prompt);
word File_Get_Files(sword protocol, char *mname, char *path);
void File_Get_Upload_Names(void);
void Open_OpusXfer(FILE **xferinfo);
void Close_OpusXfer(FILE **xferinfo);
void Delete_OpusXfer(FILE **xferinfo);
void File_Contents(void);
void File_Titles(void);
void File_Tag(int dl_cmd);
long Index_of_Area(char *an);
word Write_LastUser(void);
int cdecl Inputf(char *dest, int type, int ch, int max, char *prompt, ...);
int cdecl Input_Charf(int type, char *extra, ...);
int cdecl GetListAnswer(char *list, char *help_file, char *invalid_response, int type,
                        char *o_prompt, ...);
int cdecl InputGets(char *dest, char *prompt, ...);
int cdecl InputGetsM(char *dest, int max, char *prompt, ...);
int cdecl InputGetsWNH(char *dest, char *prompt, ...);
int cdecl InputGetse(char *dest, char ch, char *prompt, ...);
int cdecl InputGetseNH(char *dest, char ch, char *prompt, ...);
int cdecl InputGetsC(char *dest, char ch, char *prompt, ...);
int cdecl InputGetsL(char *dest, int max, char *prompt, ...);
int cdecl InputGetsNH(char *dest, int max, char *prompt, ...);
int cdecl InputGetsLe(char *dest, int max, char ch, char *prompt, ...);
int cdecl InputGetsLLe(char *dest, int max, char ch, char *prompt, ...);
int cdecl InputGetsLL(char *dest, int max, char *prompt, ...);
void Keyboard_Off(void);
void PleaseRespond(void);
