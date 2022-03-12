#include "OpenCL.h"

using namespace std;
using namespace cl;

Device *dev = nullptr;
Platform *plat = nullptr;
Context *ctx = static_cast<Context *>(malloc(sizeof(Context)));
CommandQueue *queue = static_cast<CommandQueue *>(malloc(sizeof(CommandQueue)));
Program *prog = static_cast<Program *>(malloc(sizeof(Program)));
cl_uint compute_units;

const char *kernel_src =
	"__kernel void v3_x_v3(const __global float *a, const __global float *b, __global float *out){"
	"	int index = get_global_id(0);"
	"	if(index < 3){"
	" 		out[index] = (a[index] * b[index]);"
	"	}"
	"}"
	"__kernel void vadd(const __global float *a, const __global float *b, __global float *out, __global const int *length){"
	"	int index = get_global_id(0);"
	"	if(index < *length){"
	"		for(int i=0; i<250; i++) out[index + i] = atan2(sin(a[index + i]) / cos(a[index + i]), tan(b[index + i]) * tanh(b[index+i]));"
	"	}"
	"}"
	"__kernel void v3_x_float(const float *a, const float *b, __global float *out){"
	"	int index = get_global_id(0);"
	"	if(index < 3){"
	"		out[index] = a[index] * *b;"
	"	}"
	"}"
	"__kernel void v3_p_v3(const float *a, const float *b, float *out){"
	"	int index = get_global_id(0);"
	"	if(index < 3){"
	"		out[index] = a[index] + b[index];"
	"	}"
	"}";

void cl_init()
{
	// PLATFORM INIT
	std::vector<Platform> platforms;
	Platform::get(&platforms);

	if (platforms.empty()) {
		cerr << "FATAL: No OpenCL platform detected, Aborting." << endl;
		exit(1);
	}

	plat = &platforms.at(0);

	// DEVICE INIT
	std::vector<Device> devices;
	plat->getDevices(CL_DEVICE_TYPE_GPU, &devices);

	if (devices.empty()) {
		cerr << "FATAL: No OpenCL device detected, Aborting." << endl;
		exit(1);
	}
	dev = &devices.at(0);

	compute_units = dev->getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();

	cout << "Found OpenCL capable Hardware: " << endl << dev->getInfo<CL_DEVICE_NAME>() << "\t";
	cout << dev->getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() / (int) pow(2, 20) << "MiB" << "\t";
	cout << "with " << compute_units << " compute units" << endl;
	cout << "max local work size: " << dev->getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << "\t";
	cout << "max work item sizes:" << dev->getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>().at(0) << endl;

	cl_context_properties ctxprops[3] = {
		CL_CONTEXT_PLATFORM, (cl_context_properties) (*plat)(), 0
	};

	*ctx = Context(CL_DEVICE_TYPE_GPU, ctxprops);
	*queue = CommandQueue(*ctx, *dev);

	Program::Sources src(1, make_pair(kernel_src, strlen(kernel_src)));
	*prog = Program(*ctx, src);

	if (prog->build(ctx->getInfo<CL_CONTEXT_DEVICES>()) != CL_SUCCESS) {
		cerr << "FATAL: Error building kernel: " << endl;
		cerr << prog->getBuildInfo<CL_PROGRAM_BUILD_LOG>(*dev) << endl;
		exit(1);
	} else
		cout << "Kernel compiled successfully" << endl;
}

float cl_v3_x_v3(const Vector3D a, const Vector3D b)
{
	Kernel kernel(*prog, "v3_x_v3");
	float res[] = {0, 0, 0};

	Buffer v1buf(*ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * 3, (void *) &a);
	Buffer v2buf(*ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * 3, (void *) &b);
	Buffer resbuf(*ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float) * 3, res);

	kernel.setArg(0, v1buf);
	kernel.setArg(1, v2buf);
	kernel.setArg(2, resbuf);

	queue->enqueueNDRangeKernel(kernel, NDRange(), NDRange(compute_units * 7 * 64), NDRange(64));
	queue->finish();

	queue->enqueueReadBuffer(resbuf, CL_TRUE, 0, sizeof(float) * 3, res);
	return res[0] + res[1] + res[2];
}

void cl_vadd(float *a, float *b, float *res, int length)
{
	Kernel kernel(*prog, "vadd");

	int ops = 500;
	int nlength = ceil(length / ops);

	Buffer v1buf(*ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * length, a);
	Buffer v2buf(*ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * length, b);
	Buffer resbuf(*ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(float) * length, res);
	Buffer lenbuf(*ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), &nlength);

	kernel.setArg(0, v1buf);
	kernel.setArg(1, v2buf);
	kernel.setArg(2, resbuf);
	kernel.setArg(3, lenbuf);

	auto start = chrono::steady_clock::now();
	cout << "gws: " << nlength << "\tlws: " << nlength / ops << endl;
	queue->enqueueNDRangeKernel(kernel, NDRange(), NDRange(nlength), NDRange(nlength / ops));
	queue->finish();
	auto end = chrono::steady_clock::now();
	cout << " - OpenCL took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms " << endl;

	queue->enqueueReadBuffer(resbuf, CL_TRUE, 0, sizeof(float) * length, res);
}
