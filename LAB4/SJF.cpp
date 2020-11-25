#include <iostream>
#include <string>
using namespace std;
class Process
{
public:
	int pname = 0;
	float paTime = 0.f, pbTime = 0.f;
	float wTime = 0.f, taTime = 0.f;
	float staTime = -1.f, fiTime = 0.f, resTime = 0.f;
	//Function
	void Nhap()	{
		cout << "ProcessName, Process Arrival Time, Process Burst Time: ";
		cin >> pname >> paTime >> pbTime;
	}
	void Xuat(){
		printf("%d    %8.1f\t%8.1f\t%8.1f\t%8.1f\t%8.1f\t%8.1f\t%8.1f",pname,paTime,pbTime,staTime, taTime,fiTime,wTime,resTime);
		cout<<"\n";
	}
};
class Queue
{
public:
	Process* p = NULL;
	int soLuong = 0;
	Queue(){

	}
	~Queue(){
		if (soLuong != 0)
			delete p;
	}
	void Push(Process temp){
		Process* t = new Process[soLuong];
		for (int i = 0; i < soLuong; i++)
		{
			t[i] = p[i];
		}
		soLuong += 1;
		p = new Process[soLuong];
		for (int i = 0; i < soLuong - 1; i++)
		{
			p[i] = t[i];
		}
		p[soLuong - 1] = temp;
		delete t;
	}
	Process PopAtMin(){
		float bTimeMin = p[0].pbTime;
		for (int i = 1; i < soLuong; i++)
		{
			if (p[i].pbTime < bTimeMin)
			{
				bTimeMin = p[i].pbTime;
			}
		}
		Process res;
		int index = 0;
		for (int i = 0; i < soLuong; i++)
		{
			if (p[i].pbTime == bTimeMin)
			{
				res = p[i];
				index = i;
			break;
			}
		}
		Process* t = new Process[soLuong - 1];
		for (int i = 0; i < index; i++)
		{
			t[i] = p[i];
		}
		for (int i = index + 1; i < soLuong; i++)
		{
			t[i - 1] = p[i];
		}
		soLuong -= 1;
		p = new Process[soLuong];
		for (int i = 0; i < soLuong; i++)
		{
			p[i] = t[i];
		}
		delete t;
		return res;
		}
	bool isEmpty(){
		if (soLuong == 0) return true;
		else return false;
	}
};
class Algorithm
{
public:
	Process pc[100];
	int soLuong = 0;
	float avgWTime = 0.f, avgTATime = 0.f;
	void Nhap()	{
		cout << "Nhap so tien trinh: ";
		int n; cin >> n;
		soLuong = n;
		for (int i = 0; i < n; i++)
		{
			pc[i].Nhap();
		}
	}
	void Xuat()	{
		cout << "pName   ArrTime    BurstTime         Start           TAT          Finish          Waiting          Res\n";
		for (int i = 0; i < soLuong; i++)
		{
			pc[i].Xuat();
		}
	}
	void ShortJobFirst(){
		//cout << "pName   ArrTime    BurstTime         Start           TAT          Finish\n";
		Queue pQueue;
		Process* Ketqua = new Process[soLuong];
		//Sap xep cac tien trinh theo arrival time
		for (int i = 0; i < soLuong - 1; i++)
		{
			for (int j = i + 1; j < soLuong; j++)
			{
				if (pc[i].paTime > pc[j].paTime)
				{
					Process temp = pc[i];
					pc[i] = pc[j];
					pc[j] = temp;
				}
			}
		}
		float time = pc[0].paTime;
		int so = soLuong;
		int index = 0;
		for (int i = 0; i < so; i++)
		{
			for (int j = index; j < soLuong; j++)
			{
				if (pc[j].paTime <= time)
				{
					pQueue.Push(pc[j]);
				}
				else
				{
					index = j;
					break;
				}
				if (j == soLuong - 1)
				{
					index = soLuong;
				}
			}
			Process k;
			if (pQueue.isEmpty()==true)
			{
				i--;
				time = pc[index].paTime;
				for (int j = index; j < soLuong; j++)
				{
					if (pc[j].paTime <= time)
					{
						pQueue.Push(pc[j]);
					}
					else
					{
						index = j;
						break;
					}
					if (j == soLuong - 1)
					{
						index = soLuong;
					}
				}
				continue;
			}
			else k = pQueue.PopAtMin();
			k.staTime = time;
			k.taTime = k.pbTime + time - k.paTime;
			time += k.pbTime;
			k.fiTime = time;
			k.wTime = k.staTime - k.paTime;
			k.resTime=k.staTime-k.paTime;
			Ketqua[i] = k;
			//Ketqua[i].Xuat();
		}
		for (int i = 0; i < soLuong; i++)
		{
			pc[i] = Ketqua[i];
		}
		delete Ketqua;
		//Tính avgWating và avgTAT
		for (int i = 0; i < soLuong; i++)
		{
			avgWTime += pc[i].wTime;
			avgTATime += pc[i].taTime;
		}
		avgWTime /= soLuong;
		avgTATime /= soLuong;
		cout << "\nShort Job First:\nAverage Waiting Time: " << avgWTime << "\nAverage Turn Around Time: " << avgTATime << "\n";
	}
};

int main()
{
	Algorithm a;
	a.Nhap();
	a.ShortJobFirst();
	a.Xuat();
	system("PAUSE");
	return 0;
}
