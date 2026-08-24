#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void result()
{
    FILE *fp1,*fp2,*fp3;
    int id,id1,m1,m2,m3;
    char name[50];
    fp1=fopen("student1.txt","r");
    fp2=fopen("mark1.txt","r");
    fp3=fopen("result1.txt","w");
    if(fp1==NULL || fp2==NULL || fp3==NULL)
    {
        printf("error generating result\n");
        return;
    }
    while(fscanf(fp1,"%d",&id)!=EOF)
    {
        fgetc(fp1);
        fgets(name,sizeof(name),fp1);
        name[strcspn(name,"\n")]='\0';
        fscanf(fp2,"%d %d %d %d",&id1,&m1,&m2,&m3);
        if(id!=id1)
        {
            printf("data mismatch error\n");
            break;
        }
        int total=m1+m2+m3;
        float per=total/3.0;
        char grade;
        if(per>=80)
            grade='A';
        else if(per>=60)
            grade='B';
        else if(per>=40)
            grade='C';
        else
            grade='F';
        fprintf(fp3,"%d|%s|%d %d %d|%d|%.2f|%c\n",id,name,m1,m2,m3,total,per,grade);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

void add()
{
    FILE *fp1,*fp2;
    int id,m1,m2,m3;
    char name[50];
    fp1=fopen("student1.txt","a");
    fp2=fopen("mark1.txt","a");
    if(fp1==NULL || fp2==NULL)
    {
        printf("file error\n");
        return;
    }
    printf("enter ID: ");
    scanf("%d",&id);
    getchar();
    printf("enter name: ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]='\0';
    printf("enter marks of 3 subjects: ");
    scanf("%d %d %d",&m1,&m2,&m3);
    fprintf(fp1,"%d %s\n",id,name);
    fprintf(fp2,"%d %d %d %d\n",id,m1,m2,m3);
    fclose(fp1);
    fclose(fp2);
    result();
    printf("data added successfully\n");
}

void display()
{
    result();
    FILE *fp;
    int id,m1,m2,m3,total;
    int tid=0;
    float top=0,per;
    char name[50],grade;
    char tname[50],tgrade;
    fp=fopen("result1.txt","r");
    if(fp==NULL)
    {
        printf("no data found\n");
        return;
    }
    printf("\nID\t\tname\t\t\t\tmarks\t\ttotal\tper\tgrade\n");
    while(fscanf(fp,"%d|%[^|]|%d %d %d|%d|%f|%c\n",
                 &id,name,&m1,&m2,&m3,&total,&per,&grade)!=EOF)
    {
        printf("%d\t\t%s\t\t\t%d %d %d\t%d\t%.2f\t%c\n",id,name,m1,m2,m3,total,per,grade);
        if(per>top)
        {
            top=per;
            tid=id;
            strcpy(tname,name);
            tgrade=grade;
        }
    }
    fclose(fp);
    printf("\n   TOPPER   \n");
    printf("top ID\ttop name\tper\tgrade\n");
    printf("%d\t%s\t\t%.2f\t%c\n",
           tid,tname,top,tgrade);
}

void search()
{
    FILE *fp;
    int id,sid;
    char name[50];
    fp=fopen("student1.txt","r");
    if(fp==NULL)
    {
        printf("file not found\n");
        return;
    }
    printf("enter ID to search: ");
    scanf("%d",&sid);
    while(fscanf(fp,"%d",&id)!=EOF)
    {                                                                                                                                                                                                     
        fgetc(fp);
        fgets(name,sizeof(name),fp);
        name[strcspn(name,"\n")]='\0';
        if(id==sid)
        {
            printf("Found: %d %s\n",id,name);
            fclose(fp);
            return;
        }
    }
    printf("record not found\n");
    fclose(fp);
}

void update()
{
    FILE *fp1,*fp2,*t1,*t2;
    int id,id1,uid,m1,m2,m3;
    char name[50];
    fp1=fopen("student1.txt","r");
    fp2=fopen("mark1.txt","r");
    t1=fopen("t1.txt","w");
    t2=fopen("t2.txt","w");
    if(fp1==NULL || fp2==NULL || t1==NULL || t2==NULL)
    {
        printf("file error\n");
        return;
    }
    printf("enter ID to update: ");
    scanf("%d",&uid);
    int found=0;
    while(fscanf(fp1,"%d",&id)!=EOF)
    {
        fgetc(fp1);
        fgets(name,sizeof(name),fp1);
        name[strcspn(name,"\n")]='\0';
        fscanf(fp2,"%d %d %d %d",&id1,&m1,&m2,&m3);
        if(id!=id1)
        {
            printf("data mismatch error\n");
            break;
        }
        if(id==uid)
        {
            found=1;
            getchar();
            printf("enter new name: ");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name,"\n")]='\0';
            printf("enter new marks: ");
            scanf("%d %d %d",&m1,&m2,&m3);
        }
        fprintf(t1,"%d %s\n",id,name);
        fprintf(t2,"%d %d %d %d\n",id,m1,m2,m3);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(t1);
    fclose(t2);
    remove("student1.txt");
    remove("mark1.txt");
    rename("t1.txt","student1.txt");
    rename("t2.txt","mark1.txt");
    result();
    if(found)
        printf("updated successfully\n");
    else
        printf("record not found\n");
}

void deletedata()
{
    FILE *fp1,*fp2,*t1,*t2;
    int id,id1,did,m1,m2,m3;
    char name[50];
    fp1=fopen("student1.txt","r");
    fp2=fopen("mark1.txt","r");
    t1=fopen("t1.txt","w");
    t2=fopen("t2.txt","w");
    if(fp1==NULL || fp2==NULL || t1==NULL || t2==NULL)
    {
        printf("file error\n");
        return;
    }
    printf("enter ID to delete: ");
    scanf("%d",&did);
    int found=0;
    while(fscanf(fp1,"%d",&id)!=EOF)
    {
        fgetc(fp1);
		fgets(name,sizeof(name),fp1);
        name[strcspn(name,"\n")]='\0';
        fscanf(fp2,"%d %d %d %d",&id1,&m1,&m2,&m3);
        if(id!=id1)
        {
            printf("data mismatch error\n");
            break;
        }
        if(id!=did)
        {
            fprintf(t1,"%d %s\n",id,name);
            fprintf(t2,"%d %d %d %d\n",id,m1,m2,m3);
        }
        else
        {
            found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    fclose(t1);
    fclose(t2);
    remove("student1.txt");
    remove("mark1.txt");
    rename("t1.txt","student1.txt");
    rename("t2.txt","mark1.txt");
    result();
    if(found)
        printf("deleted successfully\n");
    else
        printf("record not found\n");
}

int main()
{
    int ch;
    while(1)
    {
        printf("\nMENU\n");
        printf("1 add\n2 display\n3 search\n4 update\n5 delete\n6 exit\n");
        printf("enter choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                add();
                break;
            case 2:
                display();
                break;
            case 3:
                search();
                break;
            case 4:
                update();
                break;
            case 5:
                deletedata();
                break;
            case 6:
                exit(0);
            default:
                printf("invalid choice\n");
        }
    }
}
