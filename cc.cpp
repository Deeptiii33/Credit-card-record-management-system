#include<stdio.h>
#include<cstring>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iostream>
using namespace std;

int no = 0;
char rec_ind[5], rec_cno[5],rec_ctype[55];
int rec_flag = 0;

struct record
{
	char cpin[5], ind[5];
	char name[30];
	char id[20];
	char cno[10];
	char ctype[100];
}rec[20];

struct index
{
	char id[20], ind[20];
}in[20], temp;

void sort_index()
{
	int i, j;
	for (i = 0;i < no - 1;i++)
		for (j = 0;j < no - i - 1;j++)
			if (strcmp(in[j].id, in[j + 1].id) > 0)
			{
				temp = in[j];
				in[j] = in[j + 1];
				in[j + 1] = temp;
			}
}

void retrive_record(char* ind)
{
	int flag = 0, i = 0;
	fstream f9;
	f9.open("record.txt", ios::in);
	while (!f9.eof())
	{
		f9.getline(rec[i].ind, 5, '|');
		f9.getline(rec[i].id, 20, '|');
		f9.getline(rec[i].name, 30, '|');
		f9.getline(rec[i].cpin, 5, '|');
		f9.getline(rec[i].cno, 10, '|');
		f9.getline(rec[i].ctype, 100, '\n');
		i++;
	}
	for (int j = 0;j < i;j++)
	{
		if (strcmp(rec[j].ind, ind) == 0)
		{
			strcpy(rec_ind, ind);
			rec_flag = 1;
			std::cout << "Record found\n";
			std::cout << rec[j].id << "|" << rec[j].name << "|" << rec[j].cpin << "|" << rec[j].cno << "|" << rec[j].ctype << "\n";
			return;
		}
	}

}


int search_index(char* id)
{
	int flag = 0;
	fstream ff;
	ff.open("index.txt", ios::in);
	int i = 0;
	while (!ff.eof())
	{
		ff.getline(in[i].id, 20, '|');
		ff.getline(in[i].ind, 20, '\n');
		i++;

	}
	for (int j = 0;j < i;j++)
	{
		if (strcmp(in[j].id, id) == 0)
		{
			retrive_record(in[j].ind);
			flag = 1;
		}
	}
	//cout <<"flag is"<< flag ;
	if (flag)
	{
		return 1;
	}
	else
		return -1;
}

int search_id(char* id, int j)
{
	int flag = 0;
	for (int i = 0;i < j;i++)
		if (strcmp(rec[i].id, id) == 0)
		{
			flag = 1;
			break;
		}
	if (flag)
		return 1;
	else
		return -1;
}




void delet(char* st_id)
{
	rec_flag = 0;
	int fr = 0;
	rec_flag = search_index(st_id);
	if (!rec_flag)
	{
		std::cout << "deletion failed record not found\n";
		return;
	}

	for (int i = 0;i < no;i++)
	{
		if (strcmp(rec[i].ind, rec_ind) == 0)
		{
			fr = i;
			break;
		}
	}
	for (int i = fr;i < no - 1;i++)
	{
		rec[i] = rec[i + 1];
		char str[3];
		sprintf(str, "%d", i);
		strcpy(rec[i].ind, str);
	}
	no--;

	fstream f1, f2, f3;
	f1.open("record.txt", ios::out);
	f2.open("index.txt", ios::out);
	f3.open("no.txt", ios::out);
	f3 << no;
	f3.close();

	for (int i = 0;i < no;i++)
	{

		strcpy(in[i].id, rec[i].id);
		strcpy(in[i].ind, rec[i].ind);

	}
	sort_index();

	for (int i = 0;i < no;i++)
	{
		f1 << rec[i].ind << "|" << rec[i].id << "|" << rec[i].name << "|" << rec[i].cpin << "|" << rec[i].cno << "|" << rec[i].ctype << "\n";
		f2 << in[i].id << "|" << in[i].ind << "\n";

	}

	f1.close();
	f2.close();

	std::cout << "deletion successful\n";
}

int owner_authen() {
	char o_username[20], o_password[20];
	char o_user[20] = "admin", o_pass[20] = "abcd";
	cout << endl << endl;
	cout.width(25);
	cout << "Enter Username and Password\n" << "------------------------------------------------------------------------------------\n";
	cout << endl << "Username: ";
	cin >> o_username;
	cout << "Password: ";
	cin >> o_password;
	cout << "------------------------------------------------------------------------------------\n";
	if (strcmp(o_username, o_user) == 0 && strcmp(o_password, o_pass) == 0)
		return 1;
	else
		return 0;
}

