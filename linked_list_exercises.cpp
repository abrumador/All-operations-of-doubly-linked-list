//This program is a implementation of single, doubly linked list and their operations, such as reverse,
//insert,delete,find,print.
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <iomanip>  
#include <algorithm>
#include <cctype>



using namespace std;


struct Product {
int prod_id;
string prod_name;
int amount;
Product * next;
}*first = nullptr;


struct Customer{
int cust_id;
string cust_name;
Customer * prev;
Customer * next;
Product * prod;
}*first_cus = nullptr;


struct Node{
int cust_id;
string cust_name;
int amount;
Node * next;
}*first_node = nullptr;




void find_customer(struct Customer *head)
{
	// This function finds the desired customer.
	struct Product *q;
	q = head->prod;
	string s;
	int counter = 0;
	cout << "Enter customer's ID or name and surname:";
	cin.ignore();
	getline(cin,s);						//Entering the input
	while(head)
	{
	q = head->prod; 
	if(head->cust_name == s || std::to_string(head->cust_id) == s) // Checking both name and ID
	{
		cout << "Customer found!" << endl;

		cout << "ID: " << head->cust_id <<" Name: " << head->cust_name<< endl; //If customer is found,then printing
		while(q)																
		{                                                                         //Also printing the products
			cout << "Item ID: " << q->prod_id << " Item name: " << q->prod_name << ". " <<" Amount: " << q->amount<<endl;
			q= q->next;
		}

		q = nullptr;
		head=head->next;
		counter ++;
	}


	else
	{
		head= head -> next;
	}

	}

	if (counter ==0)
		cout << "CUSTOMER CAN NOT FOUND. GOING BACK TO MAIN MENU " << endl;

}

void sorting (struct Product *head)
{

	// Sorting function
	Product * temphead = head;
	int temp_id;
	int temp_amount;
	string tempname;
	int counter = 0;
	while (temphead)
	{
		temphead = temphead->next;
		counter++;
	}
	temphead = head;
	
	for (int j=0; j<counter; j++) // Looking all the possibilites.
	{
		while (temphead->next)
		{
			if (temphead->prod_id > temphead->next->prod_id) // Checking the which elemet is bigger than the others
			{
				temp_id = temphead->prod_id;
				temphead->prod_id = temphead->next->prod_id;
				temphead->next->prod_id = temp_id;			//Prod id operation

				tempname = temphead->prod_name;
				temphead->prod_name = temphead->next->prod_name;
				temphead->next->prod_name = tempname;        //Prod name operation

				
				temp_amount = temphead->amount;
				temphead->amount = temphead->next->amount;
				temphead->next->amount = temp_amount;  //Amount operation
			}
			temphead = temphead->next;
		}	
		temphead = head;
	}
}


void double_linked_list_sorting(struct Customer *head)
{

	// Doubly linked list sorting function
	Customer * temphead = head;
	int temp_cust_id;
	Product * temp_pointer;
	string temp_cust_name;
	int counter = 0;
	while (temphead)
	{
		temphead = temphead->next;
		counter++;
	}
	temphead = head;
	
	for (int j=0; j<counter; j++)
	{
		while (temphead->next)
		{
			if (temphead->cust_id > temphead->next->cust_id) // Checking for ID values
			{
				temp_cust_id = temphead->cust_id;
				temphead->cust_id = temphead->next->cust_id;
				temphead->next->cust_id = temp_cust_id; // Customer id operation

				temp_cust_name = temphead->cust_name;
				temphead->cust_name = temphead->next->cust_name;
				temphead->next->cust_name = temp_cust_name;  // Customer name operation

				temp_pointer = temphead ->prod;
				temphead->prod = temphead->next->prod;
				temphead->next->prod = temp_pointer;   

				
			}
			temphead = temphead->next;
		}	
		temphead = head;
	}




}

Customer* create_doubly_linked_list(vector<string> & name_surname, vector<int> & ID_num,vector<vector<int>> &amount_big_mat,vector<vector<string>> & product_name_big_mat, vector<vector<int>> & product_Id_big_mat, vector < Product*> & empty)
{
	// Creating a doubly linked list function
	// For solving the problem doubly linked list is needed.
	struct Customer *temp, *last;

	first_cus = new Customer;

	first_cus -> cust_id = ID_num[0];
	first_cus -> cust_name = name_surname[0]; // Getting the first values from vectors
	first_cus -> prod = empty[0];
	first_cus->prev = nullptr;
	first_cus->next = nullptr;
	last = first_cus;

	for (int i = 1; i < amount_big_mat.size(); i++) // Adding all the values from vectors to linked list
	{
			temp = new Customer;
			temp -> cust_id = ID_num[i];
			temp -> cust_name = name_surname[i];
			temp -> prod = empty[i];
			temp -> next = last -> next;
			temp -> prev = last;
			last -> next = temp;
			last = temp;
	}
		
		double_linked_list_sorting(first_cus);
		return first_cus;

}


