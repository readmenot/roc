/*
 * Copyright (c) 2015 Mikhail Baranov
 * Copyright (c) 2015 Victor Gaydov
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <CppUTest/CommandLineArguments.h>
#include <CppUTest/CommandLineTestRunner.h>

#include "roc_core/log.h"

int main(int argc, const char** argv) {
    CommandLineArguments args(argc, argv);

    if (args.parse(NULL) && args.isVerbose()) {
        roc::core::set_log_level(roc::LogDebug);
    } else {
        roc::core::set_log_level(roc::LogNone);
    }

    MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();

    return CommandLineTestRunner::RunAllTests(argc, argv);
}
