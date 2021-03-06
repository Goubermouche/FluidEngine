#include "GPUCompute.cuh"

#include <stdio.h>
#include "cuda_runtime_api.h"

extern "C" {
	bool InitCUDA(DeviceInfo* deviceInfo) {
		int deviceCount;
		cudaGetDeviceCount(&deviceCount);

		if (deviceCount == 0) {
			// No device that could potentially support CUDA has been detected
			return false;
		}

		int device;
		cudaGetDevice(&device);

		struct cudaDeviceProp deviceProperties;
		cudaGetDeviceProperties(&deviceProperties, device);

		if (deviceProperties.major < 1 || (device == 0 && deviceProperties.major == 9999 && deviceProperties.minor == 9999)) {
			// No device supporting CUDA has been detected
			return false;
		}

		deviceInfo->name = deviceProperties.name;
		deviceInfo->clockRate = deviceProperties.memoryClockRate;
		deviceInfo->globalMemory = deviceProperties.totalGlobalMem;
		deviceInfo->concurrentKernels = deviceProperties.concurrentKernels;
		// deviceInfo->coreCount = _ConvertSMVer2Cores(deviceProperties.major, deviceProperties.minor) * deviceProperties.multiProcessorCount;

        // GetSPcores(deviceProperties);
		
		// Currently, this doesn't do anything since we're already getting the active device 
		// with the cudaGetDevice function, but this will be useful later on when support
		// for multiple GPU's is implemented
		cudaSetDevice(device);
		
		return true;
	}
}