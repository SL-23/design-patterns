/* open closed::
  open to extension
  closed for modification

  never required yourself to go back

*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color
{
  red,
  green,
  blue
};
enum class Size
{
  small,
  medium,
  large
};

struct Product
{
  string name;
  Color color;
  Size size;
};

/*

OLDDDDDD

struct ProductFilter
{
  vector<Product *> byColor(vector<Product *> items, Color color)
  {
    vector<Product *> result;
    for (auto &item : items)
    {
      if (item->color == color)
        result.push_back(item);
    }
    return result;
  }

  vector<Product *> bySize(vector<Product *> items, Size size)
  {
    vector<Product *> result;
    for (auto &item : items)
    {
      if (item->size == size)
        result.push_back(item);
    }
    return result;
  }
};

*/

template <typename T>
struct AndSpecification;

template <typename T>
struct Specification
{
  virtual ~Specification() = default;
  virtual bool isSatisfied(T *item) = 0;
};

template <typename T>
AndSpecification<T> operator&&(const Specification<T> &first, const Specification<T> &second)
{
  return {first, second};
};

template <typename T>
struct AndSpecification : Specification<T>
{
  Specification<T> &first;
  Specification<T> &second;

  AndSpecification(Specification<T> &first, Specification<T> &second) : first(first), second(second) {}

  bool isSatisfied(T *item) override
  {
    return first.isSatisfied(item) && second.isSatisfied(item);
  }
};

template <typename T>
struct Filter
{
  virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product>
{
  vector<Product *> filter(vector<Product *> items, Specification<Product> &spec)
      override
  {
    vector<Product *> result;
    for (auto &item : items)
    {
      if (spec.isSatisfied(item))
        result.push_back(item);
    }
    return result;
  }
};

struct ColorSpecification : Specification<Product>
{
  Color color;

  ColorSpecification(Color color) : color(color) {}

  bool isSatisfied(Product *item) override
  {
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product>
{
  Size size;

  SizeSpecification(Size size) : size(size) {}

  bool isSatisfied(Product *item) override
  {
    return item->size == size;
  }
};

int main()
{
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  vector<Product *> items{&apple, &tree, &house};

  // ProductFilter pf;

  BetterFilter bf;
  ColorSpecification green(Color::green);

  for (auto &item : bf.filter(items, green))
  {
    cout << item->name << " is green" << endl;
  }

  SizeSpecification large(Size::large);
  AndSpecification<Product> greenAndLarge(green, large);

  for (auto &item : bf.filter(items, greenAndLarge))
  {
    cout << item->name << " is green and large" << endl;
  }

  return 0;
}