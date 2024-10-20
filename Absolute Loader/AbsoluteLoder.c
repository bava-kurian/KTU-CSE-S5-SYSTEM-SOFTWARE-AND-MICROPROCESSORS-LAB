#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *fp;
    int i, staddr1;
    char name[10], line[50], name1[10], staddr[10];

    printf("Enter Program Name: ");
    scanf("%s", name);
    fp = fopen("object.txt", "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fscanf(fp, "%s", line);
    strncpy(name1, line + 2, 6);
    name1[6] = '\0';
    printf("\nName from Obj: %s\n", name1);

    if (strcmp(name, name1) == 0) {
        do {
            fscanf(fp, "%s", line);
            if (line[0] == 'T') {
                strncpy(staddr, line + 2, 6);
                staddr[6] = '\0';
                staddr1 = (int)strtol(staddr, NULL, 16);
                i = 12;

                while (line[i] != '\0') {
                    // Skip special characters
                    if (line[i] == '^' || line[i] == '$') {
                        i++;
                        continue;
                    }

                    // Break if the end of the object code is reached
                    if (line[i] == '\0') {
                        break;
                    }

                    // Prepare to store the object code
                    char obj_code[9] = "xxxxxxxx"; // Initialize with 'x'
                    int j = 0;

                    // Read the next bytes
                    while (j < 4 && line[i] != '\0' && line[i] != '$') {
                        if (line[i] != '^') {
                            if (line[i + 1] != '\0' && line[i + 1] != '$') {
                                obj_code[j * 2] = line[i];
                                obj_code[j * 2 + 1] = line[i + 1];
                                j++;
                                i += 2; // Move to the next byte (two characters)
                            } else {
                                break; // Break if the next character is missing
                            }
                        } else {
                            i++; // Skip '^'
                        }
                    }

                    // Fill remaining spaces with 'x'
                    for (; j < 4; j++) {
                        obj_code[j * 2] = 'x';
                        obj_code[j * 2 + 1] = 'x';
                    }

                    // Output the address and the concatenated object code
                    printf("%06X   %s\n", staddr1, obj_code);
                    staddr1 += 4; // Increment address by 4
                }
            } else if (line[0] == 'E') {
                break; // Exit the loop if the end of the program is reached
            }
        } while (!feof(fp));
    }

    fclose(fp);
}
