// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The LUX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"
#include "primitives/transaction.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

///////////////////////////////////////////// // lux
#include <libdevcore/SHA3.h>
#include <libdevcore/RLP.h>
//#include "arith_uint256.h"
/////////////////////////////////////////////

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

bool CheckProof(uint256 hash, unsigned int nBits)
{
    bool fNegative;
    bool fOverflow;
    uint256 bnTarget;


    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget == 0 || fOverflow)
        return false; //error("CheckProofOfWork() : nBits below minimum work");

    // Check proof of work matches claimed amount
    if (hash > bnTarget)
        return false; //error("CheckProofOfWork() : hash doesn't match nBits");

    return true;
}

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 60 * 60 * 24 * 7; //604,800 seconds
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port), NODE_NETWORK);
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
            ( 0,   uint256("0x") )
            ( 175,   uint256("0x") )
            ( 2241,   uint256("0x") )
            ( 6901,   uint256("0x") )
            ( 25318,   uint256("0x") )
            ( 97176,   uint256("0x") )
            ( 122237,   uint256("0x") )
            ( 203690,   uint256("0x") )
            ( 293220,   uint256("0x") )
            ( 299500,   uint256("0x") )
            ( 303112,   uint256("0x") ); //keeping this like that until i find out mathematical formula to solve for last PoWBlock Date, Time, Seconds, Miliseconds

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1530481662, // * UNIX timestamp of last checkpoint block // do math for this
    624779,     // * total number of transactions between genesis and last checkpoint // and this
                //   (the tx=... number in UpdateTip debug.log lines)
    350058        // * estimated number of transactions per day after checkpoint // and this -_-
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    0
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0
};

static Checkpoints::MapCheckpoints mapCheckpointsSegWittest =
        boost::assign::map_list_of(0, uint256("0"));
static const Checkpoints::CCheckpointData dataSegwittest = {
        &mapCheckpointsSegWittest,
        0,
        0,
        0
};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        //consensus.BIP34Height = 227931;
        //consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8");
        consensus.powLimit = ~uint256(0) >> 20; // LUX starting difficulty is 1 / 2^12
        consensus.nPowTargetTimespan = 30 * 60; //36 * 60 * 60; // LUX: 1 36hrs MODIFIED VELOCITY?
        consensus.nPowTargetSpacing = 7 * 60;  // LUX: 7 Minutes | (0r 420 seconds)
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1026; // 95% of 1080 is 1026
        consensus.nMinerConfirmationWindow = 1080; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nLastPOWBlock = 6000000; // do math for this as well -_-
        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1545696059; // Tuesday, December 25, 2018 00:00:59 AM
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1577232059; // Wednesday, December 25, 2019 12:00:59 AM

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1545696059; // Tuesday, December 25, 2018 00:00:59 AM
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1577232059; // Wednesday, December 25, 2019 12:00:59 AM

        //SMART_CONTRACTS_HARDFORK deployment does not require start time and timeout, because it uses block number
        //This is not used now, because we need to check this bit in block.h using versionbits, which results in cyclic
        //dependency block <- versionbits <- chain <- block
        //TODO: fix cyclic dependency
        consensus.vDeployments[Consensus::SMART_CONTRACTS_HARDFORK].bit = 30;

        nSwitchPhi2Block = 299501;
        nFirstSCBlock = 350000;
        nPruneAfterHeight = 300000;
        nSplitRewardBlock = 300000;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xb1;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0xc4;
        vAlertPubKey = ParseHex("042d13c016ed91528241bcff222989769417eb10cdb679228c91e26e26900eb9fd053cd9f16a9a2894ad5ebbd551be1a4bd23bd55023679be17f0bd3a16e6fbeba");
        nDefaultPort = 20029;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nMaturity = 80;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 615800;

        const char* pszTimestamp = "Bitcoin Cash Celebrates Its One-Year Anniversary | Author. JP Buntinx"; // Input Activation code to activate blockchain
        CMutableTransaction txNew;
        txNew.nVersion = 1;
        txNew.nTime = 1532858400; // Sunday, July 29, 2018 3:00:00 AM
        txNew.nLockTime = 0;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        genesis.nVersion = 1;
        genesis.nTime = 1532858400; // Sunday, July 29, 2018 3:00:00 AM
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 0;
        genesis.hashStateRoot = uint256(h256Touint(dev::h256("e965ffd002cd6ad0e2dc402b8044de833e06b23127ea8c3d80aec91410771495"))); // lux
        genesis.hashUTXORoot = uint256(h256Touint(dev::sha3(dev::rlp("")))); // lux

        consensus.hashGenesisBlock = genesis.GetHash();

