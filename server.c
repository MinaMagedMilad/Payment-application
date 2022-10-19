#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include"card.h"
#include"terminal.h"
#include"server.h"

int index = -1;

ST_accountsDB_t accountDatabase_arr[255] = { {20000, "3452132345545890"}, {25000,"45623323455998903456"},
	{80000,"3452132345543245"}, {30000,"34521323455998903214"}, {65000,"34521323455998917495"},
	{70000,"34521323453459603214"}, {35000,"58971323455998903214"}, {45000,"34521323455998967124"},
	{90000,"34521323455998905678"}, {60000,"34521323455998443214"} };

ST_transaction_t server_sideTransaction_arr[255] = { 0 };

ST_accountsDB_t Approved_Account = {0};


EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	

	
	

	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	transData->transState = APPROVED;
	
	accountDatabase_arr[index].balance = accountDatabase_arr[index].balance- transData->terminalData.transAmount;
	printf("your new balance is : %f\n", accountDatabase_arr[index].balance);
	if (saveTransaction(transData) == SAVING_FAILED) {
		return INTERNAL_SERVER_ERROR;
	}
	return APPROVED;
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	
	bool flag = false;
	bool status = false;
	int i = 0;
	while (i < 255) {

		//if (accountDatabase_arr[i].primaryAccountNumber != '\0') {
			//bool status = true;
		//}
		if (strcmp(accountDatabase_arr[i].primaryAccountNumber,cardData->primaryAccountNumber) ==0) {
			status = true;
			break;
		}

		else {
			i++;
		}
	}
	if (i != 255) {
		if (status) {
			flag = true;
			index = i;

		}
	} 
	else	if ((!flag) && (i == 255)) {
			return ACCOUNT_NOT_FOUND;
		}
	
	else
	return CORRECT;


}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {


		
	if (accountDatabase_arr[index].balance < termData->transAmount) {
		return LOW_BALANCE;
	}
	return CORRECT;
	
		}

		EN_serverError_t saveTransaction(ST_transaction_t * transData) {
			int i = 255;
				if (transData->transState == APPROVED && (i < 255)) {
					server_sideTransaction_arr[i] = *transData;
					printf("SAVED AS APPROVED\n");
					transData->transactionSequenceNumber++;
					i++;
					return CORRECT;
				}
				

				else if (transData->transState == DECLINED_INSUFFECIENT_FUND && (i < 255)) {

					server_sideTransaction_arr[i] = *transData;
					printf("SAVED AS DECLINED INSUFFECIENT FUND\n");
					transData->transactionSequenceNumber++;
					i++;
					return CORRECT;
				}
				else if (transData->transState == DECLINED_STOLEN_CARD && (i < 255)) {
					server_sideTransaction_arr[i] = *transData;
					printf("SAVED AS DECLINED STOLEN CARD\n");
					transData->transactionSequenceNumber++;
					i++;
					return CORRECT;
				}
				else if (i == 255) {
					
					return SAVING_FAILED;
				}

			}

		EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
		{
			if (saveTransaction(&transData) == SAVING_FAILED) {
				printf(" CAN'T SAVE TRANSACTION AS DATABASE IS FULL!\n");
			}
			else 
			return CORRECT;
		}

		


