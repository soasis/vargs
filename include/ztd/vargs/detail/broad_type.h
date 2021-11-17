// =============================================================================
//
// ztd.vargs
// Copyright © 2021 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
// ============================================================================>

#ifndef ZTD_VARGS_DETAIL_BROAD_TYPE_H
#define ZTD_VARGS_DETAIL_BROAD_TYPE_H

#include <ztd/vargs/version.h>

#include <ztd/vargs/va_list.h>

enum __ztdc_vargs_detail_broad_type {
	_ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,
	_ZTDC_VARGS_DETAIL_BROAD_TYPE_FLOAT,
	_ZTDC_VARGS_DETAIL_BROAD_TYPE_POINTER,
	_ZTDC_VARGS_DETAIL_BROAD_TYPE_REFERENCE
};

#if ZTD_IS_ON(ZTD_C_I_)
#define __ztdc_vargs_detail_select_broad_type(_TYPE) \
	(_Generic( *((_TYPE*)0),
          char: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		unsigned char: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		signed char: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		_Bool: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT, // cf-hack
		short: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		unsigned short: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		int: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		unsigned int: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		long: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		unsigned long: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		long long: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		unsigned long long: _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT,// cf-hack
		float: _ZTDC_VARGS_DETAIL_BROAD_TYPE_FLOAT,// cf-hack
		double: _ZTDC_VARGS_DETAIL_BROAD_TYPE_FLOAT,// cf-hack
		default: ((sizeof(_TYPE) <= sizeof(void*)) ? _ZTDC_VARGS_DETAIL_BROAD_TYPE_POINTER : _ZTDC_VARGS_DETAIL_BROAD_TYPE_REFERENCE)// cf-hack
	))
#else
#include <type_traits>

template <typename _Type>
__ztdc_vargs_detail_broad_type __ztdc_vargs_detail_select_broad_type_cxx() noexcept {
	if constexpr (::std::is_pointer_v<_Type>) {
		return _ZTDC_VARGS_DETAIL_BROAD_TYPE_POINTER;
	}
	else if constexpr (::std::is_integral_v<_Type>) {
		return _ZTDC_VARGS_DETAIL_BROAD_TYPE_INT;
	}
	else if constexpr (::std::is_floating_point_v<_Type>) {
		return _ZTDC_VARGS_DETAIL_BROAD_TYPE_FLOAT;
	}
	else {
		return ((sizeof(_Type) <= sizeof(void*)) && ::std::is_aggregate_v<_Type>)
		     ? _ZTDC_VARGS_DETAIL_BROAD_TYPE_POINTER
		     : _ZTDC_VARGS_DETAIL_BROAD_TYPE_REFERENCE;
	}
}

#define __ztdc_vargs_detail_select_broad_type(_TYPE) \
	__ztdc_vargs_detail_select_broad_type_cxx<_TYPE>()

#endif

#endif // ZTD_VARGS_DETAIL_BROAD_TYPE_H
