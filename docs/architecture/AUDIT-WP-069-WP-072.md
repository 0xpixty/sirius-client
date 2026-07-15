# Architecture Audit - WP-069 through WP-072

Date: 2026-07-13

## Status

Completed and independently reviewed.

- Auditor: `ARCHITECTURE_AUDIT_CHANGES_REQUIRED_BEFORE_EXPANSION`
- Independent Reviewer: `AUDIT_APPROVED`
- Devil's Advocate: `NO_BLOCKING_OBJECTION`
- Critical findings: none
- Medium findings: one mandatory correction
- User decision: not required

## Executive Summary

Core, Platform, DDNet adapter, module ownership, neutral activation, command composition, and registry responsibility boundaries remain intact. No manager, router, service locator, global mutable bus, or reverse dependency was introduced.

One Medium lifecycle defect must be corrected before real feature expansion: `CPlatform::Stop()` does not reconcile platform-owned feature activation behavior or activation records before module Feature shutdown. An active record survives same-instance restart, so the next activation is treated as a duplicate and its behavior is skipped. Activation APIs also remain callable while lifecycle/Core are stopped.

## Dependency and Ownership Graph

```text
DDNet CClient
  -> DDNet platform adapter
  -> CPlatformBootstrap
  -> CPlatform
       -> Core runtime/services
       -> input/binding pipeline
       -> neutral activation boundary
            -> feature resolver/controller/behavior
            -> command resolver/dispatcher
                 -> technical module-owned command registry
       -> module registry
            -> module-owned feature/command/service registries
```

- `CPlatform` owns composition and Core runtime.
- `CModuleRegistry` uniquely owns modules.
- `CModule` owns feature, command, and module-service registries by value.
- The technical command is uniquely module-owned.
- Command dispatcher/handler observers are disconnected before module shutdown.
- The pre-existing `CModuleRegistry::Remove()` diff remains separate and untouched.

## Findings

### Critical

None.

### Medium - Mandatory Before Expansion

Feature activation shutdown/restart inconsistency:

- `CPlatform::Stop()` resets command activation wiring and shuts module lifecycle/Core, but does not deactivate or reconcile active feature activation records.
- Same-instance restart retains `Active`, causing the next activation request to short-circuit without behavior execution.
- Future real module features could be lifecycle-shut down while product activation remains active.
- Feature activation APIs are not gated by active platform lifecycle.
- `Stop()` is `noexcept` while behavior `Deactivate()` may throw, so correction must define failure isolation and record reconciliation without termination.

### Low - Monitor or Handle Separately

- Obsolete binding-local activation resolver header remains.
- Mutable `CPlatform::Modules()` and unused manual deactivation surface are broader than current callers require.
- Technical input proof is not invoked by the current DDNet client input loop.
- Fixed registration helpers ignore failure results; expansion must not copy partial-registration behavior.
- Callback reentrancy and structural stability remain contractual.
- Module destructors run after Core member destruction and must remain passive; runtime cleanup belongs in lifecycle shutdown.
- The technical module and technical activation behavior must not become product catch-alls.

## Verified Strengths

- Core has no Platform or DDNet dependency.
- DDNet remains an outward adapter.
- Modules truthfully own Feature, Command, and service registries.
- Activation IDs remain source-neutral.
- Fixed two-consumer fan-out does not yet justify a router.
- WP-071 command ownership and observer lifetime are sound.
- WP-072 idempotency, commit-after-success, and exception-state consistency are sound.

## Audit Decision

`ARCHITECTURE_AUDIT_CHANGES_REQUIRED_BEFORE_EXPANSION`

The finding does not invalidate WP-071 or WP-072 approval. It requires a bounded correction before a stateful or real feature is introduced.

## Next Safe Step

Architect a correction-only WP-073 for Feature Activation Shutdown/Restart Consistency:

- reconcile active records before module Feature shutdown;
- prevent activation execution outside active lifecycle;
- define shutdown exception handling compatible with `noexcept`;
- add focused active/inactive Stop/restart tests;
- preserve WP-072 ordinary transition semantics;
- add no product feature, manager/router, module scan, resolver cleanup, or DDNet integration.
