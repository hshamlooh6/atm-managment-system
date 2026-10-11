#include "header.h"

void removeAccount(struct User u)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    clearScreen();
    printf("\t\t====== Remove an account ======\n\n");
    int accountNbr = readIntSafe("Enter the account id you want to remove: ");

    int index = findRecordIndex(records, count, u.id, accountNbr);
    if (index == -1)
    {
        printf("\n✖ No account with that id was found for your user.\n");
        waitForEnter();
        return;
    }

    printf("\nAre you sure you want to delete account %d (balance $%.2f)?\n",
           records[index].accountNbr, records[index].amount);
    char confirmation[8];
    readStringSafe("Type YES to confirm: ", confirmation, sizeof(confirmation));

    if (strcmp(confirmation, "YES") != 0)
    {
        printf("\nCancelled - nothing was deleted.\n");
        waitForEnter();
        return;
    }

    for (int i = index; i < count - 1; i++)
    {
        records[i] = records[i + 1];
    }
    count--;

    saveAllRecords(records, count);
    printf("\n✔ Account removed.\n");
    waitForEnter();
}

void transferOwnership(struct User u)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    clearScreen();
    printf("\t\t====== Transfer account ownership ======\n\n");
    int accountNbr = readIntSafe("Enter the account id you want to transfer: ");

    int index = findRecordIndex(records, count, u.id, accountNbr);
    if (index == -1)
    {
        printf("\n✖ No account with that id was found for your user.\n");
        waitForEnter();
        return;
    }

    char newOwnerName[NAME_LEN];
    readStringSafe("Enter the username to transfer this account to: ",
                    newOwnerName, sizeof(newOwnerName));

    if (strcmp(newOwnerName, u.name) == 0)
    {
        printf("\nYou already own this account.\n");
        waitForEnter();
        return;
    }

    struct User newOwner;
    if (!findUserByName(newOwnerName, &newOwner))
    {
        printf("\n✖ No user named \"%s\" exists.\n", newOwnerName);
        waitForEnter();
        return;
    }

    records[index].userId = newOwner.id;
    strncpy(records[index].name, newOwner.name, NAME_LEN - 1);
    records[index].name[NAME_LEN - 1] = '\0';

    saveAllRecords(records, count);

    printf("\n✔ Account %d transferred to %s.\n", accountNbr, newOwner.name);

    waitForEnter();
}
