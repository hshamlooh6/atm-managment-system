#include <math.h>
#include <stdio.h>
#include "../src/header.h"

static int testsRun = 0;
static int testsFailed = 0;

static int nearlyEqual(double a, double b)
{
    return fabs(a - b) < 0.005;
}

static void expectDoubleEqual(const char *testName, double expected, double actual)
{
    testsRun++;
    if (!nearlyEqual(expected, actual))
    {
        testsFailed++;
        printf("FAIL: %s (expected %.2f, got %.2f)\n", testName, expected, actual);
    }
    else
    {
        printf("PASS: %s\n", testName);
    }
}

static void expectIntEqual(const char *testName, int expected, int actual)
{
    testsRun++;
    if (expected != actual)
    {
        testsFailed++;
        printf("FAIL: %s (expected %d, got %d)\n", testName, expected, actual);
    }
    else
    {
        printf("PASS: %s\n", testName);
    }
}

int main(void)
{
    expectDoubleEqual("savings monthly interest matches spec example",
                       5.97, monthlyInterest(1023.20, "savings"));

    expectDoubleEqual("savings rate is 7%", 0.07, interestRateForType("savings"));
    expectDoubleEqual("fixed01 rate is 4%", 0.04, interestRateForType("fixed01"));
    expectDoubleEqual("fixed02 rate is 5%", 0.05, interestRateForType("fixed02"));
    expectDoubleEqual("fixed03 rate is 8%", 0.08, interestRateForType("fixed03"));
    expectDoubleEqual("current rate is 0%", 0.00, interestRateForType("current"));

    expectIntEqual("savings earns interest", 1, accountEarnsInterest("savings"));
    expectIntEqual("current earns no interest", 0, accountEarnsInterest("current"));
    expectIntEqual("fixed03 earns interest", 1, accountEarnsInterest("fixed03"));

    expectIntEqual("current allows transactions", 1, accountAllowsTransactions("current"));
    expectIntEqual("savings allows transactions", 1, accountAllowsTransactions("savings"));
    expectIntEqual("fixed01 blocks transactions", 0, accountAllowsTransactions("fixed01"));
    expectIntEqual("fixed02 blocks transactions", 0, accountAllowsTransactions("fixed02"));
    expectIntEqual("fixed03 blocks transactions", 0, accountAllowsTransactions("fixed03"));

    printf("\n%d/%d tests passed.\n", testsRun - testsFailed, testsRun);
    return testsFailed == 0 ? 0 : 1;
}
