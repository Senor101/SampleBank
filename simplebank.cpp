#include<iostream>
#include<fstream>

#include<string>
#include<tuple>
using namespace std;


string acnum = "10040032";
unsigned long int accountnum;
string txt = ".txt";


class customers
{
   long long int cphone;
   char cname[30],cadress[30],actype[30];
   public:
      unsigned int balance;
      void accopen()
      {
          cout << "\nHello! Welcome to this interactive bank account opening form."
          << "\n\nPlease fill the following details." <<endl;
          cout <<"Enter your name:  ";
          cin.ignore(); // clusters not allowed
          cin.getline(cname,30);
          cout << "Enter your permanent adress:  ";
          cin.getline(cadress,30);
          cout << "Enter your Phone-No.:  ";
          cin >> cphone;
          cout << "Enter your preferred account type:  ";
          cin >> actype;
          cout << "Enter your initial deposit amount:  ";
          cin >> balance;
          accountnum = stoi(acnum); // conversion to integer
          accountnum++ ; 
          acnum = to_string(accountnum); // conversion to string
          cout << "Your account has been created." << endl;
          cout << "Account Number(please note this and don't forget this): "<< acnum <<endl;
      }
       void datafile()
       {
          string filename = acnum + txt ;
          ofstream dfile(filename);
          dfile << "Name: "  << cname<<endl;
          dfile << "Account No.:  " << acnum <<endl;
          dfile << "Adress: " << cadress <<endl;
          dfile << "Phone-No: " << cphone <<endl;
          dfile << "Account Type: " << actype <<endl;
          dfile << "Balance:  "<< balance <<endl;
       }
      void accountdisplay()
      {
         char cinfo[100];
         cout << "Hi! \nPlease Enter your account number: " ;
         cin >> acnum;
         string fname = acnum + txt;
         cout << "Your statements till date is displayed below: " <<endl;
         ifstream rfile(fname);
         if (rfile)
         {
            while (!rfile.eof())
            {
               rfile.getline(cinfo, 100);
               cout << cinfo <<endl;
            }
         }
         else { cout << "Transaction unsuccesful please try again with valid account number.\n" ;}
       } 
};

tuple <int, int> debit(int dinero)
{
   unsigned int finaldinero, debitamt;
   cout << "Enter the money you want to withdraw: " ;
   cin >> debitamt;
   if (dinero > debitamt)
   {finaldinero = dinero - debitamt;
   return make_tuple(finaldinero,debitamt);}
   else
      {cout << "Transaction Unsuccesful! Insufficient balance!!! :-( " <<endl;
      return make_tuple(0,0);}
}

tuple <int , int> credit(int dinero)
{
   unsigned int finaldinero, creditamount;
   cout << "Enter the money you want to send to you account: " ;
   cin >> creditamount;
   finaldinero = dinero + creditamount;
   return make_tuple(finaldinero,creditamount);
}

int balancextract() 
{
   string acountnumber, infor;
   cout << "Enter your account number: " ;
   cin >> acountnumber;
   unsigned int bankbalance;
   string fname = acountnumber + txt;
   ifstream fblc(fname);
   if (fblc)
      { while (!fblc.eof()) // Search till the end of the file
         {
            getline(fblc, infor);
            if (infor.rfind("Balance",0) == 0)  // pseudo in python startswith('Balance')
            {
               string s , delimiter = ":"; // delimiter distinguishes betn ahead and front of itself
               size_t pos = 0;
               while((pos = infor.find(delimiter)) != string::npos) // find the delimiter (pseudo split() in python)
               {
                  s = infor.substr(0, pos); // characters before the delimiter i.e: ':'
                  infor.erase(0,pos + delimiter.length()); // erase the front part and store back part in infor_variable refer once to cpp before using again.
               }
               bankbalance = stoi(infor); // int conversion
            }
         }}
   else { cout << "Unsuccesful please try again with valid account number.\n" ;}
   return bankbalance;
}

int balancextract(string acnom) 
{
   string infor;
   unsigned int bankbalance;
   string fname = acnom + txt;
   ifstream fblc(fname);
   if (fblc)
      { while (!fblc.eof()) // Search till the end of the file
         {
            getline(fblc, infor);
            if (infor.rfind("Balance",0) == 0)  // pseudo in python startswith('Balance')
            {
               string s , delimiter = ":"; // delimiter distinguishes betn ahead and front of itself
               size_t pos = 0;
               while((pos = infor.find(delimiter)) != string::npos) // find the delimiter (pseudo split() in python)
               {
                  s = infor.substr(0, pos); // characters before the delimiter i.e: ':'
                  infor.erase(0,pos + delimiter.length()); // erase the front part and store back part in infor_variable refer once to cpp before using again.
               }
               bankbalance = stoi(infor); // int conversion
            }
         }}
   else { cout << "Unsuccesful please try again with valid account number.\n" ;}
   return bankbalance;
}

int exit()
{
  char choice;
  cout << "\n\nDo you want to return to main menu? (y/n)" << endl;
  cin >> choice;
  if (choice == 'y')
  {
    return  1;
  }
  else 
    return  0;
}

