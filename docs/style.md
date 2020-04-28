# Zeus Style Guide

## Coding Style

The coding style used by Zeus (and indeed all of my projects) is relatively
straight-forward and uses the following guidelines:

### Function and Variable Names

All function and variable names use `snake_case` and have no leading (or
trailing underscores) or prefixes or any kind. The only exception to this rule
are private member variables of classes, in which case the variable name is
prepended with `m_`. For example:

```c++
static constexpr auto global_value{10};

void some_function(int some_param)
{
    // Do stuff here...
}
```

### Classes and Custom Types

All classes and custom types use `PascalCase`. This includes:

* `class` or `struct` types,
* `enum class` and `enum types`,
* `using`,
* template parameters.

For example:

```c++
template<typename IterType>
class Widget
{
public:
    Widget();
private:
    int m_my_var;
}

enum class Flags
{
    value_one
}
```

## Formatting

This is handled automatically by the `.clang_format` file located at the root of
all projects. Make sure that the code is formatted using `clang-format` before
pushing upstream.

## Unit Tests

All code must be unit tested to ensure that it works and prevent surprises down
the line. The tests use the following naming convention (note that Catch is used
as the unit testing framework):

```c++
TEST_CASE("[<class/file-name>] - <function-name>: <test-case>", "[<module-name>]")
{
    // Testing code here...
}
```
