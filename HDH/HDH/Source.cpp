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
	//ShortJobFirst nè
	void ShortJobFirst()
	{
		//cout << "pName   ArrTime    BurstTime         Start           TAT          Finish\n";
		Queue pQueue;
		Process* Ketqua = new Process[soLuong];
		//Sắp xếp các tiến trình theo arrival time
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
			Process k = pQueue.PopAtMin();
			if (k.pname == -1)
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
			/*cout << "Queue is:\n";
			pQueue.ViewQueue();*/
			k.staTime = time;
			k.taTime = k.pbTime + time - k.paTime;
			time += k.pbTime;
			k.fiTime = time;
			k.wTime = k.staTime - k.paTime;
			k.timeLeft = 0;
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
		cout << "\nShort Job First:\nAverage Waiting Time: "<<avgWTime<<"\nAverage Turn Around Time: "<<avgTATime<<"\n";
	}
	//Chưa xong
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
		//Sắp xếp các tiến trình theo arrival time
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

		//Lấy các process ở thời điểm đầu tiên
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
				//Cập nhật thông số của project
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
				//Cập nhật thông số của process
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
	//Xong rồi
	void ShortRemainingFirst()
	{
		cout << "pName   ArrTime    BurstTime         Start           TAT          Finish          Waiting          TimeLeft          Res\n";
		//cout << "pName   ArrTime    BurstTime         Start           TAT          Finish\n";
		Queue pQueue;
		//Process* Ketqua = new Process[soLuong];
		Queue run;
		//Sắp xếp các tiến trình theo arrival time
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
		int index = 0;
		float time = pc[0].paTime;
		Process currentProcess;
		currentProcess.timeLeft=-1;
		//Push những process cùng arrival time vào trong queue
		int j = index;
		while (j + 1 < soLuong && pc[j].paTime == pc[j + 1].paTime)
		{
			j++;
		}
		for (int k = index; k <= j; k++)
		{
			pQueue.Push(pc[k]);
		}
		index = j + 1;
		currentProcess = pQueue.PopAtMin2();
		while(true)
		{
			//Đã quăng hết vào trong queue, bây h chỉ cần lấy ra tất cả theo thử tự 
			if (index == soLuong)
			{
				//cout << "Index: " << index << " So luong: " << soLuong<<"\n";
				while (pQueue.isEmpty() != true)
				{
					if (currentProcess.timeLeft == -1)
						currentProcess = pQueue.PopAtMin2();
					if (currentProcess.staTime == -1)
					{
						currentProcess.staTime = time;
					}
					time += currentProcess.timeLeft;
					currentProcess.taTime = time - currentProcess.paTime;
					currentProcess.fiTime = time;
					currentProcess.timeLeft = 0;
					currentProcess.wTime = currentProcess.fiTime - currentProcess.paTime - currentProcess.pbTime;
					run.Push(currentProcess);
					currentProcess.Xuat();
					currentProcess.timeLeft = -1;
				}
				break;
			}
			//Đây là trường hợp xét cái đang làm thì bị đá ra
			else
			{
				//Xét trường hợp này là cái queue còn dư và cái time sau tới lâu tới múc mà cái currentProcess có thể chạy xong
				while (pc[index].paTime - currentProcess.timeLeft > time)
				{
					if (currentProcess.timeLeft == -1)
					{
						if (pQueue.isEmpty() == true) break;
						else currentProcess = pQueue.PopAtMin2();
					}
					//if (currentProcess.staTime == -1)
					{
						currentProcess.staTime = time;
					}
					time += currentProcess.timeLeft;
					currentProcess.taTime = time - currentProcess.paTime;
					currentProcess.timeLeft = 0;
					currentProcess.fiTime = time;
					currentProcess.wTime = currentProcess.fiTime - currentProcess.paTime - currentProcess.pbTime;
					run.Push(currentProcess);
					currentProcess.Xuat();
					// cout << "In ra o while thu 2\n";
					if (pQueue.isEmpty() != true)
					{
						currentProcess = pQueue.PopAtMin2();
					}
					else
					{
						currentProcess.timeLeft = -1;
					}
				}
				//Trường hợp queue trống thì sẽ như thế này
				if (pQueue.isEmpty() == true && currentProcess.timeLeft==-1)
				{
					time = pc[index].paTime;
					int j = index;
					while (j + 1 < soLuong && pc[j].paTime == pc[j + 1].paTime)
					{
						j++;
					}
					for (int k = index; k <= j; k++)
					{
						pQueue.Push(pc[k]);
					}
					index = j + 1;
					currentProcess = pQueue.PopAtMin2();
				}
				//Nếu như có process mới nhảy vô thì cập nhật lại cái timmeleft
				else
				{
					if (currentProcess.staTime == -1)
					{
						currentProcess.staTime = time;
					}
					currentProcess.timeLeft -= (pc[index].paTime - time);
					//Push những process cùng arrival time vào trong queue
					int j = index;
					time = pc[j].paTime;
					while (j + 1 < soLuong && pc[j].paTime == pc[j + 1].paTime)
					{
						j++;
					}
					for (int k = index; k <= j; k++)
					{
						pQueue.Push(pc[k]);
					}
					index = j + 1;
					
					//Xem xét thử có bị đá ra không 
					Process maybeCurrent = pQueue.ViewAtMin();
					if (currentProcess.timeLeft > maybeCurrent.timeLeft)
					{
						run.Push(currentProcess);
						currentProcess.Xuat();
						pQueue.Push(currentProcess);
						//cout << currentProcess.pname << " bi da boi " << maybeCurrent.pname<<"\n";
						currentProcess = maybeCurrent;
						pQueue.PopAtMin2();
						time = maybeCurrent.paTime;
					}
					else time = pc[j].paTime;
				}
				if (index == soLuong)
				{
					while (pQueue.isEmpty() != true)
					{
						if (currentProcess.timeLeft == -1)
							currentProcess = pQueue.PopAtMin2();
						if (currentProcess.staTime == -1)
						{
							currentProcess.staTime = time;
						}
						time += currentProcess.timeLeft;
						currentProcess.taTime = time - currentProcess.paTime;
						currentProcess.fiTime = time;
						currentProcess.timeLeft = 0;
						currentProcess.wTime = currentProcess.fiTime - currentProcess.paTime - currentProcess.pbTime;
						run.Push(currentProcess);
						currentProcess.Xuat();
						currentProcess.timeLeft = -1;
					}
					break;
				}
			}

		}
		if (currentProcess.timeLeft != -1)
		{
			if (currentProcess.staTime == -1)
			{
				currentProcess.staTime = time;
			}
			time += currentProcess.timeLeft;
			currentProcess.taTime = time - currentProcess.paTime;
			currentProcess.fiTime = time;
			currentProcess.timeLeft = 0;
			currentProcess.wTime = currentProcess.fiTime - currentProcess.paTime - currentProcess.pbTime;
			run.Push(currentProcess);
			currentProcess.Xuat();
			currentProcess.timeLeft = -1;
		}
		//Không biết vòng while này cần không nữa
		while (pQueue.isEmpty() != true)
		{
			if (currentProcess.timeLeft == -1)
				currentProcess = pQueue.PopAtMin2();
			if (currentProcess.staTime == -1)
			{
				currentProcess.staTime = time;
			}
			time += currentProcess.timeLeft;
			currentProcess.taTime = time - currentProcess.paTime;
			currentProcess.fiTime = time;
			currentProcess.timeLeft = 0;
			currentProcess.wTime = currentProcess.fiTime - currentProcess.paTime - currentProcess.pbTime;
			run.Push(currentProcess);
			currentProcess.Xuat();
			currentProcess.timeLeft = -1;
		}
		int i = 0;
		while (run.isEmpty() != true)
		{
			pc[i]=run.PopAndMerge();
			i++;
		}
		//Tính avgWating và avgTAT
		for (int i = 0; i < soLuong; i++)
		{
			avgWTime += pc[i].wTime;
			avgTATime += pc[i].taTime;
			pc[i].resTime = pc[i].staTime - pc[i].paTime;
		}
		avgWTime /= soLuong;
		avgTATime /= soLuong;
		cout << "\nShort Remaining Job First:\nAverage Waiting Time: " << avgWTime << "\nAverage Turn Around Time: " << avgTATime << "\n";
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