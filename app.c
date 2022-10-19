#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include"card.h"
#include"terminal.h"
#include"server.h"
#include"app.h"



void appStart(void) {
	

	ST_cardData_t cardData;
	ST_terminalData_t termData;
	EN_terminalError_t UserTerm;
	ST_transaction_t transData;

	EN_cardError_t UserCard = getCardHolderName(&cardData);
	while (UserCard == WRONG_NAME) {
		printf("\WRONG NAME PLEASE TRY AGAIN : \n");
		
		UserCard = getCardHolderName(&cardData);
	}
	UserCard = getCardExpiryDate(&cardData);
	while (UserCard == WRONG_EXP_DATE) {
		printf("WRONG EXPIRATION DATE PLEASE TRY AGAIN : \n");
		
		UserCard = getCardExpiryDate(&cardData);
	}
	UserCard = getCardPAN(&cardData);
	while (UserCard == WRONG_PAN) {
		printf("INVALID PAN PLEASE TRY AGAIN : \n");
		UserCard = getCardPAN(&cardData);
	}
	UserTerm = setMaxAmount(&termData);
	while (UserTerm == INVALID_MAX_AMOUNT) {
		printf("INVALID AMOUNT PLEASE TRY AGAIN\n");
		
		UserTerm = setMaxAmount(&termData);
	}
	UserTerm = getTransactionDate(&termData);
	while (UserTerm == WRONG_DATE) {
		printf("WRONG DATE PLEASE TRY AGAIN\n");
		
		UserTerm = getTransactionDate(&termData);
	}
	UserTerm = isCardExpired(cardData, termData);
	if (UserTerm == EXPIRED_CARD) {
		printf("THIS IS AN EXPIRED_CARD\n");
		return;
	}
	UserTerm = getTransactionAmount(&termData);
	while (UserTerm == INVALID_AMOUNT) {
		printf("INVALID AMOUNT PLEASE TRY AGAIN\n");
		UserTerm = getTransactionAmount(&termData);
	}
	UserTerm = isBelowMaxAmount(&termData);
	if (UserTerm == EXCEED_MAX_AMOUNT) {
		printf("DECLINED BECAUSE IT EXCEEDED MAXIMUM AMOUNT\n");
		return;
	}
	transData.cardHolderData = cardData;
	transData.terminalData = termData;
	EN_transState_t transUser = recieveTransactionData(&transData);
	if (transUser == DECLINED_STOLEN_CARD) {
		printf("DECLINED BECAUSE IT IS A STOLEN CARD OR INVALID ACCOUNT\n");
	}
	else if (transUser == DECLINED_INSUFFECIENT_FUND) {
		printf("DECLINED BECAUSE OF INSUFFECIENT FUND\n");
	}
	else if (transUser == APPROVED) {
		printf("APPROVED\n");
		printf("SAVING TRANSACTION.......\n");
		
	}
	saveTransaction(&transData);
	getTransaction(transData.transactionSequenceNumber, &transData);

}

