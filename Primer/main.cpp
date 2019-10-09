#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include "sales_data.h"
#include "sales_item.h"

void primer1() {
  int sum{0}, val{1};
  while (val <= 10) {
    sum += val;
    ++val;
  }
  std::cout << "Sum: " << sum << std::endl;
}

void primer3() {
  int currVal = 0, val = 0;

  if (std::cin >> currVal) {
    int cnt = 1;
    while (std::cin >> val) {
      if (val == currVal)
        ++cnt;
      else {
        std::cout << currVal << " occurs " << cnt << " times" << std::endl;
        currVal = val;
        cnt = 1;
      }
    }
    std::cout << currVal << " occurs " << cnt << " times " << std::endl;
  }
}

void primer2() {
  float a, b;

  std::cout << "Hello " << std::endl;
  std::cin >> a;
  std::cin >> b;
  std::cout << " Sum: " << a + b;
}

void primer4() {
  int sum{0}, val{0};
  while (!std::cin.eof()) {
    std::cin >> val;
    sum += val;
    val = 0;
  }
  std::cout << "Sum is " << sum << std::endl;
}

int primer5() {
  Sales_item item1{"Book2"}, item2{"Book1"};
  if (item1.isbn() == item2.isbn()) {
    std::cout << item1 + item2 << std::endl;
    return 0;
  } else {
    std::cerr << "!!!" << std::endl;
    return -1;
  }
}

void primer6() {
  bool b = 42;
  int i = b;
  i = static_cast<int>(3.14);
  double pi{static_cast<double>(i)};
  unsigned char c = -100;
  signed char c2 = 259;
  // unsigned char c{static_cast<unsigned char>(-1)};

  unsigned u{10};
  int i1{-12};

  std::cout << " b: " << static_cast<bool>(b) << " i: " << i << " pi: " << pi
            << " c: " << c << " c2: " << c2 << " :: " << i1 + i1 << " -- "
            << u + i1 << " --- " << std::endl;

  // for (unsigned int i2 = 10; i2 > 0; --i2) std::cout << i2 << std::endl;
}

void primer7() {
  unsigned u{10}, u2{42};
  std::cout << u - u2 << std::endl;
  std::cout << u2 - u << std::endl;
  bool c{true};
  int i{10}, i2{42};
  std::cout << i2 - i << "==32" << std::endl;
  std::cout << i - i2 << "==-31" << std::endl;
  std::cout << i - u << "==0 ==  int == " << typeid(i - u).name() << std::endl;
  std::cout << u - i << "==0 == unsigned int == " << typeid(nullptr).name()
            << std::endl;

  std::cout << "HEllo\a\115\xFF"
               "world\v"
               "here"
            << std::endl;
}

void primer8() {
  std::cout << "\11\115" << typeid(3.14e1L).name() << std::endl;

  double price{2.3};
  double new1{price};
  price = 3.1;
  std::cout << price << " " << new1 << std::endl;
  int _1_or_2 = 1;
  std::cout << _1_or_2 << std::endl;
}

void primer9() {
  int i{100}, sum{0};
  for (int i = 0; i != 10; i++) sum += i;
  std::cout << " Sum : " << sum << " Int i = " << i << std::endl;
}

void primer10() {
  int iVal{42};

  int &ref_iVal = iVal;
  int newval = iVal;
  ref_iVal = 32;
  std::cout << "iVal : " << iVal << " ref iVal = " << &ref_iVal << "   "
            << newval << std::endl;

  int &ref_iVal3 = ref_iVal;
  ref_iVal3 = 22;
  std::cout << "ref_iVal3 : " << ref_iVal3 << " ref iVal = " << ref_iVal
            << std::endl;
}

void primer11() {
  int i{1024}, i2{2048};
  int &r{i}, r2{i2};

  int ival = 10.2;

  int i3{0}, &r3{i3};
  double d{0};
  auto &r5{d};
  std::cout << "r : " << r << " r2: " << r2 << std::endl;
  r2 = d;

  std::cout << "r : " << r << " r2: " << r2 << std::endl;
}

