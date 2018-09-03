// Copyright (c) 2016-2018 The CryptoCoderz Team / Runes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef RUNES_GENESIS_H
#define RUNES_GENESIS_H

#include "bignum.h"

/** Genesis Start Time */
static const unsigned int timeGenesisBlock = 1535778000; //  Saturday, September 1, 2018 5:00:00 AM
/** Genesis RegNet Start Time */
static const unsigned int timeRegNetGenesis = 1535792400; //  Saturday, September 1, 2018 9:00:00 AM
/** Genesis Nonce */
static const unsigned int nNonceMain = 25100;
/** Genesis Nonce Testnet */
static const unsigned int nNonceTest = 195805;
/** Genesis Nonce Regnet */
static const unsigned int nNonceReg = 8;
/** Main Net Genesis Block */
static const uint256 nGenesisBlock("0x000000395ea836274a4bcfd3b703eccf1ec8f2b7cfc50b1cb5ccf528d2d4c0e3");
/** Test Net Genesis Block */
static const uint256 hashTestNetGenesisBlock("0x00000de475b1603ef454068c77052ae7726fc9a90bb004fdac2d520e120da663");
/** Reg Net Genesis Block */
static const uint256 hashRegNetGenesisBlock("0xe9f653e9de48dc5bc6b82f3f48d017446de94af4231c043ef14d20b25bbe2ffe");
/** Genesis Merkleroot */
static const uint256 nGenesisMerkle("0xd32392205b488f64e28a222e753856abafb5cda056aa0839af0f7a811244633e");
#endif
