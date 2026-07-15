# WP-121 — UI Layout Snapshot Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-121 directly implements the approved Declarative UI Runtime Layout layer as passive logical geometry, constraint, and immutable layout snapshot infrastructure. It consumes Scene Runtime identity values and does not change ownership, lifetime, layering, public API responsibility, or runtime responsibility.

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

Introduce the first passive UI Layout Runtime snapshot vocabulary.

WP-121 starts the Layout Runtime layer after the Scene/Surface Runtime foundation by adding DDNet-independent logical geometry, first-era layout kind vocabulary, size constraints, resolved layout records, and immutable layout snapshots.

## Scope

- Add logical layout scalar, size, and rectangle value types.
- Add passive layout kind vocabulary for fixed rect, stack, dock/fill, proportional split, and scroll content extent.
- Add immutable size constraint records.
- Add immutable element layout records keyed by scene element ID.
- Add immutable layout snapshots keyed by surface and scene ID.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No layout pass or solver.
- No measurement.
- No text measurement.
- No constraint validation.
- No scroll behavior.
- No render commands.
- No DDNet `CUIRect`, `CUi`, graphics, or text rendering integration.
- No input, focus, capture, navigation, activation, hosting, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD runtime.
- No Platform composition changes.
- No Module Runtime changes.
- No DDNet adapter integration.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Layout Runtime types live only under `sirius::ui::layout`.
- Layout snapshots own immutable value records and expose them read-only.
- Layout records may refer to `sirius::ui::scene` IDs by value.
- Layout snapshots are not solvers, layout engines, measurement caches, renderers, input handlers, services, managers, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Render, Theme, Localization, Editor, or HUD headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- computes or mutates layout;
- validates constraints;
- measures text or content;
- translates to `CUIRect` or any DDNet UI/rendering type;
- emits render commands;
- performs input, focus, capture, navigation, activation, hosting, theme, localization, editor, persistence, hot reload, undo/redo, animation, or HUD behavior;
- integrates with Platform, Module Runtime, DDNet, Render, Theme, Localization, Editor, or HUD;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, or global mutable state.

## Acceptance criteria

- Logical layout scalar/size/rectangle values are immutable after construction and expose read-only accessors.
- Layout kind vocabulary represents fixed rect, stack, dock/fill, proportional split, and scroll content extent.
- Size constraint records preserve minimum, preferred, and maximum logical sizes.
- Element layout records preserve scene element ID, layout kind, bounds, size constraints, and stable order index.
- Layout snapshots preserve surface ID, scene ID, deterministic element layout record order, and read-only accessors.
- No layout solver/pass, measurement, validation, CUIRect/DDNet integration, render commands, input/focus/capture/navigation, theme/localization/editor/HUD behavior, Platform composition, Module Runtime change, DDNet adapter integration, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add layout snapshot baseline`
