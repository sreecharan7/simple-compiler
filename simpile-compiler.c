#include<stdio.h>
#include<string.h>
#include <stdbool.h>

char varname[100][20];
int datastore[100];
int varcount=0;
char line[20][20];
int m_temp=0;
char repeatcode[1000][20][20];

void lineput();
int checkvariable(char arr[]);
int checknumber(char arr[]);
int checkarthematic(char arr[]);
int variableassign();
int checkcomparters(char arr[]);
bool condtionchek(int v1,int v2,int c);
int repeat(int *cur);
int whilevaiableexrator(int * a ,int *b ,int *c);
int main_core_runner();

int main(){

    main_core_runner();
    
    return 0;
}

int main_core_runner(){
    while(1){
        //taking line input untill ;
        lineput();
        
        // printing line
        // for(int i=0;i<temp-1;i++)printf("%s\n",line[i]);
        
        //checking  multiple ; 
        if(m_temp==1)continue;

        //checking loop
        if(!strcmp("while",line[0])){
            // printf("loop started\n");
            int var1,var2,comp;
            whilevaiableexrator(&var1,&var2,&comp);
            int numrepeatlength=0;
            int count=0; //to track the number of loops 
            // untill the no of while macthes the endwhile the loop goes on
            while(1){
                lineput();
                if(!strcmp("endwhile",line[0])){
                    if(count==0)break;
                    count--;
                }
                if(!strcmp("while",line[0])){count++;}
                for(int i=0;i<m_temp;i++)strcpy(repeatcode[numrepeatlength][i],line[i]);
                numrepeatlength++;
            }
            // printf("taken input\n");
            // for(int x=0;x<=numrepeatlength;x++){
            //     printf("%d : ",x);
            //     for(int i=0;i<20;i++)printf("%s ",repeatcode[x][i]);printf("\n");
            // }
            while(condtionchek(var1,var2,comp)){
                for(int x=0;x<numrepeatlength;x++){
                    for(int i=0;i<20;i++)strcpy(line[i],repeatcode[x][i]);
                    // for(int i=0;i<20;i++)printf("%s ",line[i]);
                    // printf("\n");
                    if(!strcmp("while",line[0])){
                        if(repeat(&x)==1)return 1;
                        // x=x-1;
                        // printf("ind  at : %d \n",x);
                    }else{
                        // printf("%d %d at x\n",datastore[var1],datastore[var2]);
                        if(variableassign()==1)return 1;
                    }
                }
                // printf("%d %d\n",datastore[var1],datastore[var2]);
            }
            // printf("loop ended\n");
        }else{
            if(variableassign()==1)return 1;
        }

    }
}


int repeat(int *cur){
    int var1,var2,comp;
    whilevaiableexrator(&var1,&var2,&comp);
    int temp=*cur+1;int last=0;
    // printf("came again loop at %d\n",temp);
    while(condtionchek(var1,var2,comp)){
        while(1){
            for(int i=0;i<20;i++)strcpy(line[i],repeatcode[temp][i]);
            // for(int i=0;i<20;i++)printf("%s ",line[i]);
            // printf("\n");
            if(!strcmp("endwhile",line[0])){
                last=temp;
                temp=*cur+1;
                break;
            }
            if(!strcmp("while",line[0])){
                // printf("calling again loop\n");
                if(repeat(&temp)==1)return 1;
                // printf("came at index  %d \n",temp);
            }else{
                if(variableassign()==1)return 1;
            }
            temp++;
        }
    }
    *cur=last;
}

int whilevaiableexrator(int * a ,int *b ,int *c){
    int var1=checkvariable(line[1]);
    if(var1==-999){
        int temp=checknumber(line[1]);
        if(temp!=-999){
            datastore[varcount]=temp;
            var1=varcount;
            varcount++;
        }
        else {printf("Variable not found (%s)",line[1]);return 1;}
    }
    // printf("came1");
    int comp=checkcomparters(line[2]);
    if(comp==-1){printf("comparator not found (%s)",line[2]);return 1;}
    int var2=checkvariable(line[3]);
    if(var1==-999){
        int temp=checknumber(line[1]);
        if(temp!=-999){
            datastore[varcount]=temp;
            var2=varcount;
            varcount++;
        }
        else {printf("Variable not found (%s)",line[1]);return 1;}
    }
    *a=var1;*b=var2;*c=comp;
    return 0;
}