void primer12() {
  int i{5}, &r{i};
  i = 10;
  r = 22;
  std::cout << i << " -- " << r << std::endl;
}

void primer13() {
  int *p1, *p2{nullptr};

  int iVal{42};
  p1 = &iVal;
  int **p4 = &p1;
  int *p3{&iVal};
  std::cout << "p1: " << p1 << " p2: " << p2 << " p4: " << p4 << std::endl;

  double d{12.34};
  double *pd{&d};
  double *pd2{pd};
  std::cout << "d: " << d << " pd: " << pd << " *pd " << *pd << " pd2: " << pd2
            << " *pd2 " << *pd2 << std::endl;
  *pd = 33.12;
  std::cout << "d: " << d << " pd: " << pd << " *pd " << *pd << " pd2: " << pd2
            << " *pd2 " << *pd2 << std::endl;

  std::cout << sizeof(d) << " but ptr: " << sizeof(*pd) << std::endl;

  char c{'c'};
  char *ptr_c{&c};
  std::cout << c << " --- " << sizeof(char *) << " but ptr: " << sizeof(*ptr_c)
            << std::endl;
  *ptr_c = '2';
  std::cout << c << " --- " << sizeof(c) << " but ptr: " << sizeof(*ptr_c)
            << std::endl;
  std::cout << c << " --- " << sizeof(void *) << std::endl;
}

void primer14() {
  int i1{42}, i2{56};
  int *ptr_i{&i1};
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\n*ptr_i = " << *ptr_i << "\ni1 = " << i1 << "\ni2 = " << i2
            << std::endl;
  *ptr_i = 43;
  std::cout << " --------- " << std::endl;
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\n*ptr_i = " << *ptr_i << "\ni1 = " << i1 << "\ni2 = " << i2
            << std::endl;
  ptr_i = nullptr;
  std::cout << " --------- " << std::endl;
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\ni1 = " << i1 << "\ni2 = " << i2 << std::endl;
  ptr_i = &i2;
  std::cout << " --------- " << std::endl;
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\n*ptr_i = " << *ptr_i << "\ni1 = " << i1 << "\ni2 = " << i2
            << std::endl;

  *ptr_i = 57;
  std::cout << " --------- " << std::endl;
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\n*ptr_i = " << *ptr_i << "\ni1 = " << i1 << "\ni2 = " << i2
            << std::endl;
  ptr_i--;
  std::cout << " --------- " << std::endl;
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\n*ptr_i = " << *ptr_i << "\ni1 = " << i1 << "\ni2 = " << i2
            << std::endl;
  ptr_i++;
  std::cout << " --------- " << std::endl;
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\n*ptr_i = " << *ptr_i << "\ni1 = " << i1 << "\ni2 = " << i2
            << std::endl;
  ptr_i++;
  std::cout << " --------- " << std::endl;
  std::cout << "&i1 = " << &i1 << "\n&i2 = " << &i2 << "\nptr_i = " << ptr_i
            << "\n*ptr_i = " << *ptr_i << "\ni1 = " << i1 << "\ni2 = " << i2
            << std::endl;

  int i3{42};
  int *ptr_i3 = &i3;
  *ptr_i3 = *ptr_i3 * *ptr_i3;
  std::cout << ptr_i3 << " " << *ptr_i3 << std::endl;
  // int *ptr = i3;
  // double *dp{&i3};
}

