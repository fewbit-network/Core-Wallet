#include <founder_payment.h>
#include <rpc/server.h>
#include <boost/foreach.hpp>
#include <chainparams.h>
#include <key_io.h>
#include <util.h>

std::string GetActiveFounderAddress(int nHeight)
{
    if (nHeight >= 300300) {
        return "FBA69LP6syGpa3zGiiaQmkSUTY2XrtQbov";  // Nuovo dev address solo da 300300 in avanti
    } else {
        return DEFAULT_FOUNDER_ADDRESS;  // BURN address storico per tutti i blocchi precedenti
    }
}

CAmount FounderPayment::getFounderPaymentAmount(int blockHeight, CAmount blockReward)
{
    if (blockHeight <= startBlock) {
        return 0;
    }

    for (size_t i = 0; i < rewardStructures.size(); i++) {
        if (i == 0 && blockHeight <= rewardStructures[i].blockHeight) {
            return blockReward * rewardStructures[i].rewardPercentage / 100;
        }

        if (blockHeight > rewardStructures[i - 1].blockHeight && blockHeight <= rewardStructures[i].blockHeight) {
            return blockReward * rewardStructures[i].rewardPercentage / 100;
        }
    }

    return rewardStructures.back().rewardPercentage * blockReward / 100;
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
    const CAmount founderReward = getFounderPaymentAmount(height, blockReward);

    if (founderReward == 0) {
        return true;  // Nessun founder payment previsto su questo blocco
    }

    CScript payee = GetScriptForDestination(DecodeDestination(GetActiveFounderAddress(height)));

    BOOST_FOREACH (const CTxOut& out, txNew.vout) {
        if (out.scriptPubKey == payee && out.nValue >= founderReward) {
            return true;
        }
    }

    // Eccezione: blocchi storici prima del 300300 → accettiamo comunque per non corrompere la chain
    if (height < 300300) {
        LogPrintf("FounderPayment::IsBlockPayeeValid -- Skipping strict founder check for legacy block %d\n", height);
        return true;
    }

    // Per blocchi da 300300 in poi → controllo rigoroso
    return false;
}
