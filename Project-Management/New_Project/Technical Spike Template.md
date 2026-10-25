---
title: "Technical Spike Template"
tags:
  - project-management
  - template
  - spike
type: template
pmbok:
  - Risk Management
  - Plan Risk Responses
---

# 🧪 Technical Spike Template

> [!abstract] TL;DR
> One spike = **one question**, a clear **success/failure rule**, and a **timebox**. It is a *mitigate* response in the [[Risk Register]].

Background: [[03 De-risk]] · Mapping: [[PMBOK Mapping]]

---

## Template (copy this)

```markdown
# Spike: <short title>

- Date:
- Owner:
- Linked risk (ID in Risk Register):

## Question
<One specific, answerable question>

## Why it matters (impact if the answer is "no")
<What decision or plan changes?>

## Success criteria
<What result means "yes, feasible"?>

## Failure criteria
<What result means "no"? What alternative will we try?>

## Timebox
<Agreed duration, e.g. 2 days>

## Steps
1.
2.
3.

## Result
- Outcome: Success / Failure / Inconclusive
- Evidence (logs, numbers, links):
- Limits found:

## Decision
- Continue / Change direction / Stop
- Next action and owner:
```

## Example (filled)

| Field | Value |
| --- | --- |
| Question | Does Framework X build with our toolchain and run on the target? |
| Impact if "no" | We must find an alternative library; M2 moves by ~2 weeks |
| Success | Sample program builds and runs on the target |
| Failure | Build fails or runtime crash; document the incompatibility |
| Timebox | 2 days |
| Decision | Decide at the end of day 2 |

## 🧠 Remember

> **Q – S – F – T:** Question, Success, Failure, Timebox.
