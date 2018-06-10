#include<iostream>
#include"BST.h"

using namespace std;
int main(){
	BST B;
	
	char ch;
	int c,x;
	node *n;
	do{
		//system("clear");

		cout<<"\n____________MENU___________";

		cout<<"\n1.insert";
		cout<<"\n2.search";
		cout<<"\n3.display";
		cout<<"\n4.inorder";
		cout<<"\n5.preorder";
		cout<<"\n6.postorder";
		cout<<"\n7.iterative inorder";
		cout<<"\n8.morris iterative inorder";
		cin>>c;
		switch(c){
			case 1:
				cout<<"\nEnter the element : ";
				
				cin>>x;
				B.insert(x);
			break;
			case 2:
				cout<<"\nEnter the element : ";
				
				cin>>x;
			    n =B.search(x);
				if(n)
					cout<<"\n Found";
				
				else
					cout<<"\n Not Found";
			break;
			
			case 3:
				
				system("clear");
				B.display(B.retroot(),50,50);
			break;
			case 4:
				
				cout<<"\n inorder : ";
				B.inorder(B.retroot());
			break;
			case 5:
				
				cout<<"\n preorder : ";
				B.preorder(B.retroot());
			break;
			case 6:
				
				cout<<"\n postorder : ";
				B.postorder(B.retroot());
			break;
			case 7:
				
				cout<<"\niterative inorder : ";
				B.inorder();
			break;
			case 8:
				
				cout<<"\nmoris iterative inorder : ";
				B.morris_inorder();
			break;
			default: exit(0);
		}
		
		cout<<"\nWant to use again?...(y/n)";
		cin>>ch;

	}while(ch=='y'||ch=='Y');

}
