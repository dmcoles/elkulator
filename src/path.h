/*
 * Path name handling functions
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#ifndef _PATH_H_INCLUDED
#define _PATH_H_INCLUDED

#include <linux/limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include "common.h"

#define _MAX_PATH_WITH_NULL (PATH_MAX + 1)

bool pathJoin(
    char const *path0,
    char const *path1,
    char *result,
    size_t resultSize);

bool pathResolve(
    char const *path,
    char *result,
    size_t resultSize,
    bool *pathExists);

#endif

