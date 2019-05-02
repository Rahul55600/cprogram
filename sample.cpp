#include<iostream>
using namespace std;
#define MAX 20
#define infinity 999 		//define infinity

class graph
{
public:
	int g[MAX][MAX];		//2D matrix for graph
	int n,ne;    //ne=edge  and n=vertices
	
	graph() 			//default constructor
	{
		n=0; 			//assign to zero
	}
	
	void readgraph(); 		//reading graph
	void display(); 		//displaying graph
	int prims(graph &);  			//shortest path function
	void insert(int ss,int dd,int ww); 		//inserting to graph
};

void graph::readgraph() 
{
	int s,d,wt,i,j;
	cout<<"Enter no of vertices:";
	cin>>n;
	  					//accepting no. of vertices
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			g[i][j]=0;		//assigning to zero
		}
	}
	
	cout<<"Enter no.of edges:";
	cin>>ne;			//accepting no. of edges
	
	for(i=0;i<ne;i++)
	{
		cout<<"Enter source ,destination and weight:";
		cin>>s>>d>>wt;		//accepting the weight at specified location
		insert(s,d,wt);						
		insert(d,s,wt);
	}	
}

void graph::insert(int ss,int dd,int ww)
{
	int i,j;
	for(i=0;i<ne;i++)
	{
		for(j=0;j<ne;j++)
		{
			g[ss][dd]=ww;		//assigning the weight at the given source & destination
		}
	}
}

void graph::display()
{
	cout<<"\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(g[i][j]!=0)
			{
				cout<<"(src,dst,weight)="<<"("<<i<<","<<j<<","<<g[i][j]<<")\n"; //displaying the sparse matrix
			}
		}
	}
}

int graph::prims(graph &span)
{
	int cost[MAX][MAX];
	int i,j,v,u,min_dist,min_cost,visited[MAX],distance[MAX],from[MAX];
	span.n=n;
	for(i=0;i<n;i++)     	  //creation of sparse matrix
	{
		for(j=0;j<n;j++)
		{
			if(g[i][j]==0)
			{
				cost[i][j]=infinity;   //assigning to infinity
			}
			else
			{
				cost[i][j]=g[i][j];   //if non zero then copy the weight
				span.g[i][j]=0;         
			}
		}
	}
	
	distance[0]=0; //initialization of distance,visited arrays
	visited[0]=1;

	for(i=1;i<n;i++)
	{
		distance[i]=cost[0][i];
		from[i]=0;
		visited[i]=0;
	}

	min_cost=0;
	ne=n-1;
	
	while(ne>0)
	{
		min_dist=infinity;  //find vertex at min_dis from tree
		for(i=1;i<n;i++)
		{
			if((visited[i]==0)&&distance[i]<min_dist)  //finding shorter distance
			{
				min_dist=distance[i];
				v=i;
			}
		}
		
		u=from[v];  //insert the min cost ege in a spanning tree
		span.g[u][v]=distance[v];
		span.g[v][u]=distance[v];
		min_cost=min_cost+cost[u][v];
		ne--;
		visited[v]=1;
		for(i=1;i<n;i++)    //update distance array
		{
			if(visited[i]==0 && (cost[i][v])<distance[i])
			{
				distance[i]=cost[v][i]; //updating the distance array
				from[i]=v;
			}
		}
		cout<<"\nMinimum Distance:"<<min_dist<<endl; //current minimum distance
		cout<<"Selected Vertex (v):"<<v<<endl;	   //prinitng selected vertex
		cout<<"Distance Array:\n";
		
		for(i=0;i<n;i++)
		{
			cout<<" "<<distance[i];       			//current distance array
		}
		cout<<"---------------------------------------";
	}
	
	return(min_cost);  //returning min cost
}

int main()
{
	graph gr,span;
	int total_cost,ch,start;
	
	do
	{
		cout<<"\nEnter your choice:\n";
		cout<<"\n1.Read Graph\n2.Display Graph\n3.Minimum Total Cost(Prims)\n4.Exit\n";
		
		cin>>ch;	
								//accepting choice
		switch(ch)
		{
			case 1: gr.readgraph();             //call to read grah
				    break;
				    
			case 2: gr.display();				//print the graph
				    break;
				    
			case 3: total_cost=gr.prims(span);
				    cout<<"Minimum Total Cost is:"<<total_cost<<endl;	
				    break;		
		}
	}while(ch!=4);
	return 0;
}

