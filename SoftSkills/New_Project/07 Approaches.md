---
title: "Approaches and When to Use Them"
tags:
  - project-management
  - life-cycle
  - approach
step: 7
pmbok:
  - Development Approach and Life Cycle
  - Tailoring
---

# 🧰 Approaches and When to Use Them

> [!abstract] TL;DR
> No single process fits every project. Choose the approach that matches the **nature of the problem**, and combine them.

Prev: [[06 Validate]] · Next: [[08 Pitfalls]]

---

## The four approaches

| Approach | Idea | Use when | Strength |
| --- | --- | --- | --- |
| 🔽 **Top-down** | Start from goals, architecture, modules, data flow, then implementation | New project, large codebase, many modules, unclear requirements | You see the context and avoid optimizing the wrong component |
| 🔼 **Bottom-up** | Start from one API, library, driver or component, then expand | Unfamiliar framework, tricky API, driver, issue you can reproduce in a small example | Behavior is easy to verify and causes are easy to isolate |
| 🧪 **Spike** | Run a small, controlled experiment on a key assumption | Missing information, new technology, uncertain compatibility or performance | You gather evidence before a big investment |
| 🔁 **Incremental / iterative** | Split into verifiable pieces, get feedback, adjust | Requirements may change, many components, continuous integration | Problems appear early, late fixes cost less |

> [!success] Combine all four
> **Top-down** to set direction → **Bottom-up** to understand components → **Spike** to reduce risk → **Incremental** to deliver.
> This works well for most projects with new technology.

---

## 🔗 PMBOK link

PMBOK 7th groups delivery approaches under the **Development Approach and Life Cycle** domain:

| Life cycle type | Meaning | Closest to |
| --- | --- | --- |
| **Predictive** | Plan everything up front, deliver at the end | Fixed scope, safety-critical, certification |
| **Iterative** | Repeat cycles to refine the result | Spike → learn → repeat |
| **Incremental** | Deliver working parts step by step | Vertical slices, milestones M1–M4 |
| **Agile** | Iterative + incremental, with frequent feedback | Short sprints, changing requirements |
| **Hybrid** | A mix, e.g. predictive for hardware, agile for software | Embedded systems with firmware and hardware |

| Principle | How it matches |
| --- | --- |
| **Tailoring** | Fit the approach to the context. Don't apply the full process to every task. |
| **Adaptability & resiliency** | Be ready to change direction when a spike fails |

> [!note] Terminology
> *Top-down* and *bottom-up* are also used in PMBOK for **estimating** (top-down vs. bottom-up estimating), but here they mean **ways of learning a system**.

## 🧠 Remember

> **Top-down** = *map*. **Bottom-up** = *microscope*. **Spike** = *experiment*. **Incremental** = *delivery*.
> Choose by problem, then **tailor**.
