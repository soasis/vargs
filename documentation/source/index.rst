.. =============================================================================
..
.. ztd.vargs
.. Copyright © JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
.. https://www.apache.org/licenses/LICENSE-2.0
..
.. Unless required by applicable law or agreed to in writing, software
.. distributed under the License is distributed on an "AS IS" BASIS,
.. WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
.. See the License for the specific language governing permissions and
.. limitations under the License.
..
.. =============================================================================>

``ztd.vargs``
=================

The premiere library for handling text in different encoding forms for C software.



Who Is This Library For?
------------------------

Ideally?

Nobody.

This is mostly a proof of concept to make a proposal go through ISO/IEC JTC1 SC22 WG14 - Programming Language, C (AKA, C Standards Committee) easier and faster.

But if you're still curious, well, have a look! It works mostly like ``va_start``, ``va_arg``, and ``va_end``, but so far iterates over all arguments (regardless of whether they were passed statically or not).

.. code-block:: cpp
	:linenos:
	:caption: How snazzy and cool, 3 arguments iterated over and used!
	:name: index-splash_example.cpp

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

	int main() {
		int result0 = imul3(3, 4, 5);
		ZTD_ASSERT(result0 == 60);
		return result0;
	}

.. toctree::
	:maxdepth: 1
	:caption: Contents:

	api
	architectures
	license





Indices & Search
================

.. toctree::

	genindex
