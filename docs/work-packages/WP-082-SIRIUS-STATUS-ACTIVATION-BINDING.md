# WP-082 - Sirius Status Activation Binding

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

- Added source-neutral binding `binding.sirius.status.activation`.
- Binding emits `activation.sirius.status` from `input.sirius.status.activation`.
- Existing technical activation binding was preserved.
- `ConfigureBindings()` now accepts the input key explicitly.
- No status command activation mapping, command router, scanner, manager, service locator, UI, DDNet, or adapter change was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `docs/architecture/AUDIT-WP-077-WP-081.md`
- `docs/work-packages/WP-081-SIRIUS-STATUS-ACTIVATION-BEHAVIOR.md`
- `src/sirius/platform/platform.cpp`
- `src/sirius/platform/input/bindings/activation/binding_activation_dispatcher.cpp`

## Goal

Wire a source-neutral input binding to the Sirius Status feature activation ID.

The status feature and activation behavior already exist. This WP adds one explicit binding so a matching input event emits `activation.sirius.status`. Existing feature activation fan-out opens the status feature. Command activation remains unchanged and safely ignores this activation because no status command activation mapping exists yet.

## Exact Scope

1. Make `CPlatform::ConfigureBindings()` accept the input key explicitly.
2. Preserve the existing technical activation binding and key.
3. Add a new binding:
   - Binding ID: `binding.sirius.status.activation`
   - Activation ID: `activation.sirius.status`
   - Input key: `input.sirius.status.activation`
   - Action: `Pressed`
4. Do not add any command activation mapping for status commands.

## Non-Goals

- No command routing for status commands.
- No module scanning or command dispatcher generalization.
- No router, manager, service locator, or global command registry.
- No UI/DDNet/adapter/config/networking changes.
- No changes to status feature behavior or lifecycle.
- No public `CPlatform` API.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

Bindings remain source-neutral. The binding layer only maps an input key to `activation.sirius.status`; it does not know features or commands. `CPlatform` still performs explicit local composition.

## Acceptance Criteria

1. Existing technical activation binding behavior is preserved.
2. Status activation binding is registered with `activation.sirius.status`.
3. The status binding uses `input.sirius.status.activation`.
4. No status command activation mapping is added.
5. No command router/scanner/generalized dispatcher is introduced.
6. Protected dirty files remain untouched and unstaged.
7. `git diff --check` passes.
8. Debug `game-client` builds.
9. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "binding\\.sirius\\.status\\.activation|input\\.sirius\\.status\\.activation|activation\\.sirius\\.status" src/sirius/platform/platform.cpp
rg -n "command\\.sirius\\.status\\.(open|close)" src/sirius/platform/platform.cpp
rg -n "router|scanner|scan|CommandManager|ServiceLocator" src/sirius/platform/platform.cpp
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are not added in this WP because local GTest remains unavailable; required client builds remain mandatory.

## Suggested Commit Message

`feat(input): bind sirius status activation`
