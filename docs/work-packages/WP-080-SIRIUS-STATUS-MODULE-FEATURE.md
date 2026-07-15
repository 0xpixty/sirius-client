# WP-080 - Sirius Status Module Feature

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Design verdict:

- User architecture decision: after platform composition cleanup, begin the first real module-owned feature and its module-owned commands.
- Lead architecture fallback: `ARCHITECT_FALLBACK_APPROVED`.
- Lead internal WP review: approved.
- Lead implementation: complete.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Reviewer fallback: `REVIEWER_FALLBACK_APPROVED`.
- Devil's Advocate fallback: `DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`.
- Documentation fallback: `DOCUMENTATION_FALLBACK_CONSISTENT`.
- User decision: not required.

Implementation evidence:

- Added `CSiriusStatusFeature : IFeature` with initialized/open state.
- Added module-owned `COpenSiriusStatusCommand` and `CCloseSiriusStatusCommand`.
- Added explicit `module.sirius.status` composition in `CPlatform`.
- Commands hold direct `CSiriusStatusFeature&` references created by composition.
- No activation mapping, input binding, command router, scanner, manager, service locator, UI, DDNet, or adapter change was added.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.
- Focused tests: not added/executed because local GTest remains unavailable; this first feature slice was mechanically validated by source inspection and required client builds.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `docs/work-packages/WP-070-FEATURE-ARCHITECTURE-PLANNING.md`
- `docs/work-packages/WP-079-PLATFORM-MODULES-TEST-SEAM-CLEANUP.md`
- `src/sirius/platform/features/feature.h`
- `src/sirius/platform/commands/command.h`
- `src/sirius/platform/modules/module.h`
- `src/sirius/platform/platform.cpp`

## Goal

Add the first real module-owned Sirius feature and its module-owned commands without adding routing or activation integration.

The feature is `CSiriusStatusFeature`, a small product-shaped status panel state owner. It owns initialized/open state and exposes explicit feature methods. The owning module registers open/close commands that hold direct references to the feature through composition.

## Exact Scope

1. Add `CSiriusStatusFeature : IFeature`.
2. Add `COpenSiriusStatusCommand : ICommand`.
3. Add `CCloseSiriusStatusCommand : ICommand`.
4. Register a new `module.sirius.status` module in `CPlatform` composition.
5. Register the status feature in that module's feature registry.
6. Register both status commands in that module's command registry.
7. Preserve explicit feature-before-command composition so command references are lifetime-safe.
8. Update Sirius source lists.

## IDs

- Module: `module.sirius.status`
- Feature: `feature.sirius.status`
- Open command: `command.sirius.status.open`
- Close command: `command.sirius.status.close`

## Non-Goals

- No activation mapping for the new commands.
- No input binding.
- No UI, DDNet, renderer, menu, config, persistence, networking, or adapter changes.
- No command router, manager, service locator, scanner, generalized module registration, or global command registry.
- No changes to technical activation proof behavior.
- No public `CPlatform` feature/module accessor.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

This is the smallest real feature slice that proves the WP-070 model:

```text
module.sirius.status
  owns CSiriusStatusFeature
  owns COpenSiriusStatusCommand -> CSiriusStatusFeature&
  owns CCloseSiriusStatusCommand -> CSiriusStatusFeature&
```

The commands do not discover the feature. Platform constructs the module and wires object references explicitly. The feature owns its state. The module owns both the feature and commands. Platform remains composition-only.

## Acceptance Criteria

1. Status feature implements `IFeature` and owns its own initialized/open state.
2. Open/close commands implement `ICommand` and hold explicit `CSiriusStatusFeature&` references.
3. Status module registers the feature before constructing/registering commands.
4. Status module owns both feature and command registries through existing `CModule`.
5. Feature and commands participate in existing module lifecycle.
6. No activation route or input binding exists for the new commands in this WP.
7. No manager/router/service locator/generalized registration is introduced.
8. Protected dirty `module_registry.*` files remain untouched and unstaged.
9. `git diff --check` passes.
10. Debug `game-client` builds.
11. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "module\\.sirius\\.status|feature\\.sirius\\.status|command\\.sirius\\.status\\.(open|close)|CSiriusStatusFeature|COpenSiriusStatusCommand|CCloseSiriusStatusCommand" src/sirius
rg -n "FeatureManager|CommandManager|ServiceLocator|router|scanner|scan" src/sirius/platform/features/status src/sirius/platform/commands/status src/sirius/platform/platform.cpp
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are not added in this WP because local GTest remains unavailable; the feature/command slice is mechanically validated through source inspection and both required client builds.

## Suggested Commit Message

`feat(platform): compose sirius status feature module`
