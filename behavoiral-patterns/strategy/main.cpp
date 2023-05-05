#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Strategy
{
public:
  virtual ~Strategy() = default;
  virtual string doAlgorithm(string_view data) const = 0;
};

class Context
{
private:
  unique_ptr<Strategy> strategy_;

public:
  explicit Context(unique_ptr<Strategy> &&strategy = {}) : strategy_(move(strategy)) {}
  void set_strategy(unique_ptr<Strategy> &&strategy)
  {
    strategy_ = move(strategy);
  }
  void doSomeBusinessLogic() const
  {
    if (strategy_)
    {
      cout << "Context: sorting data using the strategy (not sure how i'll do it)\n";
      string result = strategy_->doAlgorithm("aecdb");
      cout << result << endl;
    }
    else
      cout << "Context: strategy isn't set\n";
  }
};

class ConcreteStrategyA : public Strategy
{
public:
  string doAlgorithm(string_view data) const override
  {
    string result(data);
    sort(begin(result), end(result));
    return result;
  }
};

class ConcreteStrategyB : public Strategy
{
public:
  string doAlgorithm(string_view data) const override
  {
    string result(data);
    sort(begin(result), end(result), greater<>());
    return result;
  }
};

void clientCode()
{
  Context context(std::make_unique<ConcreteStrategyA>());
  cout << "Client: strategy is set to normal sorting.\n";
  context.doSomeBusinessLogic();
  cout << endl;
  cout << "Client: strategy is set to reverse sorting.\n";
  context.set_strategy(std::make_unique<ConcreteStrategyB>());
  context.doSomeBusinessLogic();
}

int main()
{
  clientCode();
  return 0;
}