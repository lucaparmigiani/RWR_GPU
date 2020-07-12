#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wcast-qual"
#define __NV_MODULE_ID _21_cudaExpMatrix_cpp1_ii_9c0dc923
#define __NV_CUBIN_HANDLE_STORAGE__ extern
#if !defined(__CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__)
#define __CUDA_INCLUDE_COMPILER_INTERNAL_HEADERS__
#endif
#include "crt/host_runtime.h"
#include "cudaExpMatrix.fatbin.c"
extern void __device_stub__Z24matrixTransposeKernelShMPKdPdii(const double *, double *, int, int);
extern void __device_stub__Z8RWR_initPdPiidS0_(double *__restrict__, int *__restrict__, const int, const double, int *);
extern void __device_stub__Z8RWR_CUDAPiS_S_S_PdS0_iS_(int *__restrict__, int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, const int, int *);
extern void __device_stub__Z7RWR_mulPdS_S_Piid(double *__restrict__, double *__restrict__, double *__restrict__, int *__restrict__, const int, const double);
extern void __device_stub__Z9RWR_init3Pddi(double *__restrict__, const double, const int);
extern void __device_stub__Z9RWR_CUDA3PiS_S_PdS0_S0_dii(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int);
extern void __device_stub__Z9RWR_init4Pddi(double *__restrict__, const double, const int);
extern void __device_stub__Z9RWR_CUDA4PiS_S_PdS0_S0_dii(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int);
extern void __device_stub__Z9RWR_init5Pddi(double *__restrict__, const double, const int);
extern void __device_stub__Z9RWR_CUDA5PiS_S_PdS0_S0_diii(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int, const int);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll(void) __attribute__((__constructor__));
void __device_stub__Z24matrixTransposeKernelShMPKdPdii(const double *__par0, double *__par1, int __par2, int __par3){__cudaLaunchPrologue(4);__cudaSetupArgSimple(__par0, 0UL);__cudaSetupArgSimple(__par1, 8UL);__cudaSetupArgSimple(__par2, 16UL);__cudaSetupArgSimple(__par3, 20UL);__cudaLaunch(((char *)((void ( *)(const double *, double *, int, int))matrixTransposeKernelShM)));}
# 7 "/home/luca/@focus/RWR-GPU/RWR/src/device/util/cuda_transpose.cu"
void matrixTransposeKernelShM( const double *__cuda_0,double *__cuda_1,int __cuda_2,int __cuda_3)
# 9 "/home/luca/@focus/RWR-GPU/RWR/src/device/util/cuda_transpose.cu"
{__device_stub__Z24matrixTransposeKernelShMPKdPdii( __cuda_0,__cuda_1,__cuda_2,__cuda_3);
# 22 "/home/luca/@focus/RWR-GPU/RWR/src/device/util/cuda_transpose.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z8RWR_initPdPiidS0_( double *__restrict__ __par0,  int *__restrict__ __par1,  const int __par2,  const double __par3,  int *__par4) {  double *__T0;
 int *__T1;
__cudaLaunchPrologue(5); __T0 = __par0; __cudaSetupArgSimple(__T0, 0UL); __T1 = __par1; __cudaSetupArgSimple(__T1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaSetupArgSimple(__par3, 24UL); __cudaSetupArgSimple(__par4, 32UL); __cudaLaunch(((char *)((void ( *)(double *__restrict__, int *__restrict__, const int, const double, int *))RWR_init))); }
# 6 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
void RWR_init( double *__restrict__ __cuda_0,int *__restrict__ __cuda_1,const int __cuda_2,const double __cuda_3,int *__cuda_4)
# 10 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
{__device_stub__Z8RWR_initPdPiidS0_( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4);
# 17 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z8RWR_CUDAPiS_S_S_PdS0_iS_( int *__restrict__ __par0,  int *__restrict__ __par1,  int *__restrict__ __par2,  int *__restrict__ __par3,  double *__restrict__ __par4,  double *__restrict__ __par5,  const int __par6,  int *__par7) {  int *__T2;
 int *__T3;
 int *__T4;
 int *__T5;
 double *__T6;
 double *__T7;
__cudaLaunchPrologue(8); __T2 = __par0; __cudaSetupArgSimple(__T2, 0UL); __T3 = __par1; __cudaSetupArgSimple(__T3, 8UL); __T4 = __par2; __cudaSetupArgSimple(__T4, 16UL); __T5 = __par3; __cudaSetupArgSimple(__T5, 24UL); __T6 = __par4; __cudaSetupArgSimple(__T6, 32UL); __T7 = __par5; __cudaSetupArgSimple(__T7, 40UL); __cudaSetupArgSimple(__par6, 48UL); __cudaSetupArgSimple(__par7, 56UL); __cudaLaunch(((char *)((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, const int, int *))RWR_CUDA))); }
# 20 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
void RWR_CUDA( int *__restrict__ __cuda_0,int *__restrict__ __cuda_1,int *__restrict__ __cuda_2,int *__restrict__ __cuda_3,double *__restrict__ __cuda_4,double *__restrict__ __cuda_5,const int __cuda_6,int *__cuda_7)
# 27 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
{__device_stub__Z8RWR_CUDAPiS_S_S_PdS0_iS_( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7);
# 47 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z7RWR_mulPdS_S_Piid( double *__restrict__ __par0,  double *__restrict__ __par1,  double *__restrict__ __par2,  int *__restrict__ __par3,  const int __par4,  const double __par5) {  double *__T8;
 double *__T9;
 double *__T10;
 int *__T11;
__cudaLaunchPrologue(6); __T8 = __par0; __cudaSetupArgSimple(__T8, 0UL); __T9 = __par1; __cudaSetupArgSimple(__T9, 8UL); __T10 = __par2; __cudaSetupArgSimple(__T10, 16UL); __T11 = __par3; __cudaSetupArgSimple(__T11, 24UL); __cudaSetupArgSimple(__par4, 32UL); __cudaSetupArgSimple(__par5, 40UL); __cudaLaunch(((char *)((void ( *)(double *__restrict__, double *__restrict__, double *__restrict__, int *__restrict__, const int, const double))RWR_mul))); }
# 50 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
void RWR_mul( double *__restrict__ __cuda_0,double *__restrict__ __cuda_1,double *__restrict__ __cuda_2,int *__restrict__ __cuda_3,const int __cuda_4,const double __cuda_5)
# 55 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
{__device_stub__Z7RWR_mulPdS_S_Piid( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5);
# 64 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel1.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z9RWR_init3Pddi( double *__restrict__ __par0,  const double __par1,  const int __par2) {  double *__T12;
__cudaLaunchPrologue(3); __T12 = __par0; __cudaSetupArgSimple(__T12, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaLaunch(((char *)((void ( *)(double *__restrict__, const double, const int))RWR_init3))); }
# 3 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel3.cu"
void RWR_init3( double *__restrict__ __cuda_0,const double __cuda_1,const int __cuda_2)
# 5 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel3.cu"
{__device_stub__Z9RWR_init3Pddi( __cuda_0,__cuda_1,__cuda_2);




}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z9RWR_CUDA3PiS_S_PdS0_S0_dii( int *__restrict__ __par0,  int *__restrict__ __par1,  int *__restrict__ __par2,  double *__restrict__ __par3,  double *__restrict__ __par4,  double *__restrict__ __par5,  const double __par6,  const int __par7,  const int __par8) {  int *__T13;
 int *__T14;
 int *__T15;
 double *__T16;
 double *__T17;
 double *__T18;
__cudaLaunchPrologue(9); __T13 = __par0; __cudaSetupArgSimple(__T13, 0UL); __T14 = __par1; __cudaSetupArgSimple(__T14, 8UL); __T15 = __par2; __cudaSetupArgSimple(__T15, 16UL); __T16 = __par3; __cudaSetupArgSimple(__T16, 24UL); __T17 = __par4; __cudaSetupArgSimple(__T17, 32UL); __T18 = __par5; __cudaSetupArgSimple(__T18, 40UL); __cudaSetupArgSimple(__par6, 48UL); __cudaSetupArgSimple(__par7, 56UL); __cudaSetupArgSimple(__par8, 60UL); __cudaLaunch(((char *)((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int))RWR_CUDA3))); }
# 12 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel3.cu"
void RWR_CUDA3( int *__restrict__ __cuda_0,int *__restrict__ __cuda_1,int *__restrict__ __cuda_2,double *__restrict__ __cuda_3,double *__restrict__ __cuda_4,double *__restrict__ __cuda_5,const double __cuda_6,const int __cuda_7,const int __cuda_8)
# 20 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel3.cu"
{__device_stub__Z9RWR_CUDA3PiS_S_PdS0_S0_dii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7,__cuda_8);
# 52 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel3.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z9RWR_init4Pddi( double *__restrict__ __par0,  const double __par1,  const int __par2) {  double *__T19;
__cudaLaunchPrologue(3); __T19 = __par0; __cudaSetupArgSimple(__T19, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaLaunch(((char *)((void ( *)(double *__restrict__, const double, const int))RWR_init4))); }
# 6 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel4.cu"
void RWR_init4( double *__restrict__ __cuda_0,const double __cuda_1,const int __cuda_2)
# 8 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel4.cu"
{__device_stub__Z9RWR_init4Pddi( __cuda_0,__cuda_1,__cuda_2);
# 14 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel4.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z9RWR_CUDA4PiS_S_PdS0_S0_dii( int *__restrict__ __par0,  int *__restrict__ __par1,  int *__restrict__ __par2,  double *__restrict__ __par3,  double *__restrict__ __par4,  double *__restrict__ __par5,  const double __par6,  const int __par7,  const int __par8) {  int *__T20;
 int *__T21;
 int *__T22;
 double *__T23;
 double *__T24;
 double *__T25;
__cudaLaunchPrologue(9); __T20 = __par0; __cudaSetupArgSimple(__T20, 0UL); __T21 = __par1; __cudaSetupArgSimple(__T21, 8UL); __T22 = __par2; __cudaSetupArgSimple(__T22, 16UL); __T23 = __par3; __cudaSetupArgSimple(__T23, 24UL); __T24 = __par4; __cudaSetupArgSimple(__T24, 32UL); __T25 = __par5; __cudaSetupArgSimple(__T25, 40UL); __cudaSetupArgSimple(__par6, 48UL); __cudaSetupArgSimple(__par7, 56UL); __cudaSetupArgSimple(__par8, 60UL); __cudaLaunch(((char *)((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int))RWR_CUDA4))); }
# 16 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel4.cu"
void RWR_CUDA4( int *__restrict__ __cuda_0,int *__restrict__ __cuda_1,int *__restrict__ __cuda_2,double *__restrict__ __cuda_3,double *__restrict__ __cuda_4,double *__restrict__ __cuda_5,const double __cuda_6,const int __cuda_7,const int __cuda_8)
# 24 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel4.cu"
{__device_stub__Z9RWR_CUDA4PiS_S_PdS0_S0_dii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7,__cuda_8);
# 45 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel4.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z9RWR_init5Pddi( double *__restrict__ __par0,  const double __par1,  const int __par2) {  double *__T26;
__cudaLaunchPrologue(3); __T26 = __par0; __cudaSetupArgSimple(__T26, 0UL); __cudaSetupArgSimple(__par1, 8UL); __cudaSetupArgSimple(__par2, 16UL); __cudaLaunch(((char *)((void ( *)(double *__restrict__, const double, const int))RWR_init5))); }
# 7 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel5.cu"
void RWR_init5( double *__restrict__ __cuda_0,const double __cuda_1,const int __cuda_2)
# 9 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel5.cu"
{__device_stub__Z9RWR_init5Pddi( __cuda_0,__cuda_1,__cuda_2);
# 15 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel5.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
void __device_stub__Z9RWR_CUDA5PiS_S_PdS0_S0_diii( int *__restrict__ __par0,  int *__restrict__ __par1,  int *__restrict__ __par2,  double *__restrict__ __par3,  double *__restrict__ __par4,  double *__restrict__ __par5,  const double __par6,  const int __par7,  const int __par8,  const int __par9) {  int *__T27;
 int *__T28;
 int *__T29;
 double *__T30;
 double *__T31;
 double *__T32;
__cudaLaunchPrologue(10); __T27 = __par0; __cudaSetupArgSimple(__T27, 0UL); __T28 = __par1; __cudaSetupArgSimple(__T28, 8UL); __T29 = __par2; __cudaSetupArgSimple(__T29, 16UL); __T30 = __par3; __cudaSetupArgSimple(__T30, 24UL); __T31 = __par4; __cudaSetupArgSimple(__T31, 32UL); __T32 = __par5; __cudaSetupArgSimple(__T32, 40UL); __cudaSetupArgSimple(__par6, 48UL); __cudaSetupArgSimple(__par7, 56UL); __cudaSetupArgSimple(__par8, 60UL); __cudaSetupArgSimple(__par9, 64UL); __cudaLaunch(((char *)((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int, const int))RWR_CUDA5))); }
# 17 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel5.cu"
void RWR_CUDA5( int *__restrict__ __cuda_0,int *__restrict__ __cuda_1,int *__restrict__ __cuda_2,double *__restrict__ __cuda_3,double *__restrict__ __cuda_4,double *__restrict__ __cuda_5,const double __cuda_6,const int __cuda_7,const int __cuda_8,const int __cuda_9)
# 26 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel5.cu"
{__device_stub__Z9RWR_CUDA5PiS_S_PdS0_S0_diii( __cuda_0,__cuda_1,__cuda_2,__cuda_3,__cuda_4,__cuda_5,__cuda_6,__cuda_7,__cuda_8,__cuda_9);
# 57 "/home/luca/@focus/RWR-GPU/RWR/src/device/kernel/RWR_cuda_kernel5.cu"
}
# 1 "cudaExpMatrix.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T36) {  __nv_dummy_param_ref(__T36); __nv_save_fatbinhandle_for_managed_rt(__T36); __cudaRegisterEntry(__T36, ((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int, const int))RWR_CUDA5), _Z9RWR_CUDA5PiS_S_PdS0_S0_diii, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(double *__restrict__, const double, const int))RWR_init5), _Z9RWR_init5Pddi, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int))RWR_CUDA4), _Z9RWR_CUDA4PiS_S_PdS0_S0_dii, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(double *__restrict__, const double, const int))RWR_init4), _Z9RWR_init4Pddi, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, double *__restrict__, const double, const int, const int))RWR_CUDA3), _Z9RWR_CUDA3PiS_S_PdS0_S0_dii, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(double *__restrict__, const double, const int))RWR_init3), _Z9RWR_init3Pddi, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(double *__restrict__, double *__restrict__, double *__restrict__, int *__restrict__, const int, const double))RWR_mul), _Z7RWR_mulPdS_S_Piid, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(int *__restrict__, int *__restrict__, int *__restrict__, int *__restrict__, double *__restrict__, double *__restrict__, const int, int *))RWR_CUDA), _Z8RWR_CUDAPiS_S_S_PdS0_iS_, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(double *__restrict__, int *__restrict__, const int, const double, int *))RWR_init), _Z8RWR_initPdPiidS0_, (-1)); __cudaRegisterEntry(__T36, ((void ( *)(const double *, double *, int, int))matrixTransposeKernelShM), _Z24matrixTransposeKernelShMPKdPdii, (-1)); __cudaRegisterVariable(__T36, __shadow_var(counter,::counter), 0, 4UL, 0, 0); }
static void __sti____cudaRegisterAll(void) {  ____cudaRegisterLinkedBinary(__nv_cudaEntityRegisterCallback);  }

#pragma GCC diagnostic pop
