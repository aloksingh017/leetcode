#include <cmath>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

//
// SHARED CONTEXT (important for rules)
//
struct PizzaContext {
  double taxRate;
  bool hasCheeseBurst = false;
  bool hasMushroom = false;

  PizzaContext(double tax) : taxRate(tax) {}
};

//
// ABSTRACT COMPONENT
//
class Pizza {
public:
  virtual double getCost() const = 0;
  virtual PizzaContext &getContext() = 0;
  virtual ~Pizza() = default;
};

//
// BASE PIZZA
//
class BasePizza : public Pizza {
private:
  double basePrice;
  PizzaContext context;

public:
  BasePizza(int basePrice, int taxPercentage)
      : basePrice(basePrice), context(taxPercentage) {}

  double getCost() const override { return basePrice; }

  PizzaContext &getContext() override { return context; }
};

//
// DECORATOR BASE CLASS
//
class ToppingDecorator : public Pizza {
protected:
  shared_ptr<Pizza> pizza;

public:
  ToppingDecorator(shared_ptr<Pizza> pizza) : pizza(pizza) {}

  PizzaContext &getContext() override { return pizza->getContext(); }
};

//
// CHEESEBURST DECORATOR
//
class CheeseBurst : public ToppingDecorator {
private:
  int servings;

public:
  CheeseBurst(shared_ptr<Pizza> pizza, int servings)
      : ToppingDecorator(pizza), servings(servings) {

    auto &ctx = getContext();

    // Mutual exclusion rule
    if (ctx.hasMushroom) {
      throw runtime_error("Cannot add CheeseBurst after Mushroom");
    }

    // Tax uplift (only once)
    if (!ctx.hasCheeseBurst) {
      ctx.taxRate += 0.30 * ctx.taxRate;
      ctx.hasCheeseBurst = true;
    }
  }

  double getCost() const override {
    if (servings == 0)
      return 0;

    // First serving = 100, rest = 70
    return 100 + (servings - 1) * 70 + pizza->getCost();
  }
};

//
// MUSHROOM DECORATOR
//
class Mushroom : public ToppingDecorator {
private:
  int servings;

public:
  Mushroom(shared_ptr<Pizza> pizza, int servings)
      : ToppingDecorator(pizza), servings(servings) {

    auto &ctx = getContext();

    // Mutual exclusion rule
    if (ctx.hasCheeseBurst) {
      throw runtime_error("Cannot add Mushroom after CheeseBurst");
    }

    ctx.hasMushroom = true;
  }

  double getCost() const override { return pizza->getCost() + servings * 40; }
};

//
// GENERIC TOPPINGS
//
class Onion : public ToppingDecorator {
private:
  int servings;

public:
  Onion(shared_ptr<Pizza> pizza, int servings)
      : ToppingDecorator(pizza), servings(servings) {}

  double getCost() const override { return pizza->getCost() + servings * 30; }
};

class Corn : public ToppingDecorator {
private:
  int servings;

public:
  Corn(shared_ptr<Pizza> pizza, int servings)
      : ToppingDecorator(pizza), servings(servings) {}

  double getCost() const override { return pizza->getCost() + servings * 50; }
};

class Capsicum : public ToppingDecorator {
private:
  int servings;

public:
  Capsicum(shared_ptr<Pizza> pizza, int servings)
      : ToppingDecorator(pizza), servings(servings) {}

  double getCost() const override { return pizza->getCost() + servings * 50; }
};

class Pineapple : public ToppingDecorator {
private:
  int servings;

public:
  Pineapple(shared_ptr<Pizza> pizza, int servings)
      : ToppingDecorator(pizza), servings(servings) {}

  double getCost() const override { return pizza->getCost() + servings * 60; }
};

//
// MAIN SYSTEM CLASS (FACADE)
//
class PizzaPricing {
private:
  shared_ptr<Pizza> pizza;

public:
  PizzaPricing(int basePrice, int taxPercentage, string size) {
    pizza = make_shared<BasePizza>(basePrice, taxPercentage);
  }

  bool addTopping(string topping, int servings) {
    try {
      if (topping == "cheeseburst") {
        pizza = make_shared<CheeseBurst>(pizza, servings);
      } else if (topping == "mushroom") {
        pizza = make_shared<Mushroom>(pizza, servings);
      } else if (topping == "onion") {
        pizza = make_shared<Onion>(pizza, servings);
      } else if (topping == "corn") {
        pizza = make_shared<Corn>(pizza, servings);
      } else if (topping == "capsicum") {
        pizza = make_shared<Capsicum>(pizza, servings);
      } else if (topping == "pineapple") {
        pizza = make_shared<Pineapple>(pizza, servings);
      } else {
        return false;
      }
      return true;
    } catch (...) {
      return false; // rule violation → no state change
    }
  }

  int getFinalPrice() {
    double subtotal = pizza->getCost();
    double taxRate = pizza->getContext().taxRate;

    double taxAmount = (taxRate / 100.0) * subtotal;
    double finalPrice = subtotal + taxAmount;

    return (int)(finalPrice + 0.5); // round half up
  }
};

//
// TEST
//
int main() {

  // Example A
  PizzaPricing p(200, 10, "small");

  cout << p.addTopping("cheeseburst", 1) << endl;
  cout << p.addTopping("onion", 2) << endl;

  cout << "Final Price: " << p.getFinalPrice() << endl; // 407

  // Example B
  PizzaPricing q(350, 8, "medium");

  cout << q.addTopping("mushroom", 2) << endl;
  cout << q.addTopping("cheeseburst", 1) << endl; // false

  cout << "Final Price: " << q.getFinalPrice() << endl; // 464

  return 0;
}