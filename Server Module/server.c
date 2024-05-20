#include <stdio.h>
#include <string.h>
#include "server.h"
#include "../Card Module/card.h"
#include "../Terminal Module/terminal.h"
#pragma warning(disable:4996)

int m = -1;
ST_accountsDB_t accountsDB[10] = { {2000.0, RUNNING, "8989374615436851"} , {30000.0, RUNNING, "9685746578694037"} ,
	                             {15000.0, BLOCKED, "4563728191029384"} , {100000.0, BLOCKED, "5807007076043875"} ,
								 {2000, RUNNING, "1234567899876543"} , {780, RUNNING, "9876543211234567"} , 
								 {1000.0, BLOCKED, "5807007009043875"} , {90000000, RUNNING, "9586774658493021"} , 
								 {500000, RUNNING, "9586779598493021"} };
ST_accountsDB_t accRefrence;

ST_transaction_t transactionDB[10] = { {0,0,0,0} , {0,0,0,0} , {0,0,0,0} , {0,0,0,0} , {0,0,0,0} };


EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	int j;
	for (j=0; j<10; j++)
	{    
		
		  

			if (!strcmp(cardData->primaryAccountNumber, accountsDB[j].primaryAccountNumber)) {
				
				accountRefrence->balance = accountsDB[j].balance;
				strcpy(accountRefrence->primaryAccountNumber, accountsDB[j].primaryAccountNumber);
				accountRefrence->state = accountsDB[j].state;
				return SERVER_OK;
			}
			
		
	}
	
	printf("Account not found in database\n\n");
	printf("Transaction Declined \n");
	return ACCOUNT_NOT_FOUND;
	
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (accRefrence.balance >= termData->transAmount)
	{
		accRefrence.balance -= termData->transAmount;
		printf("Transaction Approved \n");
		return SERVER_OK;
	}
	else
	{
		printf("Insufficient funds\n\n");
		printf("Transaction Declined \n");
		return LOW_BALANCE;
	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	return (accountRefrence->state);
}

EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	if(isValidAccount(&transData->cardHolderData,&accRefrence))
	{
		return FRAUD_CARD;
	}
	
	if(isBlockedAccount(&accRefrence))
	{
		printf("Account is blocked\n\n");
		printf("Transaction Declined \n");
		return DECLINED_STOLEN_CARD;
	}
	
	if(isAmountAvailable(&transData->terminalData))
	{

		return DECLINED_INSUFFECIENT_FUND;
	}
	return APPROVED;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transData->transactionSequenceNumber = 101 + m;
	m++;
	transData->transState = accRefrence.state;
	strcpy(transactionDB[m].cardHolderData.cardExpirationDate , transData->cardHolderData.cardExpirationDate);
	strcpy(transactionDB[m].cardHolderData.cardHolderName , transData->cardHolderData.cardHolderName);
	strcpy(transactionDB[m].cardHolderData.primaryAccountNumber , transData->cardHolderData.primaryAccountNumber);
	strcpy(transactionDB[m].terminalData.transactionDate , transData->terminalData.transactionDate);
	transactionDB[m].terminalData.transAmount = transData->terminalData.transAmount;
	transactionDB[m].transactionSequenceNumber = transData->transactionSequenceNumber;
	transactionDB[m].transState = transData->transState;

	printf("\n\n");
	printf("__Transaction Information__\n");
	printf("Card Holder Name: %s\n", transactionDB[m].cardHolderData.cardHolderName);
	printf("Primary Account Number: %s\n", transactionDB[m].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s\n", transactionDB[m].cardHolderData.cardExpirationDate);
	printf("Transaction Amount: %.1f\n", transactionDB[m].terminalData.transAmount);
	printf("Account Balance: %.1f\n", accRefrence.balance);


	return SERVER_OK;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	if (transactionDB[m].transactionSequenceNumber==transData->transactionSequenceNumber)
	{
		return SERVER_OK;
	}
	return TRANSACTION_NOT_FOUND;
}