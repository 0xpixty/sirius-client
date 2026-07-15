# WP-163 — UI Theme Diagnostics

## Status

APPROVED

## Theme Runtime gate

Question: Does this directly move us toward immutable resolved Theme Runtime snapshots with deterministic diagnostics?

Answer: YES. WP-163 adds the passive diagnostic vocabulary and immutable diagnostic snapshot required before validation and token resolution can report failures.

## Architecture Freeze V2 drift check

WP-163 directly implements the approved Theme Runtime diagnostic surface. It does not add token resolution, styling behavior, global theme state, or DDNet renderer state.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Add passive immutable Theme Runtime diagnostics.

## Scope

- Add theme diagnostic severity vocabulary.
- Add theme diagnostic code vocabulary for identity, token, fallback, type, and alias failures.
- Add immutable theme diagnostic records with optional theme and token context.
- Add immutable theme diagnostic snapshots with count/empty/error helpers.

## Non-goals

- No theme validation.
- No token resolution.
- No fallback-chain resolution.
- No style application.
- No property mutation or property evaluation integration.
- No render command generation changes.
- No DDNet adapter translation or renderer state.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

Theme diagnostics are passive values. They give later validation and token-resolution Work Packages a stable immutable result type without introducing a resolver or theme runtime owner.

## Acceptance criteria

- Theme diagnostics expose severity, code, message, optional theme ID, optional token ID, and stable order.
- Theme diagnostic snapshots expose read-only diagnostics and error helpers.
- No theme resolver, style application, DDNet dependency, or global theme state is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): add theme diagnostics`
