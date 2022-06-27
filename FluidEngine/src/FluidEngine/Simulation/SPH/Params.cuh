#ifndef SIM_PARAMS_H_
#define SIM_PARAMS_H_

namespace fe {
#ifndef __DEVICE_EMULATION__
#define USE_TEX 1
#endif

#ifdef USE_TEX
	// macro does either global read or texture fetch
#define  FETCH(t,i)  tex1Dfetch(t##Tex, i)
#else
#define  FETCH(t,i)  t[i]
#endif

#include <vector_types.h>

#define PI   3.141592654f  //3.141592653589793
#define PI2  2.f*PI

	enum BndType { BND_BOX = 0, BND_CYL_Y, BND_CYL_Z, BND_CYL_YZ, BND_SPHERE, BND_PUMP_Y, BND_ALL, BND_DW = 0xFFFFffff };
	const static char BndNames[BND_ALL][20] =
	{ "Box", "Cylinder Y", "Cylinder Z", "Cylinders Y,Z", "Sphere", "Pump Y" };

	enum BndEff { BND_EFF_NONE = 0, BND_EFF_WRAP, BND_EFF_CYCLE, BND_EFF_WAVE, BEF_ALL, BEF_DW = 0xFFFFffff };
	const static char BndEffNames[BEF_ALL][20] =
	{ "None", "Wrap Z", "Cycle Z", "Wave Z" };

	enum ClrType { CLR_Dens = 0, CLR_Accel, CLR_DensAcc, CLR_Vel, CLR_VelAcc, CLR_VelRGB, CLR_None, CLR_ALL, CLR_DW = 0xFFFFffff };
	const static char ClrNames[CLR_ALL][20] =
	{ "Density", "Acceleration", "Density + Accel", "Velocity", "Velocity + Accel", "Velocity RGB", "None (last)" };
	const static int HUE_ALL = 3;
	const static ClrType HueType[HUE_ALL] = { CLR_Dens, CLR_Accel, CLR_Vel };


	//  Accelerator
	enum AccType { ACC_Off = 0, ACC_Box, ACC_CylY, ACC_CylYsm, /*CylZ..*/ ACC_ALL, ACC_DW = 0xFFFFffff };
	const static char AccNames[CLR_ALL][20] =
	{ "Off", "Box", "Cylind Y ellipse", "Cylind Y smooth" };

	struct Accel
	{
		float3 pos, size, acc;
		AccType type;
	};

	const int NumAcc = 4;  // max


	struct SimParams
	{
		//  simulation  --------
		float timeStep;
		unsigned int numParticles, maxParInCell;

		//  gravity
		float3 gravity;  float globalDamping;


		//  Grid  ---------------
		uint3 gridSize;  float3 cellSize;
		unsigned int gridSize_yx, numCells;
		//  World
		float3 worldMin, worldMax, worldSize,
			worldMinD, worldMaxD, worldSizeD;  // draw, -boundary
	    //  SPH  ---------------
		float particleR, h, h2;		// smoothing radius
		float SpikyKern, LapKern, Poly6Kern;	// kernel consts

		//  Fluid
		float particleMass, restDensity,
			stiffness, viscosity, minDens, minDist;  // stability


		//  Boundary
		float distBndHard, distBndSoft;
		float bndDamp, bndStiff, bndDampC;
		BndType bndType;  BndEff bndEffZ;

	};
}

#endif // !SIM_PARAMS_H_