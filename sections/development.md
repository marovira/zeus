# Developer's Manual

Zeus is a header-only library, and each header provides several functions or
classes. Here you will find a brief description and examples for each one.

## Contents

1. [Assert](#assert)
2. [Constants](#constants)
3. [Filesystem](#filesystem)
4. [Float](#float)
5. [Functional](#functional)
6. [Platform](#platform)
7. [Timer](#timer)

## Assert <a name="assert"></a>

This header defines the following two assert macros:

* `ASSERT`: if the condition fails, it will print the following: `error: in
  file <file-name>(<line-number>): <condition>`.
* `ASSERT_MSG`: if the condition fails, it will print the following: `error: in
  file <file-name>(<line-number>): <message>`. 

Both assert macros will print their corresponding messages to `stderr`. If the
code is being run on Windows with a debugger attached, the asserts will also
cause the debugger to break, allowing for easier code inspection.

In order to use the macros in your code, you must first add the following to a
*single* file.

```c++
#define ZEUS_ASSERT_IMPL
#include <zeus/assert.hpp>
```

Once you have done this, the header can now be used normally as follows:

```c++
#include <zeus/assert.hpp>

int a{0};
ASSERT(a == 0);                             // Assert with no custom message.
ASSERT_MSG(a == 0, "a should not be 0");    // Assert with custom message.
```

## Constants <a name="constants"></a>

Provides a C++ version of all the constants contained in `<cmath>` as macros.
The constants are all templated `constexpr` variables. The template will only
accept floating point types, as integral types are usually not used for these
constants (and they can be converted if need be). The defined constants are:

* `e`: Euler's constant <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/8cd34385ed61aca950a6b06d09fb50ac.svg?invert_in_darkmode" align=middle width=7.654137149999991pt height=14.15524440000002pt/>
* `log_2_e`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/47938fcd594aaea282f7702781235764.svg?invert_in_darkmode" align=middle width=49.04694134999999pt height=24.65753399999998pt/>
* `ln_2`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/a207c798427d8198615645ec1ad3b648.svg?invert_in_darkmode" align=middle width=34.70331479999999pt height=24.65753399999998pt/>
* `ln_10`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/4092a168cd2598110eceb50765db96ea.svg?invert_in_darkmode" align=middle width=42.922524149999994pt height=24.65753399999998pt/>
* `pi`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/f30fdded685c83b0e7b446aa9c9aa120.svg?invert_in_darkmode" align=middle width=9.96010619999999pt height=14.15524440000002pt/>
* `py_by_2`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/4314e67fbc49be21e488ea5d8ab8d904.svg?invert_in_darkmode" align=middle width=26.39850674999999pt height=24.65753399999998pt/>
* `one_by_pi`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/6412657d49716636093123e68f0e7078.svg?invert_in_darkmode" align=middle width=26.398524899999988pt height=24.65753399999998pt/>
* `two_by_pi`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/a85cc6dce61bb837e34b3b3a4defee1f.svg?invert_in_darkmode" align=middle width=26.398524899999988pt height=24.65753399999998pt/>
* `two_by_sqrt_pi`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/74019d50a26587de4d395edf0a652844.svg?invert_in_darkmode" align=middle width=40.09719779999999pt height=24.995338500000003pt/>
* `sqrt_2`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/71486f265f83bc1e3d2b6f67704bcc23.svg?invert_in_darkmode" align=middle width=21.91788224999999pt height=28.511366399999982pt/>
* `one_by_sqrt_2`: <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/01c9c237293271e317f3bf2a5e23613f.svg?invert_in_darkmode" align=middle width=38.35630094999999pt height=28.511366399999982pt/>

The constants can be used as follows:

```c++
#include <zeus/constants.hpp>

auto pi = zeus::Constants<float>::pi;
auto e  = zeus::Constants<double>::e;
```


3. [Filesystem](#filesystem)
4. [Float](#float)
5. [Functional](#functional)
6. [Platform](#platform)
7. [Timer](#timer)

## Filesystem <a name="filesystem"></a>

Contains a few utility functions for file-based operations. Note that this uses
the `<experimental/filesystem>` header. The reason behind this is that the
normal `<filesystem>` header under Windows is not compatible with the current
standard and will therefore not allow one of the functions to work correctly.
This will be changed once MSVC becomes compliant in C++20. The functions are:

* `get_file_last_write`: Returns the last time the provided file was written to.
* `get_file_directory`: Returns the directory where the file is contained.

Here's how to use them:

```c++
#include <zeus/filesystem.hpp>

std::time_t time_stamp = zeus::get_file_last_write("some/path/to/file.txt");

std::string root_dir = zeus::get_file_directory("some/path/to/file.txt");
```

## Float <a name="float"></a>

Provides a series of functions for floating point comparisons. All functions
rely on the same base formula for comparison. For any two floating point numbers
<img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/5f8c6707c3c404791835c4d82736cf4f.svg?invert_in_darkmode" align=middle width=23.04983339999999pt height=22.831056599999986pt/>, they are considered equal if the following condition holds:

<p align="center"><img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/916b790318b7b74911fad8714273b6ef.svg?invert_in_darkmode" align=middle width=96.78805785pt height=16.438356pt/></p>

Where <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/6f9bad7347b91ceebebd3ad7e6f6f2d1.svg?invert_in_darkmode" align=middle width=7.7054801999999905pt height=14.15524440000002pt/> is

<p align="center"><img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/5a0d975c338fd21a0280402d9e2a9a4c.svg?invert_in_darkmode" align=middle width=85.69574475pt height=34.7253258pt/></p>

The value of <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/7ccca27b5ccc533a2dd72dc6fa28ed84.svg?invert_in_darkmode" align=middle width=6.672392099999992pt height=14.15524440000002pt/> used by default is the provided machine epsilon obtained
via `std::numeric_limits<T>::epsilon`. The functions also have a template
overload that allows for a custom epsilon function to be provided. The
comparison functions are:

* `are_equal`: evaluates <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/97321138a95b4ac5143f780475e9dd79.svg?invert_in_darkmode" align=middle width=37.66158164999999pt height=22.831056599999986pt/>,
* `is_zero`: evaluates <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/939a8ccf1fb6157e90aa1d7d8e6dad5e.svg?invert_in_darkmode" align=middle width=38.82599489999999pt height=21.18721440000001pt/>,
* `geq`: evaluates <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/5c95a2dd29da20e70958bef13631050d.svg?invert_in_darkmode" align=middle width=37.66158164999999pt height=22.831056599999986pt/>,
* `leq`: evaluates <img src="https://rawgit.com/in	git@github.com:marovira/zeus/gh-pages/svgs/ba7b0048fb01eb2791ba2ac6d678eade.svg?invert_in_darkmode" align=middle width=37.66158164999999pt height=22.831056599999986pt/>.

The functions can be used as follows:

```c++
#include <zeus/float.hpp>

float a{1.0f}, b{2.0f};

auto res = zeus::are_equal(1.0f, 2.0f);
res      = zeus::is_zero(a);
res      = zeus::geq(a, b);
res      = zeus::leq(a, b);
```

To use a custom epsilon function, use:

```c++
auto epsilon = []() { return 0.0001f; };

auto res = zeus::are_equal<float, epsilon>(1.0f, 2.0f);
```

## Functional <a name="functional"></a>

## Platform <a name="platform"></a>

## Timer <a name="timer"></a>
