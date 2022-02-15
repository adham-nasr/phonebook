#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <validation>
typedef struct {
    int day;
    int month;
    int year;
} DateOfBirth;

typedef struct {
    char first[100];
    char last[100];
    DateOfBirth date;
    char address[100];
    char email[100];
    char phonenumber[100];
} record;

record contact[1000];
int size = 0,del[1000];
char *prompt[8]={"First Name","Last Name","Day of birth","Month of birth","Year of birth","Address","E-mail","Phone number"};
void *input[8];
int IsNumb(char s[100])
{
    int n,i;
    n = strlen(s);
    for(i=0;i<n;i++)
        if(!(s[i]>='0' && s[i]<='9'))
            return 0;
    return 1;
}
void RmLine(char s[10])
{
    int n=strlen(s);
    s[n-1]='\0';
}
void InpArr(int i)
{
    input[0]=&contact[i].first;
    input[1]=&contact[i].last;
    input[2]=&contact[i].date.day;
    input[3]=&contact[i].date.month;
    input[4]=&contact[i].date.year;
    input[5]=&contact[i].address;
    input[6]=&contact[i].email;
    input[7]=&contact[i].phonenumber;
}
int Read(int i,void *field)
{
    char buff[100];
    printf("%s : ",prompt[i]);
    fgets(buff,100,stdin);
    RmLine(buff);
    //if(!ArrayOfValidationFunctions[i])
        //return 0;
    if(i>=2 && i<=4)
        *((int *)field) = atoi(buff) , printf("     buff = %s    Nmb = %d  \n",buff,*((int *)field));
    else
        strcpy((char *)field,buff);
    return 1;
}
int Add()
{
        int i;
        InpArr(size);
        printf("Please enter the following :\n");
        for(i=0;i<8;i++)
            if(!Read(i,input[i])){
                printf("ERROR : \n");
                return 0;
            }
        size++;
        printf("\nContact successfully added\n");
           /// test ADD FUNTION
        for(int i=0;i<8;i++)
            if(i>=2 && i<=4)
                printf("\n%s : %d",prompt[i],*((int *)input[i]));
            else
                printf("\n%s : %s",prompt[i],(char *)input[i]);
}
int Modify()
{
    char lname[100];
    int i,ind=-1;
    printf("Enter contact's last name : ");
    fgets(lname,100,stdin);
    RmLine(lname);
    for(int i=0;i<size;i++)
        if(!strcmp(lname,contact[i].last) && !del[i])
            printf("Contact %d\n\tFirst Name : %s\n\tLast Name : %s\n",i,contact[i].first,contact[i].last),ind=0;
    if(ind == -1){
        printf("Could not find such contact\n");
        return 0;
    }
    printf("Please choose the contact you want to modify by entering the corresponding number to it : ");
    char buff[100];
    fgets(buff,100,stdin);
    RmLine(buff);
    if(!IsNumb(buff) || atoi(buff)>=size){
        printf("Invalid index\n");
        return 0;
    }
    printf("Modify the following : \n");
    for(int i=0;i<8;i++)
        if(!Read(i,input[i])){
            printf("Invalid %s\n",prompt[i]);
            return 0;
        }
}

