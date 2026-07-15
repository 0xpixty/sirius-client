# WP-165 — UI Theme Runtime Snapshot

## Status

APPROVED

## Theme Runtime gate

Question: Does this directly move us toward immutable resolved Theme Runtime snapshots with deterministic diagnostics?

Answer: YES. WP-165 publishes immutable theme snapshots with deterministic validation diagnostics as a passive Theme Runtime snapshot.

## Architecture Freeze V2 drift check

WP-165 directly implements the approved Theme Runtime snapshot boundary. It does not add token resolution, style application, global current theme state, or DDNet renderer state.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`

No implementation drift detected.

## Goal

Add passive Theme Runtime snapshot publication over the existing immutable theme snapshot and diagnostics.

## Scope

- Add immutable `CThemeRuntimeSnapshot`.
- Expose read-only theme and diagnostic accessors.
- Expose passive diagnostic/error helpers.
- Add a projection helper from immutable `CThemeSnapshot` to immutable `CThemeRuntimeSnapshot`.
- Validate the source theme snapshot during projection.

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

`CThemeRuntimeSnapshot` is a passive publication container. It pairs the immutable `CThemeSnapshot` value with immutable diagnostics so later token resolution can extend Theme Runtime without changing the snapshot boundary.

`ProjectUiThemeRuntimeSnapshot` validates the supplied theme snapshot and stores the resulting diagnostics beside the copied immutable theme value.

## Acceptance criteria

- Theme runtime snapshots expose read-only theme and diagnostics.
- Theme runtime snapshots expose diagnostic/error helpers.
- Theme runtime projection validates the source theme snapshot.
- No token resolver, style application, DDNet dependency, or global theme state is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): publish theme runtime snapshots`
