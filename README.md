# cpp-any

#### 介绍
C++11标准下实现C++17标准any类。

std::any是C++17标准才实现的类。若编译器不支持C++17标准，而我们又需要使用any类，cpp-any提供了一个实现的参考，接口与std::any保持一致。

#### 要求
编译器要求至少支持C++11标准。

#### 目录结构
```
./cpp-any
├── doc         # 文档目录
│   └── html    # doxygen生成的html文档
└── tools   
    └── qt      # QT工程

```

#### Example

```cpp
#include "any.h"
#include <iostream>

#include <any>

struct Point
{
    Point() = default;
    Point(double _x, double _y) : x(_x), y(_y) { }
    double x{ 0.0 };
    double y{ 0.0 };
};

int main(int, char*[])
{
    std::cout << std::boolalpha;

    // any type
    any a = 1;
    std::cout << a.type().name() << ": " << any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << any_cast<bool>(a) << '\n';

    // bad cast
    try {
        a = 1;
        std::cout << any_cast<float>(a) << '\n';
    } catch (const bad_any_cast& e) {
        std::cout << e.what() << '\n';
    }

    // has value
    a = 1;
    if (a.has_value()) {
        std::cout << a.type().name() << '\n';
    }

    // reset
    a.reset();
    if (!a.has_value()) {
        std::cout << "no value\n";
    }

    // pointer to contained data
    a = 1;
    int* i = any_cast<int>(&a);
    std::cout << *i << "\n";

    any any_pt = Point(10.0, 20.0);
    Point pt = any_cast<Point>(any_pt);
    std::cout << "Point.x=" << pt.x << std::endl;
    std::cout << "Point.y=" << pt.y << std::endl;

    return 0;
}
```

Possible output: 
```
i: 1
d: 3.14
b: true
bad any_cast
i
no value
1
Point.x=10
Point.y=20
```

#### 与std::any兼容

在自定义命名空间中，兼容不同C++标准。
- C++11 - C++14标准使用自实现any类
- C++17及以后标准使用std::any类

```cpp

/** cplusplus-standard version number. */
#ifdef _MSVC_LANG
#   define CPLUSPLUS__      _MSVC_LANG
#else
#   define CPLUSPLUS__      __cplusplus
#endif /* _MSVC_LANG */

#if CPLUSPLUS__ > 201402L
#   if (defined(_MSC_VER) && _MSC_VER >= 1910) || \
       (defined(__GNUC__) && __GNUC__ >= 7) || \
       (defined(__clang__) && __clang_major__ >= 4)
/* std::any */
#       define HAS_STDANY__
#endif

#if defined(HAS_STDANY__)
#   include <any>
#else
#   include "any.h"
#endif

namespace user_ns {

#if defined(HAS_STDANY__)

using user_any = std::any;
using std::bad_any_cast;
using std::any_cast;
using std::make_any;
using std::swap;

#else

using user_any = any;
using bad_any_cast;
using any_cast;
using make_any;
using swap;

#endif // !has std::any.

} // namespace dcmnet
```

#### API文档
克隆此仓库后, 使用浏览器打开 doc 目录下的 cpp-any-doc.html 文件。

#### License
```
MIT License

Copyright (c) 2021 shaoguang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```