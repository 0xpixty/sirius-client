# WP-167 — UI Theme Runtime Collection

## Status

APPROVED

## Theme Runtime gate

Question: Does this directly move us toward immutable resolved Theme Runtime snapshots with deterministic diagnostics?

Answer: YES. WP-167 adds the passive immutable Theme Runtime collection shape needed before fallback-chain resolution can inspect multiple theme snapshots.

## Architecture Freeze V2 drift check

WP-167 directly supports the approved Theme Runtime fallback-chain model without introducing a manager, global current theme, mutable registry, or generalized lookup API.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Add a passive immutable collection of Theme Runtime snapshots.

## Scope

- Add immutable `CThemeRuntimeCollectionSnapshot`.
- Expose read-only ordered theme runtime snapshots.
- Expose passive count/empty/error helpers.

## Non-goals

- No theme lookup API.
- No fallback-chain traversal.
- No active/current theme selection.
- No token resolution changes.
- No style application.
- No property mutation or property evaluation integration.
- No render command generation changes.
- No DDNet adapter translation or renderer state.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

The collection is an immutable value boundary. It stores ordered `CThemeRuntimeSnapshot` values and exposes read-only access for later deterministic fallback-chain resolution.

It intentionally does not provide lookup or selection behavior in this slice.

## Acceptance criteria

- Theme Runtime collections expose read-only ordered theme snapshots.
- Theme Runtime collections expose count/empty/error helpers.
- No lookup API, fallback traversal, global theme state, style application, DDNet dependency, or mutable cache is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): collect theme runtime snapshots`
