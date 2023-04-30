#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T, typename U>
class Iterator
{
public:
  typedef typename vector<T>::iterator iter_type;
  Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data)
  {
    m_it_ = m_p_data_->m_data_.begin();
  }

  void First()
  {
    m_it_ = m_p_data_->m_data_.begin();
  }
  void Next()
  {
    m_it_++;
  }
  bool isDone()
  {
    return (m_it_ == m_p_data_->m_data_.end());
  }
  iter_type Current()
  {
    return m_it_;
  }

private:
  U *m_p_data_;
  iter_type m_it_;
};

template <class T>
class Container
{
  friend class Iterator<T, Container>;

public:
  void Add(T a)
  {
    m_data_.push_back(a);
  }
  Iterator<T, Container> *CreateIterator()
  {
    return new Iterator<T, Container>(this);
  }

private:
  vector<T> m_data_;
};

class Data
{
private:
  int m_data_;

public:
  Data(int a = 0) : m_data_(a) {}
  void set_data(int a)
  {
    m_data_ = a;
  }
  int data()
  {
    return m_data_;
  }
};

void ClientCode()
{
  cout << " --- iterator with int --- " << endl;

  Container<int> count;

  for (int i = 0; i < 10; ++i)
  {
    count.Add(i);
  }

  Iterator<int, Container<int>> *itr = count.CreateIterator();
  for (itr->First(); !itr->isDone(); itr->Next())
  {
    cout << *itr->Current() << endl;
  }

  Container<Data> countData;
  Data a(100), b(1000), c(10000);
  countData.Add(a);
  countData.Add(b);
  countData.Add(c);

  cout << " --- iterator with custom Class --- " << endl;
  Iterator<Data, Container<Data>> *itrData = countData.CreateIterator();

  for (itrData->First(); !itrData->isDone(); itrData->Next())
  {
    cout << itrData->Current()->data() << endl;
  }

  delete itr;
  delete itrData;
}

int main()
{
  ClientCode();
  return 0;
}