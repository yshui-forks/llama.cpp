#pragma once

#include "ggml.h"
#include "ggml-backend.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef GGML_USE_HIP
#define GGML_CUDA_NAME "ROCm"
#define GGML_CUBLAS_NAME "hipBLAS"
#define GGML_BACKEND_REG ggml_backend_hip_reg
#elif defined(GGML_USE_MUSA)
#define GGML_CUDA_NAME "MUSA"
#define GGML_CUBLAS_NAME "muBLAS"
#define GGML_BACKEND_REG ggml_backend_cuda_reg
#else
#define GGML_CUDA_NAME "CUDA"
#define GGML_CUBLAS_NAME "cuBLAS"
#define GGML_BACKEND_REG ggml_backend_cuda_reg
#endif
#define GGML_CUDA_MAX_DEVICES       16

// backend API
static ggml_backend_t ggml_backend_cuda_init(int device);

static bool ggml_backend_is_cuda(ggml_backend_t backend);

// device buffer
static ggml_backend_buffer_type_t ggml_backend_cuda_buffer_type(int device);

// split tensor buffer that splits matrices by rows across multiple devices
static ggml_backend_buffer_type_t ggml_backend_cuda_split_buffer_type(int main_device, const float * tensor_split);

// pinned host buffer for use with the CPU backend for faster copies between CPU and GPU
static ggml_backend_buffer_type_t ggml_backend_cuda_host_buffer_type(void);

static int  ggml_backend_cuda_get_device_count(void);
static void ggml_backend_cuda_get_device_description(int device, char * description, size_t description_size);
static void ggml_backend_cuda_get_device_memory(int device, size_t * free, size_t * total);

static bool ggml_backend_cuda_register_host_buffer(void * buffer, size_t size);
static void ggml_backend_cuda_unregister_host_buffer(void * buffer);

GGML_BACKEND_API ggml_backend_reg_t GGML_BACKEND_REG(void);

#ifdef  __cplusplus
}
#endif
