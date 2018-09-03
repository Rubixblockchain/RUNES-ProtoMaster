// Copyright (c) 2016-2018 The CryptoCoderz Team / Runes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef RUNES_MINING_H
#define RUNES_MINING_H

#include "bignum.h"

/** Minimum nCoinAge required to stake PoS (v2) */
static const unsigned int nStakeMinAge = 2 * 60 * 60; // 2 hours
/** Minimum nCoinAge required to stake PoS (v3) */
static const int nStakeMinConfirmations = 75; // 8(minutes) × 75(confirms) ÷ 60(minutes) = 10 hours
/** Time to elapse before new modifier is computed */
static const unsigned int nModifierInterval = 10 * 60;
/** PoS Subsidy */
static const int64_t COIN_YEAR_REWARD = 25 * CENT; // 25% 25000000
/** PoS Subsidy 2 */
static const int64_t COIN_YEAR_REWARD2 = 26 * CENT; // ~26% 26000000 annually
/** PoS Subsidy 3 */
static const int64_t COIN_YEAR_REWARD3 = 9 * CENT; // ~9% 9000000 annually
/** PoS Subsidy 4 */
static const int64_t COIN_YEAR_REWARD4 = 3 * CENT; // ~3% 3000000 annually
/** Block spacing preferred */
static const int64_t BLOCK_SPACING = 8 * 60;
/** Block spacing minimum */
static const int64_t BLOCK_SPACING_MIN = 5 * 60;
/** Block spacing maximum */
static const int64_t BLOCK_SPACING_MAX = 10 * 60;
/** Genesis block subsidy */
static const int64_t nGenesisBlockReward = 1 * COIN;
/** Reserve block subsidy */
static const int64_t nBlockRewardReserve = 6400000000 * COIN; // 6.4 Billion (8%)
/** Starting block subsidy */
static const int64_t nBlockPoWReward = 888 * COIN;
/** Invalid block subsidy */
static const int64_t nBlockRewardBuffer = 0.1 * COIN;
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int nCoinbaseMaturity = 60;

#endif
