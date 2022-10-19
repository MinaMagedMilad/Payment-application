#include<stdio.h>
#include<stdint.h>
#include"card.h"
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Please enter card holder name:\n");
	scanf("%[^\n]%*c", cardData->cardHolderName);
	//uint8_t size = strlen(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) <= NULL || strlen(cardData->cardHolderName) > 24 || strlen(cardData->cardHolderName) < 20) {
		return WRONG_NAME;
	}
	else
	return OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
#define slength strlen(cardData->cardExpirationDate)


	printf("Please enter card expiry date in format : MM/YY:\n");
	scanf("%s", cardData->cardExpirationDate);


	if (slength == NULL || slength != 5 || cardData->cardExpirationDate[2] != '/') {
		return WRONG_EXP_DATE;

	}

	else {
		//printf("%s", __DATE__);
		return OK;
	}
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) {


	printf("Please enter card's Primary Account Number:\n");
	scanf("%s", cardData->primaryAccountNumber);
	//uint8_t size = strlen(cardData->cardHolderName);
	if (strlen(cardData->primaryAccountNumber) == NULL || strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16) {
		printf("Wrong card's Primary Account Number\n");
		return WRONG_PAN;
	}
	else
		return OK;

	

}

