#include "header.h"

int loadAllUsers(struct User list[], int maxCount)
{
    FILE *fp = fopen(USERS_FILE, "r");
    if (fp == NULL)
    {
        return 0; 
    }

    int count = 0;
    while (count < maxCount &&
           fscanf(fp, "%d %49s %127s",
                  &list[count].id,
                  list[count].name,
                  list[count].password) == 3)
    {
        count++;
    }

    fclose(fp);
    return count;
}

void saveAllUsers(const struct User list[], int count)
{
    FILE *fp = fopen(USERS_FILE, "w");
    if (fp == NULL)
    {
        printf("Error: could not open %s for writing.\n", USERS_FILE);
        exit(1);
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %s\n", list[i].id, list[i].name, list[i].password);
    }

    fclose(fp);
}

int findUserByName(const char *name, struct User *out)
{
    struct User users[MAX_USERS];
    int count = loadAllUsers(users, MAX_USERS);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].name, name) == 0)
        {
            *out = users[i];
            return 1;
        }
    }
    return 0;
}

int findUserById(int id, struct User *out)
{
    struct User users[MAX_USERS];
    int count = loadAllUsers(users, MAX_USERS);

    for (int i = 0; i < count; i++)
    {
        if (users[i].id == id)
        {
            *out = users[i];
            return 1;
        }
    }
    return 0;
}

int userNameExists(const char *name)
{
    struct User dummy;
    return findUserByName(name, &dummy);
}

void appendUser(struct User u)
{
    struct User users[MAX_USERS];
    int count = loadAllUsers(users, MAX_USERS);

    if (count >= MAX_USERS)
    {
        printf("Error: the system is full and cannot register more users.\n");
        exit(1);
    }

    u.id = (count == 0) ? 0 : users[count - 1].id + 1;
    users[count] = u;
    count++;

    saveAllUsers(users, count);
}

int loadAllRecords(struct Record list[], int maxCount)
{
    FILE *fp = fopen(RECORDS_FILE, "r");
    if (fp == NULL)
    {
        return 0;
    }

    int count = 0;
    while (count < maxCount)
    {
        struct Record r;
        int fieldsRead = fscanf(fp, "%d %d %49s %d %d/%d/%d %99s %d %lf %9s",
                                 &r.id,
                                 &r.userId,
                                 r.name,
                                 &r.accountNbr,
                                 &r.deposit.month,
                                 &r.deposit.day,
                                 &r.deposit.year,
                                 r.country,
                                 &r.phone,
                                 &r.amount,
                                 r.accountType);

        if (fieldsRead == EOF)
        {
            break;
        }
        if (fieldsRead != 11)
        {
            int c;
            while ((c = fgetc(fp)) != '\n' && c != EOF)
            {

            }
            continue;
        }

        list[count] = r;
        count++;
    }

    fclose(fp);
    return count;
}

void saveAllRecords(const struct Record list[], int count)
{
    FILE *fp = fopen(RECORDS_FILE, "w");
    if (fp == NULL)
    {
        printf("Error: could not open %s for writing.\n", RECORDS_FILE);
        exit(1);
    }

    for (int i = 0; i < count; i++)
    {
        const struct Record *r = &list[i];
        fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                r->id,
                r->userId,
                r->name,
                r->accountNbr,
                r->deposit.month,
                r->deposit.day,
                r->deposit.year,
                r->country,
                r->phone,
                r->amount,
                r->accountType);
    }

    fclose(fp);
}

int findRecordIndex(const struct Record list[], int count, int userId, int accountNbr)
{
    for (int i = 0; i < count; i++)
    {
        if (list[i].userId == userId && list[i].accountNbr == accountNbr)
        {
            return i;
        }
    }
    return -1;
}

int nextRecordId(void)
{
    struct Record records[MAX_RECORDS];
    int count = loadAllRecords(records, MAX_RECORDS);

    int maxId = -1;
    for (int i = 0; i < count; i++)
    {
        if (records[i].id > maxId)
        {
            maxId = records[i].id;
        }
    }
    return maxId + 1;
}
