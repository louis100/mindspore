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

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_CONCAT_BASE_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_CONCAT_BASE_H_

#include <vector>
#include "src/lite_kernel.h"
#include "nnacl/concat_parameter.h"
#include "src/runtime/kernel/arm/base/layout_transform.h"

using mindspore::lite::InnerContext;

namespace mindspore::kernel {
class ConcatBaseCPUKernel : public LiteKernel {
 public:
  ConcatBaseCPUKernel(OpParameter *parameter, const std::vector<lite::Tensor *> &inputs,
                      const std::vector<lite::Tensor *> &outputs, const InnerContext *ctx,
                      const mindspore::lite::PrimitiveC *primitive)
      : LiteKernel(parameter, inputs, outputs, ctx, primitive), ctx_(ctx), thread_count_(ctx->thread_num_) {
    concat_param_ = reinterpret_cast<ConcatParameter *>(op_parameter_);
  }

  virtual ~ConcatBaseCPUKernel() = default;

  int Init() override;

  int ReSize() override;

  int Run() override { return 0; }

 protected:
  const InnerContext *ctx_ = nullptr;
  int thread_count_ = 1;
  ConcatParameter *concat_param_ = nullptr;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_CONCAT_BASE_H_
