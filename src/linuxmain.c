/*
 * Linux main loop
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#ifndef WIN32
int mainHelper(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    return mainHelper(argc, argv);
}

#endif

