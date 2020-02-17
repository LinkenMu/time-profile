// timecounter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "timeprofile.h"
#include  <iostream>

using namespace std;
int main()
{
	//ProfileTimer time;
	ProfileTimer time("profile.txt");
	for (int i = 0; i < 10; i++)
	{
		time.Start("item_i");
		for (int j = 0; j < 10; j++)
		{
			time.Start("item_j");
			cout << "cout "<<i << j << " ..." << endl;
			time.Stop("item_j");
		}
		time.Stop("item_i");
	}
	time.Report();
	system("pause");

    return 0;
}

