# Tutorial: Business Rules – Entities, Use Cases, and the Heart of the System

Business rules are the reason a software system exists. They are the code that makes or saves money for the business—the *family jewels*. In this tutorial we’ll understand the two kinds of business rules, how to model them in Python, and how to keep them pure and independent of all infrastructure details.

All examples will use a simple banking domain: loans.

---

## 1. Critical Business Rules and [[Entities]]

**Critical Business Rules** are rules or procedures that would make or save the business money even if there were no computer system. They could be executed manually.

**Critical Business Data** is the data that those rules need—data that would exist even without automation.

When you bind these rules and data together, you get an **[[Entity]]**.

> An Entity is an object that embodies a small set of critical business rules operating on critical business data. It is *pure business and nothing else*.

### Example: A Loan Entity

Consider a bank loan. The critical data includes:
- Principal (loan balance)
- Interest rate
- Payment schedule

The critical business rules include:
- Calculating interest
- Applying a payment
- Determining the remaining balance

The following Python class is a Loan Entity. It knows nothing about databases, web frameworks, or user interfaces. It is independent and reusable in any system.

```python
# entities/loan.py
from datetime import date
from decimal import Decimal
from typing import List

class Payment:
    def __init__(self, date: date, amount: Decimal):
        self.date = date
        self.amount = amount

class Loan:
    """
    Pure Entity: embodies critical business rules and critical business data.
    No dependencies on I/O, frameworks, or databases.
    """
    def __init__(self, principal: Decimal, annual_rate: Decimal, start_date: date):
        self.principal = principal
        self.annual_rate = annual_rate  # as a decimal, e.g., 0.05 for 5%
        self.start_date = start_date
        self._payments: List[Payment] = []

    def apply_payment(self, payment: Payment) -> None:
        """Critical business rule: apply a payment, reduce principal after interest."""
        if payment.amount <= 0:
            raise ValueError("Payment amount must be positive")
        # Simple rule: payment covers interest first, then reduces principal
        interest_due = self._calculate_interest(payment.date)
        effective_principal_payment = payment.amount - interest_due
        if effective_principal_payment < 0:
            effective_principal_payment = Decimal('0')
        self.principal = max(Decimal('0'), self.principal - effective_principal_payment)
        self._payments.append(payment)

    def get_remaining_balance(self) -> Decimal:
        return self.principal

    def _calculate_interest(self, as_of: date) -> Decimal:
        # This is a simplified critical rule; in reality it might be much more complex.
        days_elapsed = (as_of - self.start_date).days
        if days_elapsed <= 0:
            return Decimal('0')
        daily_rate = self.annual_rate / 365
        return (self.principal * Decimal(days_elapsed) * daily_rate).quantize(Decimal('0.01'))
```

This entity is the heart of the loan business. It can be tested completely in isolation, without a database or web server.

```python
# test_loan.py (illustrative)
from decimal import Decimal
from datetime import date
from entities.loan import Loan, Payment

def test_apply_payment():
    loan = Loan(Decimal('10000'), Decimal('0.05'), date(2024, 1, 1))
    loan.apply_payment(Payment(date(2024, 1, 31), Decimal('1100')))
    assert loan.get_remaining_balance() < 10000
```

The entity is **unsullied** by any external concerns.

---

## 2. Application‑Specific [[Business Rules]]: [[Screaming Architecture]]

Not all business rules are critical in the manual sense. Some rules define how an automated system operates—they make or save money only through the automation. These are **application‑specific [[business rules]]** and are captured in **[[Screaming Architecture]]**.

A Use Case describes:
- The input provided by the user
- The output returned to the user
- The processing steps that orchestrate **Entities** and enforce application‑specific constraints

**Example Use Case:** *Evaluate Loan Application*

The bank has a rule that before a loan payment estimate can be shown, the officer must have entered valid contact information and verified that the applicant’s credit score is at least 500. This is an application‑specific rule—it wouldn’t exist if the process were completely manual.

The use case does **not** describe the user interface. It doesn’t say whether it’s a web page, a CLI, or an API. It simply defines the application‑specific policy: what data is required and how the entities are invoked.

### Designing the Use Case Object

A use case is an object with:
- One or more functions that implement the application‑specific rules.
- Simple **request** and **response** data structures (no framework dependencies).
- References to the Entity objects it needs to orchestrate.

**Important:** Entities know nothing about use cases. Use cases depend on Entities (lower‑level depends on higher‑level). Entities are higher‑level because they are general and farther from I/O; use cases are specific to one application and closer to the system’s inputs/outputs.

