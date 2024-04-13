# `pb` - the all-in-one progress bar
`pb` is a header-only C++ library.

![Example video of the progress bar](example.gif "Example")

## Usage
### Iterators
```cpp
std::vector<int> v(50, 1);
for (auto &i : pb<std::vector<int>>(v)) {
    sleep(1);
}
```