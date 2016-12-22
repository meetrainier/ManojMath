#include <string>
namespace my_ns {
  struct my_type {
    int x;
    double d;
    std::string s;
  };
  struct my_type_view {
    my_type* ptr;
  };
}

namespace std {
  template<>
  struct tuple_size<my_ns::my_type_view> : std::integral_constant<std::size_t, 3>
  {};

  template<> struct tuple_element<my_ns::my_type_view, 0> { using type = int; };
  template<> struct tuple_element<my_ns::my_type_view, 1> { using type = double; };
  template<> struct tuple_element<my_ns::my_type_view, 2> { using type = std::string; };
}

namespace my_ns {
  template<std::size_t I>
  decltype(auto) get(my_type_view const& v) {
    if constexpr (I == 0)
      return v.ptr->x;
    else if constexpr (I == 1)
      return v.ptr->d;
    else if constexpr (I == 2)
      return v.ptr->s;
    static_assert(I < 3, "Only 3 elements");
  }
}



my_ns::my_type t{ 1, 3.14, "hello world" };

my_ns::my_type_view foo() {
  return{ &t };
}

int main() {
  auto[x, d, s] = foo();
  std::cout << x << ',' << d << ',' << s << '\n';
}