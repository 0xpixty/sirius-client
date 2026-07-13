# WP-084 - Sirius Status Module Composition

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Architect consultant: `ARCHITECT_UNAVAILABLE` after one silent instance and one silent retry.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Reviewer consultant: `REVIEWER_UNAVAILABLE` after one silent instance and one silent retry.
- Devil's Advocate consultant: `DEVIL_UNAVAILABLE` after one silent instance and one silent retry.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Added `src/sirius/platform/modules/status/sirius_status_module.*`.
- Status-local composition now owns construction/registration of:
  - `CSiriusStatusFeature`;
  - `CSiriusStatusActivationBehavior`;
  - `COpenSiriusStatusCommand`;
  - `CCloseSiriusStatusCommand`.
- Status-local helpers provide Status module, feature, feature activation, command, and command activation IDs.
- `CPlatform::ConfigureStatusModule()` now calls `CreateSiriusStatusModule()` and keeps explicit feature activation, command activation, input binding, dispatcher/handler, and module-registry wiring.
- No router, scanner, manager, service locator, generalized factory registry, global command registry, UI, DDNet, adapter, config, networking, or gameplay change was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `docs/architecture/AUDIT-WP-082-WP-083.md`
- `docs/work-packages/WP-080-SIRIUS-STATUS-MODULE-FEATURE.md`
- `docs/work-packages/WP-081-SIRIUS-STATUS-ACTIVATION-BEHAVIOR.md`
- `docs/work-packages/WP-082-SIRIUS-STATUS-ACTIVATION-BINDING.md`
- `docs/work-packages/WP-083-SIRIUS-STATUS-COMMAND-ACTIVATION.md`
- `src/sirius/platform/platform.h`
- `src/sirius/platform/platform.cpp`

## Goal

Move Sirius Status module object assembly and Status-owned identifiers out of `CPlatform` into a narrow Status-local module composition helper.

This is a cleanup WP after the first real module-owned feature and commands have landed. It reduces product-specific construction detail inside Platform without introducing a manager, service locator, router, scanner, or generalized module composition system.

## Exact Scope

1. Add a Status-local module composition header/source under `src/sirius/platform/modules/status/`.
2. The Status-local composition code may expose only narrow Status-specific helpers:
   - Status module ID.
   - Status feature ID.
   - Status feature activation ID.
   - Status open/close command IDs.
   - Status open/close command activation IDs.
   - A function that creates and returns the fully assembled `module.sirius.status` module.
3. The Status-local module creation function must create/register:
   - `CSiriusStatusFeature`.
   - `CSiriusStatusActivationBehavior`.
   - `COpenSiriusStatusCommand`.
   - `CCloseSiriusStatusCommand`.
4. `CPlatform` must call the Status-local creation helper and remain responsible for:
   - registering feature activation records/resolver mappings;
   - registering command activation resolver mappings;
   - registering input bindings;
   - registering the completed module in the platform module registry;
   - constructing dispatchers/handlers after module lifecycle initialization.
5. Update `src/sirius/CMakeLists.txt` for new files.
6. Update this WP status/evidence after validation.

## Non-Goals

- No new manager.
- No service locator.
- No command router.
- No module scanner.
- No generalized module factory registry.
- No global command registry.
- No public `CPlatform` API.
- No behavior change to Status feature, activation behavior, commands, bindings, or dispatch.
- No UI, DDNet, adapter, config, networking, or gameplay integration.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

`CPlatform` remains the composition root, but it no longer needs to spell out every Status-owned object construction detail. The Status module can own assembly of its Feature, activation behavior, and Commands as one local product slice.

The important boundary stays intact:

```text
CPlatform
  -> calls Status-local module creation helper
  -> wires activation/input mappings explicitly
  -> registers the completed module
```

There is still no lookup across modules, no module iteration for command routing, and no generalized construction registry.

## Acceptance Criteria

1. Status-owned IDs are provided by Status-local composition code instead of repeated as raw literals in `CPlatform` where practical.
2. Status module creation is local to `src/sirius/platform/modules/status/`.
3. `CPlatform::ConfigureStatusModule()` no longer directly constructs Status feature, behavior, open command, or close command objects.
4. `CPlatform` still explicitly wires Status feature activation, Status command activation, and Status input bindings.
5. Runtime lifecycle and activation order are unchanged.
6. No router/scanner/manager/service locator/global registry is introduced.
7. Protected dirty `src/sirius/platform/modules/module_registry.*` files remain untouched and unstaged.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "CreateSiriusStatusModule|SiriusStatus.*Id|SiriusStatus.*ActivationId" src/sirius/platform
rg -n "router|scanner|scan|CommandManager|ServiceLocator|global command|factory registry" src/sirius/platform
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused GoogleTest execution remains unavailable in this local infrastructure unless the existing configured builds expose it; required client builds remain mandatory.

## Suggested Commit Message

`refactor(platform): localize sirius status module composition`
