#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>
#include<process.h>
#include<fstream.h>
#include<ctype.h>


char USERNAME[25];
char PASSWORD[25];
ifstream r;
ofstream w;

void border();
void centerText(char* string, int color=WHITE, int newline = 1, int extraSpace = 0);
void getPass(char* pass);
void displayMessage(char* message, int color);
void loading(int time);
int polish(char* p);

int numlen(long num);

class Book
{
	int id;
	char name[50];
	char author[50];
	char genre[50];
	float salerate;
	float purchaserate;
	int stock;

	public:

	void add();
	void rem();
	void update();
	void display(int);
	void display1();
	void search();
	int getId()
	{
		return id;
	}
	int getStock()
	{
		return stock;
	}
	void addStock(int m = 1)
	{
		if(m)
			stock--;
		else
			stock++;
	}
}b;

struct User
{
	char username[50];
	char password[50];
	char name[50];
	int age;
	long phone;
	int booksTaken[50];
}u;

void account();
void login();
void createAcc();
void adminPanel();
void adminLogin();
void guest();

void main()
{
	int choice;

	mainmenu:

	clrscr();
	border();
	cout<<endl<<endl<<endl;
	centerText("SUMA LIBRARY", YELLOW);
	cout<<endl<<endl;
	centerText("1.GUEST", GREEN);
	centerText("2.MEMBERS LOGIN", GREEN);
	centerText("3.CREATE MEMBERSHIP", GREEN);
	centerText("4.ADMIN LOGIN", GREEN);
	centerText("5.EXIT", GREEN);

	centerText("enter your choice>>", LIGHTBLUE, 0);
	cin>>choice;
	switch(choice)
	{
		case 1:
			guest();
			goto mainmenu;
		case 2:
			login();
			goto mainmenu;
		case 3:
			createAcc();
			goto mainmenu;
		case 4:
			adminLogin();
			goto mainmenu;
		case 5:
			clrscr();
			border();
			cout<<endl<<endl;
			centerText("THANK YOU", YELLOW + BLINK);
			cout<<endl<<endl<<endl;
			centerText("CREATED BY", GREEN);
			cout<<endl<<endl;
			centerText("*** -------- ***", LIGHTBLUE);
			sleep(5);
			exit(0);
		default:
			displayMessage("Enter a valid choice", RED);
			sleep(2);
			goto mainmenu;
	}
}

void border()
{
	int x, y;
	clrscr();
	x = wherex();
	y = wherey();

	textcolor(LIGHTRED);
	cout<<"  ";
	for(int i=0;i<=76;i++)
		cprintf("=");
	cout<<endl;
	for(i=0;i<23;i++)
	{
		cout<<"  ";
		for(int j=1;j<=1;j++)
			cprintf("|");
		for(j = 0;j<=74;j++)
			cout<<" ";
		cprintf("|");
		cout<<endl;
	}
	cout<<"  ";
	for(i=0;i<=76;i++)
		cprintf("=");

	gotoxy(x, y);
	textcolor(WHITE);
}

void centerText(char* string, int color, int newline, int extraSpace)
{
	int x = wherex();
	int y = wherey();
	textcolor(color);
	if(!extraSpace)
		for(int i=0;i<(80 - strlen(string))/2;i++)
			gotoxy(x++, y);
	else
		for(int i=0;i<(80 - (strlen(string) + 15))/2;i++)
			gotoxy(x++, y);
	cprintf(string);
	if(newline)
		cout<<endl<<endl;
	textcolor(WHITE);
}

void getPass(char* pass)
{
	char* temp = pass;
	textcolor(LIGHTGREEN);
	char ch;
	int x, y;
	while(1)
	{
		ch = getch();
		if((int)ch == 13)
		{
			*pass = '\0';
			break;
		}
		if((int)ch == 8)
		{
			if(pass != temp)
			{
				pass--;
				x = wherex();
				y = wherey();
				gotoxy(x-1, y);
				cout<<" ";
				gotoxy(x-1, y);
			}
			continue;
		}
		*pass = ch;
		cprintf("*");
		pass++;
	}
	textcolor(WHITE);
}

void displayMessage(char* message, int color)
{
	int x = wherex();
	int y = wherey();
	gotoxy(1,23);
	centerText(message, color);
	gotoxy(x, y);
}

void loading(int time)
{
	int center = ((80 - (time + 2))/2) + 1;
	int y = wherey();
	gotoxy(center, y+2);
	cout<<"|";
	int x = wherex();
	y = wherey();
	for(int j=0;j<time;j++)
		cout<<" ";
	cout<<"|";
	gotoxy(x, y);
	textcolor(YELLOW);
	for(int i=0;i<time;i++)
	{
		cprintf("=");
		sleep(1);
	}
}

