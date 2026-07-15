# WP-164 — UI Theme Validation

## Status

APPROVED

## Theme Runtime gate

Question: Does this directly move us toward immutable resolved Theme Runtime snapshots with deterministic diagnostics?

Answer: YES. WP-164 validates immutable theme snapshots and produces deterministic theme diagnostics before token resolution is introduced.

## Architecture Freeze V2 drift check

WP-164 directly implements approved Theme Runtime diagnostics for invalid theme/token data. It does not add token resolution, styling behavior, global theme state, or DDNet renderer state.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Add passive deterministic validation for one immutable theme snapshot.

## Scope

- Validate theme ID presence.
- Validate token ID presence.
- Validate supported token category vocabulary.
- Validate supported state dimension vocabulary.
- Validate duplicate token keys by token ID and state dimension.
- Validate fallback chain IDs are non-empty, do not self-reference, and do not repeat.
- Return immutable theme diagnostic snapshots.
- Support a stable-order offset overload for later aggregate validation.

## Non-goals

- No token resolution.
- No cross-theme fallback lookup.
- No style application.
- No property mutation or property evaluation integration.
- No render command generation changes.
- No DDNet adapter translation or renderer state.
- No Platform composition.
- No Module Runtime changes.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

Theme validation is passive and read-only. It inspects the immutable theme snapshot and produces immutable diagnostics without resolving tokens or mutating theme values.

Fallback validation is intentionally local in this slice: it checks for empty, self-referential, and repeated fallback IDs, but does not attempt cross-theme existence checks because no theme collection/resolution boundary exists yet.

## Acceptance criteria

- Invalid theme identity produces deterministic diagnostics.
- Invalid token identity/category/state produces deterministic diagnostics.
- Duplicate token keys produce deterministic diagnostics.
- Invalid local fallback-chain structure produces deterministic diagnostics.
- No token resolver, style application, DDNet dependency, or global theme state is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): validate theme snapshots`
