#ifndef FASTREAD_GRISU3_H_
#define FASTREAD_GRISU3_H_

/* Copyright Jukka Jylänki
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/* This file is part of an implementation of the "grisu3" double to string
	conversion algorithm described in the research paper

	"Printing Floating-Point Numbers Quickly And Accurately with Integers"
	by Florian Loitsch, available at
	http://www.cs.tufts.edu/~nr/cs257/archive/florian-loitsch/printf.pdf */

extern "C"
{

/// Converts the given double-precision floating point number to a string representation.
/** For most inputs, this string representation is the
	shortest such, which deserialized again, returns the same bit
	representation of the double.
	@param v The number to convert.
	@param dst [out] The double-precision floating point number will be written here
		as a null-terminated string. The conversion algorithm will write at most 25 bytes
		to this buffer. (null terminator is included in this count).
		The dst pointer may not be null.
	@return the number of characters written to dst, excluding the null terminator (which
		is always written) is returned here. */
int dtoa_grisu3(double v, char *dst);

}

#ifdef __cplusplus

#include <string>
std::string dtoa_grisu3_string(double v);

#endif

#endif
