
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

#include <ztd/vargs.hpp>
#include <ztd/idk/assert.hpp>

int imul3(...) {
	ztdc_va_list vl;
	ztdc_va_start(vl);
	int num0 = ztdc_va_arg(vl, int);
	int num1 = ztdc_va_arg(vl, int);
	int num2 = ztdc_va_arg(vl, int);
	ztdc_va_end(vl);
	return num0 * num1 * num2;
}

double dmul3(...) {
	ztdc_va_list vl;
	ztdc_va_start(vl);
	int num0    = ztdc_va_arg(vl, int);
	double num1 = ztdc_va_arg(vl, double);
	int num2    = ztdc_va_arg(vl, int);
	ztdc_va_end(vl);
	return num0 * num1 * num2;
}

int main() {
	double result0 = imul3(3, 4, 5);
	double result1 = dmul3(3, 4.5, 5);
	ZTD_ASSERT(result0 == 60);
	ZTD_ASSERT(result1 == 67.5);
	return 0;
}
