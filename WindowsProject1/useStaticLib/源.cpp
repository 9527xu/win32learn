#include"StaticLib.h"
#include<iostream>
#pragma comment(lib,"StaticLib.lib")//引入库
//"StaticLib.lib"表示为静态库路径，因为我把该静态库直接放该项目里了，所以直接写名字就好了
using namespace std;
int main()
{
	int c = add(5, 4);
	cout << c;
}