#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../Card Module/card.h"
#include "../Server Module/server.h"
#include "../Terminal Module/terminal.h"
#pragma warning(disable:4996)

void appStart(void)
{
	ST_cardData_t carddata;
	ST_terminalData_t terminaldata;
	ST_transaction_t transactiondata;

	/*Calling Card module functions */
	
	getCardHolderName(&carddata);
	getCardExpiryDate(&carddata);
	getCardPAN(&carddata);

	/*Calling Terminal module functions */
	getTransactionDate(&terminaldata);
	if(isCardExpired(&carddata, &terminaldata))
	{
		printf("Transaction Declined\n");
		exit(1);
	}
	isValidCardPAN(&carddata);
	setMaxAmount(&terminaldata);
	getTransactionAmount(&terminaldata);
	if(isBelowMaxAmount(&terminaldata))
	{
		printf("Transaction Declined\n");
		exit(1);
	}

	/*Calling Server module functions*/
	strcpy(transactiondata.cardHolderData.primaryAccountNumber, carddata.primaryAccountNumber);
	strcpy(transactiondata.cardHolderData.cardHolderName, carddata.cardHolderName);
	strcpy(transactiondata.cardHolderData.cardExpirationDate, carddata.cardExpirationDate);
	transactiondata.terminalData.transAmount = terminaldata.transAmount;
	if (recieveTransactionData(&transactiondata))
	{
		exit(1);
	}
	saveTransaction(&transactiondata);
	if (getTransaction(transactiondata.transactionSequenceNumber, &transactiondata))
	{
		exit(1);
	}
}