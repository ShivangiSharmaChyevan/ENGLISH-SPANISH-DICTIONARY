#include<iostream>
#include<fstream>
using namespace std;

struct node
{
        string word,spanish;
        node *left,*right;
        int height;
};

class avl
{
        public:
        node *root;
        
        avl()
        {
                root=NULL;
        }
        node* new_node(string wo,string an);
        int find_ht(node*);
        int balance(node*);
        node* l_rot(node *);
        node* r_rot(node *);
        node *insert(node *,string,string);
        void preorder(node*);
        node *leftmost(node* );
        node * delet(node *root,string w);
        void search(node*,string);
        void modify(node*,string);
        node * ret()
        {
        return root;
        }
        int max(int a, int b)
        {
        return (a > b)? a : b;
        }
        
};
void avl::search(node* r,string w)
{
        if(r==NULL)
        {
                cout<<"\n Not Found";
                return ;
        }
     
        if(w<r->word)
        search(r->left,w);
        if(w>r->word)
        search(r->right,w);
        else if(r->word==w)
        {
       cout<<"\nWord : "<<r->word;
       cout<<"\nSpanish : "<<r->spanish;
        return ;
        }
        
        
}
void avl::modify(node* r,string w)
{
          
        if(r==NULL)
        {
                cout<<"\n Not Found";
                return ;
        }
     string spa;
        if(w<r->word)
        modify(r->left,w);
        if(w>r->word)
        modify(r->right,w);
        else if(r->word==w)
        {
       
       cout<<"\nWord : "<<r->word;
       cout<<"\nOriginal SPANISH : "<<r->spanish;
       cout<<"\n New SPANISH : ";
       cin>>spa;
       r->spanish=spa;
       fstream f,f1;
       string g;
       f.open("dic.txt",ios::in|ios::out);
       f1.open("dic1.txt",ios::out);
       while(f)
       {
              f>>g;
              if(g!=w)
              {
                  f1<<g;
                  getline(f,g);
                  f1<<g;  
                f1<<endl;                                    
              
              }
              
              else
              {
              f1<<g;
              
              f1<<" ";
              f1<<spa;
              
              f1<<endl;
              getline(f,g);
              }
              if(f.eof())
              break;
       
        }
        remove("dic.txt");
        rename("dic1.txt","dic.txt");
        
         return ;
        
   }
   }
int avl:: find_ht(node * t)
{
        if(t==NULL)
        return 0;
        return t->height;
}
int avl::balance(node *t)
{
        if(t==NULL)
        return 0;
        return ((find_ht(t->left))-find_ht(t->right));
        
}

