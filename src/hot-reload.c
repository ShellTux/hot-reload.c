#include "math.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

const double pi = 3.141592654;

trig_func plug_msin = NULL;
trig_func plug_mcos = NULL;
trig_func plug_mtan = NULL;
trig_func plug_mcosh = NULL;
trig_func plug_msinh = NULL;

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
    *strchr(command, '\n') = '\0';

    // Check for exit command
    if (strcmp(command, "exit") == 0) {
      break;
    }

    if (strcmp(command, "reload") == 0) {
      const char *so_filename = "./target/debug/libmath.so";
      printf("Reloading %s...\n", so_filename);

      void *handle = dlopen(so_filename, RTLD_NOW);
      if (handle == NULL) {
        fprintf(stderr, "Failed to load %s: %s\n", so_filename, dlerror());
        continue;
      }

      plug_msin = (trig_func)dlsym(handle, "msin");
      plug_mcos = (trig_func)dlsym(handle, "mcos");
      plug_mtan = (trig_func)dlsym(handle, "mtan");
      plug_msinh = (trig_func)dlsym(handle, "msinh");
      plug_mcosh = (trig_func)dlsym(handle, "mcosh");

      continue;
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
      if (plug_msin == NULL) {
        fprintf(stderr, "sin function not loaded yet. reload\n");
        continue;
      }
      printf("sin(%fº) = sin(%f) = %f\n", angleDeg, angleRad, 
             plug_msin(angleRad));
    } else if (strcmp(func, "cos") == 0) {
      if (plug_mcos == NULL) {
        fprintf(stderr, "cos function not loaded yet. reload\n");
        continue;
      }
      printf("cos(%fº) = cos(%f) = %f\n", angleDeg, angleRad, 
             plug_mcos(angleRad));
    } else if (strcmp(func, "tan") == 0) {
      if (plug_mtan == NULL) {
        fprintf(stderr, "tan function not loaded yet. reload\n");
        continue;
      }
      printf("tan(%fº) = tan(%f) = %f\n", angleDeg, angleRad, 
             plug_mtan(angleRad));
    } else if (strcmp(func, "sinh") == 0) {
      printf("sinh(%fº) = sinh(%f) = %f\n", angleDeg, angleRad, 
             plug_msinh(angleRad));
    } else if (strcmp(func, "cosh") == 0) {
      printf("cosh(%fº) = cosh(%f) = %f\n", angleDeg, angleRad, 
             plug_mcosh(angleRad));
    } else {
      printf("Unknown function: %s. Please try again.\n", func);
    }
  }

  printf("Exiting REPL. Goodbye!\n");
  return 0;
}
