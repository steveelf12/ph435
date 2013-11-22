#include <stdio.h>
#include <stdlib.h>

const double pi = 52163./16604.;

struct complex { 
  int re;
  int im;
};
  
double power(double x, int j) {  
  int i;
  int x_0 = x;
  if ((j==0) && (x==0)) {
    printf("error: 0^0\n");
    exit(1);
  }
  if (j==0) {
    return 1;
  }
  else { 
    for (i=1; i<j; i++) {
      x = x*x_0;
    }
  }
  return x;
}

int factorial(int n) { 
  int product = n;
  if (n==0) {
    return 1;
  }
  else {
    while (n-1>0) {
      product = product * (n-1);
      n = n-1;
    }
  }
  return product;
}

double sin(double x) {
  double taylor_sum = 0;
  int i;
  for (i=0; i<50; i++) {
    taylor_sum = taylor_sum + power(-1,i)*power(x,(1+2*i))/factorial(1 + 2*i);
  }
  return taylor_sum;
}

int choose(int n, int k) {
  int n_choose_k = factorial(n) / (factorial(k)*(factorial(n-k)));
  return n_choose_k;
}

double laguerre_polynomial(double x, int l, int p) {
  int i;
  double sum = 0;
  for (i=0; i<=p; i++) {
    sum = sum + power(-1, i)*choose((p+l),(p-i))*(power(x,i)/factorial(i));
  }
  return sum;
}

int main() {
  printf("%f\n",sin(pi));
  return 0;
}