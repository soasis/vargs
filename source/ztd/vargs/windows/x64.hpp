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

#ifndef ZTD_VARGS_SOURCE_WINDOWS_VCXX_X64_HPP
#define ZTD_VARGS_SOURCE_WINDOWS_VCXX_X64_HPP

#include <ztd/vargs/va_intrinsics.h>

#include <ztd/idk/assert.hpp>

#include <cstddef>
#include <cstdint>

#include <Windows.h>

extern "C" void* __ztdc_vcxx_x64_read_homed_register_rcx(void* __return_address) noexcept;
extern "C" void* __ztdc_vcxx_x64_read_homed_register_rdx(void* __return_address) noexcept;
extern "C" void* __ztdc_vcxx_x64_read_homed_register_r8(void* __return_address) noexcept;
extern "C" void* __ztdc_vcxx_x64_read_homed_register_r9(void* __return_address) noexcept;
extern "C" double __ztdc_vcxx_x64_read_register_xmm0(void) noexcept;
extern "C" double __ztdc_vcxx_x64_read_register_xmm1(void) noexcept;
extern "C" double __ztdc_vcxx_x64_read_register_xmm2(void) noexcept;
extern "C" double __ztdc_vcxx_x64_read_register_xmm3(void) noexcept;

namespace {
	template <bool _IsIndirect = true>
	void* __ztdc_vcxx_x64_vararg_to_value(void*& __arg, size_t __position, size_t __size,
	     size_t __alignment, __ztdc_vargs_detail_broad_type __broad_type) noexcept {
		if (__broad_type == _ZTDC_VARGS_DETAIL_BROAD_TYPE_REFERENCE) {
			// references are returned as a single indirection contained at the given location,
			// so they must be indirected once:
			// T** -> (deref) -> T* -> void* -> T* -> T&
			if constexpr (_IsIndirect) {
				return __arg;
			}
			else {
				return *(reinterpret_cast<void**>(__arg));
			}
		}
		else {
			if (__broad_type == _ZTDC_VARGS_DETAIL_BROAD_TYPE_FLOAT) {
				switch (__size) {
				case sizeof(float): {
					// we must first get the double value, then do a
					// proper semantic cast
					double __value = *(_IsIndirect ? reinterpret_cast<double*>(&__arg)
					                               : reinterpret_cast<double*>(__arg));
					float __fvalue = __value;
					// reinterpret it into an argument here
					__arg = *reinterpret_cast<void**>(static_cast<float*>(&__fvalue));
					return reinterpret_cast<void*>(&__arg);
				} break;
				case sizeof(double):
					// values are returned as a double-indirection, so they can be cast:
					// T& -> T* -> void* -> T* -> T&
					return (_IsIndirect ? reinterpret_cast<void*>(&__arg) : __arg);
				default:
					// unknown float???
					ZTD_ASSERT(false);
					break;
				}
			}
			else {
				// values are returned as a double-indirection, so they can be cast:
				// T& -> T* -> void* -> T* -> T&
				return (_IsIndirect ? reinterpret_cast<void*>(&__arg) : __arg);
			}
		}
	}
} // namespace

extern "C" void __ztdc_va_start(ztdc_va_list* __p_untyped_vl, void* __return_address,
     __ztdc_vargs_detail_function_properties __properties) noexcept {
	ztdc_va_list& __vl       = *static_cast<ztdc_va_list*>(static_cast<void*>(__p_untyped_vl));
	bool __uses_indirect_struct_return_value_at_start = __properties.__return_value_aggregate
	     && __properties.__broad_type == _ZTDC_VARGS_DETAIL_BROAD_TYPE_REFERENCE;
	void* __rehome_position  = __uses_indirect_struct_return_value_at_start
	      ? reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(__return_address) + 8)
	      : __return_address;
	__vl.__stack_position    = __rehome_position;
	__vl.__post_home_stack_position    = __return_address;
	__vl.__argument_position = 0 + __properties.__argument_count;
	__vl.__home[0]           = __ztdc_vcxx_x64_read_homed_register_rcx(__rehome_position);
	__vl.__home[1]           = __ztdc_vcxx_x64_read_homed_register_rdx(__rehome_position);
	__vl.__home[2]           = __ztdc_vcxx_x64_read_homed_register_r8(__rehome_position);
	__vl.__home[3]           = __ztdc_vcxx_x64_read_homed_register_r9(__rehome_position);
	__vl.__home[4] = __vl.__home[0];
	__vl.__home[5] = __vl.__home[1];
	__vl.__home[6] = __vl.__home[2];
	__vl.__home[7] = __vl.__home[3];
	__vl.__home[8] = nullptr;
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
		__target = __ztdc_vcxx_x64_vararg_to_value(__vl.__home[__vl.__argument_position],
		     __vl.__argument_position, __size, __alignment, __broad_type);
	} break;
	default: {
		// values are stored directly, now!
		__vl.__home[8] = static_cast<void*>(static_cast<unsigned char*>(__vl.__stack_position)
		     + (sizeof(void*)) + (__vl.__argument_position * sizeof(void*)));
		__target       = __ztdc_vcxx_x64_vararg_to_value<false>(
               __vl.__home[8], __vl.__argument_position, __size, __alignment, __broad_type);
	} break;
	}
	__vl.__argument_position += 1;
	return __target;
}

#endif // ZTD_VARGS_SOURCE_WINDOWS_VCXX_X64_HPP