Product *  create_product_linked_list(vector<vector<int>> & amount_vec , vector < vector<string>> & product_name, vector<vector<int>> & product_ID, int a)

{

	// Creating single linked list

	struct Product *temp,*last;
	first = new Product;
	first->amount =amount_vec[a][0];
	first ->prod_id = product_ID[a][0]; // Similar operation with the doubly linked list creation.
	first ->prod_name = product_name[a][0];
	first -> next = nullptr;

	last = first;

	for (int i = 1; i < product_name[a].size() ; i ++)
	{
		temp = new Product;
		temp->amount =amount_vec[a][i];
		temp ->prod_id = product_ID[a][i];
		temp ->prod_name = product_name[a][i];
		temp -> next = nullptr;
		last->next = temp;
		last = temp;
		
	}

	sorting(first);
	return first;
}


void print_customer_data(struct Customer *p)
{
	struct Product *q;
	
	while(p)
	{
		cout << "ID :" << p->cust_id << " Name :" << p->cust_name << endl;
		cout << "Items in the chart:" << endl;
		q = p->prod; // Going to product linked list
		while(q)
		{
			cout <<"Item ID :" << q->prod_id << " Item name :" <<q->prod_name << "." << "Amount : " << q->amount <<  endl;
			q = q->next;
		}
		p = p->next;

	}
	


}


void display(struct Product *p)
{

	while(p != nullptr)
	{
		cout <<"Item ID:" << p->prod_id<< " Item name: " << p->prod_name << ". Amount: "<<p->amount << endl;
		p = p->next;
	}
}

Customer* insert_sorted_list(struct Customer *head,int ID,string name)
{
   
    Customer * temp = new Customer;
    temp->cust_id = ID;
	temp->cust_name =name; // Creating a new node called temp
	temp->prod = nullptr;
    temp->next = nullptr;
    temp->prev = nullptr;
    if (head == nullptr)
    {
        head = temp;
        return head;
    }


    if (ID <= head->cust_id) // Putting this node in a sorted linked list.
    {
		
        temp->next = head;
        head->prev = temp;
        head = temp;
        return head;


    }

    Customer *curr = head;
    while (curr->next!=nullptr) // Continue untill, pointers next is equal to nullptr.
    {
        if (temp->cust_id <= curr->cust_id)
        {   
            curr->prev->next = temp;
            temp->prev = curr->prev;
            temp->next = curr;
			curr->prev = temp;
            return head;
        }



        curr = curr->next;
    }


    curr->next = temp;
    temp->prev = curr;
    return head;
}

Customer* delete_operation(struct Customer *head,int ID)
{


	
	Customer *p = first_cus;


	
	while(p->cust_id != ID)
	{
		p = p->next;				// Searching all the nodes
	}
	p->prev->next = p->next;        // When it is found
	if(p->next)
		p->next->prev = p->prev;   // Deleting operation

	p->prod == nullptr;
	delete(p);

	return first_cus;
	}

bool check_given_value_is_there(struct Product * head, int ID)
{

	while(head)
	{
		if(head->prod_id == ID)			// Used for if desired value is in the linked list or not
			return true;
		else
		{
			head= head->next;
		}


	}

	return false;
}


void new_delete(struct Customer *head, int ID)
{


	// Function for deleting the first node
	struct Customer * temp;
	temp = head;
	temp->next = nullptr;
	head = head->next;
	if(head)
	head->prev = nullptr;
	delete(temp);
}

void delete_customer(struct Customer *head)
{
	// Main delete function
	int deleted_id;
	cout << "Enter an ID for the customer to be deleted: ";
	cin>>deleted_id;
	int count = 0;
	Customer *p = first_cus;
	while(head)			// Checking the given ID is in the list or not
	{
		if(head->cust_id != deleted_id)
		{
			head = head->next;
		}
		else
		{
			count ++;
			head = head->next;
		}}
	if (count == 0)
	{
		cout << "Entered ID is wrong. You are going to main menu" << endl; // If it is not go back to main
		return;
	}


	
		if(first_cus->cust_id == deleted_id) // First node deletion
		new_delete(first_cus,deleted_id);
		else
		first_cus = delete_operation(first_cus,deleted_id); // Other nodes deletion

	cout << "Customer is deleted succesfully." << endl;


}

