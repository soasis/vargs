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

#include <catch2/catch.hpp>

#include <ztd/vargs.hpp>

#include <cmath>
#include <cstdint>
#include <cstddef>

struct small {
	long long value;
};

struct large {
	long long value;
	char padding[64]; // add some thickness
};

namespace {

#define make_mulN(TYPE, NAME, N)                                                           \
	static TYPE NAME##_mul##N(...) {                                                      \
		TYPE accumulation           = { 1 };                                             \
		[[maybe_unused]] TYPE value = { 0 };                                             \
		ztdc_va_list vl;                                                                 \
		ztdc_va_start(vl);                                                               \
		if constexpr (N > 0) {                                                           \
			for (std::size_t index = 0; index < N; ++index) {                           \
				value = ztdc_va_arg(vl, TYPE);                                         \
				REQUIRE(value.value == static_cast<decltype(value.value)>(index + 2)); \
				accumulation.value *= value.value;                                     \
			}                                                                           \
		}                                                                                \
		ztdc_va_end(vl);                                                                 \
		return accumulation;                                                             \
	}                                                                                     \
	static_assert(true, "🙏")

	make_mulN(small, small, 0);
	make_mulN(small, small, 1);
	make_mulN(small, small, 2);
	make_mulN(small, small, 3);
	make_mulN(small, small, 4);
	make_mulN(small, small, 5);
	make_mulN(small, small, 6);
	make_mulN(small, small, 7);
	make_mulN(small, small, 8);

	make_mulN(large, large, 0);
	make_mulN(large, large, 1);
	make_mulN(large, large, 2);
	make_mulN(large, large, 3);
	make_mulN(large, large, 4);
	make_mulN(large, large, 5);
	make_mulN(large, large, 6);
	make_mulN(large, large, 7);
	make_mulN(large, large, 8);
} // namespace

static large large_mul7x(...) {
	large accumulation           = { 1 };
	[[maybe_unused]] large value = { 0 };
	ztdc_va_list vl;
	ztdc_va_start(vl);
	for (std::size_t index = 0; index < 7; ++index) {
		value = ztdc_va_arg(vl, large);
		REQUIRE(value.value == static_cast<decltype(value.value)>(index + 2));
		accumulation.value *= value.value;
	}
	ztdc_va_end(vl);
	return accumulation;
}

TEST_CASE("vargs/smalls", "check small struct multiples from 1 to 8 through va_args") {
	constexpr std::uint_least64_t expected_canary0 = 309231971931137ULL;
#define MUL_SECTION(N, EXPECTED, ...)                              \
	SECTION("small mul" #N) {                                     \
		std::uint_least64_t canary0 = expected_canary0;          \
		small value                 = small_mul##N(__VA_ARGS__); \
		REQUIRE(value.value == ((EXPECTED).value));              \
		REQUIRE(canary0 == expected_canary0);                    \
	}                                                             \
	static_assert(true, "🙏")


	MUL_SECTION(0, small { 1 }, small { 2 });
	MUL_SECTION(1, small { 2 }, small { 2 });
	MUL_SECTION(2, small { 6 }, small { 2 }, small { 3 });
	MUL_SECTION(3, small { 24 }, small { 2 }, small { 3 }, small { 4 });
	MUL_SECTION(4, small { 120 }, small { 2 }, small { 3 }, small { 4 }, small { 5 });
	MUL_SECTION(5, small { 720 }, small { 2 }, small { 3 }, small { 4 }, small { 5 }, small { 6 });
	MUL_SECTION(6, small { 5040 }, small { 2 }, small { 3 }, small { 4 }, small { 5 }, small { 6 },
	     small { 7 });
	MUL_SECTION(7, small { 40320 }, small { 2 }, small { 3 }, small { 4 }, small { 5 },
	     small { 6 }, small { 7 }, small { 8 });
	MUL_SECTION(8, small { 362880 }, small { 2 }, small { 3 }, small { 4 }, small { 5 },
	     small { 6 }, small { 7 }, small { 8 }, small { 9 });
#undef MUL_SECTION
}

TEST_CASE("vargs/large", "check large struct multiples from 1 to 8 through va_args") {
	constexpr std::uint_least64_t expected_canary0 = 309231971931137ULL;
#define MUL_SECTION(N, EXPECTED, ...)                              \
	SECTION("large mul" #N) {                                     \
		std::uint_least64_t canary0 = expected_canary0;          \
		large value                 = large_mul##N(__VA_ARGS__); \
		REQUIRE(value.value == EXPECTED.value);                  \
		REQUIRE(canary0 == expected_canary0);                    \
	}                                                             \
	static_assert(true, "🙏")

	SECTION("large mul7x") {
		std::uint_least64_t canary0 = expected_canary0;
		large value = large_mul7x(large { 2 }, large { 3 }, large { 4 }, large { 5 }, large { 6 },
		     large { 7 }, large { 8 });
		REQUIRE(value.value == (large { 40320 }.value));
		REQUIRE(canary0 == expected_canary0);
	}

	MUL_SECTION(0, large { 1 }, large { 2 });
	MUL_SECTION(1, large { 2 }, large { 2 });
	MUL_SECTION(2, large { 6 }, large { 2 }, large { 3 });
	MUL_SECTION(3, large { 24 }, large { 2 }, large { 3 }, large { 4 });
	MUL_SECTION(4, large { 120 }, large { 2 }, large { 3 }, large { 4 }, large { 5 });
	MUL_SECTION(5, large { 720 }, large { 2 }, large { 3 }, large { 4 }, large { 5 }, large { 6 });
	MUL_SECTION(6, large { 5040 }, large { 2 }, large { 3 }, large { 4 }, large { 5 }, large { 6 },
	     large { 7 });
	MUL_SECTION(7, large { 40320 }, large { 2 }, large { 3 }, large { 4 }, large { 5 },
	     large { 6 }, large { 7 }, large { 8 });
	MUL_SECTION(8, large { 362880 }, large { 2 }, large { 3 }, large { 4 }, large { 5 },
	     large { 6 }, large { 7 }, large { 8 }, large { 9 });
#undef MUL_SECTION
}