void dtransactionupdate(int paisa, int debitmoney)
{
   string acountid, filename;
   string detail;
   cout << "Enter your account number again to confirm the transaction." << endl;
   cin >>  acountid;
   filename = acountid + txt;
   ofstream tfile(filename, ios::out | ios::app);
   if (tfile)
   {
      tfile << endl <<endl << "Account Number: " << acountid << endl;
      tfile << "Debited Money: Nrs" << debitmoney ;
      tfile << "Balance: Nrs" << paisa << endl;
      cout << "Transaction Successful! Your remaining balance is: Nrs" << paisa <<endl;
   }
   else { cout << "Transaction unsuccesful please try again with valid account number.\n" ;}
   
}

void ctransactionupdate(int paisa, int creditmoney)
{
   string acountid, filename;
   string detail;
   cout << "Enter your account number again to confirm the transaction." << endl;
   cin >>  acountid;
   filename = acountid + txt;
   ofstream tfile(filename, ios::out | ios::app);
   if (tfile)
   {
      tfile << endl <<endl << "Account Number: " << acountid << endl;
      tfile << "Credited Money: " << creditmoney <<endl;
      tfile << "Balance: " << paisa <<endl;
      cout << "Transaction Successful! Your remaining balance is: " << paisa <<endl;
   }
   else { cout << "Transaction unsuccesful please try again with valid account number.\n" ;}
}

void send_money()
{
   string sacnum, racnum, fname1, fname2;
   char option;
   unsigned int sbalance , rbalance, sfbalance ,rfbalance, tamount;
   cout << "Please Enter your(Sender) Account number: " << endl;
   cin >> sacnum;
   sbalance = balancextract(sacnum);
   cout << "Enter the reciever account number: " << endl;
   cin >> racnum;
   rbalance = balancextract(racnum);
   cout << "Enter the amount you want to send: Nrs";
   cin >> tamount;
   cout << "Do you really want to continue(y/n)?" <<endl;
   cin >> option;
   if (option == 'y' || 'Y')
   {
      if (tamount < sbalance) 
      {
         sfbalance = sbalance - tamount;
         rfbalance = rbalance + tamount;
         fname1 = sacnum + txt;
         ofstream sfile(fname1, ios::out | ios::app);
            if (sfile)
            {
               sfile<< endl <<endl << "Account Number: " << sacnum << endl;
               sfile << "Debited Money: Nrs" <<tamount <<endl;
               sfile << "Balance: Nrs" << sfbalance <<endl;
               fname2 = racnum + txt;
               ofstream rfile(fname2, ios::out | ios::app);
               if (rfile)
               {
                  rfile << endl<<endl << "Account Number: " << racnum << endl;
                  rfile << "Credited Money: Nrs" <<tamount <<endl;
                  rfile << "Balance: Nrs" << rfbalance <<endl;
               }
               else { cout << "Transaction unsuccesful please try again with valid account number.\n" ;}
            }
            else { cout << "Transaction unsuccesful please try again with valid account number.\n" ;}
         }
         else { cout << "Unsuccesful Insufficient balance! :-( " << endl; }
   cout << "Transaction Successful!" <<endl <<endl;
   }
}


int main()
{
  system("color B1");
  unsigned int fmoney , money, opt, dmoney, cmoney;
  initial:
  system("cls");
  customers c;
  cout << "       Welcome to this sample banking project!      " << endl;
  cout << " \n 1.New account opening. \n 2.view account statements."<<
  "\n 3.Debit Money.\n 4.Credit Money. \n 5.Send Money." << endl;
  cin >> opt;
  switch (opt)
  {
    {case 1:
      system("cls");
      c.accopen();
      c.datafile();
      if (exit() == 1)
        goto initial;
      break;
    }
    {case 2:
      system("cls");
      c.accountdisplay();
      if (exit() == 1)
        goto initial;
      break;
    }
    {case 3:
      system("cls");
      money = balancextract();
      tie(fmoney, dmoney) = debit(money);
      if (fmoney != 0)
         dtransactionupdate(fmoney, dmoney);
      if (exit() == 1)
        goto initial;
      break;
    }
    {case 4:
      money = balancextract();
      tie(fmoney, cmoney) = credit(money);
      ctransactionupdate(fmoney, cmoney);
      if (exit() == 1)
        goto initial;
      break;
    }
    {case 5:
      system("cls");
      send_money();
      if (exit() == 1)
        goto initial;
      break;
    }
    {default:
        cout << "\n\n\nCommand unsuccesful! Try using a valid option" <<endl;
        if (exit() == 1)
          goto initial;
        break;
    }
  }
  system("cls");
  cout << "Message! "<< endl;
  cout << "---------------------------------------------------------------------" <<endl;
  cout << "Now that, I have sent you the money buy the 2020 macbook cheers!.  :D" <<endl;
  cout << "---------------------------------------------------------------------" <<endl;
  return 0;
}


/* first programme made fully functional with no errors that i know of in 25th of october.
Today : 27th october.
update 1.0  1.View debited amount and credited amount in the statements file. 
            2.add up a new function to send money from one account to another account.
Finished : 27th october 12:40 PM
                                  finish                                            */