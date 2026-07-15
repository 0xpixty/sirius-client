# WP-140 — UI Scene Snapshot Projection

Status: approved for implementation.

## Scene Runtime direction check

Question: Does this directly move us toward Scene Runtime?

Answer: yes.

Declaration Runtime now exposes registered, composed, validated immutable declaration snapshots. Scene Runtime has element and property-runtime projection helpers. WP-140 combines those pieces into the first complete immutable scene snapshot projection for one declared surface.

## Implementation Drift Detection

Result: no drift detected.

WP-140 directly implements approved Scene Runtime scene snapshot publication from declaration snapshots. It does not introduce surface hosting, Platform composition, DDNet integration, layout, render, input, or property evaluation.

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

Add passive Scene Runtime projection from a single surface declaration snapshot to an immutable scene snapshot.

## Scope

- Add `ProjectUiSceneSnapshot(const CUiSurfaceDeclarationSnapshot &, CUiSceneId)`.
- Use the declared surface ID as the scene snapshot surface ID.
- Use caller-provided scene ID.
- Preserve projected element declaration order through `ProjectUiSceneElements()`.
- Preserve projected property metadata order through `ProjectUiScenePropertyRuntimeSnapshot()`.

## Non-goals

- No aggregate scene runtime.
- No surface snapshot construction or host composition.
- No scene ID policy beyond caller-provided identity.
- No default value application.
- No property evaluation, dependency graph construction, generation mutation, invalidation, diagnostics generation, operations, persistence, theme, localization, animation, editor, or hot reload behavior.
- No declaration validation.
- No layout, render, HUD, input, focus, capture, navigation, command, or activation behavior.
- No Platform composition.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global scene registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Projection lives under `sirius::ui::scene`.
- The helper consumes declaration values by const reference and returns an immutable scene snapshot by value.
- The helper owns no runtime state and is not a builder, evaluator object, Platform component, service, manager, registry, or cache.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- composes or hosts surfaces;
- chooses host slots;
- applies property defaults;
- evaluates properties;
- performs layout, measurement, rendering, input, focus, capture, navigation, activation, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Platform, Module Runtime, DDNet, Layout, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Surface declaration snapshots project to immutable scene snapshots.
- Projected scene snapshots preserve the declared surface ID.
- Projected scene snapshots preserve the caller-provided scene ID.
- Projected scene snapshots preserve element projection order and property metadata projection order.
- No surface hosting/composition, scene ID policy, property default/evaluation behavior, layout, render, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Platform composition, Module Runtime change, DDNet integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): project scene snapshots`