int variableassign(){
    if(checknumber(line[0])!=-999){
        printf("Give variable name instead of num (%s)",line[0]);return 1;
    }
    if(strcmp("=",line[1])){
        printf("Syntax error (expected =)");return 1;
    }
    int checknum=checknumber(line[2]);
    // printf("%d\n",checknum);
    int assign=0;
    if(checknum==-999){
        int temp=checkvariable(line[2]);
        if(temp==-999){
            printf("Variable not found (%s)",line[2]);return 1;
        }
        assign=datastore[temp];
    }else assign=checknum;
    //checking ; or  operatoin
    if(strcmp(";",line[3])){
        int arth=checkarthematic(line[3]);
        // printf("%d",temp);
        if(arth==-1){
            printf("please use +,-,*,/ instead of %s",line[3]);return 1;
        }
        checknum=checknumber(line[4]);
        int temp2=0;
        if(checknum==-999){
            int temp=checkvariable(line[2]);
            if(temp==-999){
                printf("Variable not found (%s)",line[4]);return 1;
            }
            temp2=datastore[temp];
        }else temp2=checknum;
        if(arth==0)assign+=temp2;
        if(arth==1)assign-=temp2;
        if(arth==2)assign*=temp2;
        if(arth==3)assign/=temp2;

    }
    int temp=checkvariable(line[0]);
    printf("%s = %d\n",line[0],assign);
    if(temp!=-999){
        datastore[temp]=assign;
    }else{
        strcpy(varname[varcount],line[0]);
        datastore[varcount]=assign;
        varcount++;
    }
    return 0;
}

void lineput(){
    m_temp=0;
    while(1){
        scanf("%s",line[m_temp]);
        m_temp++;
        if(!strcmp(";",line[m_temp-1])||!strcmp("do",line[m_temp-1]))break;
    }
}

int checkvariable(char arr[]){
    // printf("%d\n",varcount);
    for(int i=0;i<varcount;i++){
        // printf("%s %s\n",arr,varname[i]);
        if(!strcmp(arr,varname[i]))return i;
    }
    return -999;
}
int checknumber(char arr[]){
    int sum=0;
    for(int i=0;i<strlen(arr);i++){
        int temp=arr[i]-'0';
        // printf("%d %s\n",temp,arr);
        if(temp>=0&&temp<=9){sum*=10;sum+=temp;}
        else return -999;
    }
    return sum;
}
int checkarthematic(char arr[]){
    if(!strcmp(arr,"+"))return 0;
    else if(!strcmp(arr,"-"))return 1;
    else if(!strcmp(arr,"*"))return 2;
    else if(!strcmp(arr,"/"))return 3;
    return -1;
}

int checkcomparters(char arr[]){
    if(!strcmp(arr,">"))return 0;
    else if(!strcmp(arr,"<"))return 1;
    else if(!strcmp(arr,">="))return 2;
    else if(!strcmp(arr,"<="))return 3;
    else if(!strcmp(arr,"=="))return 4;
    else if(!strcmp(arr,"!="))return 5;
    return -1;
}

bool condtionchek(int v1,int v2,int c){
    // printf("%d %d %d\n",v1,v2,c);
    if(c==0)return datastore[v1]>datastore[v2];
    else if(c==1)return datastore[v1]<datastore[v2];
    else if(c==2)return datastore[v1]>=datastore[v2];
    else if(c==3)return datastore[v1]<=datastore[v2];
    else if(c==4)return datastore[v1]==datastore[v2];
    else if(c==5)return datastore[v1]!=datastore[v2];
    return false;
}