---

## 3. Request and Response Models

The use case accepts a plain request data object and returns a plain response data object. These models are **not** derived from `HttpRequest` or any framework. They have no dependencies. They are simple Python classes (or dataclasses). They should **not** contain references to Entity objects—even if they share similar data—because their reasons for change are different (SRP, CCP).

### Loan Evaluation Example

We need a use case that evaluates an application, checks credit score, and returns a decision along with an estimated payment if eligible.

First, we define the request and response models:

```python
# use_cases/evaluate_loan.py
from dataclasses import dataclass
from decimal import Decimal
from typing import Optional

@dataclass(frozen=True)
class EvaluateLoanRequest:
    applicant_name: str
    applicant_email: str
    credit_score: int
    requested_amount: Decimal

@dataclass(frozen=True)
class EvaluateLoanResponse:
    approved: bool
    reason: Optional[str] = None
    estimated_monthly_payment: Optional[Decimal] = None
```

These models have zero dependencies. They are plain data.

---

## 4. The [[Use Case]] Implementation

Now we write the use case. It depends on:
- The **Loan Entity** (for computing payment estimates).
- An abstraction for checking credit score eligibility (the actual credit bureau call is a detail that will be plugged in).

Since the use case should not know about the concrete credit bureau service, we define an interface (abstract class) for it in the use case layer. This keeps the dependency inversion intact.

```python
# use_cases/interfaces.py
from abc import ABC, abstractmethod

class CreditScoreService(ABC):
    @abstractmethod
    def is_credit_score_acceptable(self, score: int) -> bool:
        pass
```

Now the use case class:

```python
# use_cases/evaluate_loan_use_case.py
from decimal import Decimal
from entities.loan import Loan
from datetime import date
from use_cases.evaluate_loan import EvaluateLoanRequest, EvaluateLoanResponse
from use_cases.interfaces import CreditScoreService

class EvaluateLoanUseCase:
    """
    Application‑specific business rule.
    Orchestrates the Loan entity and enforces rules like credit score cutoff.
    Knows nothing about the UI or database.
    """
    def __init__(self, credit_service: CreditScoreService):
        self.credit_service = credit_service

    def evaluate(self, request: EvaluateLoanRequest) -> EvaluateLoanResponse:
        # 1. Validate contact information (application‑specific rule)
        if not request.applicant_name or not request.applicant_email:
            return EvaluateLoanResponse(approved=False, reason="Contact info incomplete")

        # 2. Check credit score threshold (application‑specific rule)
        if not self.credit_service.is_credit_score_acceptable(request.credit_score):
            return EvaluateLoanResponse(approved=False, reason="Credit score below 500")

        # 3. Use the pure Entity to calculate a payment estimate
        #    (the critical business rule of how interest accrues)
        loan = Loan(
            principal=request.requested_amount,
            annual_rate=Decimal('0.06'),  # fixed bank rate
            start_date=date.today()
        )
        # Dummy: simulate a payment after 30 days to get an estimate
        estimated_interest = loan._calculate_interest(date.today().replace(day=1) + date.resolution * 30)
        monthly_payment = (request.requested_amount / 36) + estimated_interest  # simplified

        return EvaluateLoanResponse(
            approved=True,
            estimated_monthly_payment=monthly_payment.quantize(Decimal('0.01'))
        )
```

**Dependency rule check:**
- `EvaluateLoanUseCase` imports `Loan` (Entity) → dependency points **upward**.
- `Loan` does not import `EvaluateLoanUseCase` → high‑level knows nothing about low‑level.
- `EvaluateLoanUseCase` depends on `CreditScoreService` (interface) that it defines → the abstraction is owned by the use case, and the implementation will depend on that interface (dependency inversion).

---

## 5. Plugging in the Details

We can now implement the real credit score service as a plugin. This is an adapter that **implements** the `CreditScoreService` interface from the use case.

```python
# adapters/credit_bureau.py
from use_cases.interfaces import CreditScoreService

class RealCreditScoreService(CreditScoreService):
    def is_credit_score_acceptable(self, score: int) -> bool:
        # In reality, call an external credit bureau API
        return score >= 500
```

The main assembly wires everything together:

```python
# main.py
from use_cases.evaluate_loan_use_case import EvaluateLoanUseCase
from adapters.credit_bureau import RealCreditScoreService
from use_cases.evaluate_loan import EvaluateLoanRequest
from decimal import Decimal

credit_service = RealCreditScoreService()
use_case = EvaluateLoanUseCase(credit_service)

request = EvaluateLoanRequest(
    applicant_name="Jane Doe",
    applicant_email="jane@example.com",
    credit_score=520,
    requested_amount=Decimal('15000')
)
response = use_case.evaluate(request)
print(response)
```

