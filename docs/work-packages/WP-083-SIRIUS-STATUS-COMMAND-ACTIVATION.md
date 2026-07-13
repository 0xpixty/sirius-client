# WP-083 - Sirius Status Command Activation

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Added a status-specific command activation resolver.
- Added status command dispatcher/handler bound only to `module.sirius.status`.
- Registered open/close activation IDs to the status command IDs.
- Added source-neutral input bindings for status open/close command activations.
- Preserved the technical command activation path and the status feature activation path.
- No router, scanner, manager, service locator, global command registry, UI, DDNet, or adapter change was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `docs/architecture/AUDIT-WP-077-WP-081.md`
- `docs/work-packages/WP-080-SIRIUS-STATUS-MODULE-FEATURE.md`
- `docs/work-packages/WP-082-SIRIUS-STATUS-ACTIVATION-BINDING.md`
- `src/sirius/platform/platform.h`
- `src/sirius/platform/platform.cpp`

## Goal

Wire the Sirius Status module-owned open/close commands to source-neutral activation IDs without introducing generalized command routing.

WP-080 created module-owned status commands. WP-083 gives those commands explicit status-module activation dispatch. The implementation is intentionally local and bounded: one status command resolver, one dispatcher bound to `module.sirius.status`, one handler, and two bindings.

## Exact Scope

1. Add a status command activation resolver owned by `CPlatform`.
2. Add a status command dispatcher/handler bound only to `module.sirius.status`.
3. Register:
   - `activation.sirius.status.open` -> `command.sirius.status.open`
   - `activation.sirius.status.close` -> `command.sirius.status.close`
4. Register source-neutral bindings:
   - `input.sirius.status.open` -> `activation.sirius.status.open`
   - `input.sirius.status.close` -> `activation.sirius.status.close`
5. Preserve the existing technical command activation path.
6. Preserve existing feature activation path for `activation.sirius.status`.

## Non-Goals

- No command router.
- No module scanning.
- No global command registry.
- No manager/service locator/generalized dispatcher.
- No UI/DDNet/adapter/config/networking changes.
- No changes to command or feature behavior.
- No public `CPlatform` API.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

The first real feature now has concrete pressure for command activation, but only for one known module. A generalized router would be premature. This WP keeps dispatch explicit:

```text
activation.sirius.status.open
  -> status command resolver
  -> status command dispatcher bound to module.sirius.status
  -> COpenSiriusStatusCommand
```

This introduces no module iteration and no lookup across modules.

## Acceptance Criteria

1. Status command activation resolver maps open/close activation IDs to status command IDs.
2. Status command dispatcher is bound only to `module.sirius.status`.
3. Status command handler is active only after successful module lifecycle initialization.
4. Stop resets status command handler/dispatcher before feature shutdown.
5. Technical command activation path still works as before.
6. Feature activation path still works as before.
7. No router/scanner/manager/service locator/global command registry is introduced.
8. Protected dirty files remain untouched and unstaged.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "StatusCommand|activation\\.sirius\\.status\\.(open|close)|input\\.sirius\\.status\\.(open|close)|command\\.sirius\\.status\\.(open|close)" src/sirius/platform/platform.*
rg -n "router|scanner|scan|CommandManager|ServiceLocator|global command" src/sirius/platform/platform.*
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are not added in this WP because local GTest remains unavailable; required client builds remain mandatory.

## Suggested Commit Message

`feat(commands): activate sirius status commands`