void add_customer(struct Customer *head)
{
	
	int new_ID;

	cout << "Enter an ID for the user: ";
	cin>>new_ID;
	int counter = 0;

	while(head)
	{
		if(head->cust_id == new_ID)
		{
			cout << "User with ID: " <<new_ID << " already exists. Going back to main menu"<<endl;
			return;
		}

		else
		{
			head = head->next;
		}
		}
		
			string s;
			cout << "Enter the customer's name and surname :  ";
			cin.ignore();
			getline(cin,s);					// Asking the name and surname


			first_cus = insert_sorted_list(first_cus,new_ID,s); // Calling the insert function
			
			
			cout << "User with ID" << new_ID << "is inserted to the list " << endl;

		

}


Product* insert_product_sorted_list(struct Product *p, int amount, int ID, string prod_name,struct Customer *q)
{

	struct Product *temp, *q_pointer = nullptr;
	temp = new Product;
	temp->amount = amount;
	temp->prod_name = prod_name;
	temp->prod_id = ID;
	temp->next = nullptr;



	if(p == nullptr) // If node is empty
	{
		q->prod = temp;
		p = temp;


		return p;
	}

	else
	
		{

		while(p && p->prod_id < ID)
		{
		q_pointer = p;
		p=p->next;
	}
		if (p == first) // If it is the first node
		{
			temp->next = first;
			first = temp;
			return first;
		}
		else            // For the other nodes
		{
			temp->next = q_pointer->next;
			q_pointer->next = temp;
			return q_pointer;
		}
		
	}

}



void add_to_first_node(struct Product * p,int amount,int ID, string name,struct Customer *q)
{

	// IF node is headded to head of the linked list
    struct Product*temp;
    temp = new Product;
    temp->amount = amount;
	temp->prod_id = ID;
	temp->prod_name = name;
    temp->next=nullptr;
    if (p!=nullptr)
	temp->next = p;
	q->prod = temp;
    p=temp;

}


void add_product(struct Customer *head)
{


	// Adding item to single linked list
	cout << "Enter an ID for the Customer to add product:  ";
	int customer_id;
	cin>>customer_id;
	int count = 0;
	while(head)
	{
		if(head->cust_id != customer_id)
		{
			head = head->next;  // Checking the Product is there or not
		}
		else
		{
			count ++;
			head = head->next;
		}}
	if (count == 0)
	{
		cout << "Entered ID is wrong. You are going to main menu" << endl;
		return;
	}

	bool true_or_false = true;
	while(true_or_false = true)
	{
	cout << "Would you like to add item to cart(Y/y):";
	string answer;
	cin>>answer;


	if(answer == "y" || answer == "Y") // Both Y and y is accepted
	{
		int prod_id ;
		cout << "ID of the item to add cart :";
		cin>> prod_id;

		struct Product *p;
		struct Customer *q = first_cus;
	

		

		while(q->cust_id != customer_id)
		{
			q = q->next;
			
		}
		p = q->prod;


		bool check;
		check = check_given_value_is_there(p,prod_id); // Check is there or not

		if(check == true)
		{
		while(p->prod_id != prod_id)
		{

			p = p->next;

		}
		
		if (p->prod_id == prod_id)
		{
			cout << "Product already exists. How many would you like to add more: ";
			int addition;
			cin>> addition;
			p->amount = p->amount + addition;
			cout << "Products amount in the cart increased to: " << p->amount << endl;
		}
		}

		else
		{

			string produ_name;
			int amount;
			cout << "Name of the product:";
			cin>>produ_name;
			cout << "Amount:";
			cin>>amount;

			if(p == nullptr)
			{
			
				struct Product *temp = nullptr;
				temp = new Product;
				temp->amount = amount;
				temp->prod_name = produ_name;
				temp->prod_id = prod_id;
				temp->next = nullptr;

				q->prod = temp;
				p = temp;
				return;
			}

			if(p->prod_id > prod_id)
			{
			add_to_first_node(p,amount,prod_id,produ_name,q);
			}
			else
			{
			insert_product_sorted_list(p,amount,prod_id,produ_name,q);
			}
			
			// FIRSTE ESIT DEGILDI SONRADAN YAPTIM

			
			
		}
	}
	else
	{
		true_or_false = false;
		cout << "You are going to the main menu" << endl;
		break;
		return;
	}
}
}


