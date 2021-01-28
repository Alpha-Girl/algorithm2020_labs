#include "lab4_1.hpp"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL));
	int seq[] = {8, 64, 128, 512};
	Graph a;
	for (int i = 0; i < 4; i++)
	{
		int weight = 0;
		string temp = "0";
		temp[0] = '1' + i;
		string t="../input/input10.txt";
		std::ofstream ofp;
		ofp.open(t, std::ios::out | std::ios::trunc);
		//打开文件
		if (!ofp)
		{
			std::cout << "Cannot open the target file1\n";
			system("pause");
			return 0;
		}

		InitGraph(a, seq[i], ofp);
		ofp.close();
		vector<dat> ans = Kruskal(a, weight);

		ofp.open("../output/result" + temp + ".txt", std::ios::out | std::ios::trunc);
		if (!ofp)
		{
			std::cout << "Cannot open the target file2\n";
			system("pause");
			return 0;
		}

		ofp << weight << endl;
		for (vector<edge>::iterator it = ans.begin(); it != ans.end(); ++it)
			ofp << it->first << ' ' << it->second << endl;
		ofp.close();
	}
	//ShowGraph(a);
	system("pause");
	return 0;
}
