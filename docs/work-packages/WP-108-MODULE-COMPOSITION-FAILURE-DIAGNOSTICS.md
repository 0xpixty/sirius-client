# WP-108 — Composition Failure Diagnostics

## Status

Approved and implemented.

## Goal

Make Module Runtime composition failures distinguishable through a passive read-only result value before product systems depend on the subsystem.

## Scope

- Add a narrow composition result type that reports success or the failed Module Runtime composition stage.
- Preserve the existing optional composition API for current callers and tests.
- Report the following failure stages:
  - descriptor parity;
  - dependency graph;
  - lifecycle graph;
  - contract resolution;
  - contract dependency cohesion.
- Keep Platform construction/startup failure safe while including the composition failure stage in construction errors.
- Add focused tests for success and each failure stage that can be produced by current repository infrastructure.

## Non-goals

- No manager.
- No scanner.
- No service locator.
- No dynamic discovery.
- No runtime unloading.
- No UI or product work.
- No logging system.
- No console command.
- No observer or event bus.
- No hidden inferred dependencies.
- No module-facing mutation APIs.
- No generalized lookup APIs.

## Acceptance criteria

- Dependency-graph composition failure reports `DependencyGraph`.
- Lifecycle-graph composition failure reports `LifecycleGraph`.
- Contract-resolution failure reports `ContractResolution`.
- Contract/dependency cohesion failure reports `ContractDependencyCohesion`.
- Definition/constructed descriptor parity failure is available as `DescriptorParity`.
- Successful composition reports `None` and exposes the composed value.
- Existing optional composition API remains available.
- Platform continues to fail construction safely when composition fails.
- `game-client` builds in Debug and RelWithDebInfo.
- `git diff --check` has no blocking whitespace errors.

## Commit message

`feat(modules): report composition failure stages`
