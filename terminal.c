#include<stdio.h>
#include<stdint.h>
#include"card.h"
#include"terminal.h"
#include<string.h>

#define _CRT_SECURE_NO_WARNINGS

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
#define slength_t strlen(termData->transactionDate)


	printf("Please enter transaction date in format : DD/MM/YYYY:\n");
	scanf("%s", termData->transactionDate);


	if (slength_t == NULL || slength_t < 10 || (termData->transactionDate[2] && termData->transactionDate[5] != '/')) {
		
			return WRONG_DATE;

	}

	else {
		
		return Right;
	}
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	
	if ((cardData.cardExpirationDate[0] > termData.transactionDate[3]) && (cardData.cardExpirationDate[3] >= termData.transactionDate[8]) && (cardData.cardExpirationDate[4] >= termData.transactionDate[9])) {

		return Right;
	}
	else if ((cardData.cardExpirationDate[0] <= termData.transactionDate[3]) && (cardData.cardExpirationDate[1] >= termData.transactionDate[4]) && (cardData.cardExpirationDate[3] >= termData.transactionDate[8]) && (cardData.cardExpirationDate[4] > termData.transactionDate[9])) {

		return Right;
	}
	
	else {
			
			return EXPIRED_CARD;
		}
		
	}


getTransactionAmount(ST_terminalData_t* termData) {
	printf("Please enter transaction Amount\n");
	scanf("%f", &termData->transAmount);

	if (termData->transAmount <= 0) {
		
		return INVALID_AMOUNT;
	}

	else
		return Right;

}
isBelowMaxAmount(ST_terminalData_t* termData) {

	if (termData->transAmount > termData->maxTransAmount) {

		//printf("Transaction exceeds max amount\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
		return Right;
	
}
setMaxAmount(ST_terminalData_t* termData) {
	printf("please set maximum number\n");
	scanf("%f", &termData->maxTransAmount);

	if (termData->maxTransAmount <= 0) {
		
		return INVALID_MAX_AMOUNT;

	}
	else
		return Right;

}




