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

#include "tools/converter/parser/tflite/tflite_matmul_parser.h"
#include <vector>
#include <memory>
#include <map>

namespace mindspore::lite {
PrimitiveC *TfliteMatMulParser::ParseLitePrimitive(const std::unique_ptr<tflite::OperatorT> &tflite_op,
                                                   const std::unique_ptr<tflite::ModelT> &tflite_model) {
  auto primitive = std::make_unique<schema::PrimitiveT>();
  if (primitive == nullptr) {
    MS_LOG(ERROR) << "primitive is null";
    return nullptr;
  }

  std::unique_ptr<schema::MatMulT> attr = std::make_unique<schema::MatMulT>();
  if (attr == nullptr) {
    MS_LOG(ERROR) << "new op failed";
    return nullptr;
  }
  const auto &tflite_attr = tflite_op->builtin_options.AsBatchMatMulOptions();
  attr->transposeA = tflite_attr->adj_x;
  attr->transposeB = tflite_attr->adj_y;
  primitive->value.type = schema::PrimitiveType_MatMul;
  primitive->value.value = attr.release();

  return PrimitiveC::Create(primitive.release());
}

}  // namespace mindspore::lite