#ifndef WRONG_INDX
#define WRONG_INDX -1
#endif

#include "myBank.h"

#include <stdio.h>
#include <stdbool.h>

void printMenu(){
  printf("\t-help menu- \nO: Open new account \nB: Print balance \nD: Deposite  \nW: Withrawal \nC: Close account \n");
  printf("I: Add interest for all accounts \nP: Print all open accounts and balance \nE: Close all accounts and exit \nH: Help\n\n");
}

int main() {
  printf("Welcome to my online bank \nfor help in any time press H\n\n");
  bool exit = false;
  while (!exit) {
    char act;
    printf("Transaction type?\n");
    scanf(" %c", &act);
    switch (act) {
      case 'O':{
        printf("Initial deposite?\n");
        double amount;
        scanf("%lf", &amount);
        amount = round2Digits(amount);
        int ans = openAcc(amount);
        if(ans != WRONG_INDX)
          printf("Your account number is %d and your balance is %g\n", ans, getBalance(ans));
        else
          printf("I'm sorry but we don't have a place for you. try later.\n");
        break;
      }
      case 'B':{
        printf("Account number?\n");
        int account;
        scanf("%d", &account);
        double ans = getBalance(account);
        if(ans != WRONG_INDX)
          printf("The balance for %d account is %g\n", account, ans);
        else
          printf("Account dosn't exist\n");
        break;
      }
      case 'D':{
        int account;
        printf("Account number?\n");
        scanf("%d", &account);
        double amount;
        printf("Amount?\n");
        scanf("%lf", &amount);
        amount = round2Digits(amount);
        double ans = deposite(account, amount);
        if(ans != WRONG_INDX)
          printf("%g was deposite. the balance for %d account is %g\n", amount, account, ans);
        else
          printf("Account dosn't exist OR you entered a negativ amount\n");
        break;
      }
      case 'W':{
        int account;
        printf("Account number?\n");
        scanf("%d", &account);
        double amount;
        printf("Amount?\n");
        scanf("%lf", &amount);
        amount = round2Digits(amount);
        double ans = withrawal(account, amount);
        if(ans != WRONG_INDX)
          printf("%g was withrawaled. the balance for %d account is %g\n", amount, account, ans);
        else
          printf("Account dosn't exist OR you don'e have enough money OR you entered a negativ amount\n");
        break;
      }
      case 'C':{
        int account;
        printf("Account number?\n");
        scanf("%d", &account);
        bool ans = closeAcc(account);
        if(ans)
          printf("Account %d is close succsesfuly\n", account);
        else
          printf("Wrong account number\n");
        break;
      }
      case 'I':{
        double inter;
        printf("Interest rate?\n");
        scanf("%lf", &inter);
        interest(inter);
        printf("Interest was add with rate of %g\n", inter);
        break;
      }
      case 'P':{
        printAll();
        break;
      }
      case 'E':{
        closeAll();
        exit = true;
        printf("The bank is close. Goodbye!");
        break;
      }
      case 'H':{
        printMenu();
        break;
      }
      default:{
        char nothing[256];
        scanf(" %s", nothing);
        printf("Wrong input. try again. (H for help)\n");
      }
    }
    printf("\n");
  }
}
