#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student{
    char name[30];
    int roll_no;
    int reg;
    int tmaths;
    int pmaths;
    int tchem;
    int pchem;
    int tphysics;
    int pphysics;
    int tc_language;
    int pc_language;
};
struct attendence{
    float aggregate;
    float maths;
    float physics;
    float chemistry;
    float c_language;
};
void insertDetails()
{
    FILE *fl=fopen("student.txt","ab");
    if(fl == NULL)
        printf("\nFailed to open file");
    struct student detstudent;

    printf("\nEnter the name of the student: ");
    scanf("%s",detstudent.name);
    printf("Enter the roll no of the student: ");
    scanf("%d",&detstudent.roll_no);
    printf("\nEnter the registraion of the student: ");
    scanf("%d",&detstudent.reg);
    printf("\nEnter the total no of maths class : ");
    scanf("%d",&detstudent.tmaths);
    printf("\nEnter the no of classes attended in maths class : ");
    scanf("%d",&detstudent.pmaths);
    printf("\nEnter the total no of Chemistry class : ");
    scanf("%d",&detstudent.tchem);
    printf("\nEnter the no of classes attended in Chemistry class : ");
    scanf("%d",&detstudent.pchem);
    printf("\nEnter the total no of Physics class : ");
    scanf("%d",&detstudent.tphysics);
    printf("\nEnter the no of classes attended in Physics class : ");
    scanf("%d",&detstudent.pphysics);
    printf("\nEnter the total no of C language class : ");
    scanf("%d",&detstudent.tc_language);
    printf("\nEnter the no of classes attended in C language class : ");
    scanf("%d",&detstudent.pc_language);

    fwrite(&detstudent,sizeof(struct student),1,fl);
    fclose(fl);
    FILE *at=fopen("attendence.txt","ab");
    struct attendence atten;
    int total_classses = detstudent.tmaths + detstudent.tchem + detstudent.tphysics + detstudent.tc_language ;
    int present_classses = detstudent.pmaths + detstudent.pchem + detstudent.pphysics + detstudent.pc_language ;

    atten.aggregate = ((float)present_classses / total_classses) * 100 ;
    atten.maths = ((float)detstudent.pmaths / detstudent.tmaths) * 100 ;
    atten.physics = ((float)detstudent.pphysics / detstudent.tphysics) * 100 ;
    atten.chemistry = ((float)detstudent.pchem / detstudent.tchem) * 100 ;
    atten.c_language = ((float)detstudent.pc_language / detstudent.tc_language) * 100 ;

    fwrite(&atten,sizeof(struct attendence),1,at);
    fclose(at);

}
void displayDetails()
{
    FILE *fl=fopen("student.txt","rb");
    FILE *at=fopen("attendence.txt","rb");
    if(fl == NULL || at == NULL)
        printf("\nFailed to open file");
    struct student detstudent;
    struct attendence atten;
    int i=1;
    while((fread(&detstudent,sizeof(struct student),1,fl) && fread(&atten,sizeof(struct attendence),1,at)) == 1)
    {
        printf("\nStudent %d:-",i);
        printf("\n");
        printf("\nName = %s",detstudent.name);
        printf("\nRoll no = %d",detstudent.roll_no);
        printf("\nRegistration no = %d",detstudent.reg);
        printf("\nAggregate Attendence = %.2f",atten.aggregate);
        printf("\nMaths Attendence = %.2f",atten.maths);
        printf("\nPhysics Attendence = %.2f",atten.physics);
        printf("\nChemistry Attendence = %.2f",atten.chemistry);
        printf("\nC Language Attendence = %.2f",atten.c_language);
        printf("\n");
        i++;
    }
    fclose(fl);
    fclose(at);
}
void deleteDetails()
{
    char del[20];
    printf("\nEnter the name of the student to be deleted: ");
    scanf("%s",&del);
    FILE *fl1=fopen("student.txt","rb");
    FILE *fl2=fopen("attendence.txt","rb");

    FILE *tp1=fopen("temp1.txt","wb");
    FILE *tp2=fopen("temp2.txt","wb");

    if(fl1 == NULL || tp1 == NULL || fl2 == NULL || tp2 == NULL) {
        printf("\nFailed to open database!");
        return;
    }
    int flag =0,c=0;
    struct student detstudent;
    struct attendence atten;
    while ((fread(&detstudent, sizeof(struct student), 1, fl1) && fread(&atten, sizeof(struct attendence), 1, fl2)) == 1)
    {
        c++;
        if(stricmp(del,detstudent.name))
        {
            fwrite(&detstudent, sizeof(struct student),1,tp1);
            fwrite(&atten, sizeof(struct attendence), 1, tp2);
            flag ++ ;
        }
    }
    fclose(tp1);
    fclose(tp2);
    fclose(fl1);
    fclose(fl2);
    remove("student.txt");
    remove("attendence.txt");
    rename("temp1.txt","student.txt");
    rename("temp2.txt","attendence.txt");
    if(flag != c)
        printf("\nData deleted !!!");
    else
        printf("\nNo Student found !");
}
void searchDetails()
{
    FILE *fl=fopen("student.txt","rb");
    FILE *at=fopen("attendence.txt","rb");
    if(fl == NULL || at == NULL)
        printf("\nFailed to open file");
    struct student detstudent;
    struct attendence atten;
    char search[20];
    printf("\nEnter the name of the student to be searched: ");
    scanf("%s",&search);
    int flag=1;
    while((fread(&detstudent,sizeof(struct student),1,fl) && fread(&atten,sizeof(struct attendence),1,at)) == 1)
    {
        if(stricmp(search, detstudent.name) == 0)
        {
            flag=0;
            printf("\nSearch Options :-");
            printf("\n1.Aggregate Attendence");
            printf("\n2.Maths Attendence");
            printf("\n3.Physics Attendence");
            printf("\n4.Chemistry Attendence");
            printf("\n5.C Language Attendence");
            int choice;
            printf("\nEnter your choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:printf("\nAggregate Attendence = %.2f",atten.aggregate);
                       break;
                case 2:printf("\nMaths Attendence = %.2f",atten.maths);
                       break;
                case 3:printf("\nPhysics Attendence = %.2f",atten.physics);
                       break;
                case 4:printf("\nChemistry Attendence = %.2f",atten.chemistry);
                       break;
                case 5:printf("\nC Language Attendence = %.2f",atten.c_language);
                       break;
                default:printf("Invalid Input");
            }
        }
    }
    if(flag)
        printf("\nNo student found in the database !");
    fclose(fl);
    fclose(at);
}
int main()
{
    int choice;
    do
    {
        printf("\n 1.Insert details of the student ");
        printf("\n 2.Display the details of the student ");
        printf("\n 3.Search specific information ");
        printf("\n 4.Delete any detail ");
        printf("\n 5.Exit");

        printf("\nEnter the choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1 :insertDetails();
                    break;
            case 2 :displayDetails();
                    break;
            case 3 :searchDetails();
                    break;
            case 4 :deleteDetails();
                    break;
            case 5 :printf("THANK YOU FOR USING MY PROGRAM");
                    break;
            default:printf("Invalid Input");
        }
    } while (choice!=5);
    
    return 0;
}
