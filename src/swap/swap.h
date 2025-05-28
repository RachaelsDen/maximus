// SPDX-License-Identifier: GPL-2.0-or-later


#ifdef __cplusplus
extern "C"
{
#endif

    int cdecl swap(unsigned char *program_name, unsigned char *command_line,
                   unsigned char *exec_return, unsigned char *swap_fname);

    int cdecl ems4_installed(void);
    int cdecl xms_installed(void);

#ifdef __cplusplus
}
#endif


