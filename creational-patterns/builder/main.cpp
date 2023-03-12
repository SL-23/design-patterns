#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Product1
{
public:
  vector<string> parts_;
  void ListParts() const
  {
    cout << "Product parts:\n";
    for (size_t i = 0; i < parts_.size(); ++i)
    {
      if (parts_[i] == parts_.back())
      {
        cout << parts_[i];
      }
      else
        cout << parts_[i] << ",";
    }
  }
};

class Builder
{
public:
  virtual ~Builder() {}
  virtual void ProductPartA() const = 0;
  virtual void ProductPartB() const = 0;
  virtual void ProductPartC() const = 0;
};

class ConcreteBuilder1 : public Builder
{
private:
  Product1 *product;

public:
  ConcreteBuilder1()
  {
    this->Reset();
  }
  ~ConcreteBuilder1() { delete product; }

  void Reset()
  {
    this->product = new Product1();
  }

  void ProductPartA() const override
  {
    this->product->parts_.push_back("PartA1");
  }

  void ProductPartB() const override
  {
    this->product->parts_.push_back("PartB1");
  }

  void ProductPartC() const override
  {
    this->product->parts_.push_back("PartC1");
  }

  Product1 *GetPoduct()
  {
    Product1 *result = this->product;
    this->Reset();
    return result;
  }
};

class Director
{
private:
  Builder *builder;

public:
  void setBuilder(Builder *builder)
  {
    this->builder = builder;
  }

  void BuildMinimalViableProduct()
  {
    this->builder->ProductPartA();
  }

  void BuildFullFeaturedProduct()
  {
    this->builder->ProductPartA();
    this->builder->ProductPartB();
    this->builder->ProductPartC();
  }
};

void ClientCode(Director &director)
{
  ConcreteBuilder1 *builder = new ConcreteBuilder1();
  director.setBuilder(builder);

  cout << "Standard basic product:\n";
  // this is where call the builder get the parts!!
  director.BuildMinimalViableProduct();

  // just to get the result (as a product), then reset
  Product1 *p = builder->GetPoduct();
  p->ListParts();

  delete p;

  //!! the builder pattern can be used without a Director class
  cout << "Custom product:\n";
  builder->ProductPartA();
  builder->ProductPartC();

  p = builder->GetPoduct();
  p->ListParts();

  delete p;

  delete builder;
}

int main()
{
  Director *director = new Director();
  ClientCode(*director);

  delete director;
  return 0;
}
