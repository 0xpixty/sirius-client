# WP-089 - Sirius Status Command Activation Contract

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Architect consultant: `ARCHITECT_UNAVAILABLE` after one silent instance and one silent retry.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Reviewer consultant: `REVIEWER_UNAVAILABLE` after one silent instance and one silent retry.
- Devil's Advocate consultant: `DEVIL_UNAVAILABLE` after one silent instance and one silent retry.
- Lead internal design/review fallback: approved.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: continue the Sirius Status/module-owned command path after WP-088.

Implementation evidence:

- Added `modules::status::CSiriusStatusCommandActivation`.
- Added `modules::status::SiriusStatusCommandActivations()`.
- The Status-local activation pair list preserves:
  - `activation.sirius.status.open` -> `command.sirius.status.open`
  - `activation.sirius.status.close` -> `command.sirius.status.close`
  - `activation.sirius.status.toggle` -> `command.sirius.status.toggle`
- `CPlatform::ConfigureStatusModule()` now iterates the Status-local pair list and calls the existing `ConfigureStatusCommandActivations(...)`.
- No manager, router, scanner, observer, event system, service locator, generalized registry, UI, console, rendering, activation behavior, or input binding was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed after serial retry of an operational Visual Studio PDB concurrency failure.
- RelWithDebInfo `game-client`: passed.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-084-WP-086.md`
- `docs/work-packages/WP-087-SIRIUS-STATUS-MODULE-CONTRACT-CHECK.md`
- `docs/work-packages/WP-088-SIRIUS-STATUS-ADAPTER-QUERY.md`
- `src/sirius/platform/modules/status/sirius_status_module.*`
- `src/sirius/platform/platform.*`

## Goal

Move the Sirius Status command activation mapping list into the Status module contract and have Platform consume that explicit module-owned list.

This keeps Platform responsible for composition while reducing repeated Status-specific command activation knowledge in `CPlatform::ConfigureStatusModule()`.

## Exact Scope

1. Add a small immutable value type under `sirius::platform::modules::status` that pairs:
   - `activation::CActivationId`
   - `commands::CCommandId`
2. Add a Status-local function returning the complete current Sirius Status command activation pairs:
   - open activation -> open command
   - close activation -> close command
   - toggle activation -> toggle command
3. Update `CPlatform::ConfigureStatusModule()` to iterate the Status-local activation pair list and call the existing `ConfigureStatusCommandActivations(...)`.
4. Preserve the existing explicit registration path and failure semantics.
5. Update this WP status/evidence after validation.

## Non-Goals

- No UI.
- No console commands.
- No rendering.
- No config changes.
- No gameplay behavior.
- No network/protocol changes.
- No global services.
- No managers.
- No routers.
- No observers.
- No event systems.
- No generalized command routing, command scanning, module scanning, or service location.
- No new activation behavior.
- No new input bindings.
- No changes to `CCommandActivationResolver`, `CCommandActivationHandler`, or dispatcher semantics.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.
- No changes to the WP-088 adapter/query surface.

## Architecture Rationale

The Status module already owns Status command IDs and activation IDs. Platform must still wire activation mappings explicitly, but it should not repeat the same Status command activation list in multiple places as Status grows.

The bounded cleanup is to expose a Status-owned immutable activation pair list and keep Platform as the explicit composition caller:

```text
CPlatform::ConfigureStatusModule()
  -> modules::status::SiriusStatusCommandActivations()
  -> ConfigureStatusCommandActivations(pair.ActivationId(), pair.CommandId())
```

This is not scanning, routing, discovery, or service location. It is a fixed Status-local list consumed by the existing explicit composition code.

## Acceptance Criteria

1. Status command activation pair definitions live in `src/sirius/platform/modules/status/sirius_status_module.*`.
2. Platform no longer repeats each Status command activation mapping one-by-one.
3. Platform still explicitly registers all current Status command activations through `ConfigureStatusCommandActivations(...)`.
4. Open, close, and toggle Status command activation mappings are preserved exactly.
5. Existing failure semantics are preserved when registration fails.
6. No manager/router/scanner/observer/event system/service locator/generalized registry is introduced.
7. Protected dirty `src/sirius/platform/modules/module_registry.*` files remain untouched and unstaged unless a separately approved WP covers them.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "SiriusStatusCommandActivations|CSiriusStatusCommandActivation|ConfigureStatusCommandActivations" src/sirius/platform
rg -n "router|scanner|scan|CommandManager|ServiceLocator|observer|event system|EventBus|MessageBus|global service|query registry" src/sirius/platform
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused GoogleTest execution remains unavailable in this local infrastructure unless existing configured builds expose it; required client builds remain mandatory.

## Suggested Commit Message

`refactor(platform): localize status command activation contract`
