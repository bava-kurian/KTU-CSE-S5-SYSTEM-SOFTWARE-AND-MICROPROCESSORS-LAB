#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int start, optab_size = 0, symtab_size = 0, text_size = 0, i, length, flag = 0, tex_len = 0;
char locctr[10], label[10], opcode[10], operand[10], ob_op[10], ob_add[10], obj_code[20];
FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;

struct optab {
    char opcode[10];
    char mnemonic[10];
} op[30];

struct symtab {
    char address[10];
    char label[10];
    int flag;
} sym[30];

struct text_record {
    char obj[10];
    char address[10];
} TR[20];

int main() {
    // Open all files
    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "r");
    fp4 = fopen("output.txt", "w");
    fp5 = fopen("object.txt", "w");
    fp6 = fopen("length.txt", "r");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL || fp5 == NULL || fp6 == NULL) {
        printf("Error opening one or more files.\n");
        return 1;
    }

    // Load optab
    while (fscanf(fp2, "%s %s", op[optab_size].opcode, op[optab_size].mnemonic) != EOF) {
        optab_size++;
    }
    fclose(fp2);

    // Load symtab
    while (fscanf(fp3, "%s %s %d", sym[symtab_size].address, sym[symtab_size].label, &sym[symtab_size].flag) != EOF) {
        symtab_size++;
    }
    fclose(fp3);

    // Read program length
    fscanf(fp6, "%x", &length);
    fclose(fp6);

    // Read initial line (START)
    fscanf(fp1, "%s %s %x", label, opcode, &start);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp4, "\t%s\t%s\t%x", label, opcode, start);
        printf("\t%s\t%s\t%x\n", label, opcode, start);
        fprintf(fp5, "H^%-6s^%06x^%06x", label, start, length);
        printf("H^%-6s^%06x^%06x\n", label, start, length);
    }

    // Read first instruction after START
    fscanf(fp1, "%s %s %s %s", locctr, label, opcode, operand);

    while (strcmp(opcode, "END") != 0) {
        strcpy(ob_op, "");  // Clear object code
        flag = 0;

        // Search opcode in optab
        for (i = 0; i < optab_size; i++) {
            if (strcmp(op[i].opcode, opcode) == 0) {
                strcpy(ob_op, op[i].mnemonic);
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            // Search operand in symtab
            strcpy(ob_add, "");
            for (i = 0; i < symtab_size; i++) {
                if (strcmp(sym[i].label, operand) == 0) {
                    strcpy(ob_add, sym[i].address);

                    break;
                }
            }
            strcat(ob_op, ob_add);
            strcpy(TR[text_size].obj, ob_op);
            strcpy(TR[text_size].address, locctr);
            tex_len += strlen(ob_op) / 2;
            text_size++;
        } else {
            if (strcmp(opcode, "WORD") == 0) {
                sprintf(ob_op, "%06X", atoi(operand));
                strcpy(TR[text_size].obj, ob_op);
                strcpy(TR[text_size].address, locctr);
                tex_len += 3;
                text_size++;
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    for (i = 2; operand[i] != '\''; i++) {
                        sprintf(ob_op + strlen(ob_op), "%02X", operand[i]);
                    }
                } else if (operand[0] == 'X') {
                    strncpy(ob_op, operand + 2, strlen(operand) - 3);
                }
                strcpy(TR[text_size].obj, ob_op);
                strcpy(TR[text_size].address, locctr);
                tex_len += strlen(ob_op) / 2;
                text_size++;
            }
        }

        // Write to output file and print to terminal
        fprintf(fp4, "\n%s\t%s\t%s\t%s\t%s", locctr, label, opcode, operand, ob_op);
        printf("%s\t%s\t%s\t%s\t%s\n", locctr, label, opcode, operand, ob_op);

        // Read next line
        fscanf(fp1, "%s %s %s %s", locctr, label, opcode, operand);
    }

    // Write text record to object file
    fprintf(fp5, "\nT^%06s^%02X", TR[0].address, tex_len);
    printf("\nT^%06s^%02X", TR[0].address, tex_len);
    for (i = 0; i < text_size; i++) {
        fprintf(fp5, "^%s", TR[i].obj);
        printf("^%s", TR[i].obj);
    }

    // Write end record
    fprintf(fp5, "\nE^%06X", start);
    printf("\nE^%06X\n", start);

    // Final line in the output file
    fprintf(fp4, "\n%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    fclose(fp1);
    fclose(fp4);
    fclose(fp5);

    return 0;
}
