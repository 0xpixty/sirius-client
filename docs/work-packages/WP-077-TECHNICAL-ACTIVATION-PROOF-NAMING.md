# WP-077 - Technical Activation Proof Naming

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

- Renamed production technical activation command and behavior files/classes.
- Preserved command ID `command.test` and existing execution-count behavior.
- Preserved technical activation behavior state and counters.
- Updated production includes/construction, focused platform lifecycle tests, and CMake source entries.
- No source references remain to the old `test_activation_*` files or `CTestActivation*` classes.
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
- `src/sirius/platform/platform.cpp`
- `src/sirius/platform/commands/activation/test_activation_command.h/.cpp`
- `src/sirius/platform/features/activation/test_activation_behavior.h/.cpp`
- `src/test/sirius_platform_activation_lifecycle_test.cpp`
- `src/sirius/CMakeLists.txt`
- root `CMakeLists.txt`

## Goal

Rename the production technical activation proof objects so their names match their architectural role.

The current command and behavior are compiled into the production Sirius source set and owned by the built-in technical module, but their file and class names still say `test`. This creates avoidable confusion around whether they are product runtime proof infrastructure or unit-test-only helpers.

## Exact Scope

1. Rename `test_activation_command.h/.cpp` to `technical_activation_command.h/.cpp`.
2. Rename `CTestActivationCommand` to `CTechnicalActivationCommand`.
3. Rename `test_activation_behavior.h/.cpp` to `technical_activation_behavior.h/.cpp`.
4. Rename `CTestActivationBehavior` to `CTechnicalActivationBehavior`.
5. Update production includes and construction in `platform.cpp`.
6. Update focused platform lifecycle test includes and `dynamic_cast` types.
7. Update `src/sirius/CMakeLists.txt` and root `CMakeLists.txt` source entries.
8. Preserve the existing command, feature, activation, binding, and module IDs.

## Non-Goals

- No behavior changes.
- No new product feature or command.
- No new module registration mechanism.
- No removal of the built-in technical module.
- No changes to activation lifecycle, shutdown reconciliation, fan-out ordering, or exception semantics.
- No changes to test assertions except type/include names.
- No edits to protected dirty `src/sirius/platform/modules/module_registry.*`.

## Architecture Rationale

The built-in technical module remains proof infrastructure. Naming it as technical proof infrastructure is clearer than naming production classes as tests. The rename reduces future product catch-all pressure without introducing a new abstraction or changing ownership.

## Acceptance Criteria

1. No source references remain to `test_activation_command`, `test_activation_behavior`, `CTestActivationCommand`, or `CTestActivationBehavior`.
2. New technical activation command and behavior files are present in the same directories.
3. `CTechnicalActivationCommand` still owns ID `command.test` and preserves execution counting behavior.
4. `CTechnicalActivationBehavior` preserves activation/deactivation state and counters.
5. `CPlatform` still registers the technical command and behavior exactly as before, with only names changed.
6. Focused platform lifecycle tests compile against the renamed types.
7. No protected dirty files are changed or staged.
8. `git diff --check` passes.
9. Debug `game-client` builds.
10. RelWithDebInfo `game-client` builds.

## Validation

```powershell
rg -n "test_activation_command|test_activation_behavior|CTestActivationCommand|CTestActivationBehavior" src/sirius src/test CMakeLists.txt src/sirius/CMakeLists.txt
rg -n "technical_activation_command|technical_activation_behavior|CTechnicalActivationCommand|CTechnicalActivationBehavior" src/sirius src/test CMakeLists.txt src/sirius/CMakeLists.txt
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
cmake --build cmake-build-debug-visual-studio --target game-client
cmake --build cmake-build-relwithdebinfo-visual-studio --target game-client
```

Focused tests are source-updated, but execution remains limited by current local GTest availability unless a test-enabled build is already available.

## Suggested Commit Message

`refactor(platform): rename technical activation proof`
