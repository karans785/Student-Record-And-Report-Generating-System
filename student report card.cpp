#include<iostream>
#include<graphics.h>
#include<iomanip>
#include<fstream>
using namespace std;

class student{
 public:
    char name[20];
    int roll;
    int marks[5];

    student()
    {

    }
    student(char n[20],int r,int mar[5])
    {
        strcpy(name,n);
        roll=r;
        for(int i=0;i<5;i++)
            marks[i]=mar[i];
    }
    void print()
    {
        cout<<name<<setw(20)<<roll<<setw(20);
        for(int i=0;i<5;i++)
            cout<<marks[i]<<setw(15);
        cout<<percentage()<<setw(10);
        cout<<grade();
        cout<<endl;
    }
    float percentage()
    {
        float sum=0.0 ;
        for(int i=0;i<5;i++)
            sum+=marks[i];
        sum = sum/5.0;
        return sum;
    }
    char grade()
    {
        float per = percentage();
        if(per>=80 && per<=100)
            return 'A';
        else if(per>=60)
            return 'B';
        else if(per>=40)
            return 'C';
        else
            return 'F';
    }
};

student input()
{
    system("cls");
    char name[20] ;
    int roll;
    int marks[5];

    cout<<"                       ===========ADD A NEW STUDENT RECORD===========\n\n\n\n\n";
    cout<<"          \nEnter the name of Student        : ";
    cin>>name;
    cout<<"          \nEnter the roll number            : ";
    cin>>roll;
    cout<<"          \nEnter marks in Physics           : ";
    cin>>marks[0];
    cout<<"          \nEnter marks in Chemistry         : ";
    cin>>marks[1];
    cout<<"          \nEnter marks in Mathematics       : ";
    cin>>marks[2];
    cout<<"          \nEnter marks in English           : ";
    cin>>marks[3];
    cout<<"          \nEnter marks in Computer Science  : ";
    cin>>marks[4];

    student s(name,roll,marks);
    return s;
}



void write_student()
{
    ofstream file_obj;
    file_obj.open("student.txt",ios::out|ios::app);
    if(!file_obj)
	{
		cout<<"File not Found";
		exit(0);
	}
    student st=input();
    file_obj.write((char*)&st,sizeof(student));
    file_obj.close();
    cout<<"\n\nstudent record Has Been Created ";
}

void display(int roll)
{
    ifstream file_obj;
    file_obj.open("student.txt",ios::in);
    if(!file_obj)
	{
		cout<<"File not Found";
		exit(0);
	}
	int f=0;
    student st;
    file_obj.read((char*)&st,sizeof(student));
    while(!file_obj.eof())
    {
        if(st.roll==roll)
        {
            st.print();
            cout<<endl;
            f=1;
        }
        file_obj.read((char*)&st,sizeof(student));
    }
    if(!f)
    {
        cout<<"No student with roll no. "<<roll<<" found!";
    }
}

void display_all()
{
    ifstream file_obj;
    file_obj.open("student.txt",ios::in);
     if(!file_obj)
	{
		cout<<"File not Found";
		exit(0);
	}
    student st;
    file_obj.read((char*)&st,sizeof(student));
    while(!file_obj.eof())
    {
        st.print();
        file_obj.read((char*)&st,sizeof(student));
    }
}


student ModifyInput(int roll)
{
    system("cls");
    char name[20] ;
    int marks[5];

    cout<<"                       ===========MODIFY A STUDENT'S RECORD===========\n\n\n\n\n";
    cout<<"          \nRoll number of student is        : "<<roll<<"\n";

    cout<<"          \nEnter the name of Student        : ";
    cin>>name;
    cout<<"          \nEnter marks in Physics           : ";
    cin>>marks[0];
    cout<<"          \nEnter marks in Chemistry         : ";
    cin>>marks[1];
    cout<<"          \nEnter marks in Mathematics       : ";
    cin>>marks[2];
    cout<<"          \nEnter marks in English           : ";
    cin>>marks[3];
    cout<<"          \nEnter marks in Computer Science  : ";
    cin>>marks[4];

    student s(name,roll,marks);
    return s;
}

void modify(int roll)
{

    fstream file_obj;
    file_obj.open("student.txt",ios::in| ios::out);
     if(!file_obj)
	{
		cout<<"File not Found";
		exit(0);
	}
    student st;
    int f=0;
    file_obj.read((char*)&st,sizeof(student));
    while(!file_obj.eof())
    {
        if(st.roll==roll)
        {
            f=1;
            file_obj.seekg(0,ios::cur);
            st=ModifyInput(st.roll);
            file_obj.seekp(file_obj.tellg() - sizeof(st));
            file_obj.write((char*)&st, sizeof(st));
            cout<<"\n\n\nRecord has been successfully updated!";
            return;
        }

        file_obj.read((char*)&st,sizeof(student));
    }
    if(!f)
    {
        cout<<"No student with roll no. "<<roll<<" found!";
    }

}

