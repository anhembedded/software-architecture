---
title: "Step 6 — Validate"
tags:
  - project-management
  - quality
  - acceptance
step: 6
pmbok:
  - Monitoring and Controlling
  - Closing
  - Quality Management
  - Scope Management
---

# ✅ Step 6 — Validate

> [!abstract] TL;DR
> A project is not done because it builds or because you demoed it once. **Prove the result against the acceptance criteria** agreed at the start.

Prev: [[05 Implement]] · Next: [[07 Approaches]]

---

## 1. What to check

Depending on the project, validation may include:

- [ ] Functional correctness
- [ ] Error handling and recovery
- [ ] Boundary conditions
- [ ] Concurrency and race conditions
- [ ] Performance, latency and resource usage
- [ ] Integration and regression tests
- [ ] A clean rebuild from the standard environment
- [ ] Documentation and handover readiness

> [!example] Embedded example
> A communication service that works when the device connects normally does **not** prove it works when the connection drops, when malformed data arrives, or when shutdown happens midway.

## 2. Link every major risk to a test

| Biggest risk | Ordinary functional test enough? | Better check |
| --- | --- | --- |
| Memory leak | ❌ | Long-run test with memory monitoring |
| Latency | ❌ (only proves data arrived) | Timing measurement under load |
| Connection loss | ❌ | Fault injection: unplug, timeout |
| Malformed data | ❌ | Negative tests, fuzzing |

> [!important]
> Every major risk from [[03 De-risk]] needs a matching way to verify it.

---

## 🔗 PMBOK link

| PMBOK 6th | How it matches |
| --- | --- |
| **Control Quality** (M&C) | *Verify*: is the deliverable **correct** (tests, inspections)? |
| **Validate Scope** (M&C) | *Accept*: does the customer **formally accept** the deliverable? |
| **Monitor and Control Project Work** | Compare actual progress with the plan |
| **Perform Integrated Change Control** | Handle changes found during testing in a controlled way |
| **Close Project or Phase** (Closing) | Handover, final report, lessons learned |
| **Knowledge areas** | Quality, Scope, Integration |

> [!tip] Verify vs. validate
> - **Control Quality** = "Did we build it **right**?" (meets specs)
> - **Validate Scope** = "Did we build the **right thing**?" (customer accepts)

| PMBOK 7th | How it matches |
| --- | --- |
| **Delivery** domain | Deliver scope and quality to create the expected value |
| **Measurement** domain | Use evidence and metrics, not impressions |

## 🧠 Remember

> **Right** (verify) **vs. right thing** (validate).
> Every major risk gets a **matching test**.
> Evidence, not activity.
