#include "Kruskal.h"
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int seq[] = {8, 64, 128, 512};
	double t[4];
	Graph a;
	for (int i = 0; i < 4; i++)
	{

		int weight = 0;
		string temp = "0";
		temp[0] = '1' + i;
		//打开文件
		std::ofstream ofp("../input/input" + temp + ".txt", std::ios::out | std::ios::trunc);
		if (!ofp)
		{
			std::cout << "Cannot open the target file(input).\n";
			system("pause");
			return 0;
		}
		//建图&保存
		InitGraph(a, seq[i], ofp);
		ofp.close();
		//调用Kruskal
		double run_time;
		LARGE_INTEGER time_start; //开始时间
		LARGE_INTEGER time_over;  //结束时间
		double dqFreq;			  //计时器频率
		LARGE_INTEGER f;		  //计时器频率
		QueryPerformanceFrequency(&f);
		dqFreq = (double)f.QuadPart;
		QueryPerformanceCounter(&time_start); //计时开始

		vector<dat> ans = Kruskal(a, weight);

		QueryPerformanceCounter(&time_over); //计时结束
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		t[i] = run_time;
		//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
		ofp.open("../output/result" + temp + ".txt", std::ios::out | std::ios::trunc);
		if (!ofp)
		{
			std::cout << "Cannot open the target file(result).\n";
			system("pause");
			return 0;
		}
		ofp << "TIME:" << t[i] <<endl;
		ofp << "WEIGHT:" << weight << endl;
		for (auto it = ans.begin(); it != ans.end(); it++)
			ofp << it->first << ' ' << it->second << endl;
		ofp.close();
	}
	system("pause");
	return 0;
}