void ret_cno(char* cno)
{

	int flag = 0;
	for (int i = 0;i < no;i++)
	{
		if (strcmp(rec[i].cno, cno) == 0)
		{
			strcpy(rec_cno, cno);
			rec_flag = 1;
			std::cout << "Record found\n";
			std::cout << rec[i].id << "|" << rec[i].name << "|" << rec[i].cpin << "|" << rec[i].cno << "|" << rec[i].ctype << "\n";

		}
	}

}

void ret_ctype(char* ctype)
{

	int flag = 0;
	for (int i = 0;i < no;i++)
	{
		if (strcmp(rec[i].ctype, ctype) == 0)
		{
			strcpy(rec_ctype, ctype);
			rec_flag = 1;
			std::cout << "Record found\n";
			std::cout << rec[i].id << "|" << rec[i].name << "|" << rec[i].cpin << "|" << rec[i].cno << "|" << rec[i].ctype << "\n";

		}
	}

}



int main()
{
	fstream file1, file2, file4;

	cout << "---------------------------------------------------------------------------------------------------------------------";
	std::cout << "\n\t\t\t \t    CREDITCARD RECORD MANAGEMENT SYSTEM   \n";
	cout << "---------------------------------------------------------------------------------------------------------------------";


	int ch;
	char ind[5], st_id[20], name[20], cpin[5], cno[10], ctype[30], id[10];
	int i = 0, user;
label:
	
	cout << "\n Enter user : 1.Administrator\n";
	std::cin >> user;
	switch (user) {
	case 1: {
		int check;
		check = owner_authen();
		if (check == 1)
		{
			cout << "Welcome Administrator\n" << "------------------------------------------------------------------------------------\n";
			while (1)
			{
				std::cout << " \n \t 1.Add Record\n \t 2.Search Record \n \t 3.Delete Record \n \t 4.Display Record  \n \t 5.Update Record \n \t 6.Cardtype based search \n \t 7.Card number based search \n  \t 8.exit \n";
				cin >> ch;
				switch (ch)
				{
					//add
				case 1:
				{


					file1.open("record.txt", ios::app | ios::out);

					int n;
					cout << "\n Enter no of credit card \t";
					cin >> n;
					cout << " Enter their details \n ";
					file4.open("no.txt", ios::in);
					file4 >> no;
					for (i = no;i < no + n;i++)
					{
						cout << "\n Enter " << i + 1 << " creditcard \n";

						cout << " \n Enter unique key(cvv) \t";
						cin >> rec[i].id;
						std::cout << "\n Enter the card holder name: \t";
						cin >> rec[i].name;
						std::cout << "\n Enter creditcard number: \t";
						cin >> rec[i].cno;
						std::cout << "\n Enter creditcard pin \t";
						cin >> rec[i].cpin;
						std::cout << "\n Enter cardtype name \t";
						cin >> rec[i].ctype;

						int q = search_id(rec[i].id, i);
						file1 << i << "|" << rec[i].id << "|" << rec[i].name << "|" << rec[i].cpin << "|" << rec[i].cno << "|" << rec[i].ctype << "\n";
					}
					file1.close();
					no = no + n;
					fstream file1, file3, file2;
					file3.open("no.txt", ios::out);
					file3 << no;
					file3.close();
					file2.open("index.txt", ios::out);
					file1.open("record.txt", ios::in);
					for (i = 0;i < no;i++)
					{
						file1.getline(ind, 5, '|');
						file1.getline(id, 20, '|');
						file1.getline(name, 30, '|');
						file1.getline(cpin, 10, '|');
						file1.getline(cno, 50, '|');
						file1.getline(ctype, 30, '\n');
						strcpy(rec[i].ind, ind);

						strcpy(in[i].id, id);

						strcpy(in[i].ind, ind);
					}

					sort_index();
					std::cout << "\n After sorting,index file contents are:\n";
					for (i = 0;i < no;i++)
						std::cout << in[i].id << " " << in[i].ind << endl;
					for (i = 0;i < no;i++)
					{
						file2 << in[i].id << "|" << in[i].ind << "\n";
					}
					file1.close();
					file2.close();

					break;

				}

				//search

				case 2:
				{
					fstream f4;
					f4.open("no.txt", ios::in);
					f4 >> no;
					//cout << no;
					cout << " \n Enter creditcard cvv whose details are to be displayed:  \t";
					cin >> id;
					int q = search_index(id);
					if (q == 1)
						cout << "\n Successful search \n";
					else
						cout << "\n Unsuccessful search \t";

					break;
				}
				
				//deletion
				case 3: {
					cout << "\n Enter creditcard cvv to be deleted \n ";
					cin >> st_id;
					delet(st_id);
					break;
				}
				
				//display
				case 4:
				{
					fstream file1;
					file1.open("record.txt", ios::in);
					std::cout << "ID \t NAME\t CARDPIN \t CARDNO \t CARDTYPE \n";

					while (!file1.eof())
					{
						file1.getline(ind, 5, '|');
						file1.getline(id, 20, '|');
						file1.getline(name, 30, '|');
						file1.getline(cpin, 10, '|');
						file1.getline(cno, 50, '|');
						file1.getline(ctype, 30, '\n');

						cout << id << "\t" << name << "\t" << cpin << "\t    " << cno << "\t \t   " << ctype << "\n" << endl;

					}
					file1.close();
					break;

				}
				//exit
				case 8:
				{
					cout << "\n Ending program...";
					goto label;

				}
				//search card no
				case 7:
				{
					fstream f4;
					f4.open("no.txt", ios::in);
					f4 >> no;
					//cout << no;
					cout << "Enter the Card no to be searched upon: \t";
					cin >> cno;
					ret_cno(cno);
					break;

				}
				//search card type
				case 6:
				{
					fstream f4;
					f4.open("no.txt", ios::in);
					f4 >> no;
					//cout << no;
					cout << "Enter the Cardtype to be searched upon: \t";
					cin >> ctype;
					ret_ctype(ctype);
					break;

				}
				//update
				case 5:
				{

					rec_flag = 0;
					int fr = 0;
					int ch;
					cout << "\n Enter creditcard cvv to be updated : \t";
					cin >> st_id;
					rec_flag = search_index(st_id);
					if (rec_flag == -1)
					{
						std::cout << "\n Failed record not found";
						break;
					}

					for (int i = 0;i < no;i++)
					{
						if (strcmp(rec[i].ind, rec_ind) == 0)
						{
							std::cout << "\nThe old values of the Creditcard record  are ";
							std::cout << "\n CVV            : " << rec[i].id;
							std::cout << "\n Name           : " << rec[i].name;
							std::cout << "\n Creditcard pin : " << rec[i].cpin;
							std::cout << "\n Card  number   : " << rec[i].cno;
							std::cout << "\n Creditcard type: " << rec[i].ctype;
							
							std::cout << "\n1:CVV 2:Name 3:Cardpin 4:Card number 5:Card type \n Enter your choice to modify \n";
							cin>>ch;
							switch(ch)
							{
								case 1: std::cout << "\nCVV  : ";  cin >> rec[i].id;
										break;
								case 2: std::cout << "\nName : ";  cin >> rec[i].name;
										break;
								case 3: std::cout << "\nCardpin :";  cin >> rec[i].cpin;
										break;
								case 4: std::cout << "\nCardno  : ";  cin >> rec[i].cno;
										break;
								case 5: std::cout << "\n cardtype  : "; cin >> rec[i].ctype;
										break;
							}
							
							/*std::cout << "\nEnter the new values \n";
							std::cout << "\nCVV  : ";  cin >> rec[i].id;
							std::cout << "\nname : ";  cin >> rec[i].name;
							std::cout << "\ncardpin :";  cin >> rec[i].cpin;
							std::cout << "\ncardno  : ";  cin >> rec[i].cno;
							std::cout << "\n cardtype  : "; cin >> rec[i].ctype;
							break;*/
						}
					}

					fstream f1, f2;
					f1.open("record.txt", ios::out);
					f2.open("index.txt", ios::out);

					for (int i = 0;i < no;i++)
					{

						strcpy(in[i].id, rec[i].id);
						strcpy(in[i].ind, rec[i].ind);

					}
					sort_index();
					for (int i = 0;i < no;i++)
					{
						f1 << rec[i].ind << "|" << rec[i].id << "|" << rec[i].name << "|" << rec[i].cpin << "|" << rec[i].cno << "|" << rec[i].ctype << "\n";
						f2 << in[i].id << "|" << in[i].ind << "\n";

					}

					f1.close();
					f2.close();
					std::cout << "\n Updated successfully\n";
				}
				}
			}
		}
		else {

			cout << "\n Invalid login";
		}
		break;
	}

	}

	return 0;
}
