// SPDX-License-Identifier: GPL-2.0-or-later


cpp_begin()

    int far pascal dvloaded(void);
int far pascal tvloaded(void);
int far pascal ddosloaded(void);
int far pascal pcmosloaded(void);
int far pascal winloaded(void);
int far pascal mlinkloaded(void);
int far pascal os2loaded(void);
int far pascal unixloaded(void);

void far pascal dvsleep(void);
void far pascal ddossleep(void);
void far pascal pcmossleep(void);
void far pascal winsleep(void);
void far pascal mlinksleep(void);
void far pascal spoolsleep(void);
void far pascal os2sleep(void);
void far pascal unixsleep(void);

cpp_end()
