#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printMenu() {
  printf("Menu:\n");
  printf("1. Array\n");
  printf("2. Single Linked List\n");
  printf("3. Double Linked List\n");
}

int main() {
  bool isRunning = true;
  while (isRunning) {
    printMenu();
    int a;
    scanf("%d", &a);
    switch (a) {
        case 1:
            char command[] = "./array/driver";

            // Execute the executable with arguments
            int result = system(command);

            // Check if the command was executed successfully
            if (result == -1) {
                perror("Error executing the executable");
                return 1;
            }

            printf("Executable executed successfully.\n");
                printf("Array selected\n");
                break;

        case 2:
            char command2[] = "./single/driver";

            // Execute the executable with arguments
            int result2 = system(command2);

            // Check if the command was executed successfully
            if (result2 == -1) {
                perror("Error executing the executable");
                return 1;
            }

            printf("Executable executed successfully.\n");
            break;
        case 3:
            char command3[] = "./double/driver";

            // Execute the executable with arguments
            int result3 = system(command3);

            // Check if the command was executed successfully
            if (result3 == -1) {
                perror("Error executing the executable");
                return 1;
            }

            printf("Executable executed successfully.\n");
            // break;
            printf("Double Linked List selected\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
  return 0;
}
