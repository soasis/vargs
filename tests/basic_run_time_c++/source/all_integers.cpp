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
		if constexpr (std::is_same_v<int, T> && N != 0) {           \
			for (std::size_t index = 0; index < N; ++index) {      \
				value = ztdc_va_arg(vl, TYPE);                    \
				REQUIRE(value == (static_cast<TYPE>(index + 2))); \
				accumulation *= value;                            \
			}                                                      \
		}                                                           \
		ztdc_va_end(vl);                                            \
		return accumulation;                                        \
	}                                                                \
	static_assert(true, "🙏")

	make_mulN(int, int, 0);
	make_mulN(int, int, 1);
	make_mulN(int, int, 2);
	make_mulN(int, int, 3);
	make_mulN(int, int, 4);
	make_mulN(int, int, 5);
	make_mulN(int, int, 6);
	make_mulN(int, int, 7);
	make_mulN(int, int, 8);

	make_mulN(long long, ll, 0);
	make_mulN(long long, ll, 1);
	make_mulN(long long, ll, 2);
	make_mulN(long long, ll, 3);
	make_mulN(long long, ll, 4);
	make_mulN(long long, ll, 5);
	make_mulN(long long, ll, 6);
	make_mulN(long long, ll, 7);
	make_mulN(long long, ll, 8);
} // namespace

TEST_CASE("vargs/integers", "check integer multiples from 1 to 8 through va_args") {
	constexpr uint_least64_t expected_canary0 = 309231971931137ULL;
#define MUL_SECTION(N, EXPECTED, ...)                       \
	SECTION("int mul" #N) {                                \
		uint_least64_t canary0 = expected_canary0;        \
		int value              = int_mul##N(__VA_ARGS__); \
		REQUIRE(value == EXPECTED);                       \
		REQUIRE(canary0 == expected_canary0);             \
	}                                                      \
	static_assert(true, "🙏")

	MUL_SECTION(0, 1, 2);
	MUL_SECTION(1, 2, 2);
	MUL_SECTION(2, 6, 2, 3);
	MUL_SECTION(3, 24, 2, 3, 4);
	MUL_SECTION(4, 120, 2, 3, 4, 5);
	MUL_SECTION(5, 720, 2, 3, 4, 5, 6);
	MUL_SECTION(6, 5040, 2, 3, 4, 5, 6, 7);
	MUL_SECTION(7, 40320, 2, 3, 4, 5, 6, 7, 8);
	MUL_SECTION(8, 362880, 2, 3, 4, 5, 6, 7, 8, 9);
#undef MUL_SECTION
}

TEST_CASE("vargs/long long", "check long long multiples from 1 to 8 through va_args") {
	constexpr std::int_least64_t expected_canary0 = 309231971931137ULL;
#define MUL_SECTION(N, EXPECTED, ...)                         \
	SECTION("long long mul" #N) {                            \
		uint_least64_t canary0 = expected_canary0;          \
		long long value        = ll_mul##N(__VA_ARGS__);    \
		REQUIRE(value == static_cast<long long>(EXPECTED)); \
		REQUIRE(canary0 == expected_canary0);               \
	}                                                        \
	static_assert(true, "🙏")

	MUL_SECTION(0, 1ll, 2ll);
	MUL_SECTION(1, 2ll, 2ll);
	MUL_SECTION(2, 6ll, 2ll, 3);
	MUL_SECTION(3, 24ll, 2ll, 3ll, 4ll);
	MUL_SECTION(4, 120ll, 2ll, 3ll, 4ll, 5ll);
	MUL_SECTION(5, 720ll, 2ll, 3ll, 4ll, 5ll, 6ll);
	MUL_SECTION(6, 5040ll, 2ll, 3ll, 4ll, 5ll, 6ll, 7ll);
	MUL_SECTION(7, 40320ll, 2ll, 3ll, 4ll, 5ll, 6ll, 7ll, 8ll);
	MUL_SECTION(8, 362880ll, 2ll, 3ll, 4ll, 5ll, 6ll, 7ll, 8ll, 9ll);
#undef MUL_SECTION
}
