/*
 * Copyright (c) 2015 Mikhail Baranov
 * Copyright (c) 2015 Victor Gaydov
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <pthread.h>
#include <stdlib.h>

#include "roc_core/errno_to_str.h"
#include "roc_core/panic.h"
#include "roc_core/random.h"
#include "roc_core/time.h"

namespace roc {
namespace core {

namespace {

pthread_once_t once_control = PTHREAD_ONCE_INIT;

unsigned short rand_seed[3] = {};

void random_init() {
    uint64_t seed_48 = timestamp_ms();
    rand_seed[0] = (seed_48 & 0xffff);
    rand_seed[1] = ((seed_48 >> 16) & 0xffff);
    rand_seed[2] = ((seed_48 >> 32) & 0xffff);
}

} // namespace

// Insecure, but (hopefully?) uniform and thread-safe implementation.
// See arc4random_uniform() from OpenBSD.
unsigned random(unsigned from, unsigned to) {
    if (int err = pthread_once(&once_control, random_init)) {
        roc_panic("pthread_once: %s", errno_to_str(err).c_str());
    }

    roc_panic_if_not(from <= to);

    uint32_t upper = uint32_t(to - from + 1);
    uint32_t min = -upper % upper;
    uint32_t val = 0;

    for (;;) {
        if ((val = (uint32_t)nrand48(rand_seed)) >= min) {
            break;
        }
    }

    unsigned ret = from + (unsigned)(val % upper);

    roc_panic_if_not(ret >= from);
    roc_panic_if_not(ret <= to);

    return ret;
}

unsigned random(unsigned upper) {
    roc_panic_if_not(upper > 0);

    return random(0, upper - 1);
}

} // namespace core
} // namespace roc
