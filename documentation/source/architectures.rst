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

Supported Architectures
=======================

Each architecture needs to be supported explicitly, with occasional builtins or other things aiding in iteration and work. If you'd like to contribute an implementation, please make a patch to the repository!

Furthermore, it is imperative to note the various circumstances this can appear under in C++ includes member functions. Unfortunately, we have not yet developed a way of knowing this information, and member functions do change the way the compiler interacts with the ABI and where it places arguments.

.. csv-table:: Architecture List
	:header: "Compiler", "Architecture", "Supported?" "Notes / Documentation"
	:widths: 1, 1, 1, 1

	"Microsoft Visual C++", "x86_64 (AMD64)", "✅", ":doc:`Notes </architectures/vc++/x64>`"
	"", "x86 (i686)", "❌", "❌"
	"", "ARM", "❌", "❌"
	"", "ARM64", "❌", "❌"
	"Clang", "x86_64 (AMD64)", "❌", "❌"
	"", "x86 (i686)", "❌", "❌"
	"", "ARM", "❌", "❌"
	"", "ARM64", "❌", "❌"
	"GCC", "x86_64 (AMD64)", "❌", "❌"
	"", "x86 (i686)", "❌", "❌"
	"", "ARM", "❌", "❌"
	"", "ARM64", "❌", "❌"

.. toctree::
	:hidden:
	:glob:

	architectures/**
