#include<iostream>
#include<cstring>
using namespace std;

class queue
{
	int q[20], front, rear;
	public:
	queue()
	{
		rear = -1;			//initialize rear to -1
		front = -1;			//initialize front to -1
	}
	int empty();			//function to check if empty
	int full();				//function to check if full	
	void enque(int);		//function to add element
	int deque();			//function to remove element
	void display();		
};

int queue::empty()
{
	if(front == -1)
	{
		return 1;
	}
	else
		return 0;
}

int queue::full()
{
	if(rear == 19)
		return 1;
	else
		return 0;
}

void queue::enque(int item)
{
	if(empty())
	{
		front++;
		rear++;
		q[rear] = item;
	}
	else
	{
		rear++;
		q[rear] = item;
	}
}

int queue::deque()
{
	int temp;
	if(front == rear)
	{
		temp = q[front];
		front=-1;
		rear=-1;
		return temp;
	}
	else
	{
		temp = q[front];
		front++;
		return temp;
	}
}
class user
{
	public:
	int month, day, year, num, likecnt, frndCnt, index;
	char name[20];
	user *next;					//pointer next
	
	user()						//initializing all to 0
	{
		month = 0;
		day = 0;
		year = 0;
		num = 0;
		likecnt = 0;
		frndCnt = 0;
		next = NULL;
	}
	
	user(int m, int d, int y,char nm[],int com,int lk, int ind)			//parameterized constructor
	{
		month = m;
		day = d;
		year = y;
		strcpy(name, nm);
		num = com;
		likecnt = lk;
		index = ind;
	}
};

class graph
{
	user *gp[20];
	static int max;
	static int min;
	int usercnt, visited[20], i;
	public:
	graph()
	{
		cout<<"ENTER THE NUMBER OF USERS\n";
		cin>>usercnt;
		for(i = 0; i < usercnt; i++)
			gp[i] = NULL;	
	}
	
	void rdgraph();						//read graph function	
	void disgraph();					//print graph function
	void insert(int, int);				//insert function	
	void maxFriends();					//max friends function to find the max friends of user 
	void depthse(int);					//depth first search
	void initial();						//initializing function
	void breadthse(int);				//breadth first search 
	void maxmin()				
	{
		cout<<"MAXIMUM COMMENTS "<<max<<endl;
		cout<<"MINIMUM COMMENTS "<<min<<endl;
	}
};

void graph::breadthse(int v)
{
	  user *p;
          queue q;
          int j,w;
          user* temp;
          for(j=0;j<usercnt;j++)
          	visited[j]=0;
          q.enque(v);
            
          temp = gp[v];
          
          visited[v] = 1;
          cout<<temp->name;  
          while(!q.empty())
          {
          	v=q.deque();
                for(p = gp[v]; p != NULL; p = p->next)
                {
                	w = p->index;
                    	if(visited[w]==0)
                     	{
                        	q.enque(w);
                        	visited[w]=1;
                     		
                        	temp=gp[w];
                        	cout<<temp->name;                     	
                     	}
                     	
                }            
          }
} 
void graph::initial()
{
	int i;
	for(i = 0; i < 20; i++)
		visited[i] = 0;
}

int graph::max = 0;
int graph::min = 999;
void graph::depthse(int src)
{
	user* temp = gp[src];
	cout<<temp->name<<endl;
	visited[src] = 1;
	if(min > temp->num)
	{
		min = temp -> num;
		
	}
	if(max < temp->num)
	{
		max = temp -> num;
		
	}	
	
	while(temp != NULL)
	{
		src = temp->index;
		if(visited[src] == 0)
			depthse(src);
		temp = temp -> next;
	}
}
	
void graph::maxFriends()					//FUNCTION TO FIND MAX FRIENDS
{
	int i, temp = 0, x;
	user *p;
	for(i = 0; i < usercnt; i++)
	{
		p = gp[i];
		if(temp < p->frndCnt)
		{
			temp = p -> frndCnt;
			x = i;
		}
		
	}
	cout<<gp[x ]->name<<" HAS MAXIMUM FRIENDS\n";
}

void graph::rdgraph()
{
	int i, edgecnt, src, dest;
	int m, d, y, com, lk;
	char nm[20];
	user *newn;
	for(i = 0; i < usercnt; i++)
	{
		
		cout<<"ENTER THE NAME \n";
		ws(cin);
		cin.getline(nm, 20);
		cout<<"ENTER BIRTH DAY \n";
		cin>>d;
		cout<<"ENTER THE BIRTH MONTH\n";
		cin>>m;
		cout<<"ENTER THE BIRTH YEAR\n";
		cin>>y;
		cout<<"ENTER THE NUMBER OF COMMENTS\n";
		cin>>com;
		cout<<"ENTER THE NUMBER OF LIKES\n";
		cin>>lk;
		user *newn = new user(m, d, y,nm, com, lk, i);
		gp[i] = newn;
	}
	cout<<"ENTER THE NUMBER OF EDGES \n";
	cin>>edgecnt;
	for(i = 0; i < edgecnt; i++)
	{
		cout<<"ENTER SOURCE AND DESTINATON\n";
		cin>>src>>dest;
		insert(src, dest);
		insert(dest, src);
	}
}
void graph::insert(int i, int j)
{
	user *p, *q;
	q = new user(*gp[j]);
	q -> next = NULL;
	p = gp[i];
	p -> frndCnt++;
	while(p -> next != NULL)
			p = p->next;
	p -> next=q;	
}

void graph::disgraph()
{
	int i;
	user *p;
	for(i = 0; i < usercnt; i++)
	{
		p = gp[i];
		cout<<gp[i]->name<<"\t"<<gp[i]->day<<"\t"<<gp[i]->month<<"\t"<<gp[i]->year<<endl;
		p = p -> next;
		while(p != NULL)
		{ 
			cout<<"\t"<<p->name;
			if(p->next == NULL)
				cout<<endl;
			p = p -> next;
		}
	}
}

int main()
{
	graph g1;
	g1.rdgraph();
	g1.disgraph();
	g1.initial();
	g1.depthse(0);
	g1.breadthse(0);
	g1.maxmin();
	g1.maxFriends();	
	return 0;
}



