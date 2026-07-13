# WP-078 - Technical Activation Proof IDs

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

- Renamed internal technical proof command, feature, activation, binding, and synthetic input IDs away from `.test` names.
- Preserved module ID `module.sirius.technical`.
- Preserved command execution-count behavior.
- Updated focused platform lifecycle tests to use the new IDs/key.
- No old `.test` technical proof IDs remain in `src/sirius` or Sirius tests.
- Protected dirty `src/sirius/platform/modules/module_registry.*` files were not changed by this WP.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.
- Focused tests: source-updated but not executed because local GTest remains unavailable in the configured build.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `docs/architecture/AUDIT-WP-073-WP-076.md`
- `docs/work-packages/WP-077-TECHNICAL-ACTIVATION-PROOF-NAMING.md`
- `src/sirius/platform/platform.cpp`
- `src/sirius/platform/commands/activation/technical_activation_command.cpp`
- `src/test/sirius_platform_activation_lifecycle_test.cpp`

## Goal

Rename the production technical activation proof IDs and input key away from `.test` names.

WP-077 renamed the production proof files/classes from test-oriented names to technical names. The remaining internal IDs still include `.test`, which continues the same ambiguity inside runtime wiring.

## Exact Scope

1. Rename the technical command ID from `command.test` to a technical proof ID.
2. Rename the technical feature activation ID from `feature.activation.test` to a technical proof ID.
3. Rename the neutral activation ID from `activation.command.test` to a technical proof ID.
4. Rename the binding ID from `binding.activation.test` to a technical proof ID.
5. Rename the synthetic input key from `input.activation.test` to a technical proof key.
6. Update focused platform lifecycle tests to use the new IDs/key.
7. Preserve module ID `module.sirius.technical`.

## Non-Goals

- No behavior changes.
- No product feature or command.
- No new registration mechanism.
- No activation fan-out, lifecycle, shutdown, resolver, dispatcher, registry, or module changes.
- No DDNet adapter changes.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Selected IDs

- Command: `command.sirius.technical.activation`
- Feature: `feature.sirius.technical.activation`
- Activation: `activation.sirius.technical`
- Binding: `binding.sirius.technical.activation`
- Input key: `input.sirius.technical.activation`

These names stay explicit, local, and technical-proof scoped.

## Acceptance Criteria

1. No production Sirius Platform source keeps `command.test`, `feature.activation.test`, `activation.command.test`, `binding.activation.test`, or `input.activation.test`.
2. Platform technical proof wiring uses the selected technical IDs.
3. Platform lifecycle tests use the selected technical IDs/key.
4. `CTechnicalActivationCommand` preserves execution-count behavior and only changes its ID string.
5. No protected dirty files are changed or staged.
6. `git diff --check` passes.
7. Debug `game-client` builds.
8. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "command\\.test|feature\\.activation\\.test|activation\\.command\\.test|binding\\.activation\\.test|input\\.activation\\.test" src/sirius src/test
rg -n "command\\.sirius\\.technical\\.activation|feature\\.sirius\\.technical\\.activation|activation\\.sirius\\.technical|binding\\.sirius\\.technical\\.activation|input\\.sirius\\.technical\\.activation" src/sirius src/test
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are source-updated, but execution remains limited by current local GTest availability unless a test-enabled build is already available.

## Suggested Commit Message

`refactor(platform): rename technical activation proof ids`
