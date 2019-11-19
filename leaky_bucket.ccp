#include<iostream.h>
#include<dos.h>
#include<stdlib.h>

#define bucketSize 512

void bktInput(int a,int b)
{
	if(a>bucketSize)
		cout<<"\n\t\t Bucket Overflow");
	else
	{
		delay(500);
		while(a>b)
		{
			cout<<"\n\t\t"<<b<,"bytes outputted";
			a = a-b;
			delay(500);
		}
		if(a>0)
			cout<<"\n\t\t Last"<<a<<"Bytes sent \t";
			cout<<"\n\t\t Bucket output successful";
	}
}

void main()
{
	int op,pktsize;
	randomize();
	cout<<"enter output rate :";
	cin>>op;
	for(int i=1;i<=5;i++)
	{
		delay(random(1000));
		pktsize = random(1000);
		cout<<"\n Packet no "<<i<<"\t Packet size = "<<pktsize;
		bktInput(pktsize,op);
	}
}