int polish(char* p)
{
	char* temp2 = p;
	p = &p[strlen(p)-1];
	while((int)*p == 32)
	{
		*p = '\0';
		p--;
	}
	p = temp2;
	strrev(p);
	p = &p[strlen(p)-1];
	while((int)*p == 32)
	{
		*p = '\0';
		p--;
	}
	p = temp2;
	strrev(p);

	return 0;
}

int numlen(long num)
{
	int length = 0;
	while(num != 0)
	{
		num /= 10;
		length++;
	}
	return length;
}

void Book::add()
{
	char ch;
	int d;

	add:

	clrscr();
	border();
	cout<<endl;
	centerText("ADD A NEW BOOK", YELLOW);
	cout<<endl<<endl;
	centerText("Book ID: ", WHITE, 0, 1);
	cin>>id;
	cout<<endl;
	d = id;
	r.open("bookinfo.dat", ios::binary | ios::in);
	if(r)
	{
		r.seekg(0);
		while(!r.eof())
		{
			r.read((char*)this, sizeof(Book));
			if(r.eof())
				break;
			if(d == this->id)
			{
				displayMessage("This id is already given to another book!", RED);
				sleep(2);
				r.close();
				goto add;
			}
		}
		r.close();
	}
	this->id = d;
	centerText("Book Name: ", WHITE, 0, 1);
	gets(name);
	if(!strlen(name) == 0)
		polish(name);
	else
	{
		displayMessage("Please enter a valid name!", RED);
		sleep(2);
		goto add;
	}
	cout<<endl;
	centerText("Book Author: ", WHITE, 0, 1);
	gets(author);
	if(!strlen(author) == 0)
		polish(author);
	else
	{
		displayMessage("Please enter a valid author name!", RED);
		sleep(2);
		goto add;
	}
	cout<<endl;
	centerText("Book Genre: ", WHITE, 0, 1);
	gets(genre);
	if(!strlen(genre) == 0)
		polish(genre);
	else
	{
		displayMessage("Please enter a valid genre!", RED);
		sleep(2);
		goto add;
	}
	cout<<endl;
	centerText("Sale Rate: ", WHITE, 0, 1);
	cin>>salerate;
	cout<<endl;
	centerText("Purchase Rate: ", WHITE, 0, 1);
	cin>>purchaserate;
	cout<<endl;
	centerText("Stock: ", WHITE, 0, 1);
	cin>>stock;
	cout<<endl;
	displayMessage("Press any key to proceed.", GREEN);
	getch();

	w.open("bookinfo.dat", ios::binary | ios::app);
	w.write((char*)this, sizeof(Book));
	w.close();

	clrscr();
	border();
	cout<<endl;
	centerText("BOOK ADDEDD SUCCESSFULLY", GREEN);
	cout<<endl<<endl;
	centerText("Want to add more books? ", LIGHTBLUE, 0);
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
		goto add;
}

void Book::rem()
{
	int d;
	int flag = 0;

	remove:

	clrscr();
	border();
	cout<<endl;
	centerText("REMOVE A BOOK", YELLOW);
	cout<<endl<<endl;
	centerText("Enter the id of the book to remove: ", LIGHTBLUE, 0);
	cin>>d;
	ofstream temp;
	temp.open("temp.dat", ios::binary | ios::app);
	r.open("bookinfo.dat", ios::binary | ios::in);
	if(r)
	{
		while(!r.eof())
		{
			r.read((char*)this, sizeof(Book));
			if(r.eof())
				break;
			if(this->id != d)
				temp.write((char*)this, sizeof(Book));
			else
				flag = 1;
		}
		r.close();
		temp.close();
		remove("bookinfo.dat");
		rename("temp.dat", "bookinfo.dat");
		clrscr();
		if(flag)
		{
			centerText("BOOK REMOVED SUCCESSFULLY", GREEN);
			displayMessage("Press any key.", LIGHTGREEN);
		}
		else
		{
			centerText("BOOK NOT FOUND, PLEASE CHECK THE ID PROVIDED", RED);
			displayMessage("Press any key.", LIGHTGREEN);
		}
		getch();
	}
	else
	{
		clrscr();
		border();
		cout<<endl;
		temp.close();
		remove("temp.dat");
		centerText("NO BOOKS ARE AVAILABLE TO REMOVE", RED);
		displayMessage("Press any key", LIGHTGREEN);
		getch();
	}
}

