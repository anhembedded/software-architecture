When you see the term **API of a repository**, it refers to the **set of methods (the interface)** that the repository exposes to the rest of the application for interacting with data.  

---
### 🔑 Typical Repository API
A repository usually provides **CRUD-like operations** (Create, Read, Update, Delete), but expressed in terms of **domain objects**, not raw database queries.

Common methods you’ll see:

- **Find / Get**
  - `findById(id)` → returns a single entity.  
  - `findAll()` → returns all entities.  
  - `findByCriteria(criteria)` → returns entities matching some condition.  
- **Add / Save**
  - `add(entity)` or `save(entity)` → persists a new entity.  
- **Update**
  - `update(entity)` → modifies an existing entity.  
- **Remove / Delete**
  - `remove(entity)` or `deleteById(id)` → deletes an entity.  

---
### 📌 Example in code (pseudo-Java)

```java
public interface CustomerRepository {
    Customer findById(Long id);
    List<Customer> findAll();
    void save(Customer customer);
    void update(Customer customer);
    void deleteById(Long id);
}
```

The **API** here is the set of methods (`findById`, `findAll`, `save`, `update`, `deleteById`) that other parts of the system can call.

---
### ✅ Key Idea
- The repository API is **domain-oriented**, not database-oriented.  
- Business logic calls `customerRepository.findById(1)` instead of writing SQL queries.  
- This keeps the **domain layer clean** and independent of persistence details.

---

👉 In short: the **API of a repository** is the **contract (interface)** that defines how the rest of the system can interact with stored domain objects, typically through methods like `find`, `save`, `update`, and `delete`.  

Would you like me to also show how repository APIs differ when using **ORM frameworks (like JPA/Hibernate)** versus **manual SQL implementations**? That contrast makes the concept even clearer.