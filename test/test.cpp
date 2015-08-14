/*
 * Tests
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#include "elkulator-common.h"
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    auto showSummaryOnly = false;
    auto isValid = true;

    for (decltype(argc) i = 1; i < argc; ++i)
    {
        if (strcmp("--summary-only", argv[i]) == 0)
        {
            showSummaryOnly = true;
        }
        else
        {
            isValid = false;
            cerr <<
                "Unrecognized switch \"" <<
                argv[i] <<
                "\"" <<
                endl;
        }
    }

    if (!isValid)
    {
        return 1;
    }

    CPPUNIT_NS::TestResult controller;

    CPPUNIT_NS::TestResultCollector result;
    controller.addListener(&result);

    unique_ptr<CPPUNIT_NS::BriefTestProgressListener> progressListener;
    if (!showSummaryOnly)
    {
        progressListener = make_unique<CPPUNIT_NS::BriefTestProgressListener>();
        controller.addListener(progressListener.get());
    }

    CPPUNIT_NS::TextOutputter textOutputter(&result, cout);

    CPPUNIT_NS::TextTestRunner runner;
    auto& registry = CPPUNIT_NS::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run(controller);

    textOutputter.write();

    return result.wasSuccessful() ? EXIT_SUCCESS : EXIT_FAILURE;
}