void Book::update()
{
	int flag = 0;
	int d;
	int pos;
	char ch;

	update:

	clrscr();
	cout<<endl;
	centerText("UPDATE A BOOK", GREEN);
	cout<<endl<<endl;
	centerText("Enter the id of the book to be updated: ", WHITE, 0, 1);
	cin>>d;
	r.open("bookinfo.dat", ios::binary | ios::in);
	if(r)
	{
		r.seekg(0);
		while(!r.eof())
		{
			r.read((char*)this, sizeof(Book));
			if(r.eof())
				break;
			if(this->id == d)
			{
				pos = r.tellg() - sizeof(Book);
				flag = 1;
				break;
			}
		}
		r.close();
	}
	if(flag)
	{
		this->id = d;
		clrscr();
		border();
		cout<<endl;
		centerText("ENTER NEW DETAILS", YELLOW);
		cout<<endl<<endl;
		centerText("Book Name: ", WHITE, 0, 1);
		gets(name);
		polish(name);
		cout<<endl;
		centerText("Book Author: ", WHITE, 0, 1);
		gets(author);
		polish(author);
		cout<<endl;
		centerText("Book Genre: ", WHITE, 0, 1);
		gets(genre);
		polish(genre);
		cout<<endl;
		centerText("Sale Rate: ", WHITE, 0, 1);
		cin>>salerate;
		cout<<endl;
		centerText("Purchase Rate: ", WHITE, 0, 1);
		cin>>purchaserate;
		cout<<endl;
		centerText("Enter Stock: ", WHITE, 0, 1);
		cin>>stock;
		cout<<endl;
		displayMessage("Press any key to proceed.", GREEN);
		getch();

		w.open("bookinfo.dat", ios::binary | ios::ate);
		w.seekp(pos);
		w.write((char*)this, sizeof(Book));
		w.close();

		clrscr();
		border();
		cout<<endl;
		centerText("BOOK UPDATED SUCCESSFULYY", GREEN);
		displayMessage("Please wait...", LIGHTGREEN);
		sleep(2);
		cout<<endl<<endl;
		clrscr();
		centerText("Want to update more books? ", LIGHTBLUE, 0);
		cin>>ch;
		if(ch == 'y' || ch == 'Y')
			goto update;
	}
	else
	{
		clrscr();
		border();
		cout<<endl;
		centerText("PLEASE CHECK THE ID YOU HAVE PROVIDED!", RED);
		displayMessage("Press any key.", LIGHTGREEN);
		getch();
	}
}

void Book::display(int getc = 1)
{
	clrscr();
	border();
	cout<<endl;
	r.open("bookinfo.dat", ios::binary | ios::in);
	if(r)
	{
		r.seekg(0);
		gotoxy(wherex() + 8, wherey());
		cout<<"ID  NAME  AUTHOR  GENRE  SALERATE  PURCHASERATE  STOCK"<<endl<<endl;
		while(!r.eof())
		{
			r.read((char*)this, sizeof(Book));
			if(strcmp(this->name, "") == 0)
			{
				clrscr();
				centerText("No books to display", RED);
				displayMessage("Press any key to go back", LIGHTGREEN);
				getch();
				return;
			}
			if(r.eof())
				break;
			gotoxy(wherex() + 8, wherey());
			cout<<this->id<<"    ";
			cout<<this->name<<"    ";
			cout<<this->author<<"    ";
			cout<<this->genre<<"    ";
			cout<<this->salerate<<"    ";
			cout<<this->purchaserate<<"    ";
			cout<<this->stock<<"    ";
			cout<<endl;
		}
		r.close();
	}
	else
	{
		clrscr();
		border();
		cout<<endl;
		centerText("No books to display!", RED);
	}
	if(getc)
	{
		displayMessage("Press any key to go back", LIGHTGREEN);
		getch();
	}
}

void Book::display1()
{
	gotoxy(wherex() + 4, wherey());
	cout<<id<<"  ";
	cout<<name<<"  ";
	cout<<author<<"  ";
	cout<<genre<<"  ";
	cout<<salerate<<"  ";
	cout<<purchaserate<<"  ";
	cout<<stock<<endl;
}

