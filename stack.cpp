#include "stdafx.h"
#include "Stack.h"
#include <iostream>
//#include <stdio>
using namespace std;

int main()
{
	stack<int> M;
	M.push(5);
	M.push(5);
	M.pop();
	cout << M.count();
	system("pause");
    return 0;
}
