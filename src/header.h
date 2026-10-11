#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50      
#define PASSWORD_LEN 128   
#define COUNTRY_LEN 100    
#define ACC_TYPE_LEN 10   

#define MAX_USERS 500      
#define MAX_RECORDS 2000   

#define USERS_FILE "./data/users.txt"
#define RECORDS_FILE "./data/records.txt"

struct Date
{
    int month;
    int day;
    int year;
};

struct Record
{
    int id;                    
    int userId;                
    char name[NAME_LEN];       
    int accountNbr;             
    struct Date deposit;       
    char country[COUNTRY_LEN];   
    int phone;            
    double amount;              
    char accountType[ACC_TYPE_LEN]; 
};

struct User
{
    int id;
    char name[NAME_LEN];
    char password[PASSWORD_LEN]; 
};

void clearInputBuffer(void);
int readIntSafe(const char *prompt);
double readDoubleSafe(const char *prompt);
void readStringSafe(const char *prompt, char *buffer, int bufferSize);
void waitForEnter(void);
void clearScreen(void);

void hashPassword(const char *plainPassword, char outHash[PASSWORD_LEN]);
int passwordMatches(const char *plainPassword, const char *storedHash);

int loadAllUsers(struct User list[], int maxCount);
void saveAllUsers(const struct User list[], int count);
int findUserByName(const char *name, struct User *out);
int findUserById(int id, struct User *out);
int userNameExists(const char *name);
void appendUser(struct User u);

int loadAllRecords(struct Record list[], int maxCount);
void saveAllRecords(const struct Record list[], int count);
int nextRecordId(void);
int findRecordIndex(const struct Record list[], int count, int userId, int accountNbr);

int loginMenu(struct User *loggedInUser);
void registerMenu(struct User *loggedInUser);

double interestRateForType(const char *accountType);
double monthlyInterest(double balance, const char *accountType);
int accountEarnsInterest(const char *accountType);
int accountAllowsTransactions(const char *accountType);

void createNewAccount(struct User u);
void listMyAccounts(struct User u);
void showAccountDetails(struct User u);
void updateAccountInfo(struct User u);

void makeTransaction(struct User u);

void removeAccount(struct User u);
void transferOwnership(struct User u);

void mainMenu(struct User u);

#endif
