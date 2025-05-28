// SPDX-License-Identifier: GPL-2.0-or-later


static void near Write_Events(int dateit);
static void near Parse_Event_File(char *ebbsname);
static int near Process_Event_Line(char *line, struct _event *e);
static void near Parse_Day(struct _event *e, char *word);
static void near Parse_Time(struct _etime *t, char *word);
static void near Parse_Flag(struct _event *e, char *word);
static void near Event_Syntax_Err(char *err);
static void near Init_Event(struct _event *e);
static int near InEvent(struct _event *e, int for_now);
