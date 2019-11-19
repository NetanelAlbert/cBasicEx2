#ifndef FIELDS
#define FIELDS 2
#endif

#ifndef ACCOUNTS
#define ACCOUNTS 50
#endif

#ifndef FIRST_ACC
#define FIRST_ACC 901
#endif

#ifndef WRONG_INDX
#define WRONG_INDX -1
#endif

#ifndef OPEN
#define OPEN 1
#endif

#ifndef CLOSE
#define CLOSE 0
#endif

#ifndef ACC_STT
#define ACC_STT 0
#endif

#ifndef ACC_BLC
#define ACC_BLC 1
#endif

#include <stdbool.h>
#include <stdio.h>

int openedAcc = 0;

double acc[FIELDS][ACCOUNTS] = {0};

double round2Digits(double x){
  x = (int)(x*100);
  return x/100.0;
}
int findPlace(){ // return the first empty place or -1 if no space
  for(int i = 0; i < ACCOUNTS; i++){
    if(acc[ACC_STT][i] == CLOSE)
      return i + FIRST_ACC;
  }
  return WRONG_INDX;
}

bool isActive(int account){
  account -= FIRST_ACC;
  return account >= 0 && account < ACCOUNTS && acc[ACC_STT][account] == OPEN;
}

double dep_withr(int account, double amount){ // return new balance or -1 if faild
  if(isActive(account) && acc[ACC_BLC][account-FIRST_ACC] + amount >= 0){
    account -= FIRST_ACC;
    acc[ACC_BLC][account] += amount;
    return acc[ACC_BLC][account];
  }
  return WRONG_INDX;
}
double deposite(int account, double amount){
  if(amount >= 0)
    return dep_withr(account, amount);
  return WRONG_INDX;
}
int openAcc(double amount){ // return the account number or -1 if no space
  if(openedAcc >= ACCOUNTS)
    return WRONG_INDX;

  openedAcc++;
  int account = findPlace();
  acc[ACC_STT][account - FIRST_ACC] = OPEN;
  double ans = deposite(account, amount);
  if(ans == WRONG_INDX){
    printf("I'm sorry. you can't deposite a negative ammpunt.\n");
  }
  return account;
}

double getBalance(int account){
  if(isActive(account))
    return acc[ACC_BLC][account-FIRST_ACC];
  return WRONG_INDX;
}

double withrawal(int account, double amount){
  if(amount >= 0)
    return dep_withr(account, -amount);
  return WRONG_INDX;
}

bool closeAcc(int account){
  if(isActive(account)){
    account -= FIRST_ACC;
    acc[ACC_STT][account] = CLOSE;
    acc[ACC_BLC][account] = 0;
    openedAcc--;
    return true;
  }
  return false;
}
void interest(double inter){
  double rate = (100 + inter)/100;
  for(int i = 0; i < ACCOUNTS; i++){
    if(acc[ACC_STT][i] == OPEN)
      acc[ACC_BLC][i] = round2Digits(acc[ACC_BLC][i]*rate);
  }
}

void printAll(){
  for(int i = 0; i < ACCOUNTS; i++){
    if(acc[ACC_STT][i] == OPEN)
      printf("Account number: %d. Balance: %g\n", i + FIRST_ACC, acc[ACC_BLC][i]);
  }
}

void closeAll(){
  for(int i = 0; i < ACCOUNTS; i++)
    closeAcc(i);
}
