# WP-085 - Sirius Status Toggle Command

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Architect consultant: `ARCHITECT_UNAVAILABLE` after one silent instance and one silent retry.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Reviewer consultant: `APPROVED`.
- Devil's Advocate consultant: `DEVIL_UNAVAILABLE` after one silent instance and one silent retry.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Added `CSiriusStatusFeature::Toggle()`.
- Added `CToggleSiriusStatusCommand`.
- Registered the toggle command in the existing Status-local module composition helper.
- Added Status-local toggle command and activation ID helpers.
- Wired toggle activation through the existing Status command activation resolver/dispatcher/handler.
- Added source-neutral `input.sirius.status.toggle` binding.
- Added the toggle command files to `src/sirius/CMakeLists.txt`.
- No new dispatcher/handler family, Platform fan-out, router, scanner, manager, service locator, generalized registry, UI, DDNet, adapter, config, networking, or gameplay change was added.
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
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-082-WP-083.md`
- `docs/work-packages/WP-084-SIRIUS-STATUS-MODULE-COMPOSITION.md`
- `src/sirius/platform/features/status/sirius_status_feature.*`
- `src/sirius/platform/commands/status/open_sirius_status_command.*`
- `src/sirius/platform/commands/status/close_sirius_status_command.*`
- `src/sirius/platform/modules/status/sirius_status_module.*`
- `src/sirius/platform/platform.*`

## Goal

Add a module-owned Sirius Status toggle command using the existing Status module command activation path.

This continues the first real module-owned feature slice without adding another Platform command fan-out, router, manager, service locator, scanner, UI integration, or DDNet integration.

## Exact Scope

1. Add `CSiriusStatusFeature::Toggle()`:
   - returns `false` when the feature is not initialized;
   - opens the feature when closed;
   - closes the feature when open;
   - preserves the existing open/close count semantics by delegating to `Open()`/`Close()` or equivalent behavior.
2. Add `CToggleSiriusStatusCommand` under `src/sirius/platform/commands/status/`.
3. Register the toggle command in the existing Status-local module composition helper.
4. Add Status-local helper IDs for:
   - `command.sirius.status.toggle`;
   - `activation.sirius.status.toggle`.
5. Wire the toggle activation through the existing Status command activation resolver/dispatcher/handler in `CPlatform`.
6. Add one source-neutral input binding:
   - `input.sirius.status.toggle` -> `activation.sirius.status.toggle`.
7. Update `src/sirius/CMakeLists.txt`.
8. Update this WP status/evidence after validation.

## Non-Goals

- No new dispatcher or handler family.
- No new Platform command fan-out.
- No command router.
- No module scanner.
- No manager, service locator, generalized registry, or generalized routing.
- No UI, DDNet, adapter, config, networking, or gameplay integration.
- No changes to technical activation proof behavior.
- No public `CPlatform` API.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

The existing Status command activation path already dispatches commands owned by `module.sirius.status`. A Status toggle command is a small product-shaped behavior addition that stays inside that module:

```text
input.sirius.status.toggle
  -> activation.sirius.status.toggle
  -> existing Status command resolver
  -> existing Status command dispatcher bound to module.sirius.status
  -> CToggleSiriusStatusCommand
  -> CSiriusStatusFeature::Toggle()
```

The WP adds one command to the existing module and one mapping to the existing wiring path. It does not add a generalized router or any new cross-module lookup.

## Acceptance Criteria

1. `CSiriusStatusFeature::Toggle()` toggles open/closed state only when initialized.
2. Toggle behavior preserves current open/close count semantics.
3. `CToggleSiriusStatusCommand` is owned by `module.sirius.status`.
4. Toggle command initialization follows the existing Status command pattern.
5. Toggle activation uses the existing Status command activation resolver/dispatcher/handler.
6. No new dispatcher/handler family or Platform fan-out is added.
7. No router/scanner/manager/service locator/global registry is introduced.
8. Protected dirty `src/sirius/platform/modules/module_registry.*` files remain untouched and unstaged.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "Toggle|toggle|command\\.sirius\\.status\\.toggle|activation\\.sirius\\.status\\.toggle|input\\.sirius\\.status\\.toggle" src/sirius/platform
rg -n "StatusCommandDispatcher|StatusCommandActivationHandler" src/sirius/platform/platform.*
rg -n "router|scanner|scan|CommandManager|ServiceLocator|global command|factory registry" src/sirius/platform
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused GoogleTest execution remains unavailable in this local infrastructure unless existing configured builds expose it; required client builds remain mandatory.

## Suggested Commit Message

`feat(commands): add sirius status toggle command`
