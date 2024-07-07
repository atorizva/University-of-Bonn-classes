# STL Library

Containers over simple arrays:

## Size

```cpp
// Arrays
int data[17];
size_t data_size = sizeof(data) / sizeof(data[0]);
printf("Size of array: %zu\n", data_size);

// Containers
std::array<int, 17> data_{};
cout << "Size of array: " << data_.size() << endl;
```

## Empty or not

```cpp
// Arrays
int empyt_arr[10];
printf("Array empty: %d\n", empty_arr[0] == NULL);

// Containers
std::vector<int> empty_vec_{};
cout << "Array empty: " << empty_vec.empty() << endl;
```

## Access last element

```cpp
// Arrays
float f_arr[N] = {1.5, 2.3};
// What is N?
printf("Last element: %f\n", f_arr[3]); // Is it 3?

// Containers
std::array<float, 2> f_arr_{1.5, 2.3};
cout << "Last Element: " << f_arr_.back() << endl;
```

## Clear contents

```cpp
// Arrays
char letters[5] = {'n', 'a', 'c', 'h', 'o'};
memset(letters, 0, sizeof(letters)); // Does not work always with floats

// Containers
std::vector<char> letters_ = {'n', 'a', 'c', 'h', 'o'};
letters_.clear();

std::string letters_right_{"nacho"};
letters_right_.clear();
```

In summary, containers are much more readable, easier to use and have tons of methods and functions available for them. Use them every time you can, don't reinvent the wheel. Is better to provide template functions to take advantage of all of them.

## Types of containers

### std::map

Maps a unique key to a value. It allows for fast access and sorting when you cannot do it directly in you custom data/value.


## Picking the right container for the job

Think about the **most** frequent operation. Not the most complex.

## Iterators

Looks like a pointer. *Points* to an element from the container. Contains the next position in memory of the following element. They don't need to be contiguous in memory.

## Template functions

Don't define multiple functions that work in the same way with different containers. That is what **Iterators** are for!:

```cpp
template<typename Iterator>
void print_it(Iterator begin, Iterator end) {
    forr (Iterator it = begin; it != end; it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

> Iterators allow to take advantage of ton of algorithms in the STL.

## Lambda functions

```cpp
auto print = [](){};
```

`[]` captures some value outside of the lambda. May be a reference.

```cpp
int a = 1;
auto print = [&a](){};
```

> If you use `[&]` it will pass my reference everything you use in your lambda function. `[=]` is by copy.

`()` contains the arguments for the lambda function.

```cpp
auto print = [](const int num){};
```

> If you use `auto` in the argument is usually acceptable if you are working with containers, since it is implicit.

You can use the `mutable` keyword to allow for modifying something wihtin the lambda function. AVOID IT IF YOU CAN

You could even make a lambda function templated (C++ 23 only), but it is very rare:

```cpp
template <typename T>
class ExampleClass{};

int a = 5;
auto print = [&]<typename T>(const ExampleClass<T>) {};
```

> Try to use lambda functions over inline functions.

Check out lambda idioms!

## Execution policy

Similar to passing a flag to a function so that it executes in certain way:

1. Sequenced.
2. Parallel.
3. Parallel unsequenced.
4. Unsequenced.

You as a programmer are responsible to make them work. For example, if you want it to be parallel be aware of data race conditions.
