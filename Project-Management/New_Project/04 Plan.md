---
title: "Step 4 — Plan"
tags:
  - project-management
  - planning
  - schedule
step: 4
pmbok:
  - Schedule Management
  - Scope Management
  - Planning
---

# 📋 Step 4 — Plan

> [!abstract] TL;DR
> Choose a direction first, then break down the work. **Plan according to your level of certainty**: detailed for the near future, rough for the far future.

Prev: [[03 De-risk]] · Next: [[05 Implement]]

---

## 1. Avoid two extremes

- ❌ Planning in great detail without enough information
- ❌ No plan at all: "just code and see"

## 2. Split the work into milestones

Example: integrating a new framework into an existing embedded system.

| Milestone | Focus | Description | Deliverable |
| --- | --- | --- | --- |
| **M1** | 🔬 Feasibility | Confirm toolchain, dependencies, and the ability to build and run on the target | Feasibility report and remaining risks |
| **M2** | 🍰 Vertical slice | Implement a minimal flow from input to output with the new framework | A working, testable end-to-end flow |
| **M3** | ⚙️ Functional implementation | Complete features, error handling, configuration, integration | Functionality that meets the requirements |
| **M4** | 🛡️ Hardening & delivery | Test edge cases, failures, concurrency, resource usage, regression; documentation | A release that passes the acceptance criteria |

**Benefit:** you don't need to know how to do M4 when you start M1. You only need enough information for the **current milestone**: its direction, its completion criteria, and its main risks.

## 3. Prefer a vertical slice

A common planning mistake: build the whole framework integration first, then the business logic, and run on the target only at the end. By then, a wrong assumption is expensive.

Instead, cut a thin **vertical slice** through all the necessary layers:

```
Hardware/Input → Adapter → New Framework → Business Logic → Output
```

It doesn't need every feature. It only has to prove the parts can work together.

> [!caution] Not every project should prototype immediately
> For **safety-critical** systems, major architecture changes, or work that needs **certification**, you may need formal analysis and approval **before** experimenting.

## 4. Don't forget dependencies

A task can be **blocked** not because you lack knowledge, but because of:

- 🔌 No hardware yet
- 🔑 No repository access
- 👥 Another team has not finished their API
- 🧰 No toolchain
- 📄 No formal requirements
- 📊 No test data

Split your work into:

| Type | Meaning |
| --- | --- |
| ✅ **Ready** | You can do it now |
| ⏳ **Dependent** | Waiting on another condition |
| 🙋 **Needs a decision** | Management or another team must decide |

That is how you track progress against reality, not just the number of tasks.

---

## 🔗 PMBOK link

| PMBOK 6th | How it matches |
| --- | --- |
| **Create WBS** | Break the scope into work packages |
| **Define Activities** | List the tasks inside each work package |
| **Sequence Activities** | Find dependencies (FS, SS, FF, SF) |
| **Estimate Activity Durations** | Give a rough estimate, refine later |
| **Develop Schedule** | Milestones and the timeline |
| **Progressive elaboration** | Details are added as information grows |
| **Rolling wave planning** | Plan the near term in detail, the far term roughly |

**Dependency types**

| Code | Name | Meaning |
| --- | --- | --- |
| **FS** | Finish-to-Start | B starts after A finishes (most common) |
| **SS** | Start-to-Start | B starts after A starts |
| **FF** | Finish-to-Finish | B finishes after A finishes |
| **SF** | Start-to-Finish | B finishes after A starts (rare) |

| PMBOK 7th | How it matches |
| --- | --- |
| **Planning** domain | Organize and coordinate the work |
| **Development Approach & Life Cycle** | A vertical slice is an incremental approach |

## 🧠 Remember

> **Plan by certainty:** clear → detail; unclear → rough (rolling wave).
> **Slice vertically**, not layer by layer.
> Split tasks into **Ready / Dependent / Needs a decision**.
