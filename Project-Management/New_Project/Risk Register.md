---
title: "Risk Register"
tags:
  - project-management
  - template
  - risk
type: template
pmbok:
  - Risk Management
  - Risk Register
---

# 📒 Risk Register

> [!abstract] TL;DR
> The **Risk Register** is the living list of identified risks, their ranking and their responses. In PMBOK 6th it is created in *Identify Risks* and updated through *Monitor Risks*.

Background: [[03 De-risk]] · Spikes: [[Technical Spike Template]] · Mapping: [[PMBOK Mapping]]

---

## Columns

| Column | Meaning |
| --- | --- |
| **ID** | R1, R2, … |
| **Risk statement** | "If <cause>, then <event>, resulting in <effect>" |
| **Impact** | Low / Medium / High |
| **Uncertainty (probability)** | Low / Medium / High |
| **Priority** | Impact × Uncertainty |
| **Response** | Avoid / Mitigate / Transfer / Escalate / Accept |
| **Action / Spike** | What you will do |
| **Owner** | Who is responsible |
| **Status** | Open / Mitigating / Closed |

## Example

| ID | Risk statement | Impact | Uncertainty | Priority | Response | Action | Owner | Status |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| R1 | If the framework does not build with our toolchain, we must replace it, delaying M2 | High | High | 🔥 Very high | Mitigate | Spike S1: build on target | Me | Open |
| R2 | If the API is not fast enough, we miss the latency requirement | High | High | 🔥 Very high | Mitigate | Spike S2: measure latency | Me | Open |
| R3 | If a helper function is named differently, we rename it | Low | High | 🟢 Low | Accept | None | Me | Open |
| R4 | If another team's API is late, M3 is blocked | High | Medium | 🟠 High | Escalate | Raise with manager, agree a date | Manager | Open |

## Priority matrix

|  | Uncertainty Low | Uncertainty Medium | Uncertainty High |
| --- | --- | --- | --- |
| **Impact High** | 🟠 High | 🟠 High | 🔥 Very high |
| **Impact Medium** | 🟢 Low | 🟡 Medium | 🟠 High |
| **Impact Low** | 🟢 Low | 🟢 Low | 🟢 Low |

> [!tip]
> Review the register at each milestone. Close risks that spikes have removed, and add new ones that spikes revealed.
