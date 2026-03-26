# Strategy Pattern

## Definition

> **Strategy Pattern** defines a family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

---

## The Problem (Why Do We Need This?)

### Scenario: SimUDuck Application

Imagine you're building a duck simulation game with different types of ducks:

```
Duck (superclass)
├── MallardDuck
├── RedheadDuck
├── RubberDuck
└── DecoyDuck
```

**Initial approach using inheritance:**

```
Duck
├── quack()      → All ducks quack
├── swim()       → All ducks swim
├── display()    → Abstract - each duck looks different
└── fly()        → Added later... but wait!
```

### The Problem with Inheritance

When we add `fly()` to the Duck superclass:
- MallardDuck flies - correct!
- RedheadDuck flies - correct!
- RubberDuck flies - WRONG! Rubber ducks don't fly!
- DecoyDuck flies - WRONG! Wooden decoys don't fly!

**Attempted Fix #1: Override in subclasses**
```
RubberDuck.fly() → do nothing
DecoyDuck.fly() → do nothing
```

**Problem:** Every new duck type that can't fly needs to override. What about ducks that can't quack? (DecoyDuck). This becomes a maintenance nightmare!

**Attempted Fix #2: Use Interfaces**
```
Flyable interface → fly()
Quackable interface → quack()
```

**Problem:** No code reuse! If 50 duck types fly the same way, you're duplicating code in 50 classes. Change the flying behavior? Update 50 classes!

---

## Design Principles Learned

### Principle #1: Identify what varies and separate it from what stays the same

> **Take the parts that vary and encapsulate them, so that later you can alter or extend the parts that vary without affecting those that don't.**

What varies in our Duck app?
- `fly()` behavior
- `quack()` behavior

What stays the same?
- `swim()` - all ducks swim
- `display()` - structure is same, implementation varies

### Principle #2: Program to an interface, not an implementation

> **Program to a supertype (interface/abstract class) so that the actual runtime object isn't locked into the code.**

Bad:
```java
Dog d = new Dog();
d.bark();
```

Good:
```java
Animal animal = new Dog();
animal.makeSound();
```

Even Better (runtime assignment):
```java
Animal animal = getAnimal(); // Could be Dog, Cat, etc.
animal.makeSound();
```

### Principle #3: Favor composition over inheritance

> **HAS-A can be better than IS-A**

Instead of inheriting behavior, ducks will **have** behavior objects.

```
Duck HAS-A FlyBehavior
Duck HAS-A QuackBehavior
```

---

## The Solution: Strategy Pattern

### Step 1: Create Behavior Interfaces

```
┌─────────────────────┐
│   <<interface>>     │
│    FlyBehavior      │
├─────────────────────┤
│ + fly()             │
└─────────────────────┘
         △
         │ implements
    ┌────┴────┬──────────────┐
    │         │              │
┌───┴───┐ ┌───┴───┐  ┌───────┴───────┐
│FlyWith│ │FlyNo  │  │  RocketPowered │
│Wings  │ │Way    │  │     Fly        │
└───────┘ └───────┘  └────────────────┘
```

```
┌─────────────────────┐
│   <<interface>>     │
│   QuackBehavior     │
├─────────────────────┤
│ + quack()           │
└─────────────────────┘
         △
         │ implements
    ┌────┴────┬────────────┐
    │         │            │
┌───┴───┐ ┌───┴───┐  ┌─────┴─────┐
│ Quack │ │ Squeak│  │MuteQuack  │
│       │ │       │  │(no sound) │
└───────┘ └───────┘  └───────────┘
```

### Step 2: Compose Duck with Behaviors

```
┌─────────────────────────────────┐
│            Duck                 │
├─────────────────────────────────┤
│ - flyBehavior: FlyBehavior      │
│ - quackBehavior: QuackBehavior  │
├─────────────────────────────────┤
│ + performFly()                  │  → delegates to flyBehavior.fly()
│ + performQuack()                │  → delegates to quackBehavior.quack()
│ + swim()                        │
│ + display()                     │
│ + setFlyBehavior(fb)            │  → change behavior at runtime!
│ + setQuackBehavior(qb)          │  → change behavior at runtime!
└─────────────────────────────────┘
```

### Step 3: Duck Types Set Their Behaviors

```
MallardDuck:
  - flyBehavior = new FlyWithWings()
  - quackBehavior = new Quack()

RubberDuck:
  - flyBehavior = new FlyNoWay()
  - quackBehavior = new Squeak()

DecoyDuck:
  - flyBehavior = new FlyNoWay()
  - quackBehavior = new MuteQuack()
```

---

## Class Diagram

