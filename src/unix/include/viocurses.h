// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _VIOCURSES_H
#define _VIOCURSES_H

int VioSetCurPos(int row, int column, void *handle);
int VioWrtTTY(const char *string, size_t length, void *handle);
