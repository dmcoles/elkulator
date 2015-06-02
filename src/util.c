/*
 * Utilities
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#include <stdio.h>
#include "path.h"
#include "util.h"

SAMPLE *loadWavHelper(char const *dir, char const *fileName)
{
    char path[_MAX_PATH_WITH_NULL];

    if (!pathJoin(dir, fileName, path, COUNTOF(path)))
    {
        printf("! pathJoin failed\n");
        abort();
    }

    SAMPLE *result = load_wav(path);
    if (result == NULL)
    {
        printf("! Failed to load .wav file from %s\n", path);
        abort();
    }

    return result;
}

