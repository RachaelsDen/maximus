// SPDX-License-Identifier: GPL-2.0-or-later


void arcit(char *inname);
void dearcit(char *arcname, char *path, word (*dupefile)(char *, char *, char *),
             word(near *doit)(char *fn));
