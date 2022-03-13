#pragma once

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>
#include <iostream>
#include <cmath>
#include <chrono>

#include "Misc.h"
#include "Vector3D.h"

void cl_init();

[[maybe_unused]] float cl_v3_x_v3(Vector3D a, Vector3D b);
void cl_vadd(float *a, float *b, float *res, int length);
void cl_transform(int width, int height, Vector3D a, Vector3D xu, Vector3D yu, int *out);
