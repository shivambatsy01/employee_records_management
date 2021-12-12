#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct employee
{
	char emp_name[25];
	int emp_id;
	char emp_post[25];
	float emp_sal;
};

void write_employee(const char* file)
{
	FILE *fptr=fopen(file,"a"); //a=append mode
	cout<<"How many employees's record you want to enter?_  ";
	int n; cin>>n;
	for(int i=0;i<n;i++)
	{
		employee e1;
		cout<<"\nEnter records of Employee #"<<i+1<<endl;
		cout<<"Enter name of Employee: "; cin>>e1.emp_name;
		cout<<"Enter id of Employee: "; cin>>e1.emp_id;
		cout<<"Enter post of the Employee: "; cin>>e1.emp_post;
		cout<<"Enter salary of the Employee: "; cin>>e1.emp_sal;
		cout<<endl;
		fwrite(&e1,sizeof(employee),1,fptr);
	}
	cout<<n<<" records added!\n\n";
	fclose(fptr);
}
void print_employees_data(const char* file)
{
	cout<<endl;
	FILE *fptr=fopen(file,"r"); //r=read mode
	employee e1;
	int count=0;
	while(fread(&e1,sizeof(employee),1,fptr))
	{
		count++;
		cout<<"Employee's Name: "<<e1.emp_name<<endl;
		cout<<"Employee's ID: "<<e1.emp_id<<endl;
		cout<<"Employee's post in the organisation: "<<e1.emp_post<<endl;
		cout<<"Employee Salary: "<<e1.emp_sal<<endl;
		cout<<endl;
	}
	if(count==0) cout<<"Empty Database!! Nothing to Show\n";
	cout<<endl;
	fclose(fptr);
	
}
void search_employee_by_id(const char* file)
{
	cout<<"Enter id of Employee to be searched: ";
	int myid; cin>>myid;
	FILE *fptr=fopen(file,"r"); //r=read mode
	employee e1;
	while(fread(&e1,sizeof(employee),1,fptr))
	{
		if(e1.emp_id==myid)
		{
			cout<<"Employee with id: "<<e1.emp_id<<" found\n";
			cout<<"Employee's Name: "<<e1.emp_name<<endl;
			cout<<"Employee's post in the organisation: "<<e1.emp_post<<endl;
			cout<<"Employee Salary: "<<e1.emp_sal<<endl;
			cout<<endl<<endl;
			return;
		}	
	}
	fclose(fptr);
	cout<<"No employee with this id availabe\n\n";
}
void delete_employee_data(const char* file)
{
	cout<<"Enter id of Employee to be deleted: ";
	int myid; cin>>myid;
	FILE *fptr1=fopen(file,"r"); //r=read mode
	FILE *fptr2=fopen("temp.txt","w");
	employee e1;
	bool del=true;
	while(fread(&e1,sizeof(employee),1,fptr1))
	{
		if(e1.emp_id==myid)
		{
			cout<<"Employee with id: "<<e1.emp_id<<" found\n";
			cout<<"Employee's Name: "<<e1.emp_name<<endl;
			cout<<"Data deleted successfully\n";
			del=false;
			cout<<endl<<endl;
		}	
		else
		{
			fwrite(&e1,sizeof(employee),1,fptr2);
			continue;
		}
	}
	if(del) cout<<"No Employee with Id: "<<myid<<" is present in organisation\n";
	fclose(fptr1);
	fclose(fptr2);
	//delete file and then change name of temp to file
	const char* j=file;
	remove(file);
	rename("temp.txt",j);
}
void menu(void)
{
	cout<<"========================================="<<endl;
	cout<<"*******************MENU******************"<<endl;
	cout<<"========================================="<<endl;
	cout<<"1. Enter new employee's data\n";
	cout<<"2. Print all employee's data\n";
	cout<<"3. Search employee by id\n";
	cout<<"4. Delete employee's data by id\n";
	cout<<"5. Exit\n";
	cout<<"Enter your option (1 to 5): ";
}
int main(int argc, char*argv[])
{
	const char* empl= "employees.txt";
	while(true)
	{
		menu();
		int n; cin>>n;
		if(n==1) write_employee(empl);
		else if(n==2) print_employees_data(empl);
		else if(n==3) search_employee_by_id(empl);
		else if(n==4) delete_employee_data(empl);
		else if(n==5) return 0;
		else cout<<"Please enter a valid option\n";
	}
	
}
