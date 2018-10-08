#include <vector>
#include <iostream>
#include <cmath>
#include <ccomplex>
using namespace std;
#include <bits/stdc++.h>
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

pair<vector<vector<int> >,pair<int,int>> construct(int **a,int m,int n)
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
    pair<vector<vector<int> >,pair<int,int> > mastur=make_pair(seg,c);
    return mastur;
}

void print1(vector<vector<int> > seg,int row,int col,int **a,int rlow,int rhigh,int clow,int chigh,int ridx,int cidx)
{
	if(clow==chigh)
	{
		cout<<"equal"<<"\n";
		if(rlow==rhigh)
		{
			cout<<"ridx "<<ridx<<"cidx "<<cidx<<"\n";
			cout<<"sum from rlow "<<rlow<<" rhigh "<<rhigh<<" clow "<<clow<<" chigh "<<chigh<<" "<<seg[ridx][cidx]<<"\n";
			return;
		}
		return;
	}
	if(rlow!=rhigh)
	{
		for(int i=0;i<col;i++)
		{
			cout<<"sum from rlow "<<rlow<<" rhigh "<<rhigh<<" clow "<<clow<<" chigh "<<chigh<<" "<<seg[ridx][cidx]<<"\n";
		}
		return;
	}
	int mid=clow+(chigh-clow)>>2;
	print1(seg,row,col,a,rlow,rhigh,clow,mid,ridx,2*cidx+1);
	print1(seg,row,col,a,rlow,rhigh,mid+1,chigh,ridx,2*cidx+2);
	cout<<"sum from rlow "<<rlow<<" rhigh "<<rhigh<<" clow "<<clow<<" chigh "<<chigh<<" "<<seg[ridx][cidx]<<"\n";
	return;
}

void print(vector<vector<int> >seg,int row,int col,int **a,int rlow,int rhigh,int clow,int chigh,int ridx,int cidx)
{
	if(rlow==rhigh)
	{
		print1(seg,row,col,a,rlow,rhigh,clow,chigh,ridx,cidx);
		return;
	}
	int mid=rlow+(rhigh-rlow)>>2;
	print(seg,row,col,a,rlow,mid,clow,chigh,2*ridx+1,cidx);
	print(seg,row,col,a,mid+1,rhigh,clow,chigh,2*ridx+2,cidx);
	print1(seg,row,col,a,rlow,rhigh,clow,chigh,ridx,cidx);
	return;
}

int main()
{
	/*
	*
	*code for 2d segment tree
	*a is the matrix to work
	*m is row n is col
	*segment is the 2d segment tree
	*/
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

	pair<vector<vector<int> >,pair<int,int> > segment=construct(a,m,n);
	for(int i=0;i<segment.second.first;i++)
	{
		for(int j=0;j<segment.second.second;j++)
		{
			cout<<segment.first[i][j]<<" ";
		}
		cout<<"\n";
	}
	print(segment.first,segment.second.first,segment.second.second,a,0,m-1,0,n-1,0,0);
	return 0;
}
