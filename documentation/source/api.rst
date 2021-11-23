.. =============================================================================
..
.. ztd.vargs
.. Copyright © 2021 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
.. Contact: opensource@soasis.org
..
.. Commercial License Usage
.. Licensees holding valid commercial ztd.vargs licenses may use this file in
.. accordance with the commercial license agreement provided with the
.. Software or, alternatively, in accordance with the terms contained in
.. a written agreement between you and Shepherd's Oasis, LLC.
.. For licensing terms and conditions see your agreement. For
.. further information contact opensource@soasis.org.
..
.. Apache License Version 2 Usage
.. Alternatively, this file may be used under the terms of Apache License
.. Version 2.0 (the "License") for non-commercial use; you may not use this
.. file except in compliance with the License. You may obtain a copy of the
.. License at
..
.. 		https://www.apache.org/licenses/LICENSE-2.0
..
.. Unless required by applicable law or agreed to in writing, software
.. distributed under the License is distributed on an "AS IS" BASIS,
.. WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
.. See the License for the specific language governing permissions and
.. limitations under the License.
..
.. =============================================================================>

API Reference
=============

Each given function aids in iterating over a ``ztdc_va_list``. Currently, the lists are specified to iterate over **all** arguments where possible, unless compiler optimization or similar interferes with the documented ABI and API constraints of a particular compiler / platform combination. This means that for the following:

.. code-block:: cpp
	:linenos:
	:caption: An example piece of code with 2 named arguments that go unused.
	:name: api-named_argument_skip.cpp


	#include <ztd/vargs.hpp>
	#include <ztd/idk/assert.hpp>

	double dmul3([[maybe_unused]] int a,
	             [[maybe_unused]] double b,
	             ...) {
		ztdc_va_list vl;
		ztdc_va_start(vl);
		int num0    = ztdc_va_arg(vl, int);
		double num1 = ztdc_va_arg(vl, double);
		int num2    = ztdc_va_arg(vl, int);
		ztdc_va_end(vl);
		return num0 * num1 * num2;
	}

	int main() {
		double result = dmul3(3, 4.5, 5);
		ZTD_ASSERT(result == 67.5);
		return 0;
	}

Even the named argument ``a`` and ``b`` will be iterated over. (A future revision of this library may correct for this, but it is how it is for now.) This means that you should avoid using this when there are arguments present in the list, and therefore wish to execute ``


See the :doc:`architecture list</architectures/vc++/x64>` for supported architectures.



Functions
---------

.. doxygentypedef:: ztdc_va_list

.. doxygendefine:: ztdc_va_start

.. doxygendefine:: ztdc_va_start_in

.. doxygendefine:: ztdc_va_arg

.. doxygendefine:: ztdc_va_end
