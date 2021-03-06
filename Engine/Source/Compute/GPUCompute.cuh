#include <string>

extern "C" {
	struct DeviceInfo {
		std::string name;
		int clockRate; // hz
		int globalMemory; // bytes
		bool concurrentKernels;
		// int coreCount;
	};

	bool InitCUDA(DeviceInfo* deviceInfo);
}