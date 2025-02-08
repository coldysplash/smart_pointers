#include <iostream>
#include <smart_pointers.hpp>

using namespace SmartPointers;

struct Test {
  int a = 2;
  int b = 3;
};

int main() {
  uniquePtr<int> iptr1(new int(42));
  uniquePtr<int> iptr2;

  std::cout << "ptr1 " << iptr1.get() << ' ' << *iptr1 << '\n';
  std::cout << "ptr2 " << iptr2.get() << '\n';

  iptr2 = std::move(iptr1);

  std::cout << "ptr1 " << iptr1.get() << '\n';
  std::cout << "ptr2 " << iptr2.get() << ' ' << *iptr2 << '\n';

  const uniquePtr<const Test> iptr3(new Test());
  std::cout << "Value of Test struct a = " << iptr3->a << '\n';

  int *raw_ptr = iptr2.release();
  std::cout << "Val raw_ptr " << *raw_ptr << '\n';
  delete raw_ptr;

  std::cout << "iptr2 after release = " << iptr2.get() << '\n';

  struct FileDeleter {
    void operator()(FILE *f) const { fclose(f); }
  };
  using UniqueFile = uniquePtr<FILE, FileDeleter>;
  UniqueFile fptr(fopen("test.txt", "w"));
}