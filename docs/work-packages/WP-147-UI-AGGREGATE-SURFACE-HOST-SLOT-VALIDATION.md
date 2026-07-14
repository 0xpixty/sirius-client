# WP-147 — UI Aggregate Surface Host Slot Validation

## Status

APPROVED

## Architecture Freeze V2 drift check

WP-147 directly implements the approved Aggregate Surface Runtime policies for explicit host slots and deterministic conflict diagnostics.

Referenced architecture:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`
- `docs/architecture/SIRIUS-UI-PERSISTENCE.md`
- `docs/architecture/SIRIUS-UI-EDITOR.md`
- `docs/architecture/SIRIUS-UI-THEME.md`

No implementation drift detected.

## Goal

Add passive Aggregate Surface Runtime validation that reports unsupported host slots and deterministic same-slot conflicts before aggregate surface projection exists.

## Scope

- Add a read-only validation function over immutable UI declaration snapshots.
- Report `UnsupportedHostSlot` when a surface targets a host slot outside the approved initial host-slot set.
- Report `HostSlotConflict` when two declarations target the same approved exclusive host slot.
- Preserve declaration order for deterministic diagnostic generation.
- Return immutable `CSurfaceRuntimeDiagnosticSnapshot` records.

## Non-goals

- No aggregate surface projection.
- No scene snapshot generation.
- No composition status assignment.
- No conflict resolution.
- No priority, last-wins, or implicit ordering policy.
- No host-slot inference.
- No Platform composition.
- No DDNet adapter integration.
- No layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, or activation behavior.
- No managers, scanners, service locators, routers, runtime discovery, hidden registries, mutable caches, callbacks/events, generalized factories, or global mutable state.

## Design

`ValidateAggregateSurfaceDeclarations()` consumes `CUiDeclarationSnapshot` and returns a `CSurfaceRuntimeDiagnosticSnapshot`.

The validator is intentionally passive. It does not mutate declarations, allocate runtime scene IDs, compose surfaces, or choose a recovery strategy. Under the approved initial policy, repeated use of the same approved host slot is treated as an exclusive-slot conflict until a later Surface Runtime layer explicitly introduces aggregate stacking policy.

## Acceptance criteria

- Unsupported host slots produce deterministic `UnsupportedHostSlot` diagnostics.
- Same approved host-slot pairs produce deterministic `HostSlotConflict` diagnostics.
- Diagnostics preserve declaration-order discovery and stable diagnostic indexes.
- No aggregate surface projection or status assignment is introduced.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Approved commit message

`feat(ui): validate aggregate surface host slots`