void primer15() {
  int i{42};
  int *ptr_i{&i};
  std::cout << "i = " << i << "\n&i = " << &i << "\n*ptr_i = " << *ptr_i
            << "\nptr_i = " << ptr_i << "\n&ptr_i = " << &ptr_i << std::endl;

  int **ptr_ii{&ptr_i};
  std::cout << "i = " << i << "\n&i = " << &i << "\n*ptr_i = " << *ptr_i
            << "\nptr_i = " << ptr_i << "\n&ptr_i = " << &ptr_i
            << "\n*ptr_ii = " << *ptr_ii << "\nptr_ii = " << ptr_ii
            << "\n&ptr_ii = " << &ptr_ii << "\n**ptr_ii = " << **ptr_ii
            << std::endl;
  std::cout << " --------- " << std::endl;
  **ptr_ii = 123;
  std::cout << "i = " << i << "\n&i = " << &i << "\n*ptr_i = " << *ptr_i
            << "\nptr_i = " << ptr_i << "\n&ptr_i = " << &ptr_i
            << "\n*ptr_ii = " << *ptr_ii << "\nptr_ii = " << ptr_ii
            << "\n&ptr_ii = " << &ptr_ii << "\n**ptr_ii = " << **ptr_ii
            << std::endl;

  int *&ref = ptr_i;
  std::cout << ref << " - " << *ref << std::endl;
}

void primer16() {
  const int ci{1024};
  int c1{2028};

  const int *ptr_i{&ci};
  const int &ref_ci{c1};
  // ref_ci = c1;

  int i1{42};
  int &r{i1};
  const int &rr{i1};
}

void primer17() {
  const int pi{3};
  const int *ptr{&pi};

  int i{23};
  int *ptr_i{&i};
  const int *cptr_i{&i};
  *ptr_i = 123;
  //*cptr_i = 321;
  cptr_i = &pi;
}
void primer18() {
  int errNb{0};
  int *const ptr_Err{&errNb};
  const double pi{3.14};
  double pi3{0.00};

  const double *ptr_pi0{&pi};
  const double *const ptr_pi{&pi};
  ptr_pi0 = &pi3;
  // ptr_pi = &pi3;

  int i, *const cp{&i};
}
void primer19() {
  int i{0};
  int j{2};

  int *const p1{&i};
  *p1 = 32;  // нельзя переуказать p1 - он сам константа ---> TOP LEVEL
  // p1 = &j;

  const int ci = 42;   // ci не изменить, TOP LEVEL
  const int *p2{&ci};  // p2 сейчас переукажем, LOW LEVEL
  const int c2{123};
  p2 = &c2;  // p2 поменяли, но тут lowlevel с2
  // *p2 = 123; // нельзя
  const int *const p3 = p2;
  const int &r{i};
  // r = 123;
  // int *pp = p3;
  p2 = p3;
  const int &r2{i};
  const int &r3{ci};
}

void primer20() {
  const int v2{0};                              // top
  int v1 = v2;                                  // low
  int *p1{&v1}, &r1{v1};                        // no const
  const int *p2{&v2}, *const p3{&v1}, &r2{v2};  // low, top, low
}
constexpr int size() {
  constexpr int i{123};
  const int *const ptr{&i};

  return *ptr;
}
void primer21() {
  constexpr int mf{20};
  constexpr int limit{mf + 1};
  constexpr int sz = size();
  constexpr int cmf = 42;
  int j = 0;
  // constexpr const int *ptr = &j;
  const int *psz{&mf};
  std::cout << sz << std::endl;

  int null{0};
  // constexpr const int *p = null;
}

void primer22() {
  using dd = double;
  dd mydouble{123.112};
  std::cout << mydouble << typeid(mydouble).name() << std::endl;
}

void primer23() {
  auto i{12.3};
  Sales_item v1;
  Sales_item v2;
  std::cout << v1 + v2 << " --- " << sizeof v1 << typeid(v1 + v2).name()
            << std::endl;

  int a{9}, &r{a};
  auto cc{r};
  std::cout << cc << " --- " << sizeof cc << typeid(cc).name() << std::endl;
}
void primer24() {
  int i{9}, &r{i};
  const int ci = i, &cr = ci;
  auto b = ci;         // int
  auto c = cr;         // int
  auto d = &i;         // pointer int
  const auto e = &ci;  // pointer to const int
  std::cout << typeid(e).name() << std::endl;
}
void primer25() {
  const int i{42};
  auto l = i;                  // int
  const auto &k = i;           // K int
  auto *p = &i;                // PKi;
  const auto j2 = i, &k2 = i;  // kint
  std::cout << typeid(l).name() << std::endl;
  std::cout << typeid(k).name() << std::endl;
  std::cout << typeid(p).name() << std::endl;
  std::cout << typeid(j2).name() << std::endl;
  std::cout << typeid(k2).name() << std::endl;
}