void Book::search()
{
	int choice;
	int flag = 0;

	search:

	clrscr();
	border();
	cout<<endl;
	centerText("SEARCH A BOOK", YELLOW);
	cout<<endl<<endl;
	centerText("1.Search by book name");
	centerText("2.Search by author name");
	centerText("3.Back");
	cout<<endl;
	centerText("enter your choice>>", LIGHTBLUE, 0, 1);
	cin>>choice;

	switch(choice)
	{
		case 1:
			char bname[30];

			searchn:

			clrscr();
			border();
			cout<<endl;
			centerText("SEARCH BY BOOK NAME", YELLOW);
			cout<<endl<<endl;
			centerText("Enter book name: ", WHITE, 0, 1);
			gets(bname);
			if(strlen(bname) != 0)
				polish(bname);
			else
			{
				displayMessage("Enter a valid name!", RED);
				sleep(2);
				goto searchn;
			}
			r.open("bookinfo.dat", ios::binary | ios::in);
			if(r)
			{
				r.seekg(0);
				clrscr();
				border();
				cout<<endl;
				centerText("SEARCH RESULTS", YELLOW);
				cout<<endl<<endl;
				gotoxy(wherex() + 8, wherey());
				cout<<"ID  NAME  AUTHOR  GENRE  SALERATE  PURCHASERATE  STOCK"<<endl<<endl;
				while(!r.eof())
				{
					r.read((char*)this, sizeof(Book));
					if(r.eof())
						break;
					if(strcmp(this->name, bname) == 0)
					{
						flag = 1;
						gotoxy(wherex() + 8, wherey());
						cout<<this->id<<"    ";
						cout<<this->name<<"    ";
						cout<<this->author<<"    ";
						cout<<this->genre<<"    ";
						cout<<this->salerate<<"    ";
						cout<<this->purchaserate<<"    ";
						cout<<this->stock<<"    ";
						cout<<endl;
					}
				}
				r.close();
				if(!flag)
				{
					resultsn:

					clrscr();
					border();
					cout<<endl;
					centerText("No Results Found", RED);
					cout<<endl<<endl;
					centerText("1.Search another book");
					cout<<endl;
					centerText("2.Go Back");
					cout<<endl;
					centerText("enter your choice>>", LIGHTBLUE, 0);
					cin>>choice;
					if(choice == 1)
						goto searchn;
					else if(choice == 2)
						goto search;
					else
					{
						displayMessage("Enter valid choice", RED);
						sleep(2);
						goto resultsn;
					}
				}
				else
				{
					displayMessage("Press any key to go back", LIGHTGREEN);
					getch();
				}
			}
			else
			{
				clrscr();
				border();
				cout<<endl;
				centerText("No books are available to show!", RED);
				displayMessage("Press any key to go back", LIGHTGREEN);
				getch();
				return;
			}
			break;

		case 2:
			char aname[30];

			searcha:

			clrscr();
			border();
			cout<<endl;
			centerText("SEARCH BY AUTHOR NAME", YELLOW);
			cout<<endl<<endl;
			centerText("Enter author name: ", WHITE, 0, 1);
			gets(aname);
			if(strlen(aname) != 0)
				polish(aname);
			else
			{
				displayMessage("Enter a valid name!", RED);
				sleep(2);
				goto searcha;
			}
			r.open("bookinfo.dat", ios::binary | ios::in);
			if(r)
			{
				r.seekg(0);
				clrscr();
				border();
				cout<<endl;
				centerText("SEARCH RESULTS", YELLOW);
				cout<<endl<<endl;
				gotoxy(wherex() + 8, wherey());
				cout<<"ID  NAME  AUTHOR  GENRE  SALERATE  PURCHASERATE  STOCK"<<endl<<endl;
				while(!r.eof())
				{
					r.read((char*)this, sizeof(Book));
					if(r.eof())
						break;
					if(strcmp(this->author, aname) == 0)
					{
						flag = 1;
						gotoxy(wherex() + 8, wherey());
						cout<<this->id<<"    ";
						cout<<this->name<<"    ";
						cout<<this->author<<"    ";
						cout<<this->genre<<"    ";
						cout<<this->salerate<<"    ";
						cout<<this->purchaserate<<"    ";
						cout<<this->stock<<"    ";
						cout<<endl;
					}
				}
				r.close();
				if(!flag)
				{
					resultsa:

					clrscr();
					border();
					cout<<endl;
					centerText("No Results Found", RED);
					cout<<endl<<endl;
					centerText("1.Search another book");
					cout<<endl;
					centerText("2.Go Back");
					cout<<endl;
					centerText("enter your choice>>", LIGHTBLUE, 0);
					cin>>choice;
					if(choice == 1)
						goto searcha;
					else if(choice == 2)
						goto search;
					else
					{
						displayMessage("Enter a valid choice", RED);
						goto resultsa;
					}
				}
				else
				{
					displayMessage("Press any key to go back", LIGHTGREEN);
					getch();
				}
			}
			else
			{
				clrscr();
				border();
				cout<<endl;
				centerText("No books are available to show!", RED);
				displayMessage("Press any key to go back", LIGHTGREEN);
				getch();
				return;
			}
			break;

		case 3:
			return;

		default:
			displayMessage("Enter a valid choice!", RED);
			sleep(2);
			goto search;
	}
}

