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

#include <ztd/vargs/version.h>

#include <climits>

// clang-format off
// windows
#if ZTD_IS_ON(ZTD_PLATFORM_WINDOWS_I_)
	// mingw
	#if ZTD_IS_ON(ZTD_COMPILER_GCC_I_)
		#define ZTD_VARGS_SOURCE_FOUND_PLATFORM_ABI_I_ ZTD_OFF
	#else
		#if defined(_M_AMD64)
			#define ZTD_VARGS_SOURCE_FOUND_PLATFORM_ABI_I_ ZTD_ON
			#include "windows/x64.hpp"
		// #elif defined(_M_IX86)
		// #elif defined(_M_ARM)
		// #elif defined(_M_ARM64)
		#else
			#define ZTD_VARGS_SOURCE_FOUND_PLATFORM_ABI_I_ ZTD_OFF
		#endif
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_GCC_I_) || ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	// on non-windows platforms, clang follows the same ABI as GCC
	// the following list is taken from microsoft/vcpkg-tool@f6e44dfbd3bb8aaa142ce090098f078547af5f3f
	#if defined(__x86_64__)
		#define ZTD_VARGS_SOURCE_FOUND_PLATFORM_ABI_I_ ZTD_OFF
	//#elif defined(__x86__) || defined(__i386__)
	//#elif defined(__arm__)
	//#elif defined(__aarch64__)
	//#elif defined(__s390x__)
	//#elif (defined(__ppc64__) || defined(__PPC64__) || defined(__ppc64le__) || defined(__PPC64LE__))
	//       && defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	#else
		#define ZTD_VARGS_SOURCE_FOUND_PLATFORM_ABI_I_ ZTD_OFF
	#endif
#else
	// found nothing!
	#define ZTD_VARGS_SOURCE_FOUND_PLATFORM_ABI_I_ ZTD_OFF
#endif

#if ZTD_IS_OFF(ZTD_VARGS_SOURCE_FOUND_PLATFORM_ABI_I_)
	#include "stub.hpp"
#endif

// clang-format on
