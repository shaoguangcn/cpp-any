# cpp-any

#### 介绍
C++11标准下实现C++17标准any类。

std::any是C++17标准才实现的类。若编译器不支持C++17标准，而我们又需要使用any类，cpp-any提供了一个实现的参考，接口与std::any保持一致。

#### 要求
编译器要求至少支持C++11标准。

#### Example

```cpp
#include <any.h>
#include <iostream>

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
```

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