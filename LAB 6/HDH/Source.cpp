#include <iostream>
#include <vector>
using namespace std;
int n;
int a[1000];
int defau[] = { 1,9,5,2,2,0,0,6,0,0,7};
int frames=0;
int page[100] = { -1 };
int pages[100][1000];
int algo = 0;
vector<int> pageFault;
int MainMenu()
{
	cout << "--- Page Replacement algorithm ---\n";
	cout << "1. Default referenced sequence\n";
	cout << "2. Manual input sequence\n";
	int choice = 0;
	while (choice != 1 && choice != 2)
	{
		cout << "Nhap lua chon: ";
		cin >> choice;
	}
	return choice;
}
void InputMannual()
{
	cout << "Nhap do dai cua chuoi: "; 
	cin >> n;
	while (n <= 0)
	{
		cout << "Nhap lai: ";
		cin >> n;
	}
	cout << "Nhap chuoi: ";
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
}
void ChooseAlgo()
{
	cout << " - -- Page Replacement algorithm-- -\n1. FIFO algorithm\n";
	cout<<"2. OPT algorithm\n3. LRU algorithm\n";
	while (algo != 1 && algo != 2 && algo != 3)
	{
		cout << "Input type of algorithm: ";
		cin >> algo;
	}
}
int findInPage(int num)
{
	for (int i = 0; i < frames; i++)
	{
		if (page[i] == num)
			return i;
	}
	return -1;
}
void Print()
{
	cout << "-- - Page Replacement algorithm-- -\n";
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < frames; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pages[i][j] == -1) cout << "  ";
			else cout << pages[i][j] << " ";
		}
		cout << "\n";
	}
	int fault=0;
	for (int i = 0; i < pageFault.size(); i++)
	{
		if (pageFault[i] == -1)
		{
			cout << "* ";
			fault++;
		}
		else cout << "  ";
	}
	cout << "\n";
	cout<< "Number of Page Fault : "<< fault;
}
void FIFO()
{
	pageFault.resize(n);
	int index = 0;
	for (int i = 0; i < frames; i++)
	{
		page[i] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		if (findInPage(a[i]) == -1)
		{
			pageFault[i]=-1;
			page[index] = a[i];
			index++;
			if (index == frames)
			{
				index = 0;
			}
		}
		for (int j = 0; j < frames; j++)
		{
			pages[j][i] = page[j];
		}
	}
	Print();
}
void LRU()
{
	pageFault.resize(n);
	int index = 0;
	for (int i = 0; i < frames; i++)
	{
		page[i] = -1;
	}
	int timespan[100];
	for (int i = 0; i < frames; i++)
	{
		timespan[i] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		if (findInPage(a[i]) == -1)
		{
			int indexmin = 0;
			pageFault[i] = -1;
			for (int j = 0; j < frames; j++)
			{
				if (timespan[indexmin] > timespan[j])
				{
					indexmin = j;
				}
			}
			page[indexmin] = a[i];
			timespan[indexmin] = i;
		}
		else
		{
			timespan[findInPage(a[i])] = i;
		}
		for (int j = 0; j < frames; j++)
		{
			pages[j][i] = page[j];
		}
	}
	Print();
}
int Page_to_Swap(int * timespan, int step)
{
	for (int i = 0; i < frames; i++)
	{
		if (page[i] == -1)
			return i;
	}
	vector<int> notFound;
	int futureIndex[100];
	for (int i = 0; i < frames; i++)
	{
		int values = page[i];
		int j;
		for (j = step; j < n; j++)
		{
			if (a[j] == values)
			{
				futureIndex[i] = j;
				break;
			}
		}
		if (j >= n)
		{
			futureIndex[i] = -1;
			notFound.push_back(i);
		}
	}
	if (notFound.size() == 0)
	{
		int maxIndex = 0;
		for (int i = 0; i < frames; i++)
		{
			if (futureIndex[maxIndex] < futureIndex[i])
			{
				maxIndex = i;
			}
		}
		return maxIndex;
	}
	else
	{
		int minIndex = notFound[0];
		for (int i = 0; i < notFound.size(); i++)
		{
			if (timespan[notFound[i]] < timespan[minIndex])
			{
				minIndex = notFound[i];
			}
		}
		return minIndex;
	}

}
void OPT()
{
	pageFault.resize(n);
	// Khởi tạo các trang
	for (int i = 0; i < n; i++)
	{
		page[i] = -1;
	}
	// Khởi tạo các timespan
	int timespan[100];
	for (int i = 0; i < frames; i++)
	{
		timespan[i] = -1;
	}
	// Chạy các trang
	for (int i = 0; i < n; i++)
	{
		if (findInPage(a[i]) == -1)
		{
			pageFault[i] = -1;
			int swapPage = Page_to_Swap(timespan, i);
			page[swapPage] = a[i];
			timespan[swapPage] = i;
		}
		else
		{
			timespan[findInPage(a[i])] = i;
		}
		for (int j = 0; j < frames; j++)
		{
			pages[j][i] = page[j];
		}
	}
	Print();
}
int main()
{
	int type = MainMenu();
	if (type == 1)
	{
		n = 11;
		for (int i = 0; i < 11; i++)
		{
			a[i] = defau[i];
		}
	}
	else
	{
		InputMannual();
	}
	cout << "--- Page Replacement algorithm ---\nInput page frames : ";
	cin >> frames;
	while (frames <= 0)
	{
		cout << "Wrong, Input page frames again: ";
		cin >> frames;
	}
	ChooseAlgo();
	switch (algo)
	{
		case(1):
		{
			FIFO();
			break;
		}
		case(2):
		{
			OPT();
			break;
		}
		case(3):
		{
			LRU();
			break;
		}
	}
	return 0;
}