/*
 * Copyright (c) 2015 Mikhail Baranov
 * Copyright (c) 2015 Victor Gaydov
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_packet/target_stdio/roc_packet/print_packet.h
//! @brief Print packet to stdout.

#ifndef ROC_PACKET_PRINT_PACKET_H_
#define ROC_PACKET_PRINT_PACKET_H_

#include "roc_packet/ipacket.h"

namespace roc {
namespace packet {

//! Print packet to stderr.
void print_packet(const IPacket&, bool print_payload);

} // namespace packet
} // namespace roc

#endif // ROC_PACKET_PRINT_PACKET_H_
