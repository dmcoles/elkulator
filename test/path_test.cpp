/*
 * Path tests
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#include <array>
#include <cppunit/extensions/HelperMacros.h>
#include <cstring>
#include <unistd.h>
extern "C"
{
    #include "path.h"
}

using namespace std;

class PathTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PathTest);
    CPPUNIT_TEST(join);
    CPPUNIT_TEST(resolve);
    CPPUNIT_TEST(dir);
    CPPUNIT_TEST_SUITE_END();

public:
    void join();
    void resolve();
    void dir();
};

CPPUNIT_TEST_SUITE_REGISTRATION(PathTest);

void PathTest::join()
{
    bool result;
    array<char, _MAX_PATH_WITH_NULL> path;

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path.data(), 0);
    CPPUNIT_ASSERT(!result);
    CPPUNIT_ASSERT(path[0] == 'A');

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path.data(), 1);
    CPPUNIT_ASSERT(!result);
    CPPUNIT_ASSERT(path[0] == '\0');

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path.data(), 2);
    CPPUNIT_ASSERT(!result);
    CPPUNIT_ASSERT(path[0] == '\0');

    path[0] = 'A';
    result = pathJoin(".", "foo.txt", path.data(), path.size());
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(strcmp("./foo.txt", path.data()) == 0);

    result = pathJoin("/aaa/bbb/ccc", "/xxx/yyy/zzz", path.data(), path.size());
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(strcmp("/xxx/yyy/zzz", path.data()) == 0);
}

static void formatExpectedPath(char *buffer, char const *currentDir, char const *fileName)
{
#ifdef WIN32
    sprintf(buffer, "%s\\%s", currentDir, fileName);
#else
    sprintf(buffer, "%s/%s", currentDir, fileName);
#endif
}

void PathTest::resolve()
{
    bool result;
    array<char, _MAX_PATH_WITH_NULL> path;
    bool pathExists;
    array<char, _MAX_PATH_WITH_NULL> currentDir;
    array<char, _MAX_PATH_WITH_NULL> expectedPath;

    if (getcwd(currentDir.data(), currentDir.size()) == NULL)
    {
        abort();
    }

    path[0] = 'A';
    pathExists = true;
    result = pathResolve("./foo.txt", path.data(), 0, &pathExists);
    CPPUNIT_ASSERT(!result);
    CPPUNIT_ASSERT(path[0] == 'A');
    CPPUNIT_ASSERT(!pathExists);

    path[0] = 'A';
    result = pathResolve("./foo.txt", path.data(), 1, &pathExists);
    CPPUNIT_ASSERT(!result);
    CPPUNIT_ASSERT(path[0] == '\0');
    CPPUNIT_ASSERT(!pathExists);

    path[0] = 'A';
    result = pathResolve("./foo.c", path.data(), path.size(), &pathExists);
    CPPUNIT_ASSERT(result);
    formatExpectedPath(expectedPath.data(), currentDir.data(), "foo.c");
    CPPUNIT_ASSERT(strcmp(expectedPath.data(), path.data()) == 0);
    CPPUNIT_ASSERT(!pathExists);

    path[0] = 'A';
    result = pathResolve("./foo.txt", path.data(), path.size(), &pathExists);
    CPPUNIT_ASSERT(result);
    formatExpectedPath(expectedPath.data(), currentDir.data(), "foo.txt");
    CPPUNIT_ASSERT(strcmp(expectedPath.data(), path.data()) == 0);
    CPPUNIT_ASSERT(!pathExists);

    path[0] = 'A';
    result = pathResolve(".//foo.txt", path.data(), path.size(), &pathExists);
    CPPUNIT_ASSERT(result);
    formatExpectedPath(expectedPath.data(), currentDir.data(), "foo.txt");
    CPPUNIT_ASSERT(strcmp(expectedPath.data(), path.data()) == 0);
    CPPUNIT_ASSERT(!pathExists);
}

void PathTest::dir()
{
    bool result;
    array<char, _MAX_PATH_WITH_NULL> path;

    path[0] = 'A';
    result = pathDir("/aaa/bbb/ccc", path.data(), 0);
    CPPUNIT_ASSERT(!result);
    CPPUNIT_ASSERT(path[0] == 'A');

    path[0] = 'A';
    result = pathDir("/aaa/bbb/ccc", path.data(), 1);
    CPPUNIT_ASSERT(!result);
    CPPUNIT_ASSERT(path[0] == '\0');

    result = pathDir("/aaa/bbb/ccc", path.data(), path.size());
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(strcmp("/aaa/bbb", path.data()) == 0);
}
