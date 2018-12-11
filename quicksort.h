#pragma once

#ifndef QUICKSORTDEF_H
#define QUICKSORTDEF_H
#include "student.h"

#ifdef __cplusplus
extern "C" {
#endif

//void Swapright(Student *iArray[], int leftindex, int rightindex);

void QuickSort(Student *iArray[], int left, int right);

#ifdef __cplusplus
}
#endif

#endif // !QUICKDEF_H