int Load()
{
    int S=0;
    char c;
    FILE *file;
    file = fopen("RECORDS.txt","w");
    if(!file)
    {
        printf("An error occurred while loading function");
        return 0;
    }
    fscanf(file,"%d",S);
    fscanf(file,"%c",c);
    for(int i=0;i<S;i++)
        if(!del[i])
        {
            fscanf(file,"%s,%s,",contact[i].first,contact[i].last);
            fscanf(file,"%d-%d-%d,",contact[i].date.day,contact[i].date.month,contact[i].date.year);
            char c;
            c = fgetc(file);
            while(c!=',')
            {
                strncat(contact[i].address,&c,1);
                c = fgetc(file);
            }
            fscanf("%s,%s,",contact[i].email,contact[i].phonenumber);
        }

}
int Delete()
{
    char fname[100],lname[100];
    int i,b=0;
    printf("Please enter the following information about the contact you want to delete\n");
    printf("Enter contact's first name : ");
    fgets(fname,100,stdin);
    printf("Enter contact's last name : ");
    fgets(lname,100,stdin);
    RmLine(fname);   RmLine(lname);
    printf(" \n size =  %d    \n\n",size);
    for(i=0;i<size;i++)
        if(!strcmp(fname,contact[i].first) && !strcmp(lname,contact[i].last) && !del[i])
            del[i]=1,b=1;
    if(b)
        printf("Contact deleted successfully\n");
    else
        printf("Could not find contact in phone book");
}
int Query()
{
    char lname[100];
    int i,cnt=0;
    printf("Enter contact's last name : ");
    fgets(lname,100,stdin);
    RmLine(lname);
   // printf("    1111   \n");
    for(i=0;i<size;i++)
        if(!strcmp(lname,contact[i].last) && !del[i])
            cnt++,printf("Contact %d :\n\tFirst Name : %s\n\tAddress : %s\n\tE-mail : %s\n\tPhone number : %s\n",cnt,contact[i].first,contact[i].address,contact[i].email,contact[i].phonenumber);
    if(!cnt)
        printf("Could not find such contact");
}
int Print()
{
    int i,j,cnt=0;
    for(int i=0;i<size;i++)
        if(!del[i])
        {
            cnt++;
            InpArr(i);
            printf("Contact %d : \n",cnt);
            for(int j=0;j<8;j++)
                if(j>=2 && j<=4)
                    printf("\t%s : %d\n",prompt[j],*((int *)input[j]));
                else
                    printf("\t%s : %s\n",prompt[j],(char *)input[j]);
        }
    if(!cnt)
        printf("The phone book is empty\n");
}
int Save()
{
    int S=0;
    FILE *file;
    file = fopen("RECORDS.txt","w");
    if(!file){
        printf("An error occurred wile saving phone book \n");
        return 0;
    }
    for(int i=0;i<size;i++)
        if(!del[i])
            S++;
    fprintf(file,"%d\n",S);
    for(int i=0;i<size;i++)
        if(!del[i])
            fprintf(file,"%s,%s,%d-%d-%d,%s,%s,%s,",contact[i].first,contact[i].last,contact[i].date.day,contact[i].date.month,contact[i].date.year,contact[i].address,contact[i].email,contact[i].phonenumber);
    fclose(file);
}
int Quit()
{
    int b=0;
    do{
        char buff[100];
        printf("Are You Sure You want to quit ? , Type 'Yes' for quitting and 'No' to return to main menu : ");
        fgets(buff,100,stdin);
        RmLine(buff);
        if(!strcmp(buff,"Yes")){
            b=1;
            return -8;
        }
        else if(!strcmp(buff,"No"))
            b=1;
    }
    while(!b);
}
int main()
{
    int EXIT=0,ret=0;
    int (*Com[8])();
    Com[0]=Add , Com[1]=Load , Com[2]=Modify , Com[3]=Delete;
    Com[4]=Query , Com[5]=Print , Com[6]=Save , Com[7]=Quit;
    while(!EXIT)
    {
        char feature[10];
        printf("\n\nPlease enter the number corresponding to the command you want to execute\n1. ADD\n2. LOAD\n3. MODIFY\n4. DELETE\n5. QUERY\n6. SORT\n7. SAVE\n8. QUIT\n\n");
        fgets(feature,5,stdin);
        /// validate feature ! convert it to an int ! call FUNCTIONS[feature];
        RmLine(feature);
        if(IsNumb(feature) && atoi(feature)<9 && atoi(feature)>0)
            ret = Com[atoi(feature)-1]();
        else{
            printf("Please enter a number between 1 and 8\n");
            continue;
        }
        if(ret==-8)
            EXIT = 1;
    }
}

