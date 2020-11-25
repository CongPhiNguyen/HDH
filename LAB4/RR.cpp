#include <iostream>
#include <string>
using namespace std;

class Process
{
public:
	int pname=0;
	float paTime=0.f, pbTime=0.f;
	float wTime = 0.f, taTime = 0.f;
	float staTime = -1.f, fiTime=0.f;
	float timeLeft = 0.f, resTime = 0.f;// use for RR and SRJF
	//Function
	void Nhap()
	{
		cout << "ProcessName, Process Arrival Time, Process Burst Time: ";
		cin >> pname>> paTime>> pbTime;
		timeLeft = pbTime;
	}
	void Xuat()
	{
		printf("%d    %8.1f\t%8.1f\t%8.1f\t%8.1f\t%8.1f\t%8.1f\t%8.1f\t%8.1f",pname,paTime,pbTime,staTime, taTime,fiTime,wTime,timeLeft,resTime);
		cout << "\n";
	}
};
class Queue
{
public:
	Process* p = NULL;
	int soLuong = 0;
	Queue()
	{

	}
	~Queue()
	{
		if(soLuong!=0)
			delete p;
	}
	void Push(Process temp)
	{
		Process* t = new Process[soLuong];
		for (int i = 0; i < soLuong; i++)
		{
			t[i] = p[i];
		}
		soLuong += 1;
		p = new Process[soLuong];
		for (int i = 0; i < soLuong-1; i++)
		{
			p[i] = t[i];
		}
		p[soLuong - 1] = temp;
		delete t;
	}
	Process Pop()
	{
		if (soLuong == 0)
		{
			Process error;
			error.pname = -1;
			return error;
		}
		else
		{
			Process res = p[0];
			for (int i = 1; i < soLuong; i++)
			{
				p[i-1] = p[i];
			}
			soLuong -= 1;
			return res;
		}
	}
	Process PopAtMin()
	{
		if (soLuong == 0)
		{
			Process error;
			error.pname = -1;
			return error;
		}
		else
		{
			float bTimeMin = p[0].pbTime;
			for (int i = 1; i < soLuong; i++)
			{
				if (p[i].pbTime < bTimeMin)
				{
					bTimeMin = p[i].pbTime;
				}
			}
			Process res;
			int index=0;
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
			for (int i = index + 1 ; i < soLuong; i++)
			{
				t[i-1] = p[i];
			}
			soLuong -= 1;
			p= new Process[soLuong];
			for (int i = 0; i < soLuong; i++)
			{
				p[i] = t[i];
			}
			delete t;
			return res;
		}
	}
	Process ViewAtMin()
	{
		float TimeMin = p[0].timeLeft;
		for (int i = 1; i < soLuong; i++)
		{
			if (p[i].timeLeft < TimeMin)
			{
				TimeMin = p[i].pbTime;
			}
		}
		Process res;
		int index = 0;
		for (int i = 0; i < soLuong; i++)
		{
			if (p[i].timeLeft == TimeMin)
			{
				res = p[i];
				index = i;
				break;
			}
		}
		return res;
	}
	Process PopAtMin2()
	{
		if (soLuong == 0)
		{
			Process error;
			error.pname = -1;
			return error;
		}
		else
		{
			float TimeMin = p[0].timeLeft;
			for (int i = 1; i < soLuong; i++)
			{
				if (p[i].timeLeft < TimeMin)
				{
					TimeMin = p[i].timeLeft;
				}
			}
			Process res;
			int index = 0;
			for (int i = 0; i < soLuong; i++)
			{
				if (p[i].timeLeft == TimeMin)
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
	}
	bool isEmpty()
	{
		if (soLuong == 0) return true;
		else return false;
	}
	void ViewQueue()
	{
		for (int i = 0; i < soLuong; i++)
		{
			printf("%d    %8.1f\t%8.1f\t%8.1f", p[i].pname, p[i].paTime, p[i].pbTime, p[i].staTime);
			cout << "\n";
		}
		
	}
	Process PopAndMerge()
	{
		Process first = p[0];
		int indexoffirst=0;
		for (int i = 1; i < soLuong; i++)
		{
			if (first.pname == p[i].pname)
			{
				first=p[i];
				for (int j = indexoffirst; j < soLuong - 1; j++)
				{
					p[j] = p[j + 1];
				}
				indexoffirst = i - 1;
				soLuong -= 1;
				/*cout << "Bop lan 1: \n";
				ViewQueue();
				cout << "\n";*/
			}
		}
		for (int j = indexoffirst; j < soLuong - 1; j++)
		{
			p[j] = p[j + 1];
		}
		soLuong -= 1;
		/*cout << "Queue ne: \n";
		this->ViewQueue();
		cout << "\n";*/
		return first;
	}
};
class Algorithm
{
public:
	Process pc[100];
	int soLuong=0;
	float avgWTime = 0.f, avgTATime = 0.f;
	void Nhap()
	{
		cout << "Nhap so tien trinh: ";
		int n; cin >> n;
		soLuong = n;
		for (int i = 0; i < n; i++)
		{
			pc[i].Nhap();
		}
	}
	void Xuat()
	{
		cout << "pName   ArrTime    BurstTime         Start           TAT          Finish          Waiting          TimeLeft          Res\n";
		for (int i = 0; i < soLuong; i++)
		{
			pc[i].Xuat();
		}
	}	
	void RoundRobin()
	{
		Queue pQueue;
		
		//Process* Ketqua = new Process[soLuong];
		Queue run;
		float RRtime=0.f;
		//Dùng cho cái chart
		Queue chart;
		float Time[100];
		int m = 0;
		//S?p x?p các ti?n trình theo arrival time
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
		cout << "Nhap RR time: ";
		cin >> RRtime;
		while (RRtime <= 0)
		{
			cout << "Nhap lai RR time: ";
			cin >> RRtime;
		}
		cout << "pName   ArrTime    BurstTime         Start           TAT          Finish          Waiting          TimeLeft          Res\n";
		float time = pc[0].paTime;
		int index = 0;

		//L?y các process ? th?i di?m d?u tiên
		while (index < soLuong && pc[index].paTime <= time)
		{
			pQueue.Push(pc[index]);
			index++;
		}
		Process current;
		while (true)
		{
			if (pQueue.isEmpty() == true)
				break;
			current = pQueue.Pop();
			if (current.timeLeft > RRtime)
			{
				//C?p nh?t thông s? c?a project
				if (current.staTime == -1)
				{
					current.staTime = time;
				}
				current.timeLeft -= RRtime;
				//Dùng cho cái chart
				Time[m] = time;
				m++;

				time += RRtime;
				while (index < soLuong && pc[index].paTime <= time)
				{
					pQueue.Push(pc[index]);
					index++;
				}
				pQueue.Push(current);
				current.Xuat();
			}
			else if (current.timeLeft == RRtime)
			{
				//C?p nh?t thông s? c?a process
				if (current.staTime == -1)
				{
					current.staTime = time;
				}
				current.timeLeft -= RRtime;
				current.fiTime = time + RRtime;
				current.taTime = current.fiTime - current.paTime;
				current.wTime = current.fiTime - current.paTime - current.pbTime;
				current.resTime = current.staTime - current.paTime;
				//Dùng cho cái chart
				Time[m] = time;
				m++;

				time += RRtime;
				while (index < soLuong && pc[index].paTime <= time)
				{
					pQueue.Push(pc[index]);
					index++;
				}
				run.Push(current);
				current.Xuat();
			}
			else if (current.timeLeft < RRtime)
			{
				if (current.staTime == -1)
				{
					current.staTime = time;
				}
				current.fiTime = time + current.timeLeft;
				current.taTime = current.fiTime - current.paTime;
				current.wTime = current.fiTime - current.paTime - current.pbTime;
				current.resTime = current.staTime - current.paTime;
				//Dùng cho cái chart
				Time[m] = time;
				m++;

				time += current.timeLeft;
				current.timeLeft = 0;
				while (index < soLuong && pc[index].paTime <= time)
				{
					pQueue.Push(pc[index]);
					index++;
				}
				run.Push(current);
				current.Xuat();

				if (pQueue.isEmpty() == true)
				{
					time = pc[index].paTime;
					while (index < soLuong && pc[index].paTime <= time)
					{
						pQueue.Push(pc[index]);
						index++;
					}
				}
			}
			chart.Push(current);
		}
		int i = 0;
		while (run.isEmpty() != true)
		{
			pc[i] = run.Pop();
			i++;
		}
		//Dùng cho cái chart
		Time[m] = time;
		m++;

		//Tính avgWating và avgTAT
		for (int i = 0; i < soLuong; i++)
		{
			avgWTime += pc[i].wTime;
			avgTATime += pc[i].taTime;
			pc[i].resTime = pc[i].staTime - pc[i].paTime;
		}
		avgWTime /= soLuong;
		avgTATime /= soLuong;
		cout << "\nRound Ronin:\nAverage Waiting Time: " << avgWTime << "\nAverage Turn Around Time: " << avgTATime << "\n";
		
		cout << "\nGantt chart:\n";
		Process k;
		while (chart.isEmpty() != true)
		{
			k = chart.Pop();
			printf("|--  %d  --",k.pname);
			i++;
		}
		cout << "|\n";
		for (int i = 0; i < m; i++)
		{
			if (Time[i] >= 100)
			{
				cout << Time[i] << "       ";
			}
			else if (Time[i] < 10)
			{
				cout << Time[i] << "         ";
			}
			else 
				cout << Time[i] << "        ";
		}
		cout << "\n\n";

	}
};
int main()
{
	Algorithm a;
	a.Nhap();
	a.RoundRobin();
	a.Xuat();
	system("PAUSE");
}