void account()
{
	int choice;
	int bid;
	int flag = 0;
	int pos;
	int userPos;
	char greet[30] = "WELCOME ";

	r.open("users.dat", ios::binary | ios::in);
	if(r)
	{
		r.seekg(0);
		while(!r.eof())
		{
			r.read((char*)&u, sizeof(User));
			if(r.eof())
				break;
			if(strcmpi(u.username, USERNAME) == 0)
			{
				userPos = r.tellg() - sizeof(User);
				break;
			}
		}
		r.close();
	}
	else
		return;

	strcat(greet, u.name);

	account:

	clrscr();
	border();
	cout<<endl;
	centerText(greet, YELLOW);
	cout<<endl<<endl;
	centerText("1.Display book details", GREEN);
	centerText("2.Search book", GREEN);
	centerText("3.Take book", GREEN);
	centerText("4.My profile", GREEN);
	centerText("5.Log out", GREEN);
	cout<<endl;
	centerText("enter your choice>>", LIGHTBLUE, 0);
	cin>>choice;

	switch(choice)
	{
		case 1:
			b.display();
			goto account;

		case 2:
			b.search();
			goto account;

		case 3:
			clrscr();
			border();
			cout<<endl;
			centerText("Take a Book", YELLOW);
			cout<<endl<<endl;
			b.display(0);
			cout<<endl<<endl;
			centerText("enter the book id>>", LIGHTBLUE, 0);
			cin>>bid;
			for(int z=0;z<10;z++)
			{
				if(bid == u.booksTaken[z])
				{
					displayMessage("You have already taken this book", RED);
					sleep(3);
					goto account;
				}
			}
			r.open("bookinfo.dat", ios::binary | ios::in);
			if(r)
			{
				r.seekg(0);
				while(!r.eof())
				{
					r.read((char*)&b, sizeof(Book));
					if(r.eof())
						break;

					if(b.getId() == bid)
					{
						if(b.getStock() <= 0)
						{
							clrscr();
							border();
							cout<<endl;
							centerText("That book is currently out of stock", RED);
							displayMessage("Press any key to go back", LIGHTGREEN);
							getch();
							r.close();
							goto account;
						}
						else
						{
							flag = 1;
							pos = r.tellg() - sizeof(Book);
							b.addStock();
							for(int i=0;i<10;i++)
							{
								if(u.booksTaken[i] == 0)
								{
									u.booksTaken[i] = bid;
									break;
								}
							}
							r.close();
							break;
						}
					}
				}
				if(flag)
				{
					w.open("bookinfo.dat", ios::binary | ios::ate);
					w.seekp(pos);
					w.write((char*)&b, sizeof(Book));
					w.close();
					w.open("users.dat", ios::binary, ios::ate);
					w.seekp(userPos);
					w.write((char*)&u, sizeof(User));
					w.close();
					clrscr();
					centerText("BOOK PURCHASED", GREEN);
				}
				else
				{
					clrscr();
					border();
					cout<<endl;
					centerText("Please enter a valid book id from the given list", RED);
				}
				displayMessage("Press any key to go back", LIGHTGREEN);
				r.close();
				getch();
				goto account;
			}
			else
			{
				clrscr();
				border();
				cout<<endl;
				centerText("No books to display", RED);
				displayMessage("Press any key to go back", LIGHTGREEN);
				getch();
				goto account;
			}
		case 4:
			clrscr();
			border();
			cout<<endl;
			centerText("My Profile", YELLOW);
			cout<<endl<<endl;
			gotoxy(wherex() + 16, wherey());
			cout<<"Name: "<<u.name<<endl;
			gotoxy(wherex() + 16, wherey());
			cout<<"Age: "<<u.age<<endl;
			gotoxy(wherex() + 16, wherey());
			cout<<"Phone: "<<u.phone<<endl;
			gotoxy(wherex() + 16, wherey());
			cout<<"Username: "<<u.username<<endl<<endl;
			gotoxy(wherex() + 4, wherey());
			cout<<"Books Taken: "<<endl;
			r.open("bookinfo.dat", ios::binary | ios::in);
			if(r)
			{
				gotoxy(wherex() + 4, wherey());
				cout<<"ID  NAME  AUTHOR  GENRE  SALERATE  PURCHASERATE  STOCK"<<endl<<endl;
				r.seekg(0);
				for(int i=0;u.booksTaken[i]!=0;i++)
				{
					while(!r.eof())
					{
						r.read((char*)&b, sizeof(b));
						if(r.eof())
							break;
						if(b.getId() == u.booksTaken[i])
						{
							flag = 1;
							b.display1();
							r.seekg(0);
							break;
						}
					}
				}
				r.close();
				if(!flag)
				{
					gotoxy(wherex() + 16, wherey());
					cout<<"***No books taken***"<<endl;
				}
				else
					flag = 0;
			}
			else
			{
				gotoxy(wherex() + 16, wherey());
				cout<<"***No books taken***"<<endl;
			}
			displayMessage("Press any key to go back", LIGHTGREEN);
			getch();
			goto account;
		case 5:
			clrscr();
			border();
			cout<<endl;
			strcpy(greet, "See you soon ");
			strcat(greet, u.name);
			centerText(greet, YELLOW);
			strcpy(USERNAME, "");
			sleep(3);
			return;
		default:
			displayMessage("Enter a valid choice!", RED);
			sleep(2);
			goto account;
	}
}

