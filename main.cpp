/*Objective:********BANK PROJECT***********
Make a class to represent a bank account, where following details can be maintained:
Depositor name, 
account number(you may define any starting number), 
type of account(current/saving), 
balance amount in the account. 
Also, the following set of operations/actions should be provided: 
Create an account-->>
close an acoount--->>,
deposit an amount, 
withdraw amount(make sure you check the balance), 
and 
output the name & balance on demand.

  Author: Deepanshu Garg
  Created On: 09/10/2021
  Dependencies: None
*/

//the preprocessor segment including the required header files during the compilation
#include<bits/stdc++.h>

//using namespace std to tell compiler scope of std
using namespace std;

//Class Bank is declared
class Bank	{

    //Private data members are declared to store account information
    char accountHolderName[30],address[100];
    char typeOfAccount;
    float accountBalance;
    long accountNumber;
    //All Member functions are declared
    public:
      void inputdata();
      void editdata();
      void displaydata();
      int search(int );
      void deposit(float);
      void withdraw(float);
      float balance();
      char type();
      void records();
	
};

//defined to feed/enter account details in the system,i.e. Creating Bank Account
void Bank::inputdata()	{
	cin.ignore();
	cout<<"\nEnter Account Holder Name: ";      
  cin.getline(accountHolderName,30);
	cout<<"Enter type of account (S/C) : ";
  cin>>typeOfAccount;
  typeOfAccount=toupper(typeOfAccount);
  cout<<"Enter account number: ";
	cin>>accountNumber;
  cin.ignore();
  cout<<"Enter accoun holder's address: ";
	cin.getline(address,100);
  cout<<"Enter account balance: ";   
  cin>>accountBalance; 
	
}

//define to change details of existing bank account
void Bank::editdata()	{
	cin.ignore();
	cout<<"\nEnter Account Holder Name: ";      
  cin.getline(accountHolderName,30);
	cout<<"Enter type of account: ";
  cin>>typeOfAccount;
  typeOfAccount=toupper(typeOfAccount);
  cout<<"Enter account number: ";
	cin>>accountNumber;
  cin.ignore();
  cout<<"Enter accoun holder's address: ";
	cin.getline(address,100);
  cout<<"Enter account balance: ";   
  cin>>accountBalance; 
}

//defined to display account information 
void Bank::displaydata()	{
	cout<<"\nAccount Holder's name: "<<accountHolderName;
  cout<<"\nAccount Holder's address: "<<address;
	cout<<"\nAccount type: "<<typeOfAccount;
	cout<<"\nAccount number: "<<accountNumber;
	cout<<"\nAccount balance: "<<accountBalance;   
}

//defined to search for a specific account number in records
int Bank::search(int accNumber )	{
	if(accNumber==accountNumber)
		return 1;
	else return 0;
		
}

//defined to deposit amount in an account
void Bank :: deposit(float amount){
  accountBalance+=amount;
}

//defined to withdraw amount from an account
void Bank :: withdraw(float amount){
  accountBalance-=amount;
}

float Bank:: balance(){
  return accountBalance;
}

char Bank::type(){
  return typeOfAccount;
}

void Bank::records(){
	cout<<accountNumber<<setw(10)<<" "<<accountHolderName<<setw(10)<<" "<<typeOfAccount<<setw(20)<<fixed<<setprecision(2)<<accountBalance<<setw(30)<<address<<endl;
}

//function declaration
void newAccount()
{
	Bank obc;
	ofstream outFile;
	outFile.open("details.dat",ios::binary|ios::app);
	obc.inputdata();
	outFile.write(reinterpret_cast<char *> (&obc), sizeof(Bank));
	outFile.close();
}

void updateBalance(int n, int option)
{
	int amt;
	bool found=false;
	Bank obc;
	fstream File;
	File.open("details.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&obc), sizeof(Bank));
		if(obc.search((n)))
		{
			obc.displaydata();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				obc.deposit(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=obc.balance()-amt;
				if((bal<500 && obc.type()=='S') || (bal<1000 && obc.type()=='C'))
					cout<<"Insufficience balance";
				else
					obc.withdraw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(obc));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&obc), sizeof(Bank));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void displayAccDetails(int n)
{
	Bank obc;
	bool flag=false;
	ifstream inFile;
	inFile.open("details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&obc), sizeof(obc)))
	{
		if(obc.search(n))
		{
			obc.displaydata();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void modifyAccount(int n)
{
	bool found=false;
	Bank obc;
	fstream File;
	File.open("details.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&obc), sizeof(Bank));
		if(obc.search(n))
		{
			obc.displaydata();
			cout<<"\n\nEnter The New Details of account"<<endl;
			obc.editdata();
			int pos=(-1)*static_cast<int>(sizeof(Bank));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&obc), sizeof(Bank));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void displayRecord()
{
	Bank obc;
	ifstream inFile;
	inFile.open("details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.         NAME          Type           Balance                 ADDRESS\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&obc), sizeof(obc)))
	{
		obc.records();
	}
	inFile.close();
}

void closeAccount(int n)
{
	Bank obc;
	ifstream inFile;
	ofstream outFile;
	inFile.open("details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&obc), sizeof(Bank)))
	{
		if(!obc.search(n))
		{
			outFile.write(reinterpret_cast<char *> (&obc), sizeof(Bank));
		}
	}
	inFile.close();
	outFile.close();
	remove("details.dat");
	rename("Temp.dat","details.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

int main()	{

  //variable i maintains the count of entries, t is used in loops, choice is declared to know the operation to be performed
	int i=0,t,choice;

  //declared to enter account number which helps in searching the particular account in records
  int accNumber;

  //amount to be withdrwan OR amount to be deposited
 // float amount;

	while(1)	{
    //All instructions are dispalyed on screen. User can perform any operation out of the following instructions
		cout<<"\n\n\t\tMENU"
		<<"\n1. Entry of New account"
		<<"\n2. Deposit Amount"
    <<"\n3. Withdraw Amount"
		<<"\n4. Search For Details"
		<<"\n5. Edit Details Of existing account"
    <<"\n6. Display all accounts"
    <<"\n7. Close account"
		<<"\n8. Exit"
		<<"\n\nEnter your Choice: ";
		cin>>choice;//entering choice input
		
    //switch to select one operation out of all according to the choice made by user
		switch(choice)	{

      //entry of new account
			case 1:
        newAccount();
        break;

      //Deposit amount
			case 2:
        cout<<"\nEnter your Account Number: ";
        cin>>accNumber;
        updateBalance(accNumber, 1);
        break;

      //Withdraw amount
      case 3:
        cout<<"\nEnter your Account Number: ";
        cin>>accNumber;
        updateBalance(accNumber, 2);
        break;

      //display data  
			case 4: 
        cin.ignore();
				cout<<"\nEnter your Account Number: ";
        cin>>accNumber;
        //If account exist--->>Show the account information
        displayAccDetails(accNumber);
				break;
			
      //edit account information
			case 5: 
        cin.ignore();
				cout<<"\nEnter your Account Number: ";
        cin>>accNumber;
				modifyAccount(accNumber);
				break;

      case 6: 
        displayRecord();
        break;
			
      case 7:
        cout<<"\nEnter your Account Number: ";
        cin>>accNumber;
        closeAccount(accNumber);
        break;

      //exit the program
			case 8: 
        exit(0);

      //default choice
			default: 
        cout<<"\nInvalid Choice Entered";
		}
	}
	return 0;
}