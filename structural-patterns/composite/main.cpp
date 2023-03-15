#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Component
{
protected:
  Component *parent_;

public:
  virtual ~Component() {}
  void setParent(Component *parent)
  {
    this->parent_ = parent;
  }
  Component *GetParent() const
  {
    return this->parent_;
  }
  virtual void Add(Component *component) {}
  virtual void Remove(Component *component) {}

  virtual bool IsComposite() const
  {
    return false;
  }

  virtual string Operation() const = 0;
};

class Leaf : public Component
{
public:
  string Operation() const override
  {
    return "Leaf";
  }
};

class Composite : public Component
{
protected:
  list<Component *> children_;

public:
  void Add(Component *component) override
  {
    this->children_.push_back(component);
    component->setParent(this);
  }
  void Remove(Component *component) override
  {
    this->children_.remove(component);
    component->setParent(nullptr);
  }
  bool IsComposite() const override
  {
    return true;
  }

  string Operation() const override
  {
    string result;
    for (const Component *c : children_)
    {
      if (c == children_.back())
        result += c->Operation();
      else
        result += c->Operation();
    }
    return "Branch(" + result + ")";
  }
};

void ClientCode(Component *component)
{
  cout << "RESULT: " << component->Operation();
}

void ClientCode2(Component *component1, Component *component2)
{
  if (component1->IsComposite())
  {
    component1->Add(component2);
  }

  cout << "RESULT: " << component1->Operation();
}

int main()
{
  cout << "got a simple component:\n";
  Component *simple = new Leaf;
  ClientCode(simple);

  cout << endl
       << endl;

  Component *tree = new Composite;
  Component *branch1 = new Composite;

  Component *leaf1 = new Leaf;
  Component *leaf2 = new Leaf;
  Component *leaf3 = new Leaf;

  branch1->Add(leaf1);
  branch1->Add(leaf2);

  Component *branch2 = new Composite;
  branch2->Add(leaf3);

  tree->Add(branch1);
  tree->Add(branch2);

  cout << "now got a composite tree: \n";
  ClientCode(tree);
  cout << endl;
  cout << "dont need ot check the components class even when managing the tree:\n";
  ClientCode2(tree, simple);
  return 0;
}