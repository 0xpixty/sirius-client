# WP-129 — UI Element Declaration Baseline

Status: approved for implementation.

## Implementation Drift Detection

Result: no drift detected.

WP-129 directly implements the approved Declarative UI Runtime element declaration primitive as passive immutable values. It does not evaluate declarations into scenes, attach properties, compose surfaces, or introduce UI behavior.

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

Introduce the first passive UI element declaration vocabulary.

WP-129 adds immutable element declaration values carrying element identity, optional parent identity, element kind, accessibility metadata, declared action intents, and stable ordering. This creates the declaration-side counterpart to passive scene element snapshots while leaving evaluation and property attachment for later bounded Work Packages.

## Scope

- Add immutable UI element declarations over existing scene element identity/kind/accessibility vocabulary.
- Add immutable UI element declaration lists preserving deterministic declaration order.
- Register the new files in `src/sirius/CMakeLists.txt`.

## Non-goals

- No property declaration attachment.
- No scene evaluation.
- No tree validation.
- No layout, render, theme, localization, editor, HUD, input, focus, capture, navigation, command, activation, or property evaluation behavior.
- No surface composition or surface registration changes.
- No module ownership binding.
- No Module Runtime changes.
- No Platform composition changes.
- No DDNet adapter integration.
- No diagnostics generation.
- No manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global element registry, or global mutable state.
- No architecture redesign under Architecture Freeze V2.

## Ownership and boundaries

- Element declaration readiness types live only under `sirius::ui::declaration`.
- Element declarations own immutable value records and expose them read-only.
- Element declarations may refer to Scene element identity/kind/accessibility vocabulary and Action Intent snapshot values by value.
- Element declarations are not evaluated scene nodes, layout objects, render commands, widgets, services, managers, validators, or caches.
- The layer must not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, HUD, or Property headers.

## Drift-stop rules

Implementation must stop and report `IMPLEMENTATION_DRIFT_DETECTED` if it:

- attaches or evaluates properties;
- validates tree structure;
- evaluates declarations into scene snapshots;
- creates layout or render commands;
- handles input, focus, capture, navigation, command, or activation behavior;
- registers or composes surfaces;
- binds declarations to module IDs or Module Runtime descriptors;
- integrates with Platform, Module Runtime, DDNet adapter, Features, Commands, Bindings, Layout, Render, Theme, Localization, Editor, HUD, or Property Runtime behavior;
- introduces mutable runtime state, builders, managers, scanners, service locators, routers, generalized lookup APIs, callbacks/events, mutable caches, a global element registry, or global mutable state.

## Acceptance criteria

- Element declarations preserve element ID, optional parent element ID, element kind, accessibility role, accessibility label, accessibility description, declared action-intent snapshots, and stable order index with read-only accessors.
- Element declaration lists preserve ordered element declarations and expose read-only accessors.
- Element declarations do not include DDNet, Platform, Module Runtime, Feature, Command, Binding, Adapter, Layout, Render, Theme, Localization, Editor, HUD, or Property dependencies.
- No property attachment, scene evaluation, tree validation, layout/render behavior, input/focus/capture/navigation behavior, command/activation behavior, module ownership binding, Platform composition, Module Runtime change, diagnostics generation, manager, scanner, service locator, generalized lookup API, callback registry, event bus, router, mutable cache, global element registry, or global mutable state is introduced.
- Debug and RelWithDebInfo `game-client` builds pass.

## Validation

- `git diff --check`
- Debug `game-client` build
- RelWithDebInfo `game-client` build
- Focused source-boundary inspection for forbidden dependencies and APIs

## Approved commit message

`feat(ui): add element declaration baseline`
