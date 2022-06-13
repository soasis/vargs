// =============================================================================
//
// ztd.vargs
// Copyright © 2022 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
// Contact: opensource@soasis.org
//
// Commercial License Usage
// Licensees holding valid commercial ztd.vargs licenses may use this file
// in accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and Shepherd's Oasis, LLC.
// For licensing terms and conditions see your agreement. For
// further information contact opensource@soasis.org.
//
// Apache License Version 2 Usage
// Alternatively, this file may be used under the terms of Apache License
// Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// 		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================ //

#ifndef ZTD_VARGS_VA_INTRINSIC_H
#define ZTD_VARGS_VA_INTRINSIC_H

#include <ztd/vargs/version.h>

#include <ztd/vargs/va_list.h>
#include <ztd/vargs/detail/broad_type.h>
#include <ztd/vargs/detail/function_properties.h>

#if ZTD_IS_ON(ZTD_C_I_)
#include <stddef.h>
#else
#include <cstddef>
#endif

#if ZTD_IS_ON(ZTD_BUILTIN_FRAME_ADDRESS_I_)
#define __ztdc_va_start_platform(_VL) \
	__ztdc_va_start(&(_VL), __builtin_frame_address(0), _ZTDC_FUNCTION_PROPERTIES(0));
#define __ztdc_va_start_platform_in(_VL, ...) \
	__ztdc_va_start(&(_VL), __builtin_frame_address(0), _ZTDC_FUNCTION_PROPERTIES(__VA_ARGS__))
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) && ZTD_IS_ON(ZTD_PLATFORM_WINDOWS_I_)
#include <intrin.h>
#define __ztdc_va_start_platform(_VL) \
	__ztdc_va_start(&(_VL), _AddressOfReturnAddress(), _ZTDC_FUNCTION_PROPERTIES(0))
#define __ztdc_va_start_platform_in(_VL, ...) \
	__ztdc_va_start(&(_VL), _AddressOfReturnAddress(), _ZTDC_FUNCTION_PROPERTIES(__VA_ARGS__))
#else
#error "This isn't a platform we can work with, unfortunately!"
#endif


ZTD_EXTERN_C_OPEN_I_

void* __ztdc_va_next(ztdc_va_list* __vl, size_t __type_size, size_t __type_alignment,
     __ztdc_vargs_detail_broad_type __broad_type) ZTD_NOEXCEPT_IF_CXX_I_;
void __ztdc_va_start(ztdc_va_list* __vl, void* __return_address,
     __ztdc_vargs_detail_function_properties __properties) ZTD_NOEXCEPT_IF_CXX_I_;
void __ztdc_va_end(ztdc_va_list* __vl) ZTD_NOEXCEPT_IF_CXX_I_;

//////
/// @addtogroup ztdc_va_arg_intrinsics Variable Argument Intrinsics
///
/// @{
//////

//////
/// @brief Initializes and starts up the iteration of a `...` argument list!
///
/// @param[in] _VL A ztdc_va_list (not a pointer to one!).
///
/// @par Mandates
/// - The `_VL` parameter must have been previously initialized by a call to ztdc_va_start.
///
/// @remarks This currently will iterate over arguments that are already presents in the
/// non-variable arguments part of the call, so factor this in appropriately if used with a mix of
/// statically-known and variable arguments!
///
/// @par Cursed?
/// This call may not work well for everything, since occasionally critical information is missing
/// from just the raw function call. Prefer ztdc_va_arg_in, which takes both a ztdc_va_list and the
/// name of the function it is within.
//////
#define ztdc_va_start(_VL) __ztdc_va_start_platform(_VL)
//////
/// @brief Initializes and starts up the iteration of a `...` argument list!
///
/// @param[in] _VL A ztdc_va_list (not a pointer to one!).
/// @param[in] ... The function name this is being called from.
///
/// @par Mandates
/// - The `_VL` parameter must have been previously initialized by a call to ztdc_va_start.
/// - The `...` token parameters must form a complete, non-overloaded function name (qualified or
/// unqualified) which can have its type (`decltype(__VA_ARGS__)`) taken. The behavior is undefined
/// if this is not the function that is actually calling this.
///
/// @remarks This version uses specialist information from the function prototype to properly adjust
/// the internal implementation. This is important for functions which return large structs that are
/// placed in special positions thanks to Return Value Optimization (RVO), Indirect Struct Return
/// Optimizatino (ISRO), and other behaviors specific to a given platform/ABI/compiler architecture.
//////
#define ztdc_va_start_in(_VL, ...) __ztdc_va_start_platform_in(_VL, __VA_ARGS__)

//////
/// @brief Initializes and starts up the iteration of a `...` argument list!
///
/// @param[in] _VL A ztdc_va_list (not a pointer to one!).
/// @param[in] _TYPE The type to pass in. Must not be a reference type.
///
/// @par Mandates
/// - `_TYPE` shall not be a reference type (pointer types are fine).
/// - The `_VL` parameter must have been previously initialized by a call to ztdc_va_start.
///
/// @remarks This currently will iterate over arguments that are already presents in the
/// non-variable arguments part of the call, so factor this in appropriately if used with a mix of
/// statically-known and variable arguments!
///
/// @par Cursed?
//////
#define ztdc_va_arg(_VL, _TYPE) \
	*(_TYPE*)__ztdc_va_next(   \
	     &_VL, sizeof(_TYPE), alignof(_TYPE), _ZTDC_VARGS_DETAIL_SELECT_BROAD_TYPE(_TYPE));

//////
/// @brief Ends the iteration of a ztdc_va_list.
///
/// @param[in] _VL A ztdc_va_list (not a pointer to one!).
///
/// @par Mandates
/// - The `_VL` parameter must have been previously initialized by a call to ztdc_va_start.
///
/// @par Cursed?
//////
#define ztdc_va_end(_VL) __ztdc_va_end(&_VL);

//////
/// @}
//////


ZTD_EXTERN_C_CLOSE_I_

#endif // ZTD_VARGS_VA_INTRINSIC_H
