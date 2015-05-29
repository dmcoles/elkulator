/*
 * Path name handling functions
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#ifndef _PATH_H_INCLUDED
#define _PATH_H_INCLUDED

#ifdef WIN32
#define _MAX_PATH_WITH_NULL (_MAX_PATH)
#else
#include <linux/limits.h>
#define _MAX_PATH_WITH_NULL (PATH_MAX + 1)
#endif
#include <stdbool.h>
#include <stdlib.h>
#include "common.h"

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
