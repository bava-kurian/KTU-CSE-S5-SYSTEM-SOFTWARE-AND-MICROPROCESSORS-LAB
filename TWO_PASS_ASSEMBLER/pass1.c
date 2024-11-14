#include<stdio.h>
#include<string.h>
#include<conio.h>

FILE *fp1,*fp2,*fp3,*fp4,*fp5;
int locctr,i,n=-1,j=0,start,optab_size=-1,symtab_size=-1,optab_mnemonic,flag,len;
char label[10],opcode[10],operand[10],temp[10],optab_code[10];

struct optab{
    char opcode[10];
    int mnemonic;
}op[30];
struct symatb{
    int address;
    char label[10];
    int flag;
}sym[30];
void main(){
    fp1=fopen("input.txt","r");
    fp2=fopen("optab.txt","r");
    fp3=fopen("intermediate.txt","w");
    fp4=fopen("symtab.txt","w");
    fp5=fopen("length.txt","w");
    optab_size++;
    //optab reading
    while (fscanf(fp2, "%s %x", op[optab_size].opcode, &op[optab_size].mnemonic) != EOF) {
            printf("%s\n",op[optab_size].opcode);
        optab_size++;

    }
    fclose(fp2);
    fscanf(fp1,"%s %s %x",label,opcode,&start);
    //starting addres to locctr
    if(strcmp(opcode,"START")==0){
        locctr=start;
        fprintf(fp3,"\t%s\t%s\t%x",label,opcode,locctr);
    }else{
        locctr=0;
    }
    fscanf(fp1,"%s%s%s",label,opcode,operand);
    while(strcmp(opcode,"END")!=0){
        fprintf(fp3,"\n%X\t%s\t%s\t%s",locctr,label,opcode,operand);
        if(strcmp(label,"**")!=0){
            for(i=0;i<=symtab_size;i++){
                if(strcmp(sym[i].label,label)==0){
                    symtab_size++;
                    strcpy(sym[symtab_size].label,label);
                    sym[symtab_size].address=locctr;
                    sym[symtab_size].flag=1;
                    fprintf(fp4,"\n%x\t%s\t%d",sym[symtab_size].address,sym[symtab_size].label,sym[symtab_size].flag);
                    exit(0);
                }
            }
            symtab_size++;
            strcpy(sym[symtab_size].label,label);
            sym[symtab_size].address=locctr;
            sym[symtab_size].flag=0;
            fprintf(fp4,"\n%x\t%s\t%d",sym[symtab_size].address,sym[symtab_size].label,sym[symtab_size].flag);
        }
        flag=0;
        for(j=0;j<=optab_size;j++){
            if(strcmp(op[j].opcode,opcode)==0){
                locctr+=3;
                flag=1;
            }
        }
        if(flag==0){
            if(strcmp(opcode,"WORD")==0){
                locctr+=3;
            }
            else if(strcmp(opcode,"RESW")==0){
                locctr+=(3*(atoi(operand)));
            }
            else if(strcmp(opcode,"BYTE")==0){
                len=strlen(operand);
                len=len-3;
                locctr+=len;
            }
            else if(strcmp(opcode,"RESB")==0){
                locctr+=(atoi(operand));
            }else{
                printf("Mo such operand in optab and not 'WORD' 'RESB' 'RESW' 'BYTE' \n");
                exit(0);
            }
        }
        fscanf(fp1,"%s%s%s",label,opcode,operand);
    }
    fprintf(fp3,"\n%X\t%s\t%s\t%s",locctr,label,opcode,operand);
    printf("length=>%X\n",locctr-start);
    fprintf(fp5,"%X",locctr-start);
    fclose(fp1);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}
