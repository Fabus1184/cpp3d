#pragma once

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>
#include <iostream>
#include <cmath>

void cl_init(cl::Device *dev, cl::Platform *plat);

void cl_test();
