#include<bits/stdc++.h>
using namespace std;
class Process
{
public:
	string pname;
	float paTime, pbTime;
	float wTime, taTime, avgWTime, avgtATime;
	//Function
	void Nhap()
	{
		cout<<"ProcessName, Process Arrival Time, Process Burst Time: ";
		cin>>pname, paTime, pbTime;
	}
};
int main()
{
	cout<<"Nhap so tien trinh: ";
	int n; cin>>n;
	Process* ls= new Process[n];
	for(int i=0;i<n;i++)
	{
		cout<<"Nhap thong tin tien trinh: "<<i<<"\n";
		ls[i].Nhap();
	}
	delete ls;
}
