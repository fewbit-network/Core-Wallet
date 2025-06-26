#include <founder_payment.h>
#include <rpc/server.h>
#include <boost/foreach.hpp>
#include <chainparams.h>
#include <key_io.h>
#include <util.h>

CAmount FounderPayment::getFounderPaymentAmount(int blockHeight, CAmount blockReward)
{
    if (blockHeight <= startBlock) {
        return 0;
    }
    for (int i = 0; i < rewardStructures.size(); i++) {
        FounderRewardStructure rewardStructure = rewardStructures[i];
        if (rewardStructure.blockHeight == INT_MAX || blockHeight <= rewardStructure.blockHeight) {
            return blockReward * rewardStructure.rewardPercentage / 100;
        }
    }
    return 0;
}

void FounderPayment::FillFounderPayment(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, CTxOut& txoutFounderRet)
{
    CAmount founderPayment = getFounderPaymentAmount(nBlockHeight, blockReward);
    txoutFounderRet = CTxOut();

    if (founderPayment > 0) {
        CTxDestination founderAddr = DecodeDestination(GetActiveFounderAddress(nBlockHeight));
        if (!IsValidDestination(founderAddr))
            throw JSONRPCError(RPC_INVALID_ADDRESS_OR_KEY, strprintf("Invalid FewBit Founder Address: %s", GetActiveFounderAddress(nBlockHeight).c_str()));

        CScript payee = GetScriptForDestination(founderAddr);
        txNew.vout[0].nValue -= founderPayment;
        txoutFounderRet = CTxOut(founderPayment, payee);
        txNew.vout.push_back(txoutFounderRet);

        LogPrintf("FounderPayment::FillFounderPayment -- Founder payment %lld to %s at block %d\n", founderPayment, GetActiveFounderAddress(nBlockHeight).c_str(), nBlockHeight);
    }
}

bool FounderPayment::IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward)
{
    CScript payee = GetScriptForDestination(DecodeDestination(GetActiveFounderAddress(height)));
    const CAmount founderReward = getFounderPaymentAmount(height, blockReward);

    BOOST_FOREACH (const CTxOut& out, txNew.vout) {
        if (out.scriptPubKey == payee && out.nValue >= founderReward) {
            return true;
        }
    }

    return founderReward == 0;
}

std::string GetActiveFounderAddress(int nHeight)
{
    if (nHeight >= 300300) {
        return "FBA69LP6syGpa3zGiiaQmkSUTY2XrtQbov";  // Nuovo founder address dal block 300300
    } else {
        return DEFAULT_FOUNDER_ADDRESS;  // Address storico fino al 300299
    }
}
