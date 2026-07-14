# WP-125 — UI Editor Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-125 directly implements the approved Declarative UI Runtime Editor-readiness layer as passive editor document, selection, inspector, operation history, and immutable editor snapshot infrastructure. It does not implement the future product editor and does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

Architecture references:

- `docs/architecture/SIRIUS-DECLARATIVE-UI-ARCHITECTURE.md`
- `docs/architecture/SIRIUS-UI-PROPERTY-SYSTEM.md`
- `docs/architecture/SIRIUS-UI-RUNTIME-LAYERS.md`
- `docs/architecture/SIRIUS-UI-LIFETIME.md`
- `docs/architecture/SIRIUS-UI-PERSISTENCE.md`
- `docs/architecture/SIRIUS-UI-EDITOR.md`
- `docs/architecture/SIRIUS-UI-THEME.md`
- `docs/architecture/SIRIUS-UI-RENDERING.md`
- `docs/architecture/SIRIUS-UI-PERFORMANCE.md`

## Goal

Introduce the first passive UI Editor Runtime readiness snapshot vocabulary.

WP-125 starts the Editor Runtime layer after the Localization Runtime foundation by adding stable editor document/session identity, selection and hover records, preview mode vocabulary, inspector property snapshots, operation history snapshots, and immutable editor snapshots.

## Scope

- Add stable editor document ID and editor session ID value types.
- Add passive editor preview mode vocabulary.
- Add immutable editor selection snapshots keyed by scene element ID.
- Add immutable editor hover snapshots keyed by scene element ID.
- Add immutable inspector property snapshots keyed by property ID.
- Add immutable editor operation history snapshots over property operations.
- Add immutable editor snapshots containing document/session identity, preview mode, selection, hover, inspector records, and history records.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No editor UI.
- No document mutation.
- No operation application.
- No validation pipeline.
- No preview composition.
- No persistence.
- No undo/redo execution.
- No gizmo, docking, panel, plugin, visual scripting, or live layout editing behavior.
- No focus/capture transfer.
- No mutation of active runtime property, scene, layout, render, theme, localization, feature, or DDNet state.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global editor state, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Editor Runtime readiness types live only under `sirius::ui::editor`.
- Editor snapshots own immutable value records and expose them read-only.
- Editor records may refer to Scene and Property Runtime IDs by value.
- Editor snapshots are not editor UIs, document stores, validators, preview engines, persistence systems, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- applies editor operations;
- mutates documents or active runtime snapshots;
- validates staging documents;
- previews or composes scenes/layout/render commands;
- executes undo/redo;
- transfers focus/capture;
- integrates with Platform, Module Runtime, DDNet, Layout, Render, Theme, Localization, or HUD;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, global editor state, or global mutable state.

## Acceptance criteria

- Editor document and session IDs are stable string value types with read-only accessors and equality.
- Preview mode vocabulary represents inactive, document preview, runtime preview, and comparison preview.
- Selection and hover snapshots preserve optional scene element IDs and read-only accessors.
- Inspector property snapshots preserve property ID, display label, current value, persisted flag, theme-derived flag, and stable order index.
- Operation history snapshots preserve property operation batches, current history index, and read-only accessors.
- Editor snapshots preserve document/session IDs, preview mode, selection, hover, inspector record order, operation history, and read-only accessors.
- No editor UI, document mutation, operation application, validation, preview composition, persistence, undo/redo execution, focus/capture transfer, Platform composition, Module Runtime change, DDNet adapter integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global editor state, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add editor snapshot baseline`
