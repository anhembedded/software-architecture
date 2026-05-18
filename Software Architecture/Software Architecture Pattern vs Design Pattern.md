
> [!abstract]  
> Many developers confuse these two concepts.  
> They are related but exist at **two completely different levels of abstraction**.

---

# 1️⃣ 🎯 What is a Design Pattern?

> [!info]  
> Reusable solution to a design problem at the **class/object** level.

## 📚 Origin

- _Design Patterns: Elements of Reusable Object-Oriented Software_
- Erich Gamma and the “Gang of Four”
## 🔍 Key Characteristics

- Solves problems at the code level
- Usually lives within a single module / service
- Focuses on:
    - Object creation
    - Object interaction
    - Decoupling classes
## 🧩 Familiar Design Patterns

- [[Singleton]]
- [[Factory]]
- [[Observer]]
- [[Strategy]]
- [[Decorator]]
- [[Adapter]]
- [[Repository]]
- [[Command]]

## 💻 Simple Example

```cpp
class PaymentStrategy {
public:
    virtual void pay() = 0;
};

class CreditCardPayment : public PaymentStrategy {};
class CryptoPayment : public PaymentStrategy {};
```

→ This is the **Strategy Pattern**.

> [!tip]  
> It doesn’t decide how the system runs.  
> It only decides how objects interact.

---

# 2️⃣ 🏛️ What is a Software Architecture Pattern?

> [!important]  
> A high-level system organization template (**system-level**).

## 🔧 It Decides:

- How to split the system
- How services communicate
- How to deploy
- How to scale
- How to handle data

## 🧱 Examples of Architecture Patterns

- Layered Architecture
- Clean Architecture
- Hexagonal Architecture
- Microservices
- Event-Driven Architecture
- CQRS
- Monolith

> [!example]  
> Example: A large system might use Microservices + Event Streaming.

---

# 3️⃣ ⚖️ Direct Comparison

|Criteria|Design Pattern|Architecture Pattern|
|---|---|---|
|Scope|Class / Object|Entire system|
|Decided by|Developer|Architect|
|Impact|Local|Global|
|Change cost|Easy|Very expensive|
|Examples|Strategy, Factory|Microservices, Layered|

---

# 4️⃣ 🧠 Real-World Example (Trading System)

## 🏗️ Architecture Layer

Architect decides:

- Monolith or Microservices?
- Event-driven or synchronous?
- Use CQRS or not?

Suppose they choose:

> **Microservices + Event-Driven**

→ This is the **Architecture Pattern**.

---

## 🧩 Inside Each Service

Developers implement:

- Repository pattern
- Factory pattern
- Strategy pattern
- Observer pattern

→ These are **Design Patterns**.

---

# 5️⃣ 🔗 The Relationship Between Them

> [!quote]  
> Architecture Pattern = City map  
> Design Pattern = How to construct each building

## 🔬 Technical Perspective

- Architecture patterns create **constraints**.
- Design patterns operate **within those constraints**.

### Examples:

- Microservices → must consider eventual consistency
- Event-driven → heavy use of Observer pattern
- Clean Architecture → often uses Dependency Injection pattern

---

# 6️⃣ ⚙️ Embedded Perspective

If you work in embedded systems:

## 🏛️ Architecture Pattern is like:

- Choosing RTOS or bare-metal
- Choosing event loop or polling
- Choosing modular firmware or single file

## 🧩 Design Pattern is like:

- State machine
- Strategy for drivers
- HAL abstraction
- Interface classes

---

# 7️⃣ 🚨 An Important Truth

Junior developers often:  
→ Focus on design patterns

Senior / Architect:  
→ Focus on architecture patterns

> [!warning]  
> Without good design patterns,  
> even a beautiful architecture can turn into a “big ball of mud”.

---

# 8️⃣ 🎯 Summary

## Design Pattern

- Solves **micro-level complexity**

## Architecture Pattern

- Solves **macro-level complexity**

> [!success]  
> They don’t replace each other.  
> They complement each other to manage software complexity.

---

# 🏷️ Tags

#software-architecture  
#design-pattern  
#system-design  
#clean-architecture  
#engineering-thinking