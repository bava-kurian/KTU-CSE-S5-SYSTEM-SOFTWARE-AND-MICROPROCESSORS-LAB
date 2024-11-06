#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int start, optab_size = 0, symtab_size = 0,text_size=0, i,length,flag=0,tex_len;
char locctr[10], label[10], opcode[10], operand[10], ob_op[10], ob_add[10], obj_code[20];
FILE *fp1, *fp2, *fp3,*fp4,*fp5,*fp6;

struct optab
{
    char opcode[10];
    char mnemonic[10];  // Use an array to store strings
} op[30];

struct symtab
{
    char address[10];   // Use an array to store string addresses
    char label[10];
    int flag;
} sym[30];

struct text_rex
{
    char obj[10];
    char address[10];
} TR[20];
int main()
{
    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "r");
    fp4=fopen("output.txt","w");
    fp5=fopen("object.txt","w");
    fp6=fopen("length.txt","r");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
    {
        printf("Error opening one or more files.\n");
        return 1;
    }

    // Load optab
    while (fscanf(fp2, "%s %s", op[optab_size].opcode, op[optab_size].mnemonic) != EOF)
    {
        optab_size++;
    }
    fclose(fp2);  // Close after reading

    // Load symtab
    while (fscanf(fp3, "%s %s %d", sym[symtab_size].address, sym[symtab_size].label, &sym[symtab_size].flag) != EOF)
    {
        symtab_size++;
    }
    fclose(fp3);  // Close after reading
    fscanf(fp6,"%x",&length);
    // Read initial start address from intermediate file
    fscanf(fp1, "%s %s %x", label, opcode, &start);
    if(strcmp(opcode,"START")==0)
    {
        fprintf(fp4,"\t%s\t%s\t%x",label,opcode,start);
        fprintf(fp5,"H^%-6s^%06x^%06x",label,start,length);
    }
    fscanf(fp1, "%s %s %s %s", locctr, label, opcode, operand);
    while(strcmp(opcode,"END")!=0)
    {
        // Lookup opcode in optab and operand in symtab
        strcpy(ob_op, "");  // Initialize empty
        flag=0;
        for (i = 0; i < optab_size; i++)
        {
            if (strcmp(op[i].opcode, opcode) == 0)
            {
                strcpy(ob_op, op[i].mnemonic);
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            strcpy(ob_add, "");  // Initialize empty
            for (i = 0; i < symtab_size; i++)
            {
                if (strcmp(sym[i].label, operand) == 0)
                {
                    strcpy(ob_add, sym[i].address);
                    break;
                }
            }

            // Concatenate opcode and address
            strcat(ob_op, ob_add);
            strcpy(TR[text_size].obj,ob_op);
            strcpy(TR[text_size].address,locctr);
            tex_len+=(strlen(ob_op))/2;
            text_size++;
        }
        else
        {
            if(strcmp(opcode,"WORD")==0)
            {
                int word_value = atoi(operand);
                sprintf(ob_op, "%06X", word_value);
                strcpy(TR[text_size].obj,ob_op);
                strcpy(TR[text_size].address,locctr);
                tex_len+=(strlen(ob_op))/2;
                text_size++;
            }
            else if(strcmp(opcode,"BYTE")==0)
            {
                if(operand[0]=='C')
                {
                    for(i=2; operand[i]!='\''; i++)
                    {
                        sprintf(ob_op+strlen(ob_op),"%02X",operand[i]);
                    }
                }
                else if(operand[0]=='X')
                {
                    strncpy(ob_op,operand+2,strlen(operand)-3);
                }
                strcpy(TR[text_size].obj,ob_op);
                strcpy(TR[text_size].address,locctr);
                tex_len+=(strlen(ob_op))/2;
                text_size++;
            }

        }
        // Print final object code line
        fprintf(fp4,"\n%s\t%s\t%s\t%s\t%s", locctr, label, opcode, operand, ob_op);
        fscanf(fp1, "%s %s %s %s", locctr, label, opcode, operand);
    }
    fprintf(fp5,"\nT^%06s^%x",TR[0].address,tex_len);
    for(i=0; i<text_size; i++)
    {
        fprintf(fp5,"^%s",TR[i]);
    }
    fprintf(fp5,"\nE^%06X",start);
    fprintf(fp4,"\n%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    fclose(fp1);  // Close input file
    return 0;
}
