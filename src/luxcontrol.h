// Copyright (c) 2015-2017 The Bitcoin Core developers
// Copyright (c) 2017 The RÜNES developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Functionality for communicating with RÜNESGate.
 */
#ifndef BITCOIN_RÜNESCONTROL_H
#define BITCOIN_RÜNESCONTROL_H

#include <string>

#include <boost/function.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/thread.hpp>

extern const std::string DEFAULT_RÜNES_CONTROL;
static const bool DEFAULT_LISTEN_ONION = true;

void StartRÜNESControl(boost::thread_group& threadGroup);
void InterruptRÜNESControl();
void StopRÜNESControl();

#endif /* BITCOIN_RÜNESCONTROL_H */


