#include "math.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

const double pi = 3.141592654;

int main() {
  char command[1024];

  printf("Simple REPL for Trigonometric and Hyperbolic Functions\n");
  printf("Available commands: sin, cos, tan, sinh, cosh, exit\n");

  while (1) {
    printf("Enter command (sin, cos, tan, sinh, cosh) followed by angle in "
           "radians: ");
    fflush(stdout);

    const ssize_t bytes_read = read(STDIN_FILENO, command, sizeof(command));
    if (bytes_read == 0) {
      printf("\n");
      break;
    }

    // Check for exit command
    if (strcmp(command, "exit") == 0) {
      break;
    }

    // Parse the command and angle
    char func[10];
    double angleDeg;
    if (sscanf(command, "%9s %lf", func, &angleDeg) != 2) {
      printf("Invalid input. Please try again.\n");
      continue;
    }

    const double angleRad = angleDeg * pi / 180;

    // Evaluate the function based on user input
    if (strcmp(func, "sin") == 0) {
      printf("sin(%fº) = sin(%f) = %f\n", angleDeg, angleRad, msin(angleRad));
    } else if (strcmp(func, "cos") == 0) {
      printf("cos(%fº) = cos(%f) = %f\n", angleDeg, angleRad, mcos(angleRad));
    } else if (strcmp(func, "tan") == 0) {
      printf("tan(%fº) = tan(%f) = %f\n", angleDeg, angleRad, mtan(angleRad));
    } else if (strcmp(func, "sinh") == 0) {
      // printf("sinh(%fº) = sinh(%f) = %f\n", angleDeg, angleRad,  angleRad));
    } else if (strcmp(func, "cosh") == 0) {
      // printf("cosh(%fº) = cosh(%f) = %f\n", angleDeg, angleRad,  angleRad));
    } else {
      printf("Unknown function: %s. Please try again.\n", func);
    }
  }

  printf("Exiting REPL. Goodbye!\n");
  return 0;
}
