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

#ifndef ZTD_VARGS_SOURCE_VCXX_X64_HPP
#define ZTD_VARGS_SOURCE_VCXX_X64_HPP

#include <ztd/vargs/va_intrinsics.h>

#include <ztd/idk/assert.hpp>

#include <cstddef>
#include <cstdint>

#include <Windows.h>

extern "C" void* __ztdc_read_homed_register_rcx(void* __return_address) noexcept;
extern "C" void* __ztdc_read_homed_register_rdx(void* __return_address) noexcept;
extern "C" void* __ztdc_read_homed_register_r8(void* __return_address) noexcept;
extern "C" void* __ztdc_read_homed_register_r9(void* __return_address) noexcept;
extern "C" double __ztdc_read_register_xmm0(void) noexcept;
extern "C" double __ztdc_read_register_xmm1(void) noexcept;
extern "C" double __ztdc_read_register_xmm2(void) noexcept;
extern "C" double __ztdc_read_register_xmm3(void) noexcept;

inline void* __ztdc_vararg_to_value(void*& __arg, size_t __position, size_t __size,
     size_t __alignment, __ztdc_vargs_detail_broad_type __broad_type) {
	if (__broad_type == _ZTDC_VARGS_DETAIL_BROAD_TYPE_REFERENCE) {
		// references are returned as a single indirection, so they can be used directly:
		// T* -> void* -> T* -> T&
		return __arg;
	}
	else {
		// values are returned as a double-indirection, so they can be cast:
		// T& -> T* -> void* -> T* -> T&
		return reinterpret_cast<void*>(&__arg);
	}
}

extern "C" void __ztdc_va_start(ztdc_va_list* __p_untyped_vl, void* __return_address) noexcept {
	ztdc_va_list& __vl       = *static_cast<ztdc_va_list*>(static_cast<void*>(__p_untyped_vl));
	__vl.__stack_position    = __return_address;
	__vl.__argument_position = 0;
	__vl.__home[0]           = __ztdc_read_homed_register_rcx(__vl.__stack_position);
	__vl.__home[1]           = __ztdc_read_homed_register_rdx(__vl.__stack_position);
	__vl.__home[2]           = __ztdc_read_homed_register_r8(__vl.__stack_position);
	__vl.__home[3]           = __ztdc_read_homed_register_r9(__vl.__stack_position);
	double __xmm0_val        = __ztdc_read_register_xmm0();
	double __xmm1_val        = __ztdc_read_register_xmm1();
	double __xmm2_val        = __ztdc_read_register_xmm2();
	double __xmm3_val        = __ztdc_read_register_xmm3();
	__vl.__home[4]           = *reinterpret_cast<void**>(&__xmm0_val);
	__vl.__home[5]           = *reinterpret_cast<void**>(&__xmm1_val);
	__vl.__home[6]           = *reinterpret_cast<void**>(&__xmm2_val);
	__vl.__home[7]           = *reinterpret_cast<void**>(&__xmm3_val);
}

extern "C" void* __ztdc_va_next(ztdc_va_list* __p_vl, size_t __size, size_t __alignment,
     __ztdc_vargs_detail_broad_type __broad_type) noexcept {
	ztdc_va_list& __vl = *static_cast<ztdc_va_list*>(static_cast<void*>(__p_vl));
	void* __target     = nullptr;
	switch (__vl.__argument_position) {
	case 0:
	case 1:
	case 2:
	case 3: {
		if (__broad_type == _ZTDC_VARGS_DETAIL_BROAD_TYPE_FLOAT) {
			__target = __ztdc_vararg_to_value(__vl.__home[__vl.__argument_position + 4],
			     __vl.__argument_position, __size, __alignment, __broad_type);
		}
		else {
			__target = __ztdc_vararg_to_value(__vl.__home[__vl.__argument_position],
			     __vl.__argument_position, __size, __alignment, __broad_type);
		}
	} break;
	default: {
		// fallback to start
		ZTD_ASSERT(false);
	} break;
	}
	__vl.__argument_position += 1;
	return __target;
}

#endif // ZTD_VARGS_SOURCE_VCXX_X64_HPP
