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

#ifndef ZTD_VARGS_VA_LIST_H
#define ZTD_VARGS_VA_LIST_H

#include <ztd/vargs/version.h>

#if ZTD_IS_ON(ZTD_C_I_)
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#else
#include <cstddef>
#include <cstdint>
#include <cstdarg>
#endif

ZTD_EXTERN_C_OPEN_I_

//////
/// @addtogroup ztd_vargs_va_list va_list Type
///
/// @{
//////

typedef struct ztdc_va_list {
	//////
	/// @brief Private. Do not use.
	size_t __argument_position;
	//////
	/// @brief Private. Do not use.
	void* __stack_position;
	//////
	/// @brief Private. Do not use.
	void* __post_home_stack_position;
	//////
	/// @brief Private. Do not use.
	void* __home[9];
} ztdc_va_list;

//////
/// @typedef ztdc_va_list
///
/// @brief The `va_list` type. Can be used in any scenario where the argument list is empty.
///
/// @remarks Currently, only C++ supports such a declaration: Standard C compilers will break on it.
//////

//////
/// @}
//////


ZTD_EXTERN_C_CLOSE_I_

#endif // ZTD_VARGS_VA_LIST_H
