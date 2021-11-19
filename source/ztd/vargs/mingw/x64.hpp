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

#ifndef ZTD_VARGS_SOURCE_WINDOWS_GCC_X64_HPP
#define ZTD_VARGS_SOURCE_WINDOWS_GCC_X64_HPP

#include <ztd/vargs/va_intrinsics.h>

#include <ztd/idk/assert.hpp>

#include <cstddef>
#include <cstdint>

extern "C" void __ztdc_va_start(ztdc_va_list* __p_untyped_vl, void* __return_address) noexcept {
	ztdc_va_list& __vl = *static_cast<ztdc_va_list*>(static_cast<void*>(__p_untyped_vl));
}

extern "C" void* __ztdc_va_next(ztdc_va_list* __p_vl, size_t __size, size_t __alignment,
     __ztdc_vargs_detail_broad_type __broad_type) noexcept {
}

#endif // ZTD_VARGS_SOURCE_WINDOWS_GCC_X64_HPP
