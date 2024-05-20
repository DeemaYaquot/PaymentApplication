#include <stdio.h>
#include <string.h>
#include "terminal.h"
#include "../Card Module/card.h"
#pragma warning(disable:4996)



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
check:
	printf("Enter transaction date in the format DD/MM/YYYY\n");
	gets(termData->transactionDate);
	if (strlen(termData->transactionDate) != 10)
	{
		printf("Transaction date must be 10 characters\n");
		goto check;
		return WRONG_DATE;
	}
	else if (termData->transactionDate[2] != 47 || termData->transactionDate[5] != 47)
	{
		printf("Transaction date format must be DD/MM/YYYY\n");
		goto check;
		return WRONG_DATE;
	}
	else
	{
		return Terminal_OK;
	}
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if (termData->transactionDate[8] > cardData->cardExpirationDate[3])
	{
		printf("Card is expired\n");
		return EXPIRED_CARD;
	}
	else if (termData->transactionDate[8] < cardData->cardExpirationDate[3])
	{
		return Terminal_OK;
	}
	else if (termData->transactionDate[8] == cardData->cardExpirationDate[3] && termData->transactionDate[9] > cardData->cardExpirationDate[4])
	{
		printf("Card is expired\n");
		return EXPIRED_CARD;
	}
	else if (termData->transactionDate[8] == cardData->cardExpirationDate[3] && termData->transactionDate[9] == cardData->cardExpirationDate[4])
	{
		if (termData->transactionDate[3] > cardData->cardExpirationDate[0])
		{
			printf("Card is expired\n");
			return EXPIRED_CARD;
		}
		else if (termData->transactionDate[3] < cardData->cardExpirationDate[0])
		{
			return Terminal_OK;
		}
		else if (termData->transactionDate[3] == cardData->cardExpirationDate[0] && termData->transactionDate[4] > cardData->cardExpirationDate[1])
		{
			printf("Card is expired\n");
			return EXPIRED_CARD;
		}
		else return Terminal_OK;
	}
	else return Terminal_OK;

}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
	{
		printf("Invalid Primary Account Number\n");
		return INVALID_CARD;
	}
	else return Terminal_OK;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
check:
	printf("Enter transaction amount\n");
	scanf("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
	{
		printf("Transaction amount must be more than 0\n");
		goto check;
		return INVALID_AMOUNT;
	}
	else return Terminal_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = 5000;
	if (termData->maxTransAmount <= 0)
	{
		printf("Maximum transaction amount must be more than 0\n");
		return INVALID_MAX_AMOUNT;
	}
	else return Terminal_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		printf("Maximum transaction amount exceeded\n");
		return EXCEED_MAX_AMOUNT;
	}
	else return Terminal_OK;
}
