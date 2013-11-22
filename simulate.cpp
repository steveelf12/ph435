#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// goal: plug in initial beam profile, solve wave equation numerically. print the data. 
// to do:
// - double check beam profile against a mathematica plot.

//basic functions:

double power(double x, int j) {
  int i;
  int x_0 = x;
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

//complex numbers:

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
complex expz(double x) { //takes a theta and returns e^(i*theta) (using euler's formula)
  complex expz;
  expz.re = cos(x);
  expz.im = sin(x);
  return expz;
}

int main() {
  complex I;
  I.re = 0;
  I.im = 1;

  //establish 3d grid:
  double dx = .1; //scale?

  int Nx = 40;
  int Ny = 40;
  int Nz = 240;

  double* beam_profile = new double[Nx*Ny*Nz]; //the non-time dependent function u(r) from the paper.
  complex* E_phasor = new complex[Nx*Ny*Nz]; //complex valued electric field strength
  int l = 4;
  int p = 1;

  double w = 20*dx; //beam waist?

  int i, j, k;
  double x, y, z;

  for (i=0; i<Nx; i++) {
    for (j=0; j<Ny; j++) {
      for (k=0; k<Nz; k++) {
	x = i*dx;
	y = j*dx;
	z = k*dx;
	beam_profile[k*Nx*Ny + j*Nx + i] = power(-1,p)*power((sqrt(2)*(x*x + y*y)/(w*w)),l)*exp(-(x*x + y*y)/(w*w))*laguerre_polynomial(2*(x*x + y*y)/(w*w),l,p);
	E_phasor[k*Nx*Ny + j*Nx + i] = beam_profile[k*Nx*Ny + j*Nx + i]*expz(l*atan2(y,x));
      }
    }
  }

  delete[] beam_profile;
  delete[] E_phasor;
  return 0;
}