// GenesisBlock Hashing
if (true && genesis.GetHash() != hashGenesisBlock)
        {
            printf("Searching for genesis block...\n");
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;
            while(true)
            {
                thash = genesis.GetHash();
                if (thash <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                   {
                     printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                   }
                   ++genesis.nNonce;
                if (genesis.nNonce == 0)
                   {
                     printf("NONCE WRAPPED, incrementing time\n");
                     ++genesis.nTime;
                   }

                    // ONLY ENABLE TO WATCH GENESIS HASHING IN PROGRESS
                    // LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
                    // LogPrintf("block.nTime = %u \n", genesis.nTime);
                    // LogPrintf("block.nNonce = %u \n", genesis.nNonce);
                    // LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                 }

             }

// DEBUG LOG PRINT FOR FINAL GENSIS HASH OUTPUT
LogPrintf("Hashed MainNet Genesis Block Output \n");
LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
LogPrintf("block.nTime = %u \n", genesis.nTime);
LogPrintf("block.nNonce = %u \n", genesis.nNonce);
LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());

        assert(consensus.hashGenesisBlock == uint256("0x"));
        assert(genesis.hashMerkleRoot == uint256("0x"));

        //vSeeds.push_back(CDNSSeedData("140.82.21.110", "140.82.21.110"));        // Luxgate seed
        //vSeeds.push_back(CDNSSeedData("149.28.163.40", "149.28.163.40"));        // Main seed
        //vSeeds.push_back(CDNSSeedData("207.148.83.62", "207.148.83.62"));        // Chain state seed
        //vSeeds.push_back(CDNSSeedData("207.148.81.88", "207.148.81.88"));        // Global state seed
        //vSeeds.push_back(CDNSSeedData("149.28.172.147", "149.28.172.147"));      // Main seed
        ////////////////////////////////////////////////////////////////////////////////////////////////
        //vSeeds.push_back(CDNSSeedData("45.32.86.162", "45.32.86.162"));           // DNSSeed
        //vSeeds.push_back(CDNSSeedData("45.77.127.10", "45.77.127.10"));           // DNSSeed
        //vSeeds.push_back(CDNSSeedData("45.32.146.237", "45.32.146.237"));         // DNSSeed

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60); // LUX address start with 'R'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,53); // LUX script addresses start with 'N'
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,63); // Secret Keys begin with 'S'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x07)(0x28)(0xA2)(0x4E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0xD8)(0xA1)(0xE5).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "bc";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04a983220ea7a38a7106385003fef77896538a382a0dcc389cc45f3c98751d9af423a097789757556259351198a8aaa628a1fd644c3232678c5845384c744ff8d7";

        strDarksendPoolDummyAddress = "LgcjpYxWa5EB9KCYaRtpPgG8kgiWRvJY38";
        nStartMasternodePayments = 1507656633; // 10/10/2017

        nStakingRoundPeriod = 180; // 3 minutes a round
        nStakingInterval = 24;
        nStakingMinAge = 24 * 60 * 60; // 24 hours
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        //consensus.BIP34Height = 227931;
        //consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8");
        consensus.powLimit = ~uint256(0) >> 10; // LUX starting difficulty is 1 / 2^12
        consensus.nPowTargetTimespan = 30 * 60; //36 * 60 * 60; // LUX: 1 36hrs
        consensus.nPowTargetSpacing = 2 * 60;  // LUX: 2 minute
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1368; // 95% of 1440 is
        consensus.nMinerConfirmationWindow = 1440; // nPowTargetTimespan / nPowTargetSpacing
        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 577836800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 2577836900; // Never / undefined
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 577836800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 2577836900; // Never / undefined
        consensus.nLastPOWBlock = 6000000;

        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0x45;
        pchMessageStart[2] = 0xcc;
        pchMessageStart[3] = 0x3b;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce1211745607d573b8810c02c0582aed05a34eb9c4bb7626d92427c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 20062;
        nMinerThreads = 0;
        nMaturity = 25;
        nModifierUpdateBlock = 51197; //approx Tuesday, December 25, 2018 12:00:59 AM

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        const char* pszTimestamp = "Lux - Testnet 1"; // Input Activation code to activate blockchain
        CMutableTransaction txNew;
        txNew.nVersion = 1;
        txNew.nTime = 1545696059; //Tuesday, December 25, 2018 12:00:59 AM
        txNew.nLockTime = 0;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();

        genesis.SetNull();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        genesis.nVersion = 1;
        genesis.nTime = 1545696059; //Tuesday, December 25, 2018 12:00:59 AM
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 0;
        genesis.hashStateRoot = uint256(h256Touint(dev::h256("e965ffd002cd6ad0e2dc402b8044de833e06b23127ea8c3d80aec91410771495"))); // lux
        genesis.hashUTXORoot = uint256(h256Touint(dev::sha3(dev::rlp("")))); // lux

