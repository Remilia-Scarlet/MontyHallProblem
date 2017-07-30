#include <random>
#include <assert.h>
#include <iostream>
std::default_random_engine RandomEngine;
int CreateSurprise()
{
	std::uniform_int_distribution<int> u(0, 2);
	return u(RandomEngine);
}

int ChooseOne()
{
	std::uniform_int_distribution<int> u(0, 2);
	return u(RandomEngine);
}

int ExcludeOne(int surprise,int chosenIndex)
{
	if (surprise != chosenIndex)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i != surprise && i != chosenIndex)
				return i;
		}
	}
	else
	{
		std::uniform_int_distribution<int> u(0, 1);
		int choose = u(RandomEngine);
		for (int i = 0; i < 3; ++i)
		{
			if(i == surprise)
				continue;
			if (choose == 0)
				return i;
			--choose;
		}
	}

	
	assert(false);//unreachable code
	return 0;
}

int ChangeChoose(int oldChoose, int excludedIndex)
{
	static bool WILL_CHANGE = 1;
	if (WILL_CHANGE)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i != oldChoose && i != excludedIndex)
				return i;
		}
	}
	else
	{
		return oldChoose;
	}
	assert(false);//unreachable code
	return 0;
}

bool Judge(int choose, int surprise)
{
	if (choose == surprise)
		return true;
	return false;
}

int main()
{
	int tryNum = 100000;
	int succeed = 0;
	while (tryNum--)
	{
		int surprise = CreateSurprise();
		int index = ChooseOne();
		int excludedIndex = ExcludeOne(surprise, index);
		int index2 = ChangeChoose(index, excludedIndex);
		bool result = Judge(index2, surprise);
		if (result)
			succeed++;
	}
	std::cout << (double)succeed / (double)100000 << std::endl;
	system("pause");
}