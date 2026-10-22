---
title: "Step 1 — Clarify"
tags:
  - project-management
  - requirements
  - scope
step: 1
pmbok:
  - Initiating
  - Scope Management
  - Stakeholder Management
---

# 🔍 Step 1 — Clarify

> [!abstract] TL;DR
> Don't start by asking *how to build it*. First ask **what problem we are solving** and **what success looks like**.

Prev: [[Thinking New project]] · Next: [[02 Discover]]

---

## 1. The reflex to avoid

When a manager hands over a project, many engineers ask:

- Which framework should we use?
- Is there documentation?
- Is there sample code?
- Where do I start coding?

These are reasonable, but they are not the most important questions.

## 2. The Five Questions

| Question | What you need to find out |
| --- | --- |
| ❓ **Why?** | Why does this project exist? What is the current problem? |
| 🎁 **What?** | What is the concrete deliverable? |
| 🔲 **Scope?** | What is your responsibility, and what is not? |
| 🚧 **Constraints?** | Deadline, hardware, OS, RAM, CPU, compatibility, coding standards? |
| 🏁 **Done?** | What proves the project is complete? |

**Example:** the manager asks for a service on embedded Linux that receives data from a peripheral device. Don't write the requirement as *"Implement communication service."* Ask:

- [ ] What kind of data does the service receive?
- [ ] Is the link UART, SPI, TCP, or an existing API?
- [ ] Are there latency or throughput requirements?
- [ ] What happens when the device disconnects?
- [ ] May the service restart? Who manages its lifecycle?
- [ ] Do we test on real hardware, or must we support simulation?
- [ ] Must it stay compatible with the existing system's API?

> [!tip] You don't need every answer today
> The goal is to separate **what is clear**, **what is unclear**, and **what could make the project fail if misunderstood**.

## 3. Requirement vs. Solution

Suppose your manager says:

> *"We need to introduce a new framework to handle asynchronous communication."*

That is a **solution request**, not necessarily the **root problem**. Find out:

- What problem does the current system have?
- Is latency too high?
- Are there too many threads?
- Is lifecycle management hard?
- Or is the old framework no longer supported?

**Why it matters:** if you assume the stated solution is optimal, you may spend weeks integrating a complex framework when a simple event-driven mechanism would have solved the real problem.

In a company, the framework may already be an **approved architecture decision**. You don't have to push back, but you still need the goal, so you can implement correctly and spot risks.

> [!quote] Rule
> A **requirement** says what the system must achieve. A **solution** is one way to achieve it.

## 4. Output of this step

Write a short summary before moving on:

| Item | Meaning |
| --- | --- |
| 🎯 **Objective** | The goal |
| 🔲 **Scope** | The boundaries (in / out) |
| 🚧 **Constraints** | The limits |
| ✅ **Acceptance criteria** | The conditions for sign-off |
| ❓ **Open questions** | What is still unclear |
| 💭 **Assumptions** | What you temporarily take as true |

---

## 🔗 PMBOK link

| PMBOK 6th | How it matches |
| --- | --- |
| **Develop Project Charter** (Initiating) | Objective, high-level scope, success criteria |
| **Identify Stakeholders** (Initiating) | Who can answer "why" and "done"? |
| **Collect Requirements** (Planning) | Separate needs from proposed solutions |
| **Define Scope** (Planning) | The *scope statement*: in-scope, out-of-scope, assumptions, constraints |
| **Knowledge areas** | Scope, Stakeholder |

| PMBOK 7th | How it matches |
| --- | --- |
| **Stakeholder** domain | Ask the right people early |
| **Value** principle | Focus on the outcome, not the tool |

> [!info] Vocabulary
> *Acceptance criteria*, *scope statement*, *requirements*, *stakeholder*, *assumption*, *constraint*. See [[Glossary]] and [[PMBOK Mapping]].

## 🧠 Remember

> **Why → What → Scope → Constraints → Done.**
> A requirement is the *destination*; a solution is one *route*.