//        while (!CheckProof(genesis.GetHash(), genesis.nBits)) {
//            genesis.nNonce ++;
//        }

//        std::cout << genesis.nNonce << std::endl;
//        std::cout << genesis.GetHash().GetHex() << std::endl;
//        std::cout << genesis.hashMerkleRoot.GetHex() << std::endl;

        nSwitchPhi2Block = 1000;
        nSplitRewardBlock = 1500;
        nPruneAfterHeight = 5000;
        nFirstSCBlock = 10000;

        consensus.hashGenesisBlock = genesis.GetHash();

        // GenesisBlock Hashing
if (true && genesis.GetHash() != hashGenesisBlock)
        {
            printf("Searching for genesis block...\n");
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;
            while(true)
            {
                thash = genesis.GetHash();
                if (thash <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                   {
                     printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                   }
                   ++genesis.nNonce;
                if (genesis.nNonce == 0)
                   {
                     printf("NONCE WRAPPED, incrementing time\n");
                     ++genesis.nTime;
                   }

                    // ONLY ENABLE TO WATCH GENESIS HASHING IN PROGRESS
                    // LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
                    // LogPrintf("block.nTime = %u \n", genesis.nTime);
                    // LogPrintf("block.nNonce = %u \n", genesis.nNonce);
                    // LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                 }

             }

// DEBUG LOG PRINT FOR FINAL GENSIS HASH OUTPUT
LogPrintf("Hashed TestNet Genesis Block Output \n");
LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
LogPrintf("block.nTime = %u \n", genesis.nTime);
LogPrintf("block.nNonce = %u \n", genesis.nNonce);
LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());

        assert(consensus.hashGenesisBlock == uint256("0x"));
        assert(genesis.hashMerkleRoot == uint256("0x"));

        //vFixedSeeds.clear();
        //vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("luxtest1", "140.82.45.100"));
        //vSeeds.push_back(CDNSSeedData("luxtest2", "144.202.3.186"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 60); // Testnet lux addresses start with 'R'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); // Testnet lux script addresses start with 'B'
            base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 75);     // Testnet private keys start with 'X'
        // Testnet lux BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet lux BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet lux BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        bech32_hrp = "tb";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";

        strDarksendPoolDummyAddress = "LPGq7DZbqZ8Vb3tfLH8Z8VHqeV4fsK68oX";
        nStartMasternodePayments = 1545696059; //Tuesday, December 25, 2018 12:00:59 AM
        nStakingRoundPeriod = 120; // 5 seconds a round
        nStakingInterval = 22; // 30 seconds
        nStakingMinAge = 360; // 6 minutes (referenced in seconds)
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        //consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        //consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // Lux: 1 day (86,400 seconds = 24 hours)
        consensus.nPowTargetSpacing = 1 * 60; // Lux: 1 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;
        consensus.powLimit = ~uint256(0) >> 1;

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x44;
        pchMessageStart[3] = 0xab;
        nMinerThreads = 1;
        nMaturity = 2;
        genesis.nTime = 1532858400;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 8;

        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 20086;
//        assert(hashGenesisBlock == uint256("0"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 19427;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        consensus.fPowAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { consensus.nMajorityEnforceBlockUpgrade = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { consensus.nMajorityRejectBlockOutdated = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { consensus.nMajorityWindow = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { consensus.fPowAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;

