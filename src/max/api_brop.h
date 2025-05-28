// SPDX-License-Identifier: GPL-2.0-or-later


sword EXPENTRY MsgBrowseArea(BROWSE *b);
static int near BrowseCheckScanFile(BROWSE *b);
static int near Browse_Scan_Message(BROWSE *b);
int near StringMatchInStr(char *msg, char *search);
int near StringMatchEqual(char *msg, char *search);
static int near BrowseMatchMessage(BROWSE *b, char *msgtxt, word checkaddr);
