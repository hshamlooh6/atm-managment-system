#include "header.h"

void makeTransaction(struct User u)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    clearScreen();
    printf("\t\t====== Make a transaction ======\n\n");
    int accountNbr = readIntSafe("Enter the account id: ");

    int index = findRecordIndex(records, count, u.id, accountNbr);
    if (index == -1)
    {
        printf("\n✖ No account with that id was found for your user.\n");
        waitForEnter();
        return;
    }

    struct Record *r = &records[index];

    if (!accountAllowsTransactions(r->accountType))
    {
        printf("\n✖ Error: accounts of type %s cannot make transactions.\n",
               r->accountType);
        waitForEnter();
        return;
    }

    printf("\nCurrent balance: $%.2f\n", r->amount);
    printf("\t[1]- Deposit\n\t[2]- Withdraw\n");
    int choice = readIntSafe("Your choice: ");

    if (choice == 1)
    {
        double amount = readDoubleSafe("Amount to deposit: $");
        if (amount <= 0)
        {
            printf("\nThe amount must be positive.\n");
            waitForEnter();
            return;
        }
        r->amount += amount;
    }
    else if (choice == 2)
    {
        double amount = readDoubleSafe("Amount to withdraw: $");
        if (amount <= 0)
        {
            printf("\nThe amount must be positive.\n");
            waitForEnter();
            return;
        }
        if (amount > r->amount)
        {
            printf("\n✖ Insufficient funds. Current balance is $%.2f.\n", r->amount);
            waitForEnter();
            return;
        }
        r->amount -= amount;
    }
    else
    {
        printf("\nInvalid operation!\n");
        waitForEnter();
        return;
    }

    saveAllRecords(records, count);
    printf("\n✔ Done! New balance: $%.2f\n", r->amount);
    waitForEnter();
}