class CSegWitTestnet : public CChainParams
{
public:
    CSegWitTestnet()
    {
        networkID = CBaseChainParams::SEGWITTEST;
        strNetworkID = "segwit";
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = ~uint256(0) >> 20; // LUX starting difficulty is 1 / 2^12
        consensus.nPowTargetTimespan = 10 * 60; //10 minute
        consensus.nPowTargetSpacing = 60;  // LUX: 1 minute
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 9; // 95% of 10
        consensus.nMinerConfirmationWindow = 10; // nPowTargetTimespan / nPowTargetSpacing
        // Deployment of SegWit (BIP141 and BIP143)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1524733200;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1557187200; // TODO: ?? - just some random date - 05.07.2019
        //Deployment of CSV
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.nLastPOWBlock = 6000000; // MAX_MONEY / PoW Payout = nLastPOWBlock

        nSwitchPhi2Block = 1200;
        //nFirstSCBlock = 300000;
        //nPruneAfterHeight = 100000;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0x70;
        pchMessageStart[2] = 0xc7;
        pchMessageStart[3] = 0xa6;
        vAlertPubKey = ParseHex("042d13c016ed91528241bcff222989769417eb10cdb649228c91e26e26900eb9fd053cd9f164698494ad5ebbd551be1a4bd23bd55023679be17f0bd3a16e6fbeba");
        nDefaultPort = 20034;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nMaturity = 5;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 615800;
        bech32_hrp = "bcst";

        const char* pszTimestamp = "Bitcoin Cash Celebrates Its One-Year Anniversary | Author. JP Buntinx"; // Input Activation code to activate blockchain
        CMutableTransaction txNew;
        txNew.nVersion = 1;
        txNew.nTime = 1532858400;
        txNew.nLockTime = 0;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        const char* strPubKey = "039ec9c09ee245790849f297f8df36c3aab97335ee011250a23d35569fdab891f0";
        txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].scriptPubKey = CScript() << ParseHex(strPubKey) << OP_CHECKSIG;
        txNew.vout[0].nValue = 21000000000000;

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        genesis.nVersion = 1;
        genesis.nTime = 1532858400;
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 0;

        /*while (!CheckProof(genesis.GetHash(), genesis.nBits)) {
            genesis.nNonce ++;
        }

        std::cout << genesis.nNonce << std::endl;
        std::cout << genesis.GetHash().GetHex() << std::endl;
        std::cout << genesis.hashMerkleRoot.GetHex() << std::endl;*/

        consensus.hashGenesisBlock = genesis.GetHash();


// GenesisBlock Hashing
if (true && genesis.GetHash() != hashGenesisBlock)
        {
            printf("Searching for genesis block...\n");
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;
            while(true)
            {
                thash = genesis.GetHash();
                if (thash <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                   {
                     printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                   }
                   ++genesis.nNonce;
                if (genesis.nNonce == 0)
                   {
                     printf("NONCE WRAPPED, incrementing time\n");
                     ++genesis.nTime;
                   }

                    // ONLY ENABLE TO WATCH GENESIS HASHING IN PROGRESS
                    // LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
                    // LogPrintf("block.nTime = %u \n", genesis.nTime);
                    // LogPrintf("block.nNonce = %u \n", genesis.nNonce);
                    // LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                 }

             }

// DEBUG LOG PRINT FOR FINAL GENSIS HASH OUTPUT
LogPrintf("Hashed RegNet Genesis Block Output \n");
LogPrintf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
LogPrintf("block.nTime = %u \n", genesis.nTime);
LogPrintf("block.nNonce = %u \n", genesis.nNonce);
LogPrintf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());


        assert(consensus.hashGenesisBlock == uint256("0x"));
        assert(genesis.hashMerkleRoot == uint256("0x"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,144); // LUX Start letter 'Z' or '2'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,15);  // Begins with '7'
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,23);  // Begins with 'A'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x07)(0x28)(0xA2)(0x4E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0xD8)(0xA1)(0xE5).convert_to_container<std::vector<unsigned char> >();

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04a983220ea7a38a7106385003fef77896538a316548cc1234545f3c98751d9af573a097789456726259351198a8aaa628a1fd644c3232678c5845384c744ff8d7";

        strDarksendPoolDummyAddress = "LgcjpYxWa5EB9KCYaRtpPgG8kgiWRvJY38";
        nStartMasternodePayments = 1568970720; // Friday, September 20, 2019 9:12:00 AM

        nStakingRoundPeriod = 120; // 2 minutes a round
        nStakingInterval = 22;
        nStakingMinAge = 36 * 60 * 60;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataSegwittest;
    }
};
static CSegWitTestnet segwitParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    case CBaseChainParams::SEGWITTEST:
        return segwitParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

CChainParams* CreateChainParams(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return new CMainParams();
    case CBaseChainParams::TESTNET:
        return new CTestNetParams();
    case CBaseChainParams::REGTEST:
        return new CRegTestParams();
    case CBaseChainParams::SEGWITTEST:
        return new CSegWitTestnet();
    default:
        throw std::runtime_error(strprintf("%s: Unknown chain.", __func__));
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
