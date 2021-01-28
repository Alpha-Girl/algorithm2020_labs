#include "Kruskal.h"
#include <fstream>
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
		vector<data> ans = Kruskal(a, weight);

		ofp.open("../output/result" + temp + ".txt", std::ios::out | std::ios::trunc);
		if (!ofp)
		{
			std::cout << "Cannot open the target file(result).\n";
			system("pause");
			return 0;
		}

		ofp << weight << endl;
		for (auto it = ans.begin(); it != ans.end(); it++)
			ofp << it->first << ' ' << it->second << endl;
		ofp.close();
	}
	system("pause");
	return 0;
}
