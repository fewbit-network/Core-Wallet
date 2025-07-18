#ifndef SRC_FOUNDER_PAYMENT_H_
#define SRC_FOUNDER_PAYMENT_H_

#include <amount.h>
#include <limits.h>
#include <primitives/transaction.h>
#include <script/standard.h>
#include <string>
using namespace std;

static const string DEFAULT_FOUNDER_ADDRESS = "FJ4QNkE7p9mWvEYKAc9zNNRxk6vkaNMuUu";

struct FounderRewardStructure {
    int blockHeight;
    int rewardPercentage;
};

class FounderPayment
{
public:
    FounderPayment(vector<FounderRewardStructure> rewardStructures = {}, int startBlock = 0, const string& address = DEFAULT_FOUNDER_ADDRESS)
    {
        this->founderAddress = address;
        this->startBlock = startBlock;
        this->rewardStructures = rewardStructures;
    }
    ~FounderPayment() {};
    CAmount getFounderPaymentAmount(int blockHeight, CAmount blockReward);
    void FillFounderPayment(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, CTxOut& txoutFounderRet);
    bool IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward);
    int getStartBlock() { return this->startBlock; }

private:
    string founderAddress;
    int startBlock;
    vector<FounderRewardStructure> rewardStructures;
};

std::string GetActiveFounderAddress(int nHeight);

#endif /* SRC_FOUNDER_PAYMENT_H_ */
