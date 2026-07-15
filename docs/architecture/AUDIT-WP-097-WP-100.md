# Architecture Audit — WP-097 through WP-100

Date: 2026-07-13

Verdict: `AUDITOR_FALLBACK_APPROVED`

## Scope

Incremental audit from architecture baseline `779cc1c6e26546d30c431ec9e048c00909656d68` through `6e115d2bcd624cb15a327b8dd6beda0ab2413403`.

Audited Work Packages:

- WP-097 — Module Dependency Declarations
- WP-098 — Module Dependency Graph
- WP-099 — Module Lifecycle Graph
- WP-100 — Module Lifecycle Graph Ordering

Audited areas:

- Module descriptors and immutable dependency declarations
- Deterministic dependency graph construction
- Lifecycle graph construction
- Runtime lifecycle graph consumption
- Platform composition and startup policy
- Ownership and lifetime boundaries
- Public API pressure
- Forbidden architecture risks: module managers, scanners, dynamic discovery, service-location, generalized routing, observers, product/UI branching

## Summary

The WP-097 through WP-100 block correctly advances the Foundation V2 Module Runtime milestone from metadata-only dependency declarations into deterministic dependency and lifecycle graph execution.

The implementation remains composition-local and explicit:

- `CModuleDescriptor` owns immutable dependency IDs.
- `CModuleRegistrationPlan` remains the source for deterministic graph construction.
- Dependency and lifecycle graphs are inert value objects until Platform explicitly consumes them.
- `CPlatform` still owns composition and startup wiring.
- `CModuleLifecycle` executes lifecycle order but does not become a module manager.
- No scanning, discovery, dynamic loading/unloading, service locator, router, observer, or product-system work was introduced.

## Findings

### Critical

None.

### Medium

None.

### Low

1. Dependency/lifecycle graph failure reasons remain boolean-only.

   Current graph builders and graph-aware lifecycle initialization reject invalid state through `std::optional`/`bool` without structured diagnostics. This is acceptable for the completed graph-ordering block, but the next Module Runtime step should expose a read-only diagnostics snapshot rather than proliferating one-off failure checks in Platform.

2. `CPlatform` now holds the lifecycle graph as startup composition state.

   This is acceptable because Platform remains the explicit composition root and the graph is immutable after configuration. The next runtime boundary work should prevent Platform from accumulating ad hoc per-module policy by moving toward a narrow Module Runtime startup/result surface after diagnostics and typed contracts mature.

3. Graph-aware lifecycle validates shutdown order but executes shutdown by unwinding actual initialized modules.

   This is the correct safety behavior for partial initialization. Future diagnostics should report both declared graph order and actual initialized/unwound order so startup failures can be explained without changing lifecycle semantics.

## Ownership and dependency direction

Approved.

- Core remains independent of Platform and DDNet.
- DDNet remains adapter-only and untouched by this block.
- Platform remains the explicit composition root.
- Module Runtime graph types live under `sirius::platform::modules`.
- Modules do not receive lookup APIs or service-location access.
- Lifecycle and activation remain separate.

## Public API pressure

Approved with watch item.

The graph-aware `CModuleLifecycle::Initialize` overload is a narrow lifecycle execution API and does not expose module lookup or composition. The older registration-order overload remains for compatibility and tests, but Platform now consumes the graph-aware path. This does not yet require removal.

## Scalability assessment

Approved.

The block improves scalability for future module counts by establishing:

- deterministic dependency declaration,
- dependency validation,
- lifecycle ordering,
- reverse shutdown based on actual initialized order.

The next scalability bottleneck is observability: invalid graphs and lifecycle startup failures are not yet diagnosable through a stable snapshot.

## Required correction loop

None.

## Next safe step

Proceed to the next bounded Module Runtime Work Package:

Runtime diagnostics snapshot v1 for module registration, dependency graph, lifecycle graph, lifecycle state, and validation failures.

This directly follows the accepted Foundation V2 sequence:

descriptor -> definition -> deterministic registration -> dependency/lifecycle graph -> diagnostics -> typed contracts
