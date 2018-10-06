#include <vector>
#include <iostream>
#include <cmath>
#include <ccomplex>
using namespace std;

void constructutil1(int **a,int rlow,int rhigh,int clow,int chigh,vector<vector<int> >&seg,int ridx,int cidx,int n)
{
	//cout<<"1 rlow "<<rlow<<"rhigh "<<rhigh<<"\n";
     if(clow==chigh)
     {
     	if(rlow==rhigh)
     	{
     		seg[ridx][cidx]=a[rlow][clow];
     		return;
     	}
     	return;
     }
     if(rlow!=rhigh)
     {
     	for(int i=0;i<n;i++)
     	{
     		seg[ridx][i]=seg[2*ridx+1][i]+seg[2*ridx+2][i];
     	}
     	return;
     }
     int mid=clow+(chigh-clow)>>2;
     constructutil1(a,rlow,rhigh,clow,mid,seg,ridx,2*cidx+1,n);
     constructutil1(a,rlow,rhigh,mid+1,chigh,seg,ridx,2*cidx+2,n);
     seg[ridx][cidx]=seg[ridx][2*cidx+1]+seg[ridx][2*cidx+2];
     return;
}

void constructutil(int **a,int rlow,int rhigh,int clow,int chigh,vector<vector<int> >&seg,int ridx,int cidx,int n)
{
	//cout<<"rlow "<<rlow<<"rhigh "<<rhigh<<"\n";
	if(rlow==rhigh)
	{
		constructutil1(a,rlow,rhigh,clow,chigh,seg,ridx,cidx,n);
		return;
	}
	int mid=rlow+(rhigh-rlow)>>2;
	constructutil(a,rlow,mid,clow,chigh,seg,2*ridx+1,cidx,n);
	constructutil(a,mid+1,rhigh,clow,chigh,seg,2*ridx+2,cidx,n);
	constructutil1(a,rlow,rhigh,clow,chigh,seg,ridx,cidx,n);
	return;
}

void construct(int **a,int m,int n)
{
	int x=ceil(log2(m));
	int rows=2*pow(2,x)-1;
	int y=ceil(log2(n));
	int cols=2*pow(2,y)-1;
	vector<int> b(cols);
	std::vector<std::vector<int> > seg(rows,std::vector<int> (cols));
	constructutil(a,0,m-1,0,n-1,seg,0,0,cols);
	//cout<<"out "<<"\n";
    for(int i=0;i<rows;i++)
    {
    	for(int j=0;j<cols;j++)
    		cout<<seg[i][j]<<" ";
    	cout<<"\n";
    }
    pair<int,int> c=make_pair(rows,cols);
    pair<vector<vector<int> >,pair<int,int>> masturbation=make_pair(seg,c);
    return masturbation;
}

int main()
{
	/*int a[][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	cout<<"rows "<<sizeof(a)/sizeof(a[0])<<"\n";
	cout<<"cols "<<sizeof(a[0])/sizeof(a[0][0])<<"\n";*/
	int **a,m,n;
	cout<<"rows "<<"\n";
	cin>>m;
	cout<<"cols "<<"\n";
	cin>>n;
	a=new int*[m];

	for(int i=0;i<m;i++)
	{
		a[i]=new int[n];
	}

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>a[i][j];
		}
	}

	pair<vector<vector<int> >,pair<int,int> > sex=construct(a,m,n);
	for(int i=0;i<pair.second.first;i++)
	{
		for(int j=0;j<pair.second.second;j++)
		{
			cout<<pair.first[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
