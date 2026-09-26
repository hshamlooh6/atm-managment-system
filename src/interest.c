#include "header.h"

double interestRateForType(const char *accountType)
{
    if (strcmp(accountType, "savings") == 0)
    {
        return 0.07;
    }
    if (strcmp(accountType, "fixed01") == 0)
    {
        return 0.04;
    }
    if (strcmp(accountType, "fixed02") == 0)
    {
        return 0.05;
    }
    if (strcmp(accountType, "fixed03") == 0)
    {
        return 0.08;
    }
    return 0.0;
}

int accountEarnsInterest(const char *accountType)
{
    return interestRateForType(accountType) > 0.0;
}

double monthlyInterest(double balance, const char *accountType)
{
    double annualRate = interestRateForType(accountType);
    return (balance * annualRate) / 12.0;
}

int accountAllowsTransactions(const char *accountType)
{
    return strcmp(accountType, "current") == 0 ||
           strcmp(accountType, "savings") == 0;
}