void intro()
{
    system("cls");

    cout<<"\n\n\n\n\n\n\n                         STUDENTS";
    cout<<"\n                            RECORD";
    cout<<"\n\n                        MANAGEMENT";
    cout<<"\n\n                          SYSTEM";
    cout<<"\n\n\n\n\n                                     Project Made By:-";
    cout<<"\n                                                      KARAN";

    delay(30);
}

void Delete()
{
    system("cls");
    cout<<"                       ===========DELETE A STUDENT'S RECORD===========\n\n\n\n\n";
    cout<<"Enter roll number of student whose record you want to delete : ";
    int roll;
    cin>>roll;
    fstream file_obj;
    fstream newFile;
     file_obj.open("student.txt",ios::in| ios::out);
     newFile.open("new.txt",ios::out);
     if(!file_obj)
	{
		cout<<"File not Found";
		exit(0);
	}
	if(!newFile)
    {
        cout<<"File not Found";
		exit(0);
    }
    student st;
    file_obj.read((char*)&st,sizeof(student));
    int f=1;
    while(!file_obj.eof())
    {
        if(st.roll!=roll)
        {
            newFile.write((char*)&st, sizeof(st));
        }
        else
        {
            f=0;
            cout<<"\n\n\n\nRecord of "<<st.name<<" has been deleted successfully!";
        }
        file_obj.read((char*)&st,sizeof(student));
    }
    if(f)
        cout<<"No student with roll no. "<<roll<<" found!";
    file_obj.close();
    newFile.close();
    remove("student.txt");
    rename("new.txt","student.txt");
}

int main_menu()
{
    system("cls");
    int ch;
    do{
    cout<<"\t\t\t\t=======%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%========\n";
    cout<<"\t\t\t\t||       Welcome to Student Record Management System        ||\n";
    cout<<"\t\t\t\t=======%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%========\n";
    cout<<"\n\n\n\t\t\t\t\t  Choose one option amongst the following: ";
    cout<<"\n\n\n\t\t\t\t\t\t1.Add new Student\n\n\t\t\t\t\t\t2.Modify a Student's Record\n\n\t\t\t\t\t\t3.Generate report card\n\n\t\t\t\t\t\t4.Generate class Record.\n\n\t\t\t\t\t\t5.Delete record of a Student.\n\n\t\t\t\t\t\t6.Exit";
    cout<<"\n\n\n\n           \t\t\t\t\t    Enter a choice : ";
    cin>>ch;
    }while(ch<=0||ch>6);
    return ch;
}

int main()
{
    //intro();
label:
    int ch=main_menu();

    switch(ch)
    {
        case 1:
            write_student();
            ret:
            cout<<"\n\n\nPress r to return to main menu or e to exit: ";
            char c;
            cin>>c;
            if(c=='r')
                goto label;
            else
                intro();
            break;
        case 2:
            system("cls");
            cout<<"Enter the roll number of student whose data is to be modified : ";
            int roll;
            cin>>roll;
            modify(roll);
            goto ret;
            break;

        case 3:
            system("cls");
            cout<<"\n\n                ==================STUDENT REPORT==================\n\n\n\n";
            cout<<"Enter the roll number of student whose report card is to be generated : ";
            cin>>roll;

            cout<<"\n\n\n\nName"<<setw(20)<<"Roll No."<<setw(20)<<"Physics  "<<setw(15)<<"Chemistry "<<setw(15)<<"Mathematics "<<setw(15)<<"English"<<setw(15)<<"Computer Science"<<setw(15)<<"Percentage"<<setw(10)<<"Grade"<<"\n";
            cout<<"\n========================================================================================================================================\n";
            display(roll);
            goto ret;
            break;

        case 4:
            system("cls");
            cout<<"\n\n\t\t\t\t                ================  CLASS REPORT  ================\n\n\n\n";
            cout<<"=============================================================================================================================================\n";
            cout<<"Name"<<setw(20)<<"Roll No."<<setw(20)<<"Physics  "<<setw(15)<<"Chemistry "<<setw(15)<<"Mathematics "<<setw(15)<<"English"<<setw(15)<<"Computer Science"<<setw(15)<<"Percentage"<<setw(10)<<"Grade"<<"\n";
            cout<<"=============================================================================================================================================\n";
            display_all();
            goto ret;
            break;

        case 5:
            Delete();
            goto ret;

        case 6:
            intro();
            exit(0);
            break;
        }


    return 0;
}
