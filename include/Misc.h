#pragma once

#include <iostream>
#include <bit>

#define DEFAULT_WIDTH 10

template<typename T>
void printArray(T arr[], int size, int width = DEFAULT_WIDTH);

float fast_inv_sqrt(float number);