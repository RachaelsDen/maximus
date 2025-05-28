// SPDX-License-Identifier: GPL-2.0-or-later

#include "dossem.h"
#include "share.h"
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


#if defined(LINUX) && !defined(PTHREAD_MUTEX_ERRORCHECK)

#if defined(LINUX)
    char *SemPath, SemPathBuf[FILENAME_MAX + 1];
    char buf[32];
    HSEM sem;

    if (!SemHandle)
        return ERROR_INVALID_PARAMETER;

    if (SemName && (strcasecmp(SemName, "\\SEM\\") != 0))
        return ERROR_INVALID_NAME;

    if (SemName)
    {
        snprintf(SemPathBuf, sizeof(SemPathBuf), UNIX_SEMDIR "/%s", SemName);
        fixPath(SemPathBuf);
        SemPath = SemPathBuf;
        mkdir_recursive_for(SemPath);
    }
    else
    {
        mkdir_recursive(UNIX_SEMDIR);
        SemPath = tempnam(UNIX_SEMDIR, "sem_");
    }

    sem = calloc(sizeof(*sem), 1);
    if (!sem)
        return ERROR_NOT_ENOUGH_MEMORY;
    else
        *SemHandle = sem;

    sem->fd = open(SemPathBuf, O_CREAT | O_EXCL | O_RDWR, 0666);
    sem->type = dmt_sem;

    if (sem->fd < 0)
    {
        free(sem);
        *SemHandle = NULL;

        switch (errno)
        {
        case ENOENT:
        case EPERM:
            return ERROR_INVALID_NAME;
        case EEXIST:
            return ERROR_DUPLICATE_NAME;
        default:
            return ERROR_INVALID_PARAMETER;
        }
    }

    if (flock(sem->fd, LOCK_EX | LOCK_NB))
    {

    char *SemPath, SemPathBuf[FILENAME_MAX + 1];
    HSEM sem;

    if (!SemHandle)
        return ERROR_INVALID_PARAMETER;

    if (SemName && (strcasecmp(SemName, "\\SEM\\") != 0))
        return ERROR_INVALID_NAME;

    if (SemName)
    {
        snprintf(SemPathBuf, sizeof(SemPathBuf), UNIX_SEMDIR "/%s", SemName);
        fixPath(SemPathBuf);
        SemPath = SemPathBuf;
        mkdir_recursive_for(SemPath);
    }
    else
    {
        mkdir_recursive(UNIX_SEMDIR);
        SemPath = tempnam(UNIX_SEMDIR, "sem_");
    }

    sem = calloc(sizeof(*sem), 1);
    if (!sem)
        return ERROR_NOT_ENOUGH_MEMORY;
    else
        *SemHandle = sem;

    sem->fd = open(SemPathBuf, O_CREAT | O_RDWR, 0666);
    sem->type = dmt_sem;

    if (sem->fd < 0)
    {
        free(sem);
        *SemHandle = NULL;

        switch (errno)
        {
        case ENOENT:
        case EPERM:
            return ERROR_INVALID_NAME;
        default:
            return ERROR_INVALID_PARAMETER;
        }
    }

    return NO_ERROR;
}

int DosSemRequest(HSEM SemHandle, int how)
{
    int rc = NO_ERROR;

    if (SemHandle->owned)
        return NO_ERROR;

    if (how != SEM_INDEFINITE_WAIT)
        lockFlags |= LOCK_NB;

    if (flock(sem->fd, lockFlags))
        return ERROR_ALREADY_EXISTS;

    i = read(sem->fd, buf, sizeof(buf));
    buf[i] = (char)0;
    if (buf[0] && (atoi(buf) != processID()))
        rc = ERROR_SEM_OWNER_DIED;

    sprintf(buf, "%i\n", processID());
    write(sem->fd, buf, strlen(buf));
    fsync(sem->fd);

    return rc;
}

int DosSemClear(HSEM SemHandle)
{

    if (!SemHandle)
        return ERROR_INVALID_PARAMETER;

    if (!sem->owned)
        return ERROR_INVALID_HANDLE;

    ftruncate(sem->fd, 0);
    flock(sem->fd, LOCK_UN);
    sem->owned = 0;

    return NO_ERROR;
}

int DosCloseSem(HSEM SemHandle)
{

    if (!SemHandle)
        return ERROR_INVALID_PARAMETER;

    DosSemClear(SemHandle);
    close(sem->fd);
    free(sem);

    return NO_ERROR;
}

int DosSemWait(HSEM SemHandle, int how)
{

    char *SemPath, SemPathBuf[FILENAME_MAX + 1];
    char buf[32];
    HMTX hmtx;
    pthread_mutexattr_t attr;

    if (!hmtx_p)
        return ERROR_INVALID_PARAMETER;

    if (SemName && (strcasecmp(SemName, "\\SEM32\\") != 0))
        return ERROR_INVALID_NAME;

    if (SemName)
    {
        AttributeFlags |= DC_SEM_SHARED;
        snprintf(SemPathBuf, sizeof(SemPathBuf), UNIX_SEMDIR "/%s", SemName);
        fixPath(SemPathBuf);
        SemPath = SemPathBuf;
        mkdir_recursive_for(SemPath);
    }

    if (AttributeFlags & DC_SEM_SHARED)
    {
        mkdir_recursive(UNIX_SEMDIR);
        SemPath = tempnam(UNIX_SEMDIR, "sem32");
    }

    hmtx = calloc(sizeof(**hmtx_p), 1);
    if (!hmtx)
        return ERROR_NOT_ENOUGH_MEMORY;

    *hmtx_p = hmtx;
    hmtx->type = dmt_mutexsem;

    hmtx->fd = open(SemPathBuf, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (hmtx->fd < 0)
    {
        free(hmtx);
        *hmtx_p = NULL;

        switch (errno)
        {
        case ENOENT:
        case EPERM:
            return ERROR_INVALID_NAME;
        case EEXIST:
            return ERROR_DUPLICATE_NAME;
        default:
            return ERROR_INVALID_PARAMETER;
        }
    }

    if (InitialState == 0)
        return NO_ERROR;

    if (flock(hmtx->fd, LOCK_EX | LOCK_NB))
    {
    if (flock(hmtx->fd, lockMode))
    {
        switch (errno)
        {
        case EINTR:
            return ERROR_INTERRUPT;
        case EINVAL:
            return ERROR_INVALID_HANDLE;
        case EWOULDBLOCK:
