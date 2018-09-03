// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2016-2018 The Runes developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0xcc;
        pchMessageStart[3] = 0xdd;
        vAlertPubKey = ParseHex("04e22531e96c9056be6b659c91a94fbf18739d5257fe044b88695c62f71a85bf85d131a669df3be61139873ac452a2d08c6314bba5ca3cbe5616262da3d4a6efac");
        nDefaultPort = 20189;
        nRPCPort = 20188;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Crypto Onslaught in China Continues as Guangzhou Bans Cryptocurrency Events | Steve Kaaru";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, timeGenesisBlock, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = timeGenesisBlock;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = nNonceMain;
        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == d32392205b488f64e28a222e753856abafb5cda056aa0839af0f7a811244633e
        block.nTime = 1535778000
        block.nNonce = 25100
        block.GetHash = 000000395ea836274a4bcfd3b703eccf1ec8f2b7cfc50b1cb5ccf528d2d4c0e3

        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == nGenesisBlock);
        assert(genesis.hashMerkleRoot == nGenesisMerkle);

        /** DEPRICATED IN QT 5.6+ (To compile on Qt5.5.1 and lower uncomment  */
        /*
        base58Prefixes[PUBKEY_ADDRESS] = list_of(33);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(92);
        base58Prefixes[SECRET_KEY] =     list_of(144);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
        */
        /** REQUIRED IN QT 5.6+  (To compile on Qt5.5.1 and lower comment out below) */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60); // All PUBKEY_ADDRESSes begin with 'R'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,53); // All SCRIPT_ADDRESSes begin with 'N'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,63); // All SECRET_KEYs begin with 'S'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Runes dns seeds
        // vSeeds.push_back(CDNSSeedData("cryptocoderz.com",  "rns.cryptocoderz.com"));

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        // Initial block spacing, attempted 40 second block time
        nTargetSpacing = 1 * 40;
        // Block rate reduced for ~40 Second block times
        // Due to hybrid mining blocktime still varied wildly during
        // this time between 15 seconds and 1 minute
        if(nBestHeight > nBlocktimeregress)
            nTargetSpacing = 2.5 * 60;
        // Block rate reduced for 3-5 Minute block times
        // this is in conjunction with DGW-v3 retarget fork
        if(nBestHeight > nGravityFork)
            nTargetSpacing = BLOCK_SPACING * 1;
        nTargetTimespan = 10 * nTargetSpacing;
        nStartPoSBlock = 2125; // Delay PoS start until swap start

    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xd4;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("02e22531e96c9056be6b659c91a94fbfebeb904871ae044b88695c62f7c2f81f817623ac69df3be611393ab26552a2d08c6314bba5ca3cbe5616262db3d4a6efac");
        nDefaultPort = 20179;
        nRPCPort = 20178;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = nNonceTest;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == d32392205b488f64e28a222e753856abafb5cda056aa0839af0f7a811244633e
        block.nTime = 1535778000
        block.nNonce = 195805
        block.GetHash = 00000de475b1603ef454068c77052ae7726fc9a90bb004fdac2d520e120da663
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == hashTestNetGenesisBlock);

        vFixedSeeds.clear();
        vSeeds.clear();

        /** DEPRICATED IN QT 5.6+ (To compile on Qt5.5.1 and lower uncomment  */
        /*
        base58Prefixes[PUBKEY_ADDRESS] = list_of(34);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(94);
        base58Prefixes[SECRET_KEY]     = list_of(143);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);
        */
        /** REQUIRED IN QT 5.6+  (To compile on Qt5.5.1 and lower comment out below */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,122); // All PUBKEY_ADDRESSes begin with 'r'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,112); // All SCRIPT_ADDRESSes begin with 'n'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,125); // All SECRET_KEYs begin with 's'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 20;
        nStartPoSBlock = 2880;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xd5;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xb3;
        pchMessageStart[3] = 0xa2;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = timeRegNetGenesis;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = nNonceReg;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 32445;
        strDataDir = "regtest";

        /** Genesis Block TestNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == d32392205b488f64e28a222e753856abafb5cda056aa0839af0f7a811244633e
        block.nTime = 1535792400
        block.nNonce = 8
        block.GetHash = e9f653e9de48dc5bc6b82f3f48d017446de94af4231c043ef14d20b25bbe2ffe
        */

        assert(hashGenesisBlock == hashRegNetGenesisBlock);

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
