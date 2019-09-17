#include <iostream>

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

int main() {
  primer4();
  return 0;
}
