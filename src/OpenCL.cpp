#include "OpenCL.h"

using namespace std;
using namespace cl;

const char *source =
	"#include <cmath>"
	"__kernel void x2(global int* a, const global int* b)"
	"{"
	"	int length = *b;"
	"	int index = get_global_id(0);"
	"	if(index < length) {"
	"		a[index] = M_PI * index;"
	"	}"
	"}";

void cl_init(Device *dev, Platform *plat)
{
	// PLATFORM INIT
	std::vector<Platform> platforms;
	Platform::get(&platforms);

	if (platforms.empty()) {
		cerr << "FATAL: No OpenCL platform detected, Aborting." << endl;
		exit(1);
	}

	Platform stdPlatform = platforms.at(0);

	// DEVICE INIT
	std::vector<Device> devices;
	stdPlatform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

	if (devices.empty()) {
		cerr << "FATAL: No OpenCL device detected, Aborting." << endl;
		exit(1);
	}
	Device stdDevice = devices.at(0);

	cout << "Found OpenCL capable Hardware: " << endl << stdDevice.getInfo<CL_DEVICE_NAME>() << "\t";
	cout << stdDevice.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() / (int) pow(2, 20) << "MiB" << endl;

	*dev = stdDevice;
	*plat = stdPlatform;
}

void cl_test()
{
	Device dev;
	Platform plat;
	cl_init(&dev, &plat);

	// MAGIC
	cl_context_properties ctxprops[3] = {
		CL_CONTEXT_PLATFORM, (cl_context_properties) (plat)(), 0
	};

	Context ctx(CL_DEVICE_TYPE_GPU, ctxprops);

	CommandQueue queue(ctx, dev);

	const int SIZE = 1000;

	cl_uint dataX[SIZE];
	for(int i=0; i<SIZE; i++) dataX[i] = i;

	Buffer bufA(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * SIZE, dataX);
	Buffer bufB(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint), (void *) &SIZE);

	Program::Sources src(1, make_pair(source, strlen(source)));
	Program prog(ctx, src);

	if(prog.build(ctx.getInfo<CL_CONTEXT_DEVICES>()) != CL_SUCCESS)
		cout << prog.getBuildInfo<CL_PROGRAM_BUILD_LOG>(dev).c_str() << endl;
	else
		cout << "Program compiled successfully" << endl;

	Kernel kernel(prog, "x2");

	kernel.setArg(0, bufA);
	kernel.setArg(1, bufB);

	queue.enqueueNDRangeKernel(kernel, NDRange(), NDRange(SIZE));
	queue.finish();

	cl_uint res[SIZE];
	queue.enqueueReadBuffer(bufA, CL_TRUE, 0, SIZE * sizeof(cl_uint), res);

	for (cl_uint i: res) cout << i << ", ";
	cout << endl;
}