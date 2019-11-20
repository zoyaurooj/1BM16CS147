#include<iostream>

using namespace std;

int main()
{
	int n,mat[30][30],src,dist[10],vis[10],count = 0,min,prev[10]={0},u;	
	cout<<"enter the no of nodes"<<endl;
	cin>>n;
	cout<<"enter the distance matrix"<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>mat[i][j];
		}
	}
	cout<<"enter the source"<<endl;
	cin>>src;
	for(int j=0;j<n;j++)
		dist[j] = mat[src][j];
	for(int j=0;j<n;j++)
		vis[j] = 0;
	dist[src]=0;
	vis[src] = 1;
	count = 1;
	
	while(count!=n)
	{
		min = 999;
		for(int i=0;i<n;i++)
			if(dist[i]<min && vis[i]!=1)
			{
				min = dist[i];
				u = i;
			}
		vis[u]=1;
		count++;
		
		for(int i=0;i<n;i++)
		{
			if(min+mat[u][i]<dist[i] && vis[i]!=1)
			{				
				dist[i] = min+mat[u][i];
				prev[i] = u;
			}	
		}
	}

	for(int i=0;i<n;i++)
		cout<<"source "<<src<<" vertex "<<i<<" distance "<<dist[i]<<endl;
	
	for(int i =1;i<n;i++)
	{
		cout<<"Path from source to vertex "<<i<<endl;
		int k =0;
		int j =i;
		while(j!=k)
		{	
			cout<<j<<"<--";
			j = prev[j];			
		}
		cout<<0;
		cout<<endl;
	}



}
