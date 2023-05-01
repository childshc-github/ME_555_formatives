// header files
#include <stdlib.h>
#include <stdio.h>

// info struct
struct _retire_info_t {
    int months;
    // # of months applicable
    double contribution;
    // how many dollars contributed (spent = neg)
    double rate_of_return;
    // MONTHLY ror (after inflation)
};

// renaming struct
typedef struct _retire_info_t retire_info_t;

// compute retirement balance CHANGE
double balance(double num1, double num2, double num3) {
    // num1 = balance, num2 = ror, num3 = contribution
    // ((balance * ror) + contribution
    double updated_balance = (num1 * num2) + num3;
    return updated_balance;
}

// print update
int monthly_update(int num1, int num2, double num3) {
    // num1 = age, num2 = month, num3 = balance
    printf("Age %3d month %2d you have $%.2lf\n", (num1 / 12), num2, num3);

    return 0;
}

// retirement function
void retirement(int startAge, // in months
                double initial, // initial savings
                retire_info_t working, // work info
                retire_info_t retired) { // retired info

    
    // work years
    int startMonth = startAge % 12;
    monthly_update(startAge, startMonth, initial);
    startAge++;
    startMonth++;
    working.months--;

    int counter = 0;

    for (int n = 0; n <= working.months; n++) {
        initial += balance(initial, working.rate_of_return, working.contribution);
        monthly_update((startAge + n), (counter + startMonth), initial);
        counter++;
        if ((counter + startMonth) == 12) {
            counter = 0;
            startMonth = 0;
        }
    }

    // retirement years start at age 68 month 1

    // retirement years
    startAge += working.months;
    startMonth = startAge % 12;
    retired.months = retired.months - 2;

    for (int n = 0; n <= retired.months; n++) {
        initial += balance(initial, retired.rate_of_return, retired.contribution);
        monthly_update((startAge + n + 1), (counter + startMonth), initial);
        counter++;
        if ((counter + startMonth) == 12) {
            counter = 0;
            startMonth = 0;
        }
    }
}

// main info
int main(void) {
    //working info
    retire_info_t working;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = (0.045/12);

    // retired info
    retire_info_t retired;
    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = (0.01/12);

    // prints and calculations
    retirement(327, 21345, working, retired);

    return 0;
}