```
                        ┌─────────────────┐
                        │  <<interface>>  │
                        │  FlyBehavior    │
                        ├─────────────────┤
                        │ + fly()         │
                        └────────┬────────┘
                                 │
          ┌──────────────────────┼──────────────────────┐
          │                      │                      │
   ┌──────┴──────┐      ┌────────┴────────┐     ┌───────┴────────┐
   │ FlyWithWings│      │    FlyNoWay     │     │RocketPoweredFly│
   ├─────────────┤      ├─────────────────┤     ├────────────────┤
   │ + fly()     │      │ + fly()         │     │ + fly()        │
   │ "I'm flying"│      │ "Can't fly"     │     │ "Rocket fly!"  │
   └─────────────┘      └─────────────────┘     └────────────────┘

┌─────────────────────────────────────────────────────────────────────┐
│                              Duck                                   │
├─────────────────────────────────────────────────────────────────────┤
│ - flyBehavior: FlyBehavior                                          │
│ - quackBehavior: QuackBehavior                                      │
├─────────────────────────────────────────────────────────────────────┤
│ + performFly(): void           // flyBehavior.fly()                 │
│ + performQuack(): void         // quackBehavior.quack()             │
│ + setFlyBehavior(FlyBehavior): void                                 │
│ + setQuackBehavior(QuackBehavior): void                             │
│ + swim(): void                                                      │
│ + display(): void              // abstract                          │
└─────────────────────────────────────────────────────────────────────┘
        △
        │ extends
        │
   ┌────┴────┬─────────────┬──────────────┐
   │         │             │              │
┌──┴───┐ ┌───┴────┐ ┌──────┴─────┐ ┌──────┴─────┐
│Mallard│ │Redhead │ │ RubberDuck │ │ DecoyDuck  │
│ Duck  │ │ Duck   │ │            │ │            │
└───────┘ └────────┘ └────────────┘ └────────────┘
```

---

## Key Benefits

| Benefit | Explanation |
|---------|-------------|
| **Flexibility** | Change behavior at runtime with setters |
| **Reusability** | Share behaviors across different classes |
| **Testability** | Easy to mock/stub behaviors for testing |
| **Open/Closed** | Add new behaviors without modifying existing code |
| **Single Responsibility** | Each behavior class has one job |

---

## When to Use Strategy Pattern

✅ **Use when:**
- You have multiple algorithms for a specific task
- You need to switch between algorithms at runtime
- You have conditional statements selecting different behaviors
- Multiple classes differ only in their behavior

❌ **Don't use when:**
- Algorithms rarely change
- Only a few algorithms exist and they're simple
- Clients don't need to know about different strategies

---

## Real-World Examples

| Domain | Context | Strategies |
|--------|---------|------------|
| **Payments** | E-commerce checkout | CreditCard, PayPal, UPI, Crypto |
| **Sorting** | Data processing | QuickSort, MergeSort, HeapSort |
| **Compression** | File handling | ZIP, GZIP, BZIP2, LZ4 |
| **Navigation** | Maps app | Fastest, Shortest, NoTolls, Scenic |
| **Authentication** | Login system | Password, OAuth, SAML, Biometric |
| **Validation** | Form validation | Email, Phone, Regex, Custom |
| **Pricing** | E-commerce | Regular, Holiday, Membership, Bulk |
| **Logging** | Application | Console, File, Database, Cloud |

---

## Strategy vs Other Patterns

| Pattern | Purpose | Key Difference |
|---------|---------|----------------|
| **Strategy** | Swap entire algorithm | Client chooses strategy |
| **State** | Change behavior based on state | State transitions internally |
| **Template Method** | Define algorithm skeleton | Uses inheritance, not composition |
| **Decorator** | Add responsibilities | Wraps objects, doesn't replace |

---

## Summary

```
┌────────────────────────────────────────────────────────────────┐
│                     STRATEGY PATTERN                           │
├────────────────────────────────────────────────────────────────┤
│  "Encapsulate what varies"                                     │
│                                                                │
│  • Define a family of algorithms (strategies)                  │
│  • Encapsulate each in its own class                          │
│  • Make them interchangeable via a common interface           │
│  • Client can switch algorithms at runtime                    │
│                                                                │
│  COMPOSITION > INHERITANCE                                     │
│  HAS-A > IS-A                                                  │
└────────────────────────────────────────────────────────────────┘
```

---

## Practice Exercises

1. **[Beginner]** Implement the Duck example from the book
2. **[Intermediate]** Build a payment system with multiple payment strategies
3. **[Intermediate]** Create a navigation app with route calculation strategies
4. **[Advanced]** Build a compression tool that can switch compression algorithms

See the example implementations in this folder:
- `duck.go` - Book example in Go
- `payments.py` - Payment system in Python
- `navigation.js` - Navigation app in JavaScript
- `compression.go` - Compression tool in Go
