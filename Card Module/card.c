#include <stdio.h>
#include <string.h>
#include <time.h>
#include "card.h"
#pragma warning(disable:4996)


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
check:
	printf("Enter cardholder's name\n");
	gets(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
	{
		printf("Cardholder's name must be between 20 and 24 characters\n");
		goto check;
		return WRONG_NAME;
	}
	else return CARD_OK;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
check:
	printf("Enter card Expiration date in the format MM/YY\n");
	gets(cardData->cardExpirationDate);
	if (strlen(cardData->cardExpirationDate) != 5)
	{
		printf("Card expiration date must be 5 characters\n");
		goto check;
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != 47)
	{
		printf("Card expiration date format must be MM/YY\n");
		goto check;
		return WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
check:
	printf("Enter Primary Account Number\n");
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
	{
		printf("Primary Account Number must be between 16 and 19 digits\n");
		goto check;
		return WRONG_PAN;
	}
	else return CARD_OK;
}