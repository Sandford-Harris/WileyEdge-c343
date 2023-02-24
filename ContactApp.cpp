#include <iostream>
#include <vector>
using namespace std;

struct Contact{
	int id;
	string name;
	int emailId;
};

Contact createContact(int id, string name, int emailId){
	
	Contact c;
	c.id = id;
	c.name = name;
	c.emailId = emailId;
	
	return c;
}

int main(){
	
	int ch;
	
	vector<Contact> contacts;
	
	do{
		cout << "What do you want to do?\n"
			<<"1 - Insert\n2 - Update\n3 - Delete\n"
			<<"4 - Search\n5- Display Contact\n6 - Display all\n7 - Exit" << endl;
		cin >> ch;
		
		int id, emailId;
		string name;
		switch(ch){
			
			case 1: // add new Contact
			{
				cout << "Enter contact id: ";
				cin >> id;
				bool found = false;
				int index = 0;
				for(int i = 0; i < contacts.size(); i++){
					if(contacts[i].id == id){
						found = true;
						break;
					}
				}
				if(found){
					cout << "Contact with that Id already exists." << endl;
					break;
				}
				cout << "Enter contact name: ";
				cin.ignore();
				getline(cin, name);
				cout << "Enter contact email id: ";
				cin >> emailId;
				
				contacts.push_back(createContact(id, name, emailId));
				cout << "Contact Added" << endl;
				break;
			}
			case 2: // update existing contact
			{	
				cout << "Enter Id of the contact you wish to change: ";
				cin >> id;
				bool found = false;
				int index = 0;
				for(int i = 0; i < contacts.size(); i++){
					if(contacts[i].id == id){
						found = true;
						index = i;
						break;
					}
				}
				if(found){
					cout << "Enter new name for the contact (x = leave same) : ";
					cin.ignore();
					getline(cin, name);
					cout << "Enter new emailId for the contact (-1 = leave same): ";
					cin >> emailId;
					if(name != "x")
						contacts[index].name = name;
					if(emailId != -1)
						contacts[index].emailId = emailId;
					
					cout << "Contact updated" << endl;
				}
				else{
					cout << "No contact with that id exists in the system" << endl;
				}
				break;
			}
			case 3: // delete contact
			{	
				cout << "Enter Id of the contact you wish to delete: ";
				cin >> id;
				bool found = false;
				int index = 0;
				for(int i = 0; i < contacts.size(); i++){
					if(contacts[i].id == id){
						found = true;
						index = i;
						break;
					}
				}
				if(found){
					contacts.erase(contacts.begin()+index);
					cout << "Contact deleted" << endl;
				}
				else{
					cout << "No contact with that id exists in the system" << endl;
				}
				break;
			}
			case 4: // search by id
			{	
				cout << "Enter Id of the contact you wish to search for: ";
				cin >> id;
				bool found = false;
				int index = 0;
				for(int i = 0; i < contacts.size(); i++){
					if(contacts[i].id == id){
						found = true;
						index = i;
						break;
					}
				}
				if(found){
					cout << "Contact " << index+1 << " has ID " << id << endl;
				}
				else{
					cout << "No contact with that id exists in the system" << endl;
				}
				break;
			}
			case 5: // display contact by id
			{	
				cout << "Enter Id of the contact you wish to search for: ";
				cin >> id;
				bool found = false;
				int index = 0;
				for(int i = 0; i < contacts.size(); i++){
					if(contacts[i].id == id){
						found = true;
						index = i;
						break;
					}
				}
				if(found){
					cout << "Contact Info :" << endl
						<< "\tID: " << contacts[index].id << endl
						<< "\tName: " << contacts[index].name << endl
						<< "\tEmailId: " << contacts[index].emailId << endl;
				}
				else{
					cout << "No contact with that id exists in the system" << endl;
				}
				break;
			}
			case 6: // display all contacts
				for(int i = 0; i < contacts.size(); i++){
					cout << "Contact " << i+1 << " :" << endl
						<< "\tID: " << contacts[i].id << endl
						<< "\tName: " << contacts[i].name << endl
						<< "\tEmailId: " << contacts[i].emailId << endl;
				}
				break;
			case 7: // exit
				cout << "Goodbye!" << endl;
				break;
			default:
				cout << "Invalid input - try again." << endl;	
				break;		 
		}
		
	}while(ch!=7);
	
	
}
