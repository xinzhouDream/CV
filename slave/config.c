/*
 * config.c
 *
 *  Created on: Dec 23, 2015
 *      Author: xiaoxin
 */

#include "config.h"
#include "transactions.h"

int configWhseCount;

int configDistPerWhse;

int configCustPerDist;

int configUniqueItems;

int MaxBucketSize;

int configCommitCount;

int transactionsPerTerminal;
int paymentWeightValue;
int orderStatusWeightValue;
int deliveryWeightValue;
int stockLevelWeightValue;
int limPerMin_Terminal;

//the max number of wr-locks held in one transaction.
int MaxDataLockNum;

//the limited max number of new orders for each district.
int OrderMaxNum;

/* the max number of transaction ID for per process. */
int MaxTransId;

//smallbank
int configNumAccounts;
float scaleFactor;
int configAccountsPerBucket;

int FREQUENCY_AMALGAMATE;
int FREQUENCY_BALANCE;
int FREQUENCY_DEPOSIT_CHECKING;
int FREQUENCY_SEND_PAYMENT;
int FREQUENCY_TRANSACT_SAVINGS;
int FREQUENCY_WRITE_CHECK;

int MIN_BALANCE;
int MAX_BALANCE;


void InitConfig(void)
{
   transactionsPerTerminal=20000;
   paymentWeightValue=43;
   orderStatusWeightValue=0;
   deliveryWeightValue=0;
   stockLevelWeightValue=4;
   limPerMin_Terminal=0;

   configWhseCount=5;
   configDistPerWhse=10;
   configCustPerDist=3000;
   MaxBucketSize=1000000;
   configUniqueItems=100000;

   configCommitCount=60;

   MaxDataLockNum=80;

   OrderMaxNum=12000;

   MaxTransId=1000000;

   //smallbank
   scaleFactor=0.1;
   configNumAccounts=(int)(scaleFactor*1000000);
   configAccountsPerBucket=10000;

   FREQUENCY_AMALGAMATE=15;
   FREQUENCY_BALANCE=15;
   FREQUENCY_DEPOSIT_CHECKING=15;
   FREQUENCY_SEND_PAYMENT=25;
   FREQUENCY_TRANSACT_SAVINGS=15;
   FREQUENCY_WRITE_CHECK=15;

   MIN_BALANCE=10000;
   MAX_BALANCE=50000;
}
