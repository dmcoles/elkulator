#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "path_test.h"
#include "path.h"

static void pathJoinTest()
{
    bool result;
    char path[_MAX_PATH_WITH_NULL];

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path, 0);
    assert(!result);
    assert(path[0] == 'A');

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path, 1);
    assert(!result);
    assert(path[0] == '\0');

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path, 2);
    assert(!result);
    assert(path[0] == '\0');

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path, COUNTOF(path));
    assert(result);
    assert(strcmp("./foo.txt", path) == 0);

    result = pathJoin("/aaa/bbb/ccc", "/xxx/yyy/zzz", path, COUNTOF(path));
    assert(result);
    assert(strcmp("/xxx/yyy/zzz", path) == 0);
}

static void pathResolveTest()
{
    bool result;
    char path[_MAX_PATH_WITH_NULL];
    bool pathExists;
    char currentDir[_MAX_PATH_WITH_NULL];
    char expectedPath[_MAX_PATH_WITH_NULL];

    if (getcwd(currentDir, COUNTOF(currentDir)) == NULL)
    {
        abort();
    }

    path[0] = 'A';
    result = pathResolve("./foo.txt", path, 0, &pathExists);
    assert(!result);
    assert(path[0] == 'A');
    assert(!pathExists);

    path[0] = 'A';
    result = pathResolve("./foo.txt", path, 1, &pathExists);
    assert(!result);
    assert(path[0] == '\0');
    assert(!pathExists);

    path[0] = 'A';
    result = pathResolve("./foo.c", path, COUNTOF(path), &pathExists);
    assert(result);
    sprintf(expectedPath, "%s/foo.c", currentDir);
    assert(strcmp(expectedPath, path) == 0);
    assert(!pathExists);

    path[0] = 'A';
    result = pathResolve("./foo.txt", path, COUNTOF(path), &pathExists);
    assert(result);
    sprintf(expectedPath, "%s/foo.txt", currentDir);
    assert(strcmp(expectedPath, path) == 0);
    assert(!pathExists);

    path[0] = 'A';
    result = pathResolve(".//foo.txt", path, COUNTOF(path), &pathExists);
    assert(result);
    sprintf(expectedPath, "%s/foo.txt", currentDir);
    assert(strcmp(expectedPath, path) == 0);
    assert(!pathExists);
}

void runPathTests()
{
    pathJoinTest();
    pathResolveTest();
}

