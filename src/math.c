#include <stddef.h>
#include <stdio.h>

size_t factorial(const size_t number) {
  size_t result = 1;

  for (size_t n = 2; n < number; ++n) {
    result *= n;
  }

  return result;
}

double msin(const double angleRad) {
  double term = angleRad;         // First term
  double sum = term;              // Initialize sum
  for (int n = 1; n <= 10; n++) { // 10 terms
    term *=
        -angleRad * angleRad / ((2 * n) * (2 * n + 1)); // Calculate next term
    sum += term;                                        // Add term to sum
  }
  return sum;
}

double mcos(const double angleRad) {
  double term = 1;                // First term
  double sum = term;              // Initialize sum
  for (int n = 1; n <= 10; n++) { // 10 terms
    // printf("cos term %d = %f\n", n, term);
    term *=
        -angleRad * angleRad / ((2 * n - 1) * (2 * n)); // Calculate next term
    sum += term;                                        // Add term to sum
  }
  return sum;
}

double mtan(const double angleRad) { return msin(angleRad) / mcos(angleRad); }

double mcosh(const double angleRad) {
  double term = 1;                // First term
  double sum = term;              // Initialize sum
  for (int n = 1; n <= 10; n++) { // 10 terms
    term *=
        angleRad * angleRad / ((2 * n - 1) * (2 * n)); // Calculate next term
    sum += term;                                       // Add term to sum
  }
  return sum;
}

double msinh(const double angleRad) {
  double term = angleRad;         // First term
  double sum = term;              // Initialize sum
  for (int n = 1; n <= 10; n++) { // 10 terms
    term *=
        angleRad * angleRad / ((2 * n) * (2 * n + 1)); // Calculate next term
    sum += term;                                       // Add term to sum
  }
  return sum;
}