Node* make_linked_list_for_reverse(vector<int> & cust_ID, vector<string> & cust_name, vector<int> & amount)
{

	// New linked list for the list of the product owners for giving values in reverse order.
	struct Node *temp,*last;
	first_node = new Node;
	first_node->amount =amount[0];
	first_node ->cust_id = cust_ID[0];
	first_node ->cust_name = cust_name[0];
	first_node -> next = nullptr;

	last = first_node;

	for (int i = 1; i < cust_name.size() ; i ++)
	{
		temp = new Node;
		temp->amount =amount[i];
		temp ->cust_id = cust_ID[i];
		temp ->cust_name = cust_name[i];
		temp -> next = nullptr;
		last->next = temp;
		last = temp;
		
	}

	return first_node;


}

Node* reverse(struct Node *head)
{
	
	Node * next = nullptr;
	Node * current = nullptr;
	Node * previous = nullptr;
	current = head;
	// Flip the head and tail of the linked list
	while(current != nullptr){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
 
    head = previous; 
	return head; // Return the new head

}

void list_product_owners(struct Customer *head)
{


	cout <<"ID of the product to search buyers:";
	int prod_Id ;
	cin>>prod_Id;

	struct Customer *p = new Customer;
	p = head;
	struct Product *q = new Product;
	
	vector <int> cust_id;
	vector <string> cust_name;
	vector <int> amount;
	int count = 0;
	while(p)
	{
		q =p->prod;
		while(q)
		{
			if(q->prod_id == prod_Id) //If the given ID is found
			{
				amount.push_back(q->amount);
				cust_name.push_back(p->cust_name); // Putting values into new vector
				cust_id.push_back(p->cust_id);		// This vector will be used for creating linked list.
			
			q = q->next;
			count++;
			}
			else
			{
				q = q->next;
			}
		}
		
		p= p->next;
		
	}

	if (count == 0)
	{
		cout << "Product ID is not found in the chart" << endl;
	}
	else
	{
		cout << "Buyers of the product with " << prod_Id <<" is listed below" << endl;
		struct Node *q = new Node;

		q = make_linked_list_for_reverse(cust_id,cust_name,amount);
		q = reverse(q);
		while(q)
		{
			cout <<"Customer ID: " << q->cust_id << " Customer name: "<<q->cust_name<< " and Amount: " << q->amount<< endl;
			q = q->next;
			
		}
	}


}


void delete_product(struct Customer * head)
{
	cout << "Enter an ID for the customer to delete product:";
	int customer_id;
	cin>>customer_id;
	int count = 0;

	struct Customer * p;

	
	while(head)
	{
		if(head->cust_id != customer_id)
		{
			head = head->next;
		}
		else
		{
			count ++;
			p = head;
			head = head->next;
		}}
	if (count == 0)
	{
		cout << "Customer with ID: " << customer_id <<" doesn't exist. Going back to main menu."<<  endl;
		return;
	}

	struct Product *head_prod;

	cout << "ID of the item to delete from the chart:";
	int product_id;
	cin>>product_id;
	
	head_prod =p->prod;
	count = 0;
	while(head_prod)
	{
		if(head_prod->prod_id != product_id)
		{
			head_prod = head_prod->next;
		}
		else
		{
			count ++;
			head_prod = head_prod->next;
		}
	}
	if (count == 0)
	{
		cout << "Product doesn't exist. Going back to main menu" << endl;
		return;
	}

		struct Product *q;
	
		q = p->prod;

		Product *temp=new Product;
		if(q->prod_id == product_id)
		{

			
			temp=q;
			q=q->next;
			p->prod = q;
			delete temp;
		}
		else
		{
		Product *current=new Product;
		Product *temp=new Product;
		current=q;
		while(current->prod_id != product_id)
		{
		  temp=current;
		  current=current->next;
		}
		temp->next=current->next;

		}

		cout << "Product has been deleted" << endl;
		cout << "Current items in the car:" << endl;
		cout <<"ID: " << p->cust_id << " Name: " << p->cust_name << endl;
		display(q);





}

void menu(struct Customer *head)
{
while (true){
cout << endl;
cout << "***********************************************************************" << endl
<< "**************** 0 - EXIT PROGRAM ************" << endl
<< "**************** 1 - PRINT ALL CUSTOMER DATA ************" << endl
<< "**************** 2 - FIND A CUSTOMER ************" << endl
<< "**************** 3 - ADD A CUSTOMER ************" << endl
<< "**************** 4 - DELETE A CUSTOMER ************" << endl
<< "**************** 5 - ADD A PRODUCT TO A CUSTOMER ************" << endl
<< "**************** 6 - DELETE A PRODUCT FROM A CUSTOMER ************" << endl
<< "**************** 7 - LIST THE BUYERS OF A PRODUCT ************" << endl
<< "***********************************************************************" << endl;
cout << endl;
int option;
cout << "Pick an option from above (int number from 0 to 7): ";
cin >> option;
switch (option)
{
case 0:
cout << "PROGRAM EXITING ... " << endl;
system("pause");
exit(0);
case 1:
print_customer_data(head);
break;
case 2:
find_customer(head);
break;
case 3:
add_customer(head);
break;
case 4:
delete_customer(head);
break;
case 5:
add_product(head);
break;
case 6:
delete_product(head);
break;
case 7:
list_product_owners(head);
break;
default:
cout << "INVALID OPTION!!! Try again" << endl;
}
}
}

int main()
{
	
	vector <vector<string> > total;

	string line;
	string rest;
	string num;
	ifstream infile;
	infile.open("input.txt");

	

	vector < int > number_vector;
	vector <string> name_surname_vector;
		
	
	vector <int> product_ID_vec ;
	vector < vector <int>> product_Id_big_mat;

	vector <string> product_name_vec;
	vector < vector<string>> product_name_big_mat;

	vector <int > amount_vec ;
	vector <vector<int>> amount_big_mat;

	while(getline(infile,line))
	{

		if (line.find('#') != std::string::npos) // Reading lines according to # so customers can be found easily
		{

			if (product_ID_vec.size() != 0)
				product_Id_big_mat.push_back(product_ID_vec); // Putting into a vector

			if (product_name_vec.size() !=0)
				product_name_big_mat.push_back(product_name_vec);

			if(amount_vec.size() != 0)
				amount_big_mat.push_back(amount_vec);



			while(product_ID_vec.size() != 0)
			{
				product_ID_vec.pop_back();  // Every single quantity put into a vector

			}

			while(product_name_vec.size() != 0)
			{
				product_name_vec.pop_back(); // Same as ID, putting in a vector.
			}

			while(amount_vec.size() != 0)
			{
				amount_vec.pop_back();
			}
			
			string first_world = line.substr(0,line.find(" "));  // Last part of reading a file
			first_world.erase(0,1);
			first_world.erase(first_world.size()-1,first_world.size()); // Empty spaces are different size
			int number = stoi(first_world);								// so need to care every cases
			number_vector.push_back(number);
			unsigned first = line.find(',');
			unsigned last = line.find(':');
			string name_surname = line.substr(first,last-first);
			name_surname.erase(0,2);
			name_surname_vector.push_back(name_surname);
			string product_ID = line.substr(line.find(':'),line.find(" "));
			product_ID.erase(0,2);
			int product_ID_s = stoi(product_ID);
			int x = product_ID.size();
			product_ID_vec.push_back(product_ID_s);
			

			string abc = line.substr(line.find(product_ID), line.find(')'));

			string product_name = abc.substr(abc.find(' ') + 1, abc.find('('));

			string last_product_name = product_name.substr(0,product_name.find('(')-1);

			product_name_vec.push_back(last_product_name);

			string first_amount = product_name.substr(product_name.find('(')+1, product_name.find(')'));

			string amount = first_amount.substr(0,first_amount.find(')'));

			int int_amount = stoi(amount);

			amount_vec.push_back(int_amount); // Vector operations are over.

			
		
			
		}

		else
		{
			stringstream s(line);  // Reading the other lines which don't have customer names.
			int num;
			string word;
			string word2;
			string num2;
			string word_3 ;
			while(s>> num)
			{
				product_ID_vec.push_back(num);
				string new_string = to_string(num);
				
				int x = new_string.size();
				string product_name = line.substr(line.find(new_string.at(0))+x+1,line.find('('));
				string new_new = product_name.substr(0,product_name.find('(')-1);

				product_name_vec.push_back(new_new);
				
				
				string next_string = line.substr(line.find('(')+1, line.find(')'));

				string amount = next_string.substr(0,next_string.find(')'));

				int int_amount = stoi(amount);

				amount_vec.push_back(int_amount);
				
			}
	

		}	
		
	}

	if (product_ID_vec.size() != 0)
		product_Id_big_mat.push_back(product_ID_vec); // These elements are also added to vectors.

	if(product_name_vec.size() != 0)
		product_name_big_mat.push_back(product_name_vec);

	if(amount_vec.size() != 0)
		amount_big_mat.push_back(amount_vec);

	vector < Product * > empty;
	for (int i = 0; i < amount_big_mat.size() ; i ++)
	{
		first = create_product_linked_list(amount_big_mat,product_name_big_mat,product_Id_big_mat, i);
		empty.push_back(first);

	}


	// Create the doubly linked list.
	first_cus = create_doubly_linked_list(name_surname_vector,number_vector,amount_big_mat,product_name_big_mat,product_Id_big_mat,empty);
	// Call the menu for operations.
	menu(first_cus);
	

	
	return 0;
}