// =============================================================================
//
// ztd.vargs
// Copyright © JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================ //

#ifndef ZTD_VARGS_DETAIL_FUNCTION_PROPERTIES_H
#define ZTD_VARGS_DETAIL_FUNCTION_PROPERTIES_H

#include <ztd/vargs/version.h>

#include <ztd/vargs/detail/broad_type.h>

#if ZTD_IS_ON(ZTD_C)
#include <stdbool.h>
#endif

typedef struct __ztdc_vargs_detail_function_properties {
	bool __return_value_aggregate;
	__ztdc_vargs_detail_broad_type __broad_type;
	size_t __argument_count;
} __ztdc_vargs_detail_function_properties;

ZTD_EXTERN_C_OPEN_I_
extern __ztdc_vargs_detail_function_properties __ztdc_vargs_detail_empty_properties(void);
ZTD_EXTERN_C_CLOSE_I_

#if ZTD_IS_ON(ZTD_C)
#define _ZTDC_FUNCTION_PROPERTIES(...) __ztdc_vargs_detail_empty_properties
#else

#include <type_traits>

template <typename>
struct __ztd_f_traits;
template <typename _R, typename... _Args>
struct __ztd_f_traits<_R(_Args..., ...)> {
	using __return_type                                        = _R;
	static inline constexpr const std::size_t __argument_count = sizeof...(_Args);
};
template <typename _R, typename... _Args>
struct __ztd_f_traits<_R (*)(_Args..., ...)> {
	using __return_type                                        = _R;
	static inline constexpr const std::size_t __argument_count = sizeof...(_Args);
};

template <typename _Type>
__ztdc_vargs_detail_function_properties __ztdc_vargs_detail_function_properties_cxx() noexcept {
	if constexpr (::std::is_function_v<::std::remove_pointer_t<_Type>>) {
		using _TraitsT    = ::__ztd_f_traits<::std::remove_pointer_t<_Type>>;
		using _ReturnType = typename _TraitsT::__return_type;
		return { !::std::is_reference_v<_ReturnType> && ::std::is_aggregate_v<_ReturnType>,
			_ZTDC_VARGS_DETAIL_SELECT_BROAD_TYPE(_ReturnType), _TraitsT::__argument_count };
	}
	else {
		return __ztdc_vargs_detail_empty_properties();
	}
}

#define _ZTDC_FUNCTION_PROPERTIES(...) \
	__ztdc_vargs_detail_function_properties_cxx<decltype(__VA_ARGS__)>()
#endif

#endif
