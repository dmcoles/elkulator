/*
 * Path name handling functions
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "path.h"

bool pathJoin(
    char const *path0,
    char const *path1,
    char *result,
    size_t resultSize)
{
    if (path0 == NULL || path1 == NULL ||  result == NULL || resultSize < 1)
    {
        return false;
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
    result[0] = '\0';
    return false;
}

bool pathResolve(
    char const *path,
    char *result,
    size_t resultSize,
    bool *pathExists)
{
    if (path == NULL || result == NULL || resultSize < 1)
    {
        return false;
    }

    result[0] = '\0';

    if (resultSize != _MAX_PATH_WITH_NULL)
    {
        goto Error;
    }

    char *ptr = realpath(path, result);
    if (ptr == NULL && errno != ENOENT)
    {
        goto Error;
    }

    if (pathExists != NULL)
    {
        *pathExists = ptr != NULL;
    }

    return true;

Error:
    result[0] = '\0';
    if (pathExists != NULL)
    {
        *pathExists = false;
    }

    return false;
}

