/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "velox/expression/VectorFunction.h"

namespace facebook::velox::functions::sparksql {

template <template <typename> class Cmp>
class ArraySort : public exec::VectorFunction {
  /// This class implements generic array sort function. Takes an array as input
  /// and sorts it according to provided comparator |Cmp| as template parameter.
  /// Additionally |nullsFirst| ctor parameter can be used to configure nulls
  /// sort order. If |nullsFirst| is  true nulls are moved to front of array,
  ///  otherwise nulls are moved to end of array.
  ///
  /// Sorts floating points as per following ascending order:
  /// -Inf < Inf < NaN
  ///
  /// Limitation: Does not support BOOLEAN and complex types.

 public:
  explicit ArraySort(bool nullsFirst) : nullsFirst_(nullsFirst) {}

  void apply(
      const SelectivityVector& rows,
      std::vector<VectorPtr>& args,
      const TypePtr& /* outputType */,
      exec::EvalCtx* context,
      VectorPtr* result) const override;

 private:
  bool nullsFirst_;
};

std::shared_ptr<exec::VectorFunction> makeArraySort(
    const std::string& name,
    const std::vector<exec::VectorFunctionArg>& inputArgs);

std::vector<std::shared_ptr<exec::FunctionSignature>> arraySortSignatures();

std::shared_ptr<exec::VectorFunction> makeSortArray(
    const std::string& name,
    const std::vector<exec::VectorFunctionArg>& inputArgs);

std::vector<std::shared_ptr<exec::FunctionSignature>> sortArraySignatures();

} // namespace facebook::velox::functions::sparksql
