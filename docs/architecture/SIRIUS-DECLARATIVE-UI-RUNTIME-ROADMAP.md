# Sirius Declarative UI Runtime — Roadmap

## Status

Planning baseline only. Implementation is not started.

This roadmap follows the final Module Runtime readiness audit. It must be architecturally reviewed before the first Declarative UI Runtime Work Package is implemented.

## Milestone purpose

Create a minimal Sirius-owned Declarative UI Runtime foundation that can later support HUD, editor, theme, dockable windows, and product UI systems without coupling product UI directly to DDNet menu/component internals.

The first-generation goal is not to build a full UI product. It is to establish the smallest durable runtime boundary for declared UI surfaces and read-only rendering/input context flow.

## Repository evidence

Current UI and rendering facts:

- `CMenus` owns main menu rendering and page routing.
- `CUi`, `CUIRect`, `CScrollRegion`, and `CListBox` are existing UI primitives.
- Sirius-specific menu/style extensions already live under `src/game/client/components/sirius/`.
- DDNet graphics, text rendering, and menu state remain DDNet-owned adapter/runtime concerns.
- Sirius Platform and Module Runtime now provide explicit module composition, descriptors, lifecycle ordering, typed contracts, and diagnostics.

## Architectural constraints

- Do not redesign Core, Platform, Module Runtime, or DDNet adapter foundations.
- Do not begin HUD Editor, Theme System, Plugin SDK, dockable windows, replay tools, or gameplay UI product work in this milestone’s first Work Packages.
- Do not introduce service locators, global mutable UI registries, scanners, dynamic discovery, event buses, generalized routers, observers, or managers without concrete pressure and explicit approval.
- UI ownership must remain explicit. DDNet adapter code may translate/render, but Sirius UI declarations must not depend on DDNet implementation details.
- UI runtime state must be inspectable through passive snapshots where possible.
- Module-owned UI contributions must eventually compose through typed declarations/contracts rather than ambient lookup.

## Proposed bounded roadmap

### WP-109 — UI Runtime Concept Boundary

Define the minimal vocabulary and ownership boundary for Declarative UI Runtime:

- UI surface identity;
- UI node identity;
- immutable UI surface descriptor;
- non-rendering declaration value types;
- no renderer, layout engine, editor, theme system, or module integration yet.

Purpose: establish names and immutable value semantics before behavior.

### WP-110 — UI Runtime Definition Boundary

Pair UI surface descriptors with explicit construction/declaration factories, mirroring the proven Module Runtime definition pattern only where repository pressure justifies it.

Purpose: keep UI declarations explicit and composition-owned without scanning or discovery.

### WP-111 — Deterministic UI Surface Registration Plan

Add an explicit registration plan for UI surface definitions:

- deterministic order;
- duplicate/empty ID rejection;
- no rendering;
- no DDNet adapter calls.

Purpose: make future module-owned UI contributions deterministic.

### WP-112 — Passive UI Tree Snapshot Baseline

Introduce the smallest read-only snapshot model for declared UI trees:

- surface ID;
- node IDs;
- parent/child relationships if needed by the first declaration model;
- no layout calculation;
- no styling/theme resolution;
- no rendering commands.

Purpose: provide inspectable UI structure before runtime behavior.

### WP-113 — Platform Composition Boundary for UI Runtime

Wire UI runtime composition through Platform as an explicit passive composition value.

Purpose: prove Platform can compose UI runtime declarations without becoming a UI manager or leaking module internals.

### WP-114 — DDNet Adapter Read-only UI Runtime Query

Expose a narrow read-only query path through the DDNet adapter for the passive UI runtime snapshot.

Purpose: create the future rendering foundation without implementing renderer, menus, HUD, editor, or theme behavior.

## Architectural review

Lead fallback review: approved for planning only.

Rationale:

- The roadmap directly follows the completed Module Runtime foundation.
- It starts with immutable declarations and deterministic composition before behavior.
- It avoids product UI work, rendering, theme, editor, plugin, and HUD scope.
- It does not require a manager, scanner, service locator, dynamic discovery, or event system.
- Each proposed WP is small enough to validate independently.

Implementation remains paused until the first UI Runtime Work Package is explicitly selected and reviewed under SDS.
