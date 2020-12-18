/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_NPU_RESIZE_NPU_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_NPU_RESIZE_NPU_H_
#include <vector>
#include "nnacl/resize_parameter.h"
#include "src/ops/resize.h"
#include "nnacl/arithmetic_common.h"
#include "src/runtime/kernel/npu/npu_kernel.h"
#include "include/graph/op/all_ops.h"
#include "src/runtime/kernel/npu/transpose_base_npu.h"
namespace mindspore::kernel {
class ResizeNPUKernel : public TransposeBaseNPUKernel {
 public:
  ResizeNPUKernel(OpParameter *parameter, const std::vector<lite::Tensor *> &inputs,
                  const std::vector<lite::Tensor *> &outputs, const lite::InnerContext *ctx,
                  const mindspore::lite::PrimitiveC *primitive)
      : TransposeBaseNPUKernel(parameter, inputs, outputs, ctx, primitive) {
    auto resize_parameter = reinterpret_cast<ResizeParameter *>(parameter);
    method_ = resize_parameter->method_;
    new_height_ = resize_parameter->new_height_;
    new_width_ = resize_parameter->new_width_;
    align_corners_ = resize_parameter->align_corners_;
    preserve_aspect_ratio_ = resize_parameter->preserve_aspect_ratio_;
  }
  ~ResizeNPUKernel() override;

  int IsSupport(const std::vector<lite::Tensor *> &inputs, const std::vector<lite::Tensor *> &outputs,
                OpParameter *opParameter) override;
  int SetNPUInputs(const std::vector<lite::Tensor *> &inputs, const std::vector<lite::Tensor *> &outputs,
                   const std::vector<ge::Operator *> &npu_inputs) override;

  ge::Operator *GetNPUOp() override;

 private:
  ge::Operator *op_ = nullptr;
  int method_;
  int64_t new_height_;
  int64_t new_width_;
  bool align_corners_;
  bool preserve_aspect_ratio_;
};
}  // namespace mindspore::kernel
#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_NPU_RESIZE_NPU_H_