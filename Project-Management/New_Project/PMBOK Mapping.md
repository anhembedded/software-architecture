---
title: PMBOK Mapping
aliases:
  - PMBOK Cheat Sheet
tags:
  - project-management
  - pmbok
  - reference
type: reference
status: evergreen
---

# 🗺️ PMBOK Mapping

> [!abstract] TL;DR
> The six steps in this folder are a **practical engineer's view** of what the PMBOK Guide describes formally. This page is the bridge: use it to translate "what I do at work" into "what PMBOK calls it".

Back to the index: [[Thinking New project]]

---

## 1. PMBOK 6th Edition — Processes

### 5 Process Groups (when in the project?)

| Group | Question it answers |
| --- | --- |
| **Initiating** | Should we start? Who cares? |
| **Planning** | How will we do it? |
| **Executing** | Do the work. |
| **Monitoring & Controlling** | Are we on track? Is the output right? |
| **Closing** | Finish, hand over, learn. |

> [!tip] Remember
> **I-P-E-M-C** → *"I Plan Every Monday Carefully."*

### 10 Knowledge Areas (what topic?)

| # | Area | One-line meaning |
| --- | --- | --- |
| 1 | **Integration** | Keep all parts working together; manage change |
| 2 | **Scope** | What is in, what is out |
| 3 | **Schedule** | When things happen |
| 4 | **Cost** | How much money |
| 5 | **Quality** | Fit for purpose and meets requirements |
| 6 | **Resource** | People, equipment, materials |
| 7 | **Communications** | Who needs what information, when |
| 8 | **Risk** | Uncertain events (threats and opportunities) |
| 9 | **Procurement** | Buying from outside the project |
| 10 | **Stakeholder** | People affected by, or affecting, the project |

> [!tip] Remember
> Process groups = **time** (when). Knowledge areas = **topic** (what). Each process sits at one crossing of the two.

---

## 2. PMBOK 7th Edition — Principles and Performance Domains

### 12 Principles (how to think)

| Principle | Short meaning |
| --- | --- |
| **Stewardship** | Act responsibly and ethically |
| **Team** | Build a collaborative team culture |
| **Stakeholders** | Engage them proactively |
| **Value** | Focus on outcomes and benefits |
| **Systems thinking** | See the whole system and its interactions |
| **Leadership** | Show and adapt leadership behavior |
| **Tailoring** | Fit the approach to the context |
| **Quality** | Build quality into processes and deliverables |
| **Complexity** | Navigate it using learning and adaptation |
| **Risk** | Respond to both threats and opportunities |
| **Adaptability & resiliency** | Absorb change and recover |
| **Change** | Enable change to reach the future state |

### 8 Performance Domains (what to do well)

| Domain | Short meaning |
| --- | --- |
| **Stakeholder** | Productive relationships with stakeholders |
| **Team** | People who deliver the outcomes |
| **Development Approach & Life Cycle** | Predictive, iterative, incremental, agile, hybrid |
| **Planning** | Organize and coordinate the work |
| **Project Work** | Run the work, manage resources and communication |
| **Delivery** | Deliver scope and quality, and the expected value |
| **Measurement** | Metrics and evidence of performance |
| **Uncertainty** | Ambiguity, complexity, volatility, uncertainty and risk |

---

## 3. Step → PMBOK Table

| Step | Process group (6th) | Typical processes (6th) | Knowledge areas | 7th ed. link |
| --- | --- | --- | --- | --- |
| [[01 Clarify]] | Initiating, Planning | Develop Project Charter, Identify Stakeholders, Collect Requirements, Define Scope | Scope, Stakeholder | Stakeholder domain, *Value* |
| [[02 Discover]] | Planning | Collect Requirements, review EEF and OPA | Integration, Scope | *Systems thinking* |
| [[03 De-risk]] | Planning, Executing, M&C | Identify Risks, Perform Qualitative Risk Analysis, Plan Risk Responses, Implement Risk Responses, Monitor Risks | Risk | Uncertainty domain, *Risk* principle |
| [[04 Plan]] | Planning | Create WBS, Define and Sequence Activities, Estimate Activity Durations, Develop Schedule | Schedule, Scope | Planning domain |
| [[05 Implement]] | Executing | Direct and Manage Project Work, Manage Quality, Manage Communications | Integration, Quality, Communications | Project Work domain |
| [[06 Validate]] | M&C, Closing | Control Quality, Validate Scope, Perform Integrated Change Control, Close Project or Phase | Quality, Scope, Integration | Delivery and Measurement domains |

> [!info] Terms used in the table
> - **EEF** = Enterprise Environmental Factors (conditions you cannot change: culture, tools, regulations).
> - **OPA** = Organizational Process Assets (what the company already has: templates, lessons learned, past plans).
> - **WBS** = Work Breakdown Structure (the project scope split into smaller work packages).
> - **M&C** = Monitoring and Controlling.

---

## 4. Concept Map: This Folder ↔ PMBOK

| Idea in these notes | PMBOK concept | Note |
| --- | --- | --- |
| Problem / technical / execution uncertainty | 7th ed. *Uncertainty* domain (ambiguity, complexity, volatility, uncertainty, risk) | **Analogy, not official.** PMBOK does not use these three labels. |
| Requirement vs solution | Requirements (what) vs product/design (how) | Official idea, informal wording |
| Layered survey | *Systems thinking* principle | Analogy |
| Impact × Uncertainty | Probability × Impact (risk matrix) | Same logic. PMBOK says *probability*. |
| Spike | Risk response: **mitigate** (and a way to gather information) | Spike is an Agile/XP term, not PMBOK |
| Plan by certainty level | **Progressive elaboration**, **rolling wave planning** | Official |
| Milestones | Milestone list, milestone schedule | Official |
| Dependencies / blockers | Dependency types (FS, SS, FF, SF), constraints, **Issue Log** | Official |
| Fact / assumption / verified | **Assumption Log**, Issue Log | Official (6th ed.) |
| Verify vs prove it is accepted | **Control Quality** (is it correct?) vs **Validate Scope** (does the customer accept it?) | Official |
| Small bug skips the 6 steps | *Tailoring* principle | Official |
| Top-down / incremental / spike | Development Approach and Life Cycle domain | Official categories |
| Evidence, not activity | Measurement and Delivery domains | Official |
| Escalate blockers early | **Escalate** risk response, Issue Log, Communications Management | Official |
| Lessons learned | **Lessons Learned Register**, Close Project or Phase | Official |

> [!warning] About editions
> This mapping uses the **6th and 7th editions**. A newer (8th) edition exists; check wording against the edition you study for.

---

## 5. Related

- [[Glossary]]
- [[Risk Register]]
- [[Technical Spike Template]]
- [[Project Onboarding Checklist]]
