#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* basic functions */

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

/* complex numbers and operators */

class complex {
public:
  double re;
  double im;
};

//defining addition
complex operator +(complex z1, complex z2) {
  complex z0;
  z0.re = z1.re + z2.re;
  z0.im = z1.im + z2.im;
  return z0;
}
complex operator +(complex z, double x) {
  complex z0;
  z0.re = z.re + x;
  z0.im = z.im;
  return z0;
}

complex operator +(double x, complex z) {
  return z+x;
}

//defining multiplication
complex operator *(complex z1, double x) {
  complex z0;
  z0.re = x*z1.re;
  z0.im = x*z1.im;
  return z0;
}

complex operator *(double x, complex z) {
  return z*x;
}

//exponential tools
double mod(complex z) {
  double modz = sqrt(z.re*z.re + z.im*z.im);
  return modz;
}
double phase(complex z) {
  double phasez = atan2(z.im, z.re);
  return phasez;
}
complex expz(complex z) {
  complex expz;
  expz.re = mod(z)*cos(phase(z));
  expz.im = mod(z)*sin(phase(z));
  return expz;
}


int main() {
  complex I;
  I.re = 0;
  I.im = 1;
  return 0;
}
