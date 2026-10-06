# Key Words

## Strangler Fig Pattern

A well-known pattern introduced by Martin Fowler for replacing a legacy system without a risky full rewrite.

- Instead of doing a big-bang rewrite, a new system is built around the old one.
- New features are developed in the new system first.
- Older features are gradually rewritten and routed to the new platform.
- Once the new system covers the full functionality, the legacy system is retired and shut down.

This approach reduces risk and allows incremental migration.

## Walking Skeleton

A term coined by Alistair Cockburn, one of the founders of Agile.

- A walking skeleton is the smallest possible version of a system.
- It does not yet contain full business logic, but it connects the entire architecture end-to-end.
- It typically includes: basic UI → API → database.
- Most importantly, it must work through the automation pipeline and be deployable to a real environment.

The goal is to prove early that the system architecture works correctly before adding the full business features.

## Risk-first vs Safety-first

These are two different project prioritization philosophies in software delivery.

### Risk-first

- Focuses on tackling the hardest and most uncertain parts first.
- Aims to fail early so that critical risks are exposed sooner rather than later.
- Helps prevent large-scale project failure after significant investment.

### Safety-first

- Prioritizes easier, familiar, and lower-risk work first.
- Builds early momentum and gives stakeholders visible progress.
- Helps reduce anxiety and create confidence before tackling harder tasks.

In short, risk-first optimizes for learning and risk discovery, while safety-first optimizes for confidence and steady delivery.

## ADR

ADR stands for Architectural Decision Record.

- It is a short document that records important architecture decisions made during a project.
- It explains what decision was made, why it was made, and what alternatives were considered.
- It helps the team understand the reasoning behind technical choices and avoid repeating past debates.
- ADRs are especially useful in long-lived systems where architecture evolves over time.

A typical ADR usually includes:

- the context or problem,
- the decision itself,
- the consequences of the decision,
- and any trade-offs or future considerations.

ADR helps teams preserve architectural knowledge and makes it easier for new developers to understand the system.