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

#include <catch2/catch.hpp>

#include <ztd/vargs.hpp>

#include <cmath>
#include <cstdint>
#include <cstddef>

namespace {

#define make_mulN(TYPE, NAME, N)                                      \
	template <typename T = int>                                      \
	static TYPE NAME##_mul##N(...) {                                 \
		TYPE accumulation           = 1;                            \
		[[maybe_unused]] TYPE value = 0;                            \
		ztdc_va_list vl;                                            \
		ztdc_va_start(vl);                                          \
		if constexpr (std::is_same_v<T, int> && N > 0) {            \
			for (std::size_t index = 0; index < N; ++index) {      \
				value = ztdc_va_arg(vl, TYPE);                    \
				REQUIRE(value == static_cast<double>(index + 2)); \
				accumulation *= value;                            \
			}                                                      \
		}                                                           \
		ztdc_va_end(vl);                                            \
		return accumulation;                                        \
	}                                                                \
	static_assert(true, "🙏")

	make_mulN(float, float, 0);
	make_mulN(float, float, 1);
	make_mulN(float, float, 2);
	make_mulN(float, float, 3);
	make_mulN(float, float, 4);
	make_mulN(float, float, 5);
	make_mulN(float, float, 6);
	make_mulN(float, float, 7);
	make_mulN(float, float, 8);

	make_mulN(double, double, 0);
	make_mulN(double, double, 1);
	make_mulN(double, double, 2);
	make_mulN(double, double, 3);
	make_mulN(double, double, 4);
	make_mulN(double, double, 5);
	make_mulN(double, double, 6);
	make_mulN(double, double, 7);
	make_mulN(double, double, 8);
} // namespace

TEST_CASE("vargs/floats", "check float multiples from 1 to 8 through va_args") {
	constexpr uint_least64_t expected_canary0 = 309231971931137ULL;
#define MUL_SECTION(N, EXPECTED, ...)                              \
	SECTION("float mul" #N) {                                     \
		std::uint_least64_t canary0 = expected_canary0;          \
		float value                 = float_mul##N(__VA_ARGS__); \
		REQUIRE(value == static_cast<float>(EXPECTED));          \
		REQUIRE(canary0 == expected_canary0);                    \
	}                                                             \
	static_assert(true, "🙏")

	MUL_SECTION(0, 1.0, 2.0);
	MUL_SECTION(1, 2.0, 2.0);
	MUL_SECTION(2, 6.0, 2.0, 3.0);
	MUL_SECTION(3, 24.0, 2.0, 3.0, 4.0);
	MUL_SECTION(4, 120.0, 2.0, 3.0, 4.0, 5.0);
	MUL_SECTION(5, 720.0, 2.0, 3.0, 4.0, 5.0, 6.0);
	MUL_SECTION(6, 5040.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
	MUL_SECTION(7, 40320.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
	MUL_SECTION(8, 362880.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
#undef MUL_SECTION
}

TEST_CASE("vargs/double", "check double multiples from 1 to 8 through va_args") {
	constexpr uint_least64_t expected_canary0 = 309231971931137ULL;
#define MUL_SECTION(N, EXPECTED, ...)                               \
	SECTION("double mul" #N) {                                     \
		std::uint_least64_t canary0 = expected_canary0;           \
		double value                = double_mul##N(__VA_ARGS__); \
		REQUIRE(value == static_cast<double>(EXPECTED));          \
		REQUIRE(canary0 == expected_canary0);                     \
	}                                                              \
	static_assert(true, "🙏")

	MUL_SECTION(0, 1.0, 2.0);
	MUL_SECTION(1, 2.0, 2.0);
	MUL_SECTION(2, 6.0, 2.0, 3.0);
	MUL_SECTION(3, 24.0, 2.0, 3.0, 4.0);
	MUL_SECTION(4, 120.0, 2.0, 3.0, 4.0, 5.0);
	MUL_SECTION(5, 720.0, 2.0, 3.0, 4.0, 5.0, 6.0);
	MUL_SECTION(6, 5040.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
	MUL_SECTION(7, 40320.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
	MUL_SECTION(8, 362880.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
#undef MUL_SECTION
}
