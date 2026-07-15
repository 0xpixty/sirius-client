# WP-095 - Module Runtime Registration Plan

Date: 2026-07-13

## Milestone

Foundation V2: Sirius Module Runtime.

## Roadmap position

WP-093 added descriptors.
WP-094 added definitions.
WP-095 adds deterministic registration evidence: an explicit module registration plan over definitions.

This is the next bounded Module Runtime step before descriptor-backed validation, dependency graph, lifecycle graph, diagnostics, and typed contracts.

## Repository evidence

- `CPlatform` still registered the technical and Status modules through separate local calls.
- `CModuleRegistry` already preserves registration order for initialized module instances.
- WP-094 definitions provide pre-construction descriptors and factories.
- The missing runtime foundation is a pre-construction deterministic list of definitions that can later be validated before instances are created.

## Scope

- Add `CModuleRegistrationPlan` under `src/sirius/platform/modules/`.
- The plan stores `CModuleDefinition` entries in explicit insertion order.
- The plan rejects:
  - empty module IDs;
  - definitions without factories;
  - duplicate module IDs.
- Platform assembles one local plan for the current technical and Status modules.
- Platform registers modules by iterating `DefinitionsInRegistrationOrder()`.
- Existing module registry ownership and lifecycle remain unchanged.
- Add focused plan tests and CMake source entries.

## Non-goals

- No module manager.
- No scanner or dynamic discovery.
- No runtime unloading.
- No service locator or global registry.
- No dependency graph.
- No lifecycle graph.
- No diagnostics snapshot.
- No typed contracts or import/export resolution.
- No descriptor-backed implementation ownership validation yet.
- No UI, HUD editor, theme system, plugin SDK, gameplay module, DDNet, rendering, protocol, config, or input work.

## Ownership and boundaries

- Registration plan is a value owned by Platform composition while registering built-in modules.
- `CModuleRegistry` remains the owner of constructed module instances.
- Definitions remain construction descriptions.
- The plan is not a runtime owner and does not expose module lookup to product code.

## Acceptance criteria

- `CModuleRegistrationPlan` exists.
- It preserves explicit definition order.
- It rejects duplicate, empty-ID, and empty-factory definitions.
- Platform registers technical and Status modules through one deterministic plan.
- Existing technical and Status module IDs and behavior are preserved.
- No new manager/router/scanner/service-location mechanism is introduced.
- Focused plan tests are wired into CMake for GTest-enabled environments.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Internal review

`ARCHITECT_FALLBACK_APPROVED`

The WP directly follows the approved Module Runtime roadmap: descriptors -> definitions -> deterministic registration.

`DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`

The plan is intentionally pre-graph and pre-validation. It does not own modules after construction, does not scan for modules, does not resolve dependencies, and does not alter lifecycle ordering beyond making the existing explicit order inspectable before construction.

## Validation plan

- `git diff --check`
- Debug `game-client` build through the Visual Studio developer environment
- RelWithDebInfo `game-client` build through the Visual Studio developer environment
- focused C++ tests when GTest targets are available

## Approved commit message

`feat(modules): add deterministic module registration plan`