void primer26() {
  const int ci{0}, &cj{ci};
  decltype(ci) x = 0;
  decltype(cj) y = x;
  const int &d = ci;

  std::cout << typeid(x).name() << std::endl;
  std::cout << typeid(y).name() << std::endl;
}

void primer27() {
  int i{42}, *p{&i}, &r{i};
  std::cout << typeid(i).name() << typeid(p).name() << typeid(r).name()
            << std::endl;
  decltype(r + 0) b = r;
  b = 12;
  std::cout << typeid(b).name() << b << i << std::endl;

  decltype(*p) c = r;
  r = 13;
  std::cout << typeid(c).name() << c << i << std::endl;

  decltype((r)) d = r;
  std::cout << typeid(d).name() << d << std::endl;
}

void primer28() {
  int a{3}, b{6};
  decltype(a) c{a};  // i3
  std::cout << typeid(c).name() << c << std::endl;
  decltype((b)) d = a;  // int&
  std::cout << typeid(d).name() << d << std::endl;
  ++c;
  ++c;

  std::cout << c << "..." << d << std::endl;  //  4 6
}
void primer29() {
  int a{3}, b{4};
  decltype(a) c = a;      // int
  decltype(a = b) d = a;  // int&
  d = b;
  int *p = &d;
  std::cout << typeid(b).name() << d << std::endl;
  d = 10;
  std::cout << typeid(b).name() << d << std::endl;
  std::cout << typeid(d).name() << d << std::endl;
}

void primer30() {
  Sales_data s1, s2;
  double price{0};
  std::cin >> s1.bookNo >> s1.units_sold >> price;
  s1.revenue = s1.units_sold * price;
  std::cout << s1.bookNo << " ::: " << s1.revenue;
}
void primer31() {
  std::string s{"hello world!"};
  if (!s.empty()) std::cout << s[0] << std::endl;

  for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]);
       ++index)
    s[index] = toupper(s[index]);

  std::cout << s << std::endl;
}

void primer32() {
  const std::string hexdigits{"0123456789ABCDEF"};
  std::cout << "Enter a series of numbers betwenn 0 - 15 "
               "hit Enter when completed"
            << std::endl;
  std::string result;

  std::string::size_type n;
  while (std::cin >> n)
    if (n < hexdigits.size()) result += hexdigits[n];
  std::cout << "Your hex number is : " << result << std::endl;
}
void primer33() {
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line == "stop_me") break;
    for (auto &c : line) c = {'x'};
    std::cout << line << std::endl;
  }
}

void primer34() {
  std::string s;
  while (getline(std::cin, s)) {
    for (auto &c : s)
      if (ispunct(c)) c = '\b';
    std::cout << s << std::endl;
  }
}

void primer35() {
  std::vector<std::vector<int>> ivec;
  std::vector<std::string> svec(10, "hello");

  for (auto s : svec) std::cout << s << std::endl;
  std::vector<std::string> v7{10, "hi"};
  for (auto s : v7) std::cout << s << std::endl;
}

void primer36() {
  std::vector<int> v1;
  for (int i{0}; i < 300; i++) {
    std::cout << i << " Size : " << v1.size() << " Capacity: " << v1.capacity()
              << std::endl;
    v1.push_back(i);
  }

  // for (auto d : v1) std::cout << d << std::endl;
}

void primer37() {
  std::string word;
  std::vector<std::string> text;
  while (std::cin >> word) text.push_back(word);
  for (auto w : text) std::cout << w << std::endl;
}

void primer38() {
  std::vector<int> v_int;
  int i;
  while (std::cin >> i) v_int.push_back(static_cast<int>(i));

  for (auto i : v_int)
    std::cout << i << " with type " << typeid(i).name() << std::endl;
}
int main() {
  primer38();

  return 0;
}
