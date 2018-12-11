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
	//��������֮ǰ���ж�һ�µ�ǰ����������Ԫ�ظ����ǲ��Ǵ���1 �����û�б�Ҫ����
	if (left >= right)
	{
		//ֱ���˳��������  û�б�Ҫ����������
		return;
	}

	//��ʼ���п����㷨
	//���������ȱ���left������Ӧ������  ��ǰ������Ϊ�и��������
	Student *stutemp = new Student();
	int pivotstu = 0;
	stutemp = iArray[left];
	pivotstu = iArray[left]->getScore(1);

	//������ʱ������������2�˵�����
	int leftIndex = left;
	int rightIndex = right;

	while (leftIndex < rightIndex)
	{
		//��������ͨ��ѭ�����ұ߿�ʼ����һ������ֵС������
		while (leftIndex < rightIndex)
		{
			//����ұߵ���С�ڵ�ǰ�Ĳ�����ֵ
			if (pivotstu > iArray[rightIndex]->getScore(1))
			{
				//�Ҷ�����ָʾ������
				rightIndex--;
			}
			else if(pivotstu == iArray[rightIndex]->getScore(1)){
				//�����ܷ���ͬ
				if (stutemp->getScore(2) > iArray[rightIndex]->getScore(2)) { rightIndex--; }
				else if (stutemp->getScore(2) < iArray[rightIndex]->getScore(2)) { 
					iArray[leftIndex] = iArray[rightIndex];
					leftIndex++;
					break;
				}
				else if (stutemp->getScore(2) == iArray[rightIndex]->getScore(2)) {
					//���ķ�����ͬ������ѧ
					if (stutemp->getScore(3) > iArray[rightIndex]->getScore(3)) { rightIndex--; }
					else if (stutemp->getScore(3) < iArray[rightIndex]->getScore(3)) {
						iArray[leftIndex] = iArray[rightIndex];
						leftIndex++;
						break;
					}
					else if (stutemp->getScore(3) == iArray[rightIndex]->getScore(3)) {
						//��ѧ������ͬ����Ӣ��
						if (stutemp->getScore(4) > iArray[rightIndex]->getScore(4)) { rightIndex--; }
						else if (stutemp->getScore(4) < iArray[rightIndex]->getScore(4)) {
							iArray[leftIndex] = iArray[rightIndex];
							leftIndex++;
							break;
						}
						else if (stutemp->getScore(4) == iArray[rightIndex]->getScore(4)) {
							//Ӣ�������ͬ�����ۺ�
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
				//˵�������Ҷ˳��ֱ���ֵ���������
				//���ʱ�����ǾͿ��԰���������������䵽������������Ӧ�ĵط�
				iArray[leftIndex] = iArray[rightIndex];
				leftIndex++;
				//������Ҫ����ѭ���˵�ǰ�������
				break;
			}
		}

		//����߿�ʼ����һ������ֵ���������д�ϴ����µĿ�
		while (leftIndex < rightIndex)
		{
			//�����ߵ����ݴ�����ֵ ��������ָʾ����������
			if (pivotstu < iArray[leftIndex]->getScore(1))
			{
				leftIndex++;
			}
			else if (pivotstu == iArray[leftIndex]->getScore(1)) {
				//�����ܷ���ͬ
				if (stutemp->getScore(2) < iArray[leftIndex]->getScore(2)) { leftIndex++; }
				else if (stutemp->getScore(2) > iArray[leftIndex]->getScore(2)) {
					iArray[rightIndex] = iArray[leftIndex];
					rightIndex--;
					break;
				}
				else if (stutemp->getScore(2) == iArray[leftIndex]->getScore(2)) {
					//���ķ�����ͬ������ѧ
					if (stutemp->getScore(3) < iArray[leftIndex]->getScore(3)) { leftIndex++; }
					else if (stutemp->getScore(3) > iArray[leftIndex]->getScore(3)) {
						iArray[rightIndex] = iArray[leftIndex];
						rightIndex--;
						break;
					}
					else if (stutemp->getScore(3) == iArray[leftIndex]->getScore(3)) {
						//��ѧ������ͬ����Ӣ��
						if (stutemp->getScore(4) < iArray[leftIndex]->getScore(4)) { leftIndex++; }
						else if (stutemp->getScore(4) > iArray[leftIndex]->getScore(4)) {
							iArray[rightIndex] = iArray[leftIndex];
							rightIndex--;
							break;
						}
						else if (stutemp->getScore(4) == iArray[leftIndex]->getScore(4)) {
							//Ӣ�������ͬ�����ۺ�
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
				//˵������������ҵ��˱���ֵ���������
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
