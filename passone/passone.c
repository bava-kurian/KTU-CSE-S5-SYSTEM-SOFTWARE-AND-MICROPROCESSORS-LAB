//pass1 ss lab

#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

char opcode[10],operand[10],label[10],ch,t1[20],t2[20],t3[10];
int locctr,start,len,s=-1,o=-1,i,j=0,flag,size=0,opd;

FILE *fp1,*fp2,*fp3,*fp4,*fp5;

struct SYMTAB{
    char label[10];
    int addr;
}ST[30];

struct OPTAB{
    char opcode[10],hexcode[10];
}OT[30];
void read_OPTAB(){
    while(1){
        o++;
        fscanf(fp2,"%s%s",OT[o].opcode,OT[o].hexcode);
        if(getc(fp2)==EOF)
            break;
    }
}




void read_line(){
    strcpy(t1,"");
    strcpy(t2,"");
    strcpy(t3,"");
    fscanf(fp1,"%s",t1);
    if(getc(fp1)!='\n'){
        fscanf(fp1,"%s",t2);
        if(getc(fp1)!='\n'){
            fscanf(fp1,"%s",t3);
        }
    }
    if(strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")!=0){
        strcpy(label,t1);
        strcpy(opcode,t2);
        strcpy(operand,t3);
    }else if(strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")==0){
        strcpy(label,"");
        strcpy(opcode,t1);
        strcpy(operand,t2);

    }else if(strcmp(t1,"")!=0 && strcmp(t2,"")==0 && strcmp(t3,"")==0){
        strcpy(label,"");
        strcpy(opcode,t1);
        strcpy(operand,"");
    }
}
int main(){
    fp1=fopen("input.txt","r");
    fp2=fopen("optab.txt","r");
    read_OPTAB();
    fp3=fopen("symtab.txt","w");
    fp4=fopen("intermed.txt","w");
    fp5=fopen("length.txt","w");

    fscanf(fp1,"%s%s%x",label,opcode,&opd);

    if(strcmp(opcode,"START")==0){
        start=opd;
        locctr=start;
        fprintf(fp4,"\t%s\t%s\t%x\n",label,opcode,opd);
        read_line();
    }
    else{
        locctr=0;
    }
    while(strcmp(opcode,"END")!=0){
        fprintf(fp4,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(label,"")!=0){
            for(i=0;i<=s;i++){
                if(strcmp(ST[i].label,label)==0){
                    printf("Error");
                    exit(0);
                }
            }
            s++;
            strcpy(ST[s].label,label);
            ST[s].addr=locctr;
        }
        flag=0;
        for(i=0;i<=o;i++){
            if(strcmp(opcode,OT[i].opcode)==0){
                locctr+=3;
                size=size+3;
                flag=1;
                break;
            }
        }
        if(flag==0){
            if(strcmp(opcode,"WORD")==0){
                locctr+=3;
                size=size+3;
            }
            else if(strcmp(opcode,"RESW")==0){
                locctr+=(3*(atoi(operand)));

            }
            else if(strcmp(opcode,"RESB")==0){
                locctr+=(atoi(operand));
            }
            else if(strcmp(opcode,"BYTE")==0){
                len=strlen(operand);
                if(operand[0]=='C' || operand[0]=='c'){
                    len=len-3;
                }
                else{
                    len=(len-3)/2;
                }
                locctr+=len;
                size=size+len;
            }
        }
        read_line();
    }
    fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);//for last instruction
    for(i=0;i<=s;i++){
        fprintf(fp3,"%s\t%x\n",ST[i].label,ST[i].addr);
    }
    fprintf(fp5,"%x\n%x",locctr-size,size);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    return 0;
}
