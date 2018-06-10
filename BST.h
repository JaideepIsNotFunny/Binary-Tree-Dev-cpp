#include<iostream>
#include<conio.h>
#include<process.h>
#include<math.h>
#include<iomanip>

#include <stack> 

/*
gotoxy() is a standard C function defined in <conio.h>, but it will not work in ANSI C compilers such as Dev-C++. Why? Because gotoxy() is a Turbo-C++ specific function, which means it is not part of the standard. However, if you insist on using console functions, you can define your own function by using member functions available in <windows.h>
To use gotoxy() in Dev-C++, #include <windows.h> and insert this snippet before the main() function:
*/
//Defines gotoxy() for ANSI C compilers.
#include<windows.h>
void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

using namespace std;
class node
{
	int info;
	node *left,*right;
	int level;
	bool visited; //used in iterative inorder
	
	public:
	node(){
		info=0;
		left=right=0;
		visited = false; // used in iterative inorder
	}
	node(int x,node * l =0 ,node * r=0){
		info=x;
		left=l;
		right=r;
	}
	node (node & n){
		info=n.info;
		left= n.left;
		right= n.right;
		level = n.level;
	}
	node(int x,int L,node* l=0,node* r=0)
	{
		info=x;
		left=l;
		right=r;
		level=L;
	}

	friend class BST;
};
class BST
{
	node * root;
	int leaves,hieght;
	public:
		BST()
		{
			root=0;
			leaves=0;
			hieght=0;
		}
		void visit(node * p)
		{
			cout<<p->info<<" ";
			p->visited = true; //used in iterative inorder  (void inorder())
		}
		void insert(int);
		node* search(int);
		void display(node*,double,double);
		
		void inorder(node*);
		void preorder(node*);
		void postorder(node*);
		void inorder(); // iterative inorder
		
		node * predicessor(node*);
		void morris_inorder();
		
		
		node* retroot()
		{
			return root;
		}

};
void BST::insert(int x)
{
	node * p=root,*prev=0;
	//cout<<"YAT";
	while(p)
	{       prev=p;
		if(x>p->info)
			p=p->right;
		else	
			p=p->left;
	//	cout<<"YAT";
	}
	if(root==0)	{
		root=new node(x,0);
	//	cout<<"yayy";
	}	
	else if(x>prev->info)   prev->right= new node(x,prev->level+1);
	else if(x<prev->info)	prev->left= new node(x,prev->level+1);
	if(prev && prev->level>hieght-2)	hieght++;

}


void BST::display(node *p,double x,double y)
{	
	
	if (p)
	{
		int n=pow(2,(hieght- p->level - 1));

		char hl=-60,vl=-77,ul=-38,ur=-65;
		if(p->left)
		{
			gotoxy(x-n,y);		cout<<ul;
			for(int i=1;i<n;i++)	cout<<hl;

			gotoxy(x-n,y+1);	cout<<vl;

		}
		gotoxy(x,y);
		cout<<setw(2)<<setfill('0')<<p->info;
		if(p->right)
		{
			gotoxy(x+2,y);
			for(int i=1;i<n;i++)   	cout<<hl;
			cout<<ur;

			gotoxy(x+1+n,y+1);	cout<<vl;
		}
		display(p->left,x-n,y+2);
		display(p->right,x+n+1,y+2);
	}
}
node*  BST::search(int x){
	node *n=root;
	while(n){
		if(x==n->info)
			return  n;
		else if(x>n->info)
			n=n->right;
		else
			n=n->left;
	}
	return 0;
}



void BST::inorder(node*p)
{
	if(p)
	{
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}
void BST::preorder(node*p)
{
	if(p)
	{
		visit(p);
		preorder(p->left);
		preorder(p->right);
	}
}
void BST::postorder(node*p)
{
	if(p)
	{
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}

void BST::inorder(){
	stack <node*> S;
	node *n= root;
	if(n){
		S.push(n);
		while(!S.empty()){
			if(S.top()->left && !(S.top()->left->visited)){
				S.push(S.top()->left);
				continue;
			}
			if(!S.top()->visited){
				visit(S.top());	
				continue;			
			}

			if(S.top()->right && !(S.top()->right->visited)){
				S.push(S.top()->right);
				continue;
			}
			S.pop();
		}	
	}
	
	
}

node * BST::predicessor(node * n){
	if(n){
		if(n->left){
			n=n->left;
		} 
		while(n->right) 
			n=n->right;
		return n;
	}
}
void BST::morris_inorder(){//not working
	node *curr = root;
	while(curr){
		if(!curr->left){
			visit(curr);
			curr = curr ->right;
		}
		else{
			(predicessor(curr))->right = curr;
			curr = curr->left;
		}
	}
}
/*class node{
	int x;
	node * l, *r;
	public:
		node(){
			x=0;
			l=r=0;
		}
		node(int x,node * l =0 ,node * r=0){
			this->x=x;
			this->l=l;
			this->r=r;
		}
		node (node & n){
			this->x=n.x;
			this->l= n.l;
			this->r= n.r;
		}
		friend class BST;
};
class BST{
	node *root;
	public:
		BST(){
			root = 0;
		}
		void insert(int x);
		bool remove(int x);
		node * search(int x);
};
void BST::insert(int x){
	if(root){
		node *n=root,*p=0;
		while(n){
			p=n;
			if(x>n->x)
				n=n->r;
			else 
				n=n->l;
		}
		if(x>p->x)
			p->r = new node (x);
		else 
			p->l = new node(x);
			
	}
	else{
		root = new node(x);
	}
}
node*  BST::search(int x){
	node *n=root;
	while(n){
		if(x==n->x)
			return  n;
		else if(x>n->x)
			n=n->r;
		else
			n=n->l;
	}
	return 0;
}
*/
