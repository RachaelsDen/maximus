#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#define P_WAIT 1
#define P_NOWAIT 2
#define P_NOWAITO 3
#define P_OVERLAY 4

int spawnvp(int mode, const char *file, char *const argv[]);

#endif /* PROCESS_H_INCLUDED */
