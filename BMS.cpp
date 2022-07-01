#include <iostream>
using namespace std;

struct books 
{
	int bookid;
	int genid;
	int price;
	int qty;  
	struct books *next; 
}; 

struct books *newn(int bid, int gid, int prc, int qt) 
{ 
	struct books *new_node = new struct books; 
	new_node->bookid = bid; 
	new_node->genid = gid;
	new_node->price = prc;
	new_node->qty = qt; 
	new_node->next = NULL; 
	return new_node; 
}

struct books *insert(struct books *head, int bid, int gid, int prc, int qt) 

{ 
	struct books *ptr = newn(bid, gid, prc, qt); 
	if(head == NULL) 
	{ 
		head = ptr; 
	} 
	 
	else 
	{ 
		struct books *temp = head;
		while(temp->next!=NULL)
		{
			temp = temp->next;
		}
		temp->next=ptr; 
	} 
	return head; 
}

int find(struct books *head, int bid)
{
	int f = 0;
	struct books *temp = head;
	while(temp!=NULL)
	{
		if(temp->bookid==bid)
		{	f=1;
			break;
		}
		temp = temp->next;
	}
	return f;
}

struct books *findn(struct books *head, int bid)
{
	struct books *temp = head;
	struct books *ptr = NULL;
	while(temp!=NULL)
		{
			if(temp->bookid==bid)
			{
				ptr = temp;
				break;
			}
			temp = temp->next;
		}
	return ptr;
}

struct books *del(struct books *head, int bid) 

{ 
	int fo = find(head, bid);
	if(fo==1)
	{
		struct books *temp = findn(head,bid);
		struct books *ptr = head;
		if(ptr==temp)
		{
			head = head->next;
			delete temp;
		}
		else
		{
			while(ptr->next!=temp)
			{
				ptr = ptr->next;
			}
			ptr->next = temp->next;
			delete temp;
		}
		cout<<"Deletion done"<<endl;
		return head;
	} 
	else 
	{ 
		cout<<"Invalid Operation"<<endl; 
	} 
}

struct books *buy(struct books *head, int bid, int qty) 

{ 
	int fo = find(head, bid);
	if(fo==1)
	{
		struct books *temp = findn(head,bid);
		if(temp->qty==0)
		cout<<"Required book is sold out."<<endl;
		else if(temp->qty<qty)
		cout<<"We don't have the desired quantity of books."<<endl;
		else
		{
			temp->qty = temp->qty - qty;
			double price = (double)(temp->price*qty);
			cout<<"Please pay an amount of "<<price<<endl;
			return head;
		}
	} 
	else 
	{ 
		cout<<"Book Unavailable."<<endl; 
	} 
}

int menu()
{
	int ch;
	cout<<"===============MENU==============="<<endl;
	cout<<"1. Insert a Record."<<endl;
	cout<<"2. Find a Book Record"<<endl;
	cout<<"3. Delete a Book Record"<<endl;
	cout<<"4. Buy Book"<<endl;
	cout<<"5. Display the Records"<<endl;
	cout<<"6. Quit"<<endl;
	cout<<"Enter your choice from 1-6: ";
	cin>>ch;
	return ch;	
}

int main()
{
	struct books *b[4] = {NULL, NULL, NULL, NULL};
	int choice;
	choice  = menu();
	while(choice<=5)
	{
		if(choice==1)
		{
			int bid, gid, prc, qt;
			cout<<"Enter Book ID: ";
			cin>>bid;
			cout<<"Enter Genre ID: ";
			cin>>gid;
			cout<<"Enter Book's Price: ";
			cin>>prc;
			cout<<"Enter Quantity of Books available: ";
			cin>>qt;
			b[gid] = insert(b[gid],bid, gid, prc, qt);
			
			choice = menu();
		}
		
		else if(choice==2)
		{
			int fo, bid, gid;
			cout<<"Enter the following details of the book to be found:"<<endl;
			cout<<"Enter Book ID: ";
			cin>>bid;
			cout<<"Enter Genre ID: ";
			cin>>gid;
			fo = find(b[gid], bid);
			if(fo==1)
			{
				cout<<"Book is available with us.\n";
				struct books *temp = findn(b[gid], bid);
				cout<<"[Book ID: "<<temp->bookid<<", Genre ID: "<<temp->genid<<", Price: "<<temp->price<<", Quantity: "<<temp->qty<<"]"<<endl;
			}
			else
				cout<<"Book is unavailable.\n";
			choice = menu();
		}
		
		else if(choice==3)
		{
			int bid, gid;
			cout<<"Enter the following details of the book to be deleted:"<<endl;
			cout<<"Enter Book ID: ";
			cin>>bid;
			cout<<"Enter Genre ID: ";
			cin>>gid;
			b[gid] = del(b[gid], bid);
			choice = menu();
		}
		
		else if(choice==4)
		{
			int bid, gid, qty;
			cout<<"Enter the following details of the book to be purchased:"<<endl;
			cout<<"Enter Book ID: ";
			cin>>bid;
			cout<<"Enter Genre ID: ";
			cin>>gid;
			cout<<"Enter Quantity of Book: ";
			cin>>qty;
			b[gid] = buy(b[gid], bid, qty);
			choice = menu();
		}
		
		else if(choice==5)
		{
			int i = 0;
			for(i=0;i<4;i++)
			{
				struct books *temp = b[i];
				if(temp==NULL)
				{
					cout<<"Books of this genre unavailable"<<endl;
					
				}
				else
				{
					while(temp!=NULL)
					{
						cout<<"[Book ID: "<<temp->bookid<<", Genre ID: "<<temp->genid<<", Price: "<<temp->price<<", Quantity: "<<temp->qty<<"]"<<"->";
						temp=temp->next;
					}
					cout<<"\n";
				}
			}
			cout<<"\n";
			choice = menu();
		}
		
	}
	cout<<"Thank You\n";
}
