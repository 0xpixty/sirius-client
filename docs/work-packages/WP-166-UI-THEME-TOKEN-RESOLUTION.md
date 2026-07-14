# WP-166 — UI Theme Token Resolution

## Status

APPROVED

## Theme Runtime gate

Question: Does this directly move us toward immutable resolved Theme Runtime snapshots with deterministic diagnostics?

Answer: YES. WP-166 adds a narrow read-only token resolution result over one immutable Theme Runtime snapshot.

## Architecture Freeze V2 drift check

WP-166 directly implements approved Theme Runtime token resolution in its narrowest useful form. It does not add global theme state, fallback-chain policy, style application, property mutation, or DDNet renderer state.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Add deterministic token resolution for one token ID/state against one immutable Theme Runtime snapshot.

## Scope

- Add immutable token resolution result snapshot.
- Resolve a requested token ID and state by exact match against the Theme Runtime snapshot tokens.
- Return the resolved immutable token snapshot when present.
- Return deterministic diagnostics for empty requested token IDs and missing required tokens.
- Treat missing optional tokens as an empty result without diagnostics.

## Non-goals

- No fallback-chain traversal.
- No state fallback policy.
- No alias resolution.
- No type conversion or typed token payload parsing.
- No style application.
- No property mutation or property evaluation integration.
- No render command generation changes.
- No DDNet adapter translation or renderer state.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The resolver is a pure read-only helper over one immutable `CThemeRuntimeSnapshot`. It performs an exact token ID/state match and returns a passive result object containing either the resolved token or diagnostics.

Fallback-chain traversal and state fallback are intentionally deferred because those policies require a broader theme collection boundary and must not be invented prematurely.

## Acceptance criteria

- Exact token ID/state matches resolve deterministically.
- Empty requested token IDs produce deterministic diagnostics.
- Missing required tokens produce deterministic diagnostics.
- Missing optional tokens produce an empty non-error result.
- No global theme state, fallback-chain traversal, style application, DDNet dependency, or mutable cache is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): resolve theme tokens`