void login()
{
	char username[50];
	char password[50];
	int flag = 0;
	int chances = 3;

	login:

	clrscr();
	border();
	cout<<endl;
	if(chances == 0)
	{
		centerText("Please try again later.", RED);
		sleep(2);
		return;
	}
	centerText("LOGIN", YELLOW);
	cout<<endl<<endl;
	centerText("Username: ", GREEN, 0, 1);
	gets(username);
	if(strlen(username) != 0)
		polish(username);
	else
	{
		displayMessage("Enter a valid email", RED);
		goto login;
	}
	cout<<endl;
	centerText("Password: ", GREEN, 0, 1);
	getPass(password);

	r.open("users.dat", ios::binary | ios::in);
	if(r)
	{
		r.seekg(0);
		while(!r.eof())
		{
			r.read((char*)&u, sizeof(User));
			if(r.eof())
				break;
			if(strcmpi(u.username, username) == 0 && strcmp(u.password, password) == 0)
			{
				flag = 1;
				strcpy(USERNAME, username);
				strcpy(PASSWORD, password);
				r.close();
				account();
				return;
			}
		}
		r.close();
	}
	if(!flag)
	{
		displayMessage("Invalid username or password!", RED);
		chances--;
		sleep(2);
		goto login;
	}
}

void createAcc()
{
	char name[50];
	int age;
	long phone;
	char username[50];
	char password[50];
	int chances = 3;
	int flag = 1;

	reg:

	clrscr();
	border();
	cout<<endl;
	if(chances == 0)
	{
		centerText("TRY AGAIN LATER", RED);
		sleep(2);
		return;
	}
	centerText("CREATE AN ACCOUNT", YELLOW);
	cout<<endl<<endl;
	centerText("Name: ", GREEN, 0, 1);
	gets(name);
	if(strlen(name) != 0)
		polish(name);
	else
	{
		displayMessage("Enter a valid name!", RED);
		sleep(2);
		goto reg;
	}
	cout<<endl;
	centerText("Age: ", GREEN, 0, 1);
	cin>>age;
	if(age <= 10)
	{
		displayMessage("You are not eligible to create an account!", RED);
		sleep(3);
		return;
	}
	cout<<endl;
	centerText("Phone: ", GREEN, 0, 1);
	cin>>phone;
	if(numlen(phone) != 10 && numlen(phone) != 7)
	{
		displayMessage("Enter a valid phone number!", RED);
		sleep(2);
		goto reg;
	}
	cout<<endl;
	centerText("Username: ", GREEN, 0, 1);
	gets(username);
	if(strlen(username) != 0)
		polish(username);
	else
	{
		displayMessage("Enter a valid username!", RED);
		sleep(2);
		goto reg;
	}
	cout<<endl;
	centerText("Password: ", GREEN, 0, 1);
	getPass(password);

	r.open("users.dat", ios::binary | ios::in);
	if(r)
	{
		r.seekg(0);
		while(!r.eof())
		{
			r.read((char*)&u, sizeof(User));
			if(r.eof())
				break;
			if(strcmpi(u.username, username) == 0)
			{
				flag = 0;
				displayMessage("Username already taken!", RED);
				sleep(2);
				chances--;
				goto reg;
			}
		}
		r.close();
	}
	if(flag)
	{
		strcpy(u.name, name);
		u.age = age;
		u.phone = phone;
		strcpy(u.username, username);
		strcpy(u.password, password);
		for(int i=0;i<10;i++)
			u.booksTaken[i] = 0;
		strcpy(USERNAME, username);
		strcpy(PASSWORD, password);
		w.open("users.dat", ios::binary | ios::app);
		w.write((char*)&u, sizeof(User));
		w.close();
		displayMessage("You are successfully registerd.", LIGHTGREEN);
		sleep(2);
		strcpy(USERNAME, username);
		strcpy(PASSWORD, password);
		account();
		return;
	}
}