The use case knows nothing about `RealCreditScoreService` or how the credit score is checked. It only knows about the interface. This keeps the application‑specific rules clean and testable.

---

## 6. Visualizing the Dependency Direction

The following Mermaid diagram shows the relationship between Entities, Use Cases, and their plugins. Notice how all dependencies point from the use case (and its adapters) toward the Entity—the highest‑level component.

```mermaid
graph TD
    subgraph Entity[Entity (Highest Level)]
        Loan
    end
    subgraph UseCase[Use Case Layer]
        EvaluateLoanUseCase
        CreditScoreService["CreditScoreService (interface)"]
        Request["EvaluateLoanRequest"]
        Response["EvaluateLoanResponse"]
    end
    subgraph Adapters[Adapters / Plugins]
        RealCreditScoreService
    end
    Loan -->|no dependencies| None
    EvaluateLoanUseCase -->|uses| Loan
    EvaluateLoanUseCase -->|uses| CreditScoreService
    EvaluateLoanUseCase -->|uses| Request
    EvaluateLoanUseCase -->|uses| Response
    RealCreditScoreService -.->|implements| CreditScoreService
    Request -->|zero dependencies| None
    Response -->|zero dependencies| None

    style Entity fill:#e6ffe6,stroke:#009900
    style UseCase fill:#e0f2fe,stroke:#0284c7
    style Adapters fill:#fef3c7,stroke:#b45309
```

The arrow from `RealCreditScoreService` points **up** to the interface in the use case layer. The use case depends on the `Loan` Entity (arrow upward). The `Loan` Entity has no outgoing arrows. This is a classic dependency inversion structure: high‑level policy is independent.

---

## 7. Why Entities Are Higher Level Than Use Cases

The chapter explains that level is the distance from I/O. Entities are *general*—they can be used in many applications. They are far from the specifics of any one system’s inputs and outputs. Use cases are *specific* to one application; they are closer to the system’s boundary because they orchestrate the interaction between the user and the entities. Therefore:

- **Entities** = higher‑level (more abstract, more stable)
- **Use Cases** = lower‑level (more concrete to the application, closer to I/O)

This is why use cases depend on entities, never the reverse.

---

## 8. The Purity of Business Rules

The core principle of the chapter is that business rules must remain **pristine**. They should be:

- Free from framework dependencies (no `Flask`, `Django`, `SQLAlchemy`).
- Free from UI concerns (no HTML, no console rendering).
- Free from database concerns (no SQL, no ORM imports).

Everything else—the web, the database, the credit bureau—are **plugins**. They are interchangeable details that serve the business rules.

### Testing Pure Business Rules

Because entities and use cases depend only on abstractions, you can test them with simple stubs.

```python
# test_use_case.py
from use_cases.evaluate_loan_use_case import EvaluateLoanUseCase
from use_cases.evaluate_loan import EvaluateLoanRequest
from decimal import Decimal

class MockCreditService:
    def is_credit_score_acceptable(self, score: int) -> bool:
        return True

def test_approval():
    use_case = EvaluateLoanUseCase(MockCreditService())
    response = use_case.evaluate(EvaluateLoanRequest("John", "john@test.com", 510, Decimal('5000')))
    assert response.approved == True
    assert response.estimated_monthly_payment is not None
```

No database, no web server, no external API. The tests are fast and reliable.

---

## 9. Conclusion

Business rules are the heart of any software system. They come in two flavours:

| Type | Examples | Characteristics |
|------|----------|-----------------|
| **Critical Business Rules (Entities)** | Loan interest calculation, account balance rules | Independent of any specific automation; reusable across applications; highest‑level. |
| **Application‑Specific Business Rules (Use Cases)** | Loan application evaluation, order processing workflow | Depend on Entities; orchestrate the dance; closer to I/O; lower‑level. |

The architecture must keep these rules clean by:

- Binding critical rules and critical data into **Entities** that know nothing of the outside world.
- Creating **Use Case** objects that accept simple **request/response models** and depend on abstractions for external services.
- Ensuring that dependencies always point **upward**—from use cases to entities, and from plugins to use case interfaces.

When you follow these rules, the precious business logic becomes the most independent and reusable part of your system. It remains the family jewels—protected from the constant churn of frameworks, databases, and user interfaces.