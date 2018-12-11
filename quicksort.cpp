#include "quicksort.h"
#include <iostream>
#include "student.h"

using namespace std;

void Swapright(Student *iArray[], int &leftindex, int rightindex) {
	Student *temp = new Student();
	iArray[leftindex] = iArray[rightindex];
	leftindex++;
}


void QuickSort(Student *iArray[], int left, int right)
{
	//快速排序之前先判断一下当前待排序数组元素个数是不是大于1 否则就没有必要排序
	if (left >= right)
	{
		//直接退出排序代码  没有必要进行排序了
		return;
	}

	//开始进行快排算法
	//首先我们先保存left索引对应的数据  当前数据作为切割数组的轴
	Student *stutemp = new Student();
	int pivotstu = 0;
	stutemp = iArray[left];
	pivotstu = iArray[left]->getScore(1);

	//定义临时变量保存数组2端的索引
	int leftIndex = left;
	int rightIndex = right;

	while (leftIndex < rightIndex)
	{
		//现在我们通过循环从右边开始搜索一个比轴值小的数据
		while (leftIndex < rightIndex)
		{
			//如果右边的数小于当前的参数轴值
			if (pivotstu > iArray[rightIndex]->getScore(1))
			{
				//右端索引指示器左移
				rightIndex--;
			}
			else if(pivotstu == iArray[rightIndex]->getScore(1)){
				//两者总分相同
				if (stutemp->getScore(2) > iArray[rightIndex]->getScore(2)) { rightIndex--; }
				else if (stutemp->getScore(2) < iArray[rightIndex]->getScore(2)) { 
					iArray[leftIndex] = iArray[rightIndex];
					leftIndex++;
					break;
				}
				else if (stutemp->getScore(2) == iArray[rightIndex]->getScore(2)) {
					//语文分数相同，比数学
					if (stutemp->getScore(3) > iArray[rightIndex]->getScore(3)) { rightIndex--; }
					else if (stutemp->getScore(3) < iArray[rightIndex]->getScore(3)) {
						iArray[leftIndex] = iArray[rightIndex];
						leftIndex++;
						break;
					}
					else if (stutemp->getScore(3) == iArray[rightIndex]->getScore(3)) {
						//数学分数相同，比英语
						if (stutemp->getScore(4) > iArray[rightIndex]->getScore(4)) { rightIndex--; }
						else if (stutemp->getScore(4) < iArray[rightIndex]->getScore(4)) {
							iArray[leftIndex] = iArray[rightIndex];
							leftIndex++;
							break;
						}
						else if (stutemp->getScore(4) == iArray[rightIndex]->getScore(4)) {
							//英语分数相同，比综合
							if (stutemp->getScore(5) > iArray[rightIndex]->getScore(5)) { rightIndex--; }
							else if (stutemp->getScore(5) < iArray[rightIndex]->getScore(5)) {
								iArray[leftIndex] = iArray[rightIndex];
								leftIndex++;
								break;
							}
							else {
								rightIndex--;
							}
						}
					}
				}
			}
			else
			{
				//说明我们右端出现比轴值更大的数据
				//这个时候我们就可以把这个更大的数据填充到索引轴索引对应的地方
				iArray[leftIndex] = iArray[rightIndex];
				leftIndex++;
				//我们需要跳出循环了当前工作完毕
				break;
			}
		}

		//从左边开始搜索一个比轴值更大的数填写上次留下的坑
		while (leftIndex < rightIndex)
		{
			//如果左边的数据大于轴值 我们索引指示器就往右走
			if (pivotstu < iArray[leftIndex]->getScore(1))
			{
				leftIndex++;
			}
			else if (pivotstu == iArray[leftIndex]->getScore(1)) {
				//两者总分相同
				if (stutemp->getScore(2) < iArray[leftIndex]->getScore(2)) { leftIndex++; }
				else if (stutemp->getScore(2) > iArray[leftIndex]->getScore(2)) {
					iArray[rightIndex] = iArray[leftIndex];
					rightIndex--;
					break;
				}
				else if (stutemp->getScore(2) == iArray[leftIndex]->getScore(2)) {
					//语文分数相同，比数学
					if (stutemp->getScore(3) < iArray[leftIndex]->getScore(3)) { leftIndex++; }
					else if (stutemp->getScore(3) > iArray[leftIndex]->getScore(3)) {
						iArray[rightIndex] = iArray[leftIndex];
						rightIndex--;
						break;
					}
					else if (stutemp->getScore(3) == iArray[leftIndex]->getScore(3)) {
						//数学分数相同，比英语
						if (stutemp->getScore(4) < iArray[leftIndex]->getScore(4)) { leftIndex++; }
						else if (stutemp->getScore(4) > iArray[leftIndex]->getScore(4)) {
							iArray[rightIndex] = iArray[leftIndex];
							rightIndex--;
							break;
						}
						else if (stutemp->getScore(4) == iArray[leftIndex]->getScore(4)) {
							//英语分数相同，比综合
							if (stutemp->getScore(5) < iArray[leftIndex]->getScore(5)) { leftIndex++; }
							else if (stutemp->getScore(5) > iArray[leftIndex]->getScore(5)) {
								iArray[rightIndex] = iArray[leftIndex];
								rightIndex--;
								break;
							}
							else {
								leftIndex++;
							}
						}
					}
				}
			}
			else
			{
				//说明我们在左端找到了比轴值更大的数据
				iArray[rightIndex] = iArray[leftIndex];
				rightIndex--;
				break;
			}
		}
	}

	iArray[leftIndex] = stutemp;

	QuickSort(iArray, left, leftIndex - 1);
	QuickSort(iArray, rightIndex + 1, right);
}