node * avl::new_node(string wo,string opp)
{
        node *r=new node();
        r->word=wo;
        r->spanish=opp;
        r->height=1;
        r->left=NULL;
        r->right=NULL;
        return r;
        
}
node *avl::r_rot(node *y)
{
        node *t=y->left;
        node *g=t->right;
         t->right=y;
        y->left=g;
       
        
        y->height=max(find_ht(y->left),find_ht(y->right))+1;
        t->height=max(find_ht(t->left),find_ht(t->right))+1;
      
        
        return t;
        
}
node *avl::l_rot(node *y)
{
        node *t=y->right;
        node *g=t->left;
         t->left=y;
        
        y->right=g;
       
        y->height=max(find_ht(y->left),find_ht(y->right))+1;
        t->height=max(find_ht(t->left),find_ht(t->right))+1;
       
        
        return t;
        
}
node * avl::insert(node *k,string w,string m)
{
        
        if(k==NULL)
        return( new_node(w,m));
        if(w<k->word)
        k->left=insert(k->left,w,m);
        else if(w>k->word)
        k->right=insert(k->right,w,m);
        
        k->height=max(find_ht(k->left),find_ht(k->right))+1;
        
      int g=balance(k);
       
          
      
       if(g>1 && w<k->left->word)
        return r_rot(k);
        
        
         if(g>1 && w>k->left->word)
        {
            k->left=l_rot(k->left);
            return r_rot(k);
        }
        
        if(g<-1 && w>k->right->word)
       return l_rot(k);
        
        
        if(g<-1 && w<k->right->word)
         {
            k->right=r_rot(k->right);
            return l_rot(k);
        }
        
     return k;  
                
        
}
void avl::preorder(node * root)
{
    if(root != NULL)
    {
        
        cout<<root->word<<":"<<root->spanish<<"\n";
        preorder(root->left);
        preorder(root->right);
    }
    
}
node *avl::leftmost(node* nod)
{
    node* current = nod;
 
    
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
node* avl::delet(node *n,string w)
{
        if(n==NULL)
        return n;
        
        if(w<n->word)
                n->left=delet(n->left,w);
        else if(w>n->word)
                n->right=delet(n->right,w);
        else
        {
                if((n->left==NULL) ||(n->right==NULL))
                {
                        node *temp=n->left?n->left:n->right;
                        
                        if(temp==NULL)
                        {
                                temp=n;
                                n=NULL;
                        }
                        else
                        {
                                n=temp;
                                
                        }
                        
                       delete temp; 
                }
                else
                {
                node *temp=leftmost(n->right);
                
                n->word=temp->word;
                
                n->right=delet(n->right,temp->word);
                
                }
        }
        if(n==NULL)
        return n;
        
        n->height=1+max(find_ht(n->left),find_ht(n->right));
        
        int bal=balance(n);
        
        if (bal > 1 && balance(n->left) >= 0)
        return r_rot(n);
 
   
    if (bal > 1 && balance(n->left) < 0)
    {
        n->left =  l_rot(n->left);
        return r_rot(n);
    }
 
    
    if (bal < -1 && balance(n->right) <= 0)
        return l_rot(n);
 
    
    if (bal < -1 && balance(n->right) > 0)
    {
        n->right = r_rot(root->right);
        return l_rot(root);
    }
    
        fstream f ,f1;
        string g;
       f.open("dic.txt",ios::in|ios::out);
       f1.open("dic1.txt",ios::out);
       while(f)
       {
              f>>g;
              if(g!=w)
              {
                  f1<<g;
                  getline(f,g);
                  f1<<g;  
                f1<<endl;                                    
              
              }
              else
              {
              getline(f,g);
              }
              
              
              if(f.eof())
              break;
       
        }
        remove("dic.txt");
        rename("dic1.txt","dic.txt");
 
    return n;
        
}

int main()
{
       avl a;
       fstream f;
      f.open("dic.txt",ios::in);
       string s,w,span;
       
       while(!f.eof())
       {
        f>>s;
        w=s;
        getline(f,span);
        a.root=a.insert(a.root,w,span);
        if(f.eof())
        break;
       } 
        
       int ch;
       
      string a1,b;
       
       while(1)
       {
         
      cout<<"\n\t********** ENGLISH-SPANISH DICTIONARY*********\n";
      cout<<"\n1.For exploring whole dictionary";
      cout<<"\n2.For seacrhing specific word";
      cout<<"\n3.For modifying meaning of a word";
      cout<<"\n4.For deleting a word";
      cout<<"\n5.For inserting a word";
      cout<<"\n6.Exit";
      
      cout<<"\nYOUR CHOICE : ";
      cin>>ch;
      
      switch(ch)
      {
        case 1: a.preorder(a.ret());
                break;
        case 2:cout<<"\n Enter word ";
               cin>>s;
               a.search(a.ret(),s);
               break;
        case 3: cout<<"\n Enter word ";
                cin>>s;
                a.modify(a.ret(),s);
                cin.clear();
                cin.ignore();
                break;
        case 4: cout<<"\n Enter word ";
                cin>>s;
                a.delet(a.ret(),s);
                break;
        case 5:
                cout<<"\n Enter Word : ";
                cin>>s;
                cout<<"\n Enter Spanish equivalent : ";
                cin>>w;
                a.insert(a.ret(),s,w);
                 
                f.open("dic.txt",ios::in);
               
               
               while(!f.eof())
               {
                f>>a1;
                getline(f,b);
                
                if(f.eof())
                {
                f<<s;
                f<<" ";
                f<<w;
                f<<endl;
                break;
                } 
        
                break;
                        
        case 6: cout<<"Thanks for visiting ! ";
                break;
      }
                  
                    
       
     }
     return 0;
     }
}

