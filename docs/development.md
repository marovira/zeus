# Developer's Manual

Zeus is a header-only library, and each header provides several functions or
classes. Here you will find a brief description and examples for each one.

## `assert.hpp`

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

## `constants.hpp`

Provides a C++ version of all the constants contained in `<cmath>` as macros.
The constants are all templated `constexpr` variables. The template will only
accept floating point types, as integral types are usually not used for these
constants (and they can be converted if need be). The defined constants are:

* `e`: $e$,
* `log_2_e`: $\log_2(e)$,
* `ln_2`: $\ln(2)$,
* `ln_10`: $\ln(10)$,
* `pi`: $\pi$,
* `py_by_2`: $\pi / 2$,
* `one_by_pi`: $1 / \pi$,
* `two_by_pi`: $2 / \pi$,
* `two_by_sqrt_pi`: $2 / \sqrt{\pi}$,
* `sqrt_2`: $\sqrt{2}$,
* `one_by_sqrt_2`: $1 / \sqrt{2}$

The constants can be used as follows:

```c++
#include <zeus/constants.hpp>

auto pi = zeus::Constants<float>::pi;
auto e  = zeus::Constants<double>::e;
```

## `filesystem.hpp`

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

## `float.hpp`

Provides a series of functions for floating point comparisons. All functions
rely on the same base formula for comparison. For any two floating point numbers
$a, b$, they are considered equal if the following condition holds:

$$
\vert a - b \vert \leq \epsilon \cdot s
$$

Where $s$ is

$$
s = \frac{\vert a \vert + \vert b \vert}{2}
$$

The value of $\epsilon$ used by default is the provided machine epsilon obtained
via `std::numeric_limits<T>::epsilon`. The functions also have a template
overload that allows for a custom epsilon function to be provided. The
comparison functions are:

* `are_equal`: evaluates $a = b$,
* `is_zero`: evaluates $a = 0$,
* `geq`: evaluates $a \geq b$,
* `leq`: evaluates $a \leq b$.

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

## `functional.hpp`

Provides a different version of `std::iota` that allows you to increment each
entry in the list by a custom amount. It can be used as follows:

```c++
#include <zeus/functional.hpp>
#include <vector>

std::vector<int> list(10);

zeus::iota(list.begin(), list.end(), 0, 2);   // List starting at 0 increasing by 2
```

## `platform.hpp`

Defines macros and variables that define the current platform and build
configuration. These can be used for defining cross-platform behaviour both at
the pre-processor level as well as through usage of `if constexpr`. The defined
macros are:

* `ZEUS_PLATFORM_WINDOWS`: defined in both 64-bit and 32-bit builds for windows
  platforms.
* `ZEUS_PLATFORM_LINUX`: defined in all Linux-based systems.
* `ZEUS_BUILD_DEBUG`: defined for debug builds.
* `ZEUS_BUILD_RELEASE`: defined for all non-debug builds.

The constants are:

* `current_platform`: defines the platform. Can be either `windows` or `linux`.
* `current_build`: defines the build. Can be either `debug` or `release`.

These can be used as follows:

```c++
#include <zeus/platform.hpp>

#if defined(ZEUS_PLATFORM_WINDOWS)
// Do something for Windows.
#elif defined(ZEUS_PLATFORM_LINUX)
// Do something for linux.
#endif

#if defined(ZEUS_BUILD_DEBUG)
// Debug builds.
#elif defined(ZEUS_BUILD_RELEASE)
// Release builds.
#endif

if constexpr (current_platform == zeus::Platform::windows)
{
    // Windows.
}

if constexpr (current_build == zeus::BuildType::debug)
{
    // Debug.
}
```

## `timer.hpp`

Provides a simple timer for use in performance analysis of code. The timer
relies on `std::chrono` for timing purposes and its precision is therefore tied
to the precision of the implementation of `std::chrono`. The timer is templated
to allow for variable precision depending on the use case. It can be used as
follows:

```c++
#include <zeus/timer.hpp>

zeus::Timer<float> timer;

timer.start();              // Starts the timer.
auto t = timer.elapsed();   // Retrieved the elapsed time in seconds.

timer.start();              // Starts the timer again.
timer.reset();              // Clears the timer.
```
