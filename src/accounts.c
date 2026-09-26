#include "header.h"

void createNewAccount(struct User u)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    struct Record r;
    r.userId = u.id;
    strncpy(r.name, u.name, NAME_LEN - 1);
    r.name[NAME_LEN - 1] = '\0';

    clearScreen();
    printf("\t\t\t===== New account =====\n");

    while (1)
    {
        r.deposit.month = readIntSafe("\nEnter today's month (1-12): ");
        r.deposit.day = readIntSafe("Enter today's day (1-31): ");
        r.deposit.year = readIntSafe("Enter today's year (e.g. 2026): ");
        r.accountNbr = readIntSafe("\nChoose an account id (a number): ");

        int alreadyExists = 0;
        for (int i = 0; i < count; i++)
        {
            if (records[i].userId == u.id && records[i].accountNbr == r.accountNbr)
            {
                alreadyExists = 1;
                break;
            }
        }

        if (alreadyExists)
        {
            printf("\nYou already have an account with that id. Try a different one.\n");
            continue;
        }
        break;
    }

    readStringSafe("\nEnter the country: ", r.country, sizeof(r.country));
    r.phone = readIntSafe("Enter the phone number: ");
    r.amount = readDoubleSafe("Enter amount to deposit: $");

    while (1)
    {
        readStringSafe(
            "\nChoose the type of account:\n"
            "\t-> savings\n\t-> current\n\t-> fixed01 (1 year)\n"
            "\t-> fixed02 (2 years)\n\t-> fixed03 (3 years)\n\n\tYour choice: ",
            r.accountType, sizeof(r.accountType));

        if (strcmp(r.accountType, "savings") == 0 ||
            strcmp(r.accountType, "current") == 0 ||
            strcmp(r.accountType, "fixed01") == 0 ||
            strcmp(r.accountType, "fixed02") == 0 ||
            strcmp(r.accountType, "fixed03") == 0)
        {
            break;
        }
        printf("That's not one of the listed account types.\n");
    }

    r.id = nextRecordId();

    if (count >= MAX_RECORDS)
    {
        printf("\nError: the system cannot store any more accounts.\n");
        waitForEnter();
        return;
    }

    records[count] = r;
    count++;
    saveAllRecords(records, count);

    printf("\n✔ Account created successfully!\n");
    waitForEnter();
}

void listMyAccounts(struct User u)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    clearScreen();
    printf("\t\t====== All accounts for %s ======\n\n", u.name);

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (records[i].userId == u.id)
        {
            found = 1;
            printf("_____________________\n");
            printf("Account id:      %d\n", records[i].accountNbr);
            printf("Deposit date:    %02d/%02d/%04d\n",
                   records[i].deposit.month, records[i].deposit.day, records[i].deposit.year);
            printf("Country:         %s\n", records[i].country);
            printf("Phone number:    %d\n", records[i].phone);
            printf("Balance:         $%.2f\n", records[i].amount);
            printf("Account type:    %s\n", records[i].accountType);
        }
    }

    if (!found)
    {
        printf("You don't have any accounts yet.\n");
    }

    waitForEnter();
}

void showAccountDetails(struct User u)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    clearScreen();
    printf("\t\t====== Account details ======\n\n");
    int accountNbr = readIntSafe("Enter the account id you want to see: ");

    int index = findRecordIndex(records, count, u.id, accountNbr);
    if (index == -1)
    {
        printf("\n✖ No account with that id was found for your user.\n");
        waitForEnter();
        return;
    }

    struct Record *r = &records[index];
    printf("\n_____________________\n");
    printf("Account id:      %d\n", r->accountNbr);
    printf("Deposit date:    %02d/%02d/%04d\n", r->deposit.month, r->deposit.day, r->deposit.year);
    printf("Country:         %s\n", r->country);
    printf("Phone number:    %d\n", r->phone);
    printf("Balance:         $%.2f\n", r->amount);
    printf("Account type:    %s\n\n", r->accountType);

    if (!accountEarnsInterest(r->accountType))
    {
        printf("You will not get interests because the account is of type %s\n",
               r->accountType);
    }
    else
    {
        double interest = monthlyInterest(r->amount, r->accountType);
        printf("You will get $%.2f as interest on day %d of every month\n",
               interest, r->deposit.day);
    }

    waitForEnter();
}

void updateAccountInfo(struct User u)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    clearScreen();
    printf("\t\t====== Update account information ======\n\n");
    int accountNbr = readIntSafe("Enter the account id you want to change: ");

    int index = findRecordIndex(records, count, u.id, accountNbr);
    if (index == -1)
    {
        printf("\n✖ No account with that id was found for your user.\n");
        waitForEnter();
        return;
    }

    printf("\nWhich field do you want to update?\n");
    printf("\t[1]- Country (currently: %s)\n", records[index].country);
    printf("\t[2]- Phone number (currently: %d)\n", records[index].phone);
    int choice = readIntSafe("Your choice: ");

    if (choice == 1)
    {
        readStringSafe("New country: ", records[index].country, sizeof(records[index].country));
    }
    else if (choice == 2)
    {
        records[index].phone = readIntSafe("New phone number: ");
    }
    else
    {
        printf("\nOnly the country or the phone number can be updated.\n");
        waitForEnter();
        return;
    }

    saveAllRecords(records, count);
    printf("\n✔ Account updated successfully!\n");
    waitForEnter();
}
