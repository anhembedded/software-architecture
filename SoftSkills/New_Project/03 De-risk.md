---
title: "Step 3 — De-risk"
tags:
  - project-management
  - risk
  - spike
step: 3
pmbok:
  - Risk Management
  - Uncertainty
---

# 🛡️ Step 3 — De-risk

> [!abstract] TL;DR
> You can't be sure the whole design is right. But you **can** find the most dangerous assumptions and verify them early.

Prev: [[02 Discover]] · Next: [[04 Plan]]

---

## 1. Risk is not the same as a hard task

A task can be hard but **low-risk**: stable technology, good documentation, someone has done it before.

A task that looks simple can be **high-risk**: for example, it depends on a library that nobody has verified on your target.

**Typical risk questions:**

- Does the framework run on the **target's Linux version**?
- Does the library support the device's **CPU architecture**?
- Does the API meet the **latency limit**?
- Does it **build with the project's toolchain**?
- Does it depend on a **license** or library that is not allowed?
- Is it **compatible** with the existing system?

Any of these answers can change the whole plan.

## 2. Rank risks with Impact × Uncertainty

$$ Risk \approx Impact \times Uncertainty $$

- **Impact:** if the assumption is wrong, how bad is it?
- **Uncertainty:** how confident are you right now?

> [!note]
> A practical ranking model, not a formal quantitative formula. PMBOK's version is **probability × impact** (see below).

| Assumption | Impact if wrong | Uncertainty | Priority |
| --- | --- | --- | --- |
| Framework builds on the target | 🔴 High | 🔴 High | 🔥 **Very high** |
| API meets the concurrency requirement | 🔴 High | 🔴 High | 🔥 **Very high** |
| Name of a helper function | 🟢 Low | 🔴 High | 🟢 Low |
| A small snippet can be optimized | 🟢 Low | 🟡 Medium | 🟢 Low |

> [!important] Key point
> Don't verify the question that is **easiest** to answer. Verify the one whose answer is **most likely to change a major decision**.

## 3. Use a spike to reduce risk

A **technical spike** is a **timeboxed** investigation that answers **one specific question**. It does not have to be production-ready.

| Tool | Proves |
| --- | --- |
| **Prototype** | What it looks like or how it behaves for the user |
| **Spike** | Whether it is technically possible, where it is hard, and what the risks are |

**Example question:** Can Framework X run on our Linux target and receive data asynchronously?

A spike only needs to:

1. Create a minimal program.
2. Build with the **real toolchain**.
3. Run on the target (or an equivalent environment).
4. Try one basic communication flow.
5. Observe logs, resource usage and failure behavior.
6. Record the results and the limits you found.

A good spike has a clear question and a clear exit condition:

| Element | Example |
| --- | --- |
| ❓ Question | Does it build with the current toolchain? |
| ✅ Success | The sample program builds and runs on the target |
| ❌ Failure | You find the incompatibility and propose an alternative |
| ⏱️ Timebox | A duration agreed with the team in advance |

> [!tip]
> A failed spike still has value: you **ruled out an infeasible direction early**. Use the [[Technical Spike Template]] and log results in the [[Risk Register]].

---

## 🔗 PMBOK link

| PMBOK 6th | How it matches |
| --- | --- |
| **Plan Risk Management** | Decide how you will handle risk on this project |
| **Identify Risks** | List the assumptions that could fail |
| **Perform Qualitative Risk Analysis** | Probability and impact matrix = Impact × Uncertainty |
| **Plan Risk Responses** | Pick a response (table below) |
| **Implement Risk Responses**, **Monitor Risks** | Run the spike, then re-check the register |
| **Risk Register** | The living list of risks and responses → [[Risk Register]] |

**Response strategies for threats**

| Strategy | Meaning | Example |
| --- | --- | --- |
| **Avoid** | Remove the cause | Drop the unverified library |
| **Mitigate** | Reduce probability or impact | **Run a spike** on the target |
| **Transfer** | Move the impact to a third party | Vendor support contract |
| **Escalate** | Hand over to the right owner | Ask management to decide |
| **Accept** | Do nothing now, or keep a reserve | Low-impact issue; contingency reserve |

| PMBOK 7th | How it matches |
| --- | --- |
| **Uncertainty** performance domain | Ambiguity, complexity, volatility, uncertainty, risk |
| **Risk** principle | Respond to threats **and** opportunities |

## 🧠 Remember

> **Risk ≠ hard.** Rank by **Impact × Uncertainty**.
> A spike = **one question + success/failure rule + timebox**.
> Spike = *mitigate*.
