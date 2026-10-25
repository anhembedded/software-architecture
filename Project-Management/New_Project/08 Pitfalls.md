---
title: "Pitfalls — Mistakes to Avoid"
tags:
  - project-management
  - pitfalls
  - lessons-learned
step: 8
pmbok:
  - Risk Management
  - Communications Management
  - Schedule Management
---

# 🕳️ Pitfalls — Mistakes to Avoid

> [!important]
> Many failures on a new project don't come from a lack of intelligence. They come from **spending time and attention in the wrong place**.

Prev: [[07 Approaches]] · Next: [[09 Communication]]

---

## Overview

| # | Pitfall | Fix in one line | PMBOK area |
| --- | --- | --- | --- |
| 1 | Learning the technology before the problem | Write goal and questions first | Scope, Requirements |
| 2 | Reading code in file order | Trace one end-to-end flow | Integration |
| 3 | Choosing a solution before constraints | List constraints, verify high-impact assumptions | Scope, Risk |
| 4 | Prototyping for too long | One question, a timebox, a stop rule | Schedule, Scope (scope creep) |
| 5 | Assuming without verifying | Check docs, code, runtime; log it | Risk, Assumption Log |
| 6 | Staying silent when blocked | Escalate early | Communications, Issue Log |
| 7 | Promising a deadline too early | Estimate roughly, then refine | Schedule, Cost |
| 8 | Focusing on code, not outcomes | Tie milestones to deliverables | Quality, Measurement |

---

## Details

### 1. Learning the technology before understanding the problem
You read hundreds of pages but don't know which parts serve the real requirements.
**Fix:** write the goal and the technical questions first. Every learning topic should answer a concrete project need.
**PMBOK:** *Collect Requirements*, *Define Scope*. → [[01 Clarify]]

### 2. Reading code in file order
You understand many classes but not the execution flow or who owns what.
**Fix:** start from the entry point, trace one end-to-end flow, then read the related components in depth.
**PMBOK:** *Systems thinking*. → [[02 Discover]]

### 3. Choosing a solution before identifying constraints
You design a beautiful architecture that doesn't fit RAM, toolchain, coding standards, latency or compatibility.
**Fix:** write the constraints down and verify high-impact assumptions before locking the architecture.
**PMBOK:** *Define Scope* (constraints), *Identify Risks*. → [[03 De-risk]]

### 4. Prototyping for too long
The prototype keeps gaining features and becomes a second product that still doesn't solve the main requirement. This is a form of **scope creep**.
**Fix:** each spike has one or a few questions, a clear timebox and stop criteria. Then decide: continue, change direction, or stop.
**PMBOK:** *Control Scope*, *Control Schedule*. → [[Technical Spike Template]]

### 5. Assuming without verifying
You assume an API is thread-safe, a callback never fires after the object is destroyed, or an operation always completes synchronously.
**Fix:** check documentation, implementation, tests or runtime behavior. Record what is uncertain instead of guessing.
**PMBOK:** *Assumption Log*, *Identify Risks*. → [[05 Implement]]

### 6. Staying silent too long when blocked
You spend days on a problem that depends on another team and don't report it because you think you must solve it alone.
**Fix:** **escalate early**. State the problem, the impact, what you tried, and the decision you need. Independence doesn't mean working alone.
**PMBOK:** *Issue Log*, *Manage Communications*, *Escalate* (risk response). → [[09 Communication]]

### 7. Promising a deadline before knowing enough
You estimate by gut feeling or by learning time and ignore integration, testing and dependencies.
**Fix:** separate known from unknown. Give a rough estimate first, then update it as spikes and surveys reduce uncertainty.
**PMBOK:** *Estimate Activity Durations*, *progressive elaboration*, *contingency reserve*. → [[04 Plan]]

### 8. Focusing on code instead of outcomes
You make many commits but have no evidence the feature meets the requirements.
**Fix:** tie each milestone to a deliverable and verification criteria. Measure progress by confirmed results, not volume of code.
**PMBOK:** *Control Quality*, *Validate Scope*, *Measurement* domain. → [[06 Validate]]

---

## 🧠 Remember

> Most pitfalls are **order mistakes**: solution before problem, code before flow, promise before evidence, silence before escalation.