void adminPanel()
{
	int choice;
	int bid;
	int pos;
	char username[50];
	char name[50];
	char ch;
	int flag = 0;
	int flag2 = 0;
	int flag3 = 0;
	int flag4 = 0;

	adminpanel:

	clrscr();
	border();
	cout<<endl;
	centerText("ADMIN PANEL", YELLOW);
	cout<<endl<<endl;
	centerText("1.Display book details", GREEN);
	centerText("2.Search for a book", GREEN);
	centerText("3.Add a book", GREEN);
	centerText("4.Remove a book", GREEN);
	centerText("5.Return book", GREEN);
	centerText("6.Member details", GREEN);
	centerText("7.Log out", GREEN);
	centerText("enter your choice>>", LIGHTBLUE, 0);
	cin>>choice;

	switch(choice)
	{
		case 1:
			b.display();
			goto adminpanel;
		case 2:
			b.search();
			goto adminpanel;
		case 3:
			b.add();
			goto adminpanel;
		case 4:
			b.rem();
			goto adminpanel;
		case 5:
			clrscr();
			border();
			cout<<endl;
			centerText("Return book", YELLOW);
			cout<<endl<<endl;
			centerText("Enter the username of returner: ", LIGHTBLUE, 0, 1);
			gets(username);
			if(strlen(username) != 0)
				polish(username);
			else
			{
				displayMessage("Enter a valid username", RED);
				goto adminpanel;
			}
			cout<<endl;
			r.open("users.dat", ios::binary | ios::in);
			if(r)
			{
				r.seekg(0);
				while(!r.eof())
				{
					r.read((char*)&u, sizeof(User));
					if(r.eof())
						break;
					if(strcmpi(u.username, username) == 0)
					{
						flag4 = 1;
						pos = r.tellg() - sizeof(User);
						r.close();
						break;
					}
				}
				if(!flag4)
				{
					displayMessage("No user found with that username", RED);
					r.close();
					sleep(3);
					goto adminpanel;
				}
				ifstream t;
				t.open("bookinfo.dat", ios::binary | ios::in);
				if(t)
				{
					while(!t.eof())
					{
						t.read((char*)&b, sizeof(Book));
						if(t.eof())
							break;
						for(int x=0;u.booksTaken[x]!=0;x++)
						{
							if(u.booksTaken[x] == b.getId())
							{
								b.display1();
								flag = 1;
							}
						}
						if(x == 0)
						{
							flag = 0;
							break;
						}
					}
					if(flag == 0)
					{
						strcpy(name, u.name);
						strcat(name, " has not taken any books");
						centerText(name, RED);
						displayMessage("Press any key to go back", LIGHTGREEN);
						getch();
						t.close();
						r.close();
						goto adminpanel;
					}
					else
						flag = 0;
					t.close();
				}
				else
				{
					strcpy(name, u.name);
					strcat(name, " has not taken any books");
					centerText(name, RED);
					displayMessage("Press any key to go back", GREEN);
					getch();
					goto adminpanel;
				}
				cout<<endl;
				centerText("Enter book id to return: ", LIGHTBLUE, 0);
				cin>>bid;
				for(int x=0;u.booksTaken[x]!=0;x++)
				{
					if(bid == u.booksTaken[x])
					{
						u.booksTaken[x] = 0;
						flag3 = 1;
						break;
					}
				}
				if(flag3)
				{
					ofstream uw, bw;
					uw.open("users.dat", ios::binary | ios::ate);
					uw.seekp(pos);
					uw.write((char*)&u, sizeof(User));
					uw.close();

					t.open("bookinfo.dat", ios::in | ios::binary);
					if(t)
					{
						t.seekg(0);
						while(!t.eof())
						{
							t.read((char*)&b, sizeof(Book));
							if(t.eof())
								break;
							if(bid == b.getId())
							{
								pos = t.tellg() - sizeof(Book);
								break;
							}
						}
						t.close();
					}
					b.addStock(0);

					bw.open("bookinfo.dat", ios::binary | ios::ate);
					bw.seekp(pos);
					bw.write((char*)&b, sizeof(Book));
					bw.close();

					clrscr();
					border();
					cout<<endl;
					centerText("BOOK RETURNED SUCCESSFULLY", GREEN);
					displayMessage("Press any key to continue", LIGHTGREEN);
					r.close();
					getch();
					goto adminpanel;
				}
				else
				{
					displayMessage("That book is not in the list", RED);
					sleep(2);
					r.close();
					goto adminpanel;
				}
			}
			else
			{
				displayMessage("No user found with that username", RED);
				sleep(2);
				goto adminpanel;
			}
		case 6:
			member:

			flag = 0;
			clrscr();
			border();
			cout<<endl;
			centerText("MEMBER DETAILS", YELLOW);
			cout<<endl<<endl;
			centerText("Enter username of any member: ", LIGHTBLUE, 0, 1);
			gets(username);
			if(strlen(username) != 0)
				polish(username);
			else
			{
				displayMessage("Enter a valid username", RED);
				sleep(2);
				goto adminpanel;
			}
			r.open("users.dat", ios::binary | ios::in);
			if(r)
			{
				r.seekg(0);
				while(!r.eof())
				{
					r.read((char*)&u, sizeof(User));
					if(r.eof())
						break;
					if(strcmpi(username, u.username) == 0)
					{
						flag = 1;
						clrscr();
						border();
						cout<<endl;
						centerText("MEMBER DETAILS", YELLOW);
						cout<<endl<<endl;
						gotoxy(wherex() + 16, wherey());
						cout<<"Name: "<<u.name<<endl;
						gotoxy(wherex() + 16, wherey());
						cout<<"Username: "<<u.username<<endl;
						gotoxy(wherex() + 16, wherey());
						cout<<"Age: "<<u.age<<endl;
						gotoxy(wherex() + 16, wherey());
						cout<<"Phone: "<<u.phone<<endl<<endl;
						gotoxy(wherex() + 4, wherey());
						cout<<"Books Taken:-"<<endl;
						gotoxy(wherex() + 4, wherey());
						cout<<"ID  NAME  AUTHOR  GENRE  SALERATE  PURCHASERATE  STOCK"<<endl<<endl;
						for(int i=0;u.booksTaken[i]!=0;i++)
						{
							ifstream t;
							t.open("bookinfo.dat", ios::binary | ios::in);
							if(t)
							{
								t.seekg(0);
								while(!t.eof())
								{
									t.read((char*)&b, sizeof(Book));
									if(t.eof())
										break;
									if(b.getId() == u.booksTaken[i])
									{
										gotoxy(0, wherey());
										b.display1();
										flag2 = 1;
									}
								}
								t.close();
							}
							else
							{
								gotoxy(wherex() + 4, wherey());
								cout<<"***No books taken***";
								break;
							}
						}
						if(!flag2)
						{
							gotoxy(wherex() + 4, wherey());
							cout<<"***No books taken***";
						}
						break;
					}
				}
				r.close();
				if(!flag)
				{
					cout<<endl;
					centerText("No user found with that username!", RED);
					cout<<endl;
				}
				cout<<endl<<endl;
				centerText("See other members? ", LIGHTBLUE, 0);
				cin>>ch;
				if(ch == 'y' || ch == 'Y')
					goto member;
				else if(ch == 'n' || ch == 'N')
					goto adminpanel;
			}
			else
			{
				clrscr();
				border();
				cout<<endl;
				centerText("No members to display", RED);
				sleep(3);
				goto adminpanel;
			}
			displayMessage("Press any key to go back", GREEN);
			getch();
			goto adminpanel;
		case 7:
			return;
		default:
			displayMessage("Enter a valid choice!", RED);
			sleep(2);
			goto adminpanel;
	}
}

