#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

struct retire_start_tag {
  int startAge;
  double initial;
};
typedef struct retire_start_tag retire_start_t;

retire_start_t compute_balance(int startAge, double initial, retire_info_t status) {
  int age_in_months = startAge;
  double balance = initial;
  retire_start_t retire_start;
  retire_start.startAge = age_in_months;
  retire_start.initial = balance;
  if (status.months < 0) {
    printf("Error! Months cannot be negtive!");
  }
  else {
    if (status.months == 0) {
      printf(
          "Age %3d month %2d you have $%.2lf\n", age_in_months / 12, age_in_months % 12, balance);
    }
    else {
      for (int i = 1; i <= status.months; i++) {
        printf(
            "Age %3d month %2d you have $%.2lf\n", age_in_months / 12, age_in_months % 12, balance);
        age_in_months += 1;
        balance = balance + balance * status.rate_of_return + status.contribution;
      }
      retire_start.startAge = age_in_months;
      retire_start.initial = balance;
    }
  }
  return retire_start;
}

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  retire_start_t retire_start = compute_balance(startAge, initial, working);
  startAge = retire_start.startAge;
  initial = retire_start.initial;
  compute_balance(startAge, initial, retired);
}

int main(void) {
  int Age = 327;
  double savings = 21345;
  retire_info_t working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info_t retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(Age, savings, working, retired);
  return 0;
}
