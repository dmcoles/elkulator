/*
 * Path name handling functions
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#include <errno.h>
#include <libgen.h>
#include <string.h>
#ifdef WIN32
#include <sys/stat.h>
#endif
#include "path.h"

bool pathJoin(
    char const *path0,
    char const *path1,
    char *result,
    size_t resultSize)
{
    if (path0 == NULL || path1 == NULL || result == NULL || resultSize < 1)
    {
        goto Error;
    }

    result[0] = '\0';

    size_t remainingLength = resultSize - 1;
    size_t path1Length = strlen(path1);

    bool isAbsolute = path1Length > 0 && path1[0] == '/';

    if (!isAbsolute)
    {
        size_t path0Length = strlen(path0);

        if (path0Length > remainingLength)
        {
            goto Error;
        }

        strcat(result, path0);
        remainingLength -= path0Length;

        if (remainingLength < 1)
        {
            goto Error;
        }

        strcat(result, "/");
        remainingLength -= 1;
    }

    if (path1Length > remainingLength)
    {
        goto Error;
    }

    strcat(result, path1);
    return true;

Error:
    if (result != NULL && resultSize > 0)
    {
        result[0] = '\0';
    }

    return false;
}

bool pathResolve(
    char const *path,
    char *result,
    size_t resultSize,
    bool *pathExists)
{
    if (path == NULL || result == NULL || resultSize != _MAX_PATH_WITH_NULL)
    {
        goto Error;
    }

#ifdef WIN32
    struct _stat statBuffer;
    int statResult = _stat(path, &statBuffer);
    if (statResult != 0 && errno != ENOENT)
    {
        goto Error;
    }

    _fullpath(result, path, _MAX_PATH_WITH_NULL);
    char *ptr = statResult == 0 ? result : NULL;
#else
    char *ptr = realpath(path, result);
    if (ptr == NULL && errno != ENOENT)
    {
        goto Error;
    }
#endif

    if (pathExists != NULL)
    {
        *pathExists = ptr != NULL;
    }

    return true;

Error:
    if (result != NULL && resultSize > 0)
    {
        result[0] = '\0';
    }

    if (pathExists != NULL)
    {
        *pathExists = false;
    }

    return false;
}

bool pathDir(
    char const *path,
    char *result,
    size_t resultSize)
{
    if (path == NULL || result == NULL || resultSize < 1)
    {
        return false;
    }

    size_t pathLength = strlen(path);

    if (resultSize <= pathLength)
    {
        goto Error;
    }

    strcpy(result, path);
    if (dirname(result) != result)
    {
        goto Error;
    }

    return true;

Error:
    result[0] = '\0';
    return false;
}