void adminLogin()
{
	char username[20], password[20];
	int chances = 3;

	adminlogin:

	if(chances == 0)
	{
		clrscr();
		centerText("Please try again later!", RED);
		sleep(3);
		return;
	}
	clrscr();
	border();
	cout<<endl;
	centerText("ADMIN LOGIN", YELLOW);
	cout<<endl<<endl;
	centerText("USERNAME: ", WHITE, 0, 1);
	gets(username);
	if(strlen(username) == 0)
	{
		displayMessage("Enter a valid username", RED);
		sleep(2);
		goto adminlogin;
	}
	else
		polish(username);
	cout<<endl;
	centerText("PASSWORD: ", WHITE, 0, 1);
	getPass(password);
	if(strlen(password) == 0)
	{
		displayMessage("Enter a valid password", RED);
		sleep(2);
		goto adminlogin;
	}
	if(strcmp(username, "admin") == 0 && strcmp(password, "password") == 0)
	{
		displayMessage("ACCESS GRANTED", LIGHTGREEN);
		sleep(3);
		adminPanel();
		return;
	}
	else
	{
		displayMessage("Invalid details!", RED);
		sleep(2);
		chances--;
		goto adminlogin;
	}
}

void guest()
{
	int choice;

	guest:

	clrscr();
	border();
	cout<<endl;
	centerText("SUMA LIBRARY", YELLOW);
	cout<<endl<<endl;
	centerText("1.Display Book Details", GREEN);
	centerText("2.Search Book", GREEN);
	centerText("3.Back", GREEN);
	centerText("enter your choice>>", LIGHTBLUE, 0);
	cin>>choice;
	switch(choice)
	{
		case 1:
			b.display();
			break;
		case 2:
			b.search();
			break;
		case 3:
			return;
		default:
			displayMessage("Enter a valid choice!", RED);
			sleep(2);
			goto guest;
	}
}
