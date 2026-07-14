# WP-168 — UI Theme Fallback Resolution

## Status

APPROVED

## Theme Runtime gate

Question: Does this directly move us toward a complete immutable Theme Runtime Snapshot?

Answer: YES. WP-168 adds deterministic fallback-chain token resolution over immutable Theme Runtime collection snapshots.

## Architecture Freeze V2 drift check

WP-168 directly implements the approved Theme Runtime responsibilities: deterministic token lookup, fallback-chain resolution, and diagnostics over immutable theme snapshots. It does not introduce styling framework behavior, scriptability, runtime editing, global current theme state, managers, service locators, or DDNet renderer state.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Add deterministic fallback-chain token resolution for immutable Theme Runtime collections.

## Scope

- Add collection-based token resolution from theme ID, token ID, and state.
- Resolve against the requested theme first.
- Resolve against the requested theme fallback chain in declared order.
- Return deterministic diagnostics for empty theme IDs, empty token IDs, missing requested themes, missing fallback themes, and missing required tokens.
- Preserve optional-token behavior as an empty non-error result when no required-token failure exists.

## Non-goals

- No CSS-like language.
- No style scripting.
- No runtime theme editing.
- No animation ownership.
- No profile management.
- No persistence changes.
- No plugin discovery.
- No dynamic loaders.
- No style application.
- No property mutation or property evaluation integration.
- No render command generation changes.
- No DDNet adapter translation or renderer state.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The resolver is a pure read-only helper over `CThemeRuntimeCollectionSnapshot`. It finds the requested immutable theme snapshot by ID, checks for an exact token ID/state match, then checks the requested theme fallback chain in declared order.

Missing fallback themes produce deterministic diagnostics. Resolution returns the first matching token found in deterministic order. It does not traverse fallback themes' own fallback chains; the requested theme snapshot owns the explicit fallback chain for this first implementation era.

## Acceptance criteria

- Requested theme token matches resolve before fallback tokens.
- Fallback tokens resolve in declared fallback-chain order.
- Missing requested themes produce deterministic diagnostics.
- Missing fallback themes produce deterministic diagnostics.
- Missing required tokens produce deterministic diagnostics after fallback-chain resolution.
- Missing optional tokens produce an empty result, preserving any missing-fallback diagnostics.
- No global theme state, style application, scripting, DDNet dependency, or mutable cache is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): resolve theme fallback tokens`
