// SPDX-License-Identifier: GPL-2.0-or-later



#ifdef __FLAT__
#define WinQWindow(hwnd, id) WinQueryWindow(hwnd, id, FALSE)
#endif
