# WP-073 - Feature Activation Shutdown/Restart Consistency

## Status

Completed and approved by Sirius Lead on 2026-07-13. Correction-only package required by `docs/architecture/AUDIT-WP-069-WP-072.md`. No user decision was required.

Internal Work Package review:

- Sirius Architect: `ARCHITECTURE_APPROVED`.
- Independent Reviewer: `APPROVED` after required platform test-observability correction.
- Devil's Advocate: `NO_BLOCKING_OBJECTION` after required platform test-observability correction.
- User decision: not required.

Implementation evidence:

- Lead implementation: complete.
- Validator subagent: operationally unavailable after permitted retries.
- Validator fallback: `VALIDATOR_FALLBACK_PASS`.
- Independent Reviewer: `APPROVED`.
- Devil's Advocate: `NO_BLOCKING_OBJECTION`.
- Documentation Guardian: operationally unavailable after retry; Lead documentation fallback found docs consistent after checkpoint corrections.
- `git diff --check`: passed with line-ending warnings only.
- Debug `game-client`: passed via Visual Studio developer environment.
- RelWithDebInfo `game-client`: passed via Visual Studio developer environment.
- Focused tests: source and CMake coverage added; not executed because the configured repository test path has no `testrunner` without GTest, and a separate `DOWNLOAD_GTEST=ON` build could not fetch GoogleTest from GitHub in the current environment.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/architecture/AUDIT-WP-069-WP-072.md`
- `docs/work-packages/WP-070-FEATURE-ARCHITECTURE-PLANNING.md`
- `docs/work-packages/WP-071-MODULE-OWNED-COMMAND-COMPOSITION.md`
- `docs/work-packages/WP-072-FEATURE-ACTIVATION-TRANSITION-CONSISTENCY.md`
- `src/sirius/platform/platform.h`
- `src/sirius/platform/platform.cpp`
- `src/sirius/platform/features/feature_activation.h`
- `src/sirius/platform/features/feature_activation_registry.h/.cpp`
- `src/sirius/platform/features/feature_activation_controller.h/.cpp`
- `src/sirius/platform/features/activation/feature_activation_behavior.h`
- `src/sirius/platform/features/activation/feature_activation_behavior_registry.h/.cpp`
- `src/sirius/platform/features/activation/test_activation_behavior.h/.cpp`
- `src/sirius/platform/modules/module_lifecycle.h/.cpp`
- `src/sirius/core/runtime/core_runtime.h/.cpp`
- `src/sirius/platform/commands/activation/test_activation_command.h`
- `src/test/sirius_feature_activation_controller_test.cpp`
- root `CMakeLists.txt` test sections

## Goal

Make feature activation state consistent with platform shutdown and same-instance restart before any real or stateful feature is added.

`CPlatform::Stop()` must reconcile every active platform-owned feature activation record before module Feature shutdown. Each applicable deactivation behavior receives one best-effort call. Because Stop is `noexcept`, a throwing deactivation is isolated per record, cannot terminate shutdown or prevent other records from being processed, and its record is forced Inactive. Activation fan-out does nothing outside a completely successful active lifecycle. A later Start on the same instance permits a fresh ordinary activation.

## Architectural Role and Ordering

`CPlatform` remains the lifecycle-aware composition root:

```text
Stop
  -> disconnect command activation observers
  -> best-effort reconcile all feature activation records/behaviors
  -> shut down module services, commands, Features, and Modules
  -> stop Core
```

`CFeatureActivationController` remains the sole transition coordinator and gains one shutdown-scoped non-throwing operation. `CFeatureActivationRegistry` remains passive storage; it exposes no public enumeration or lifecycle policy. Ordinary WP-072 transitions remain unchanged. Forced Inactive exists only at the `noexcept` shutdown boundary.

## Exact Scope

1. Modify `feature_activation_registry.h` only to friend `CFeatureActivationController` for private storage enumeration. Add no public method, callback enumeration API, container exposure, secondary index, or ordering structure.
2. Add exactly `CFeatureActivationController::DeactivateAllForShutdown() noexcept` in the controller header/implementation.
3. Visit every record without snapshot allocation and without structural registry mutation.
4. Skip inactive records. For each active record, use ordinary controller deactivation so the callback sees Active and successful deactivation commits Inactive per WP-072.
5. Catch exceptions separately per active record. On throw, force only that record Inactive, discard the exception at this shutdown boundary, and continue. Do not retry, translate, aggregate, or add logging dependencies.
6. Make repeated reconciliation callback-idempotent.
7. Leave cross-feature order unspecified; no callback may depend on another feature's deactivation order.
8. Update the behavior interface documentation: ordinary exceptions propagate and preserve pre-state; shutdown isolates per behavior, forces record Inactive, continues, and does not roll back behavior side effects. Existing non-reentry and pointer/registry stability restrictions apply.
9. Update `CPlatform::Stop()` to reset command activation handler/dispatcher, reconcile features, shut module lifecycle, then stop Core. Reconciliation runs safely for repeated Stop, Stop-before-Start, and Stop after failed Start.
10. Gate private `CPlatform::Activate()` and `Deactivate()` so they return without feature/command fan-out unless Core is running and module lifecycle initialized. This covers binding activation and public `DeactivateActivation()` centrally.
11. Preserve successful Start, already-started idempotency, initialization rollback, and command observer construction. Failed Start remains gated.
12. Add no public lifecycle query, feature registry accessor, production hook, status/result type, logger dependency, or failure collection.
13. Extend `src/test/sirius_feature_activation_controller_test.cpp` with shutdown cases.
14. Add `src/test/sirius_platform_activation_lifecycle_test.cpp`. It must observe command fan-out through the existing technical module command's `ExecutionCount()` using existing `CPlatform::Modules()` and test-only `dynamic_cast<CTestActivationCommand *>`.
15. Add a narrowly scoped non-public test observation peer for `CPlatform`, declared as a private friend in `platform.h` and defined only in `src/test/sirius_platform_activation_lifecycle_test.cpp`. The peer may read the existing technical feature activation record and `CTestActivationBehavior` counters/state. It must add no public runtime accessor, no production hook method, no mutable test control, and no generalized registry exposure.
16. Add the platform test alphabetically to root `TESTS` and add the exact existing source closure below to `TESTS_EXTRA`, retaining WP-072 entries without duplicates.
17. Do not edit `module_registry.h/.cpp`; tests use existing `Clear()` and never depend on the dirty `Remove()` work.

## Shutdown Semantics

| Record state | Behavior | Shutdown result |
|---|---|---|
| Inactive | any | no callback; remains Inactive |
| Active | absent | becomes Inactive |
| Active | succeeds | callback once while Active; then Inactive |
| Active | throws | exception isolated; forced Inactive; remaining records processed |
| Already reconciled | any | repeated call makes no callbacks |

Behavior side effects are not transactional. A throwing callback may partially change behavior-owned state. Forced Inactive prevents stale controller state suppressing a fresh activation after restart.

## Lifecycle Gating

- Before first successful Start: activation/deactivation fan-out does nothing.
- During complete active lifecycle: existing feature-first, optional-command fan-out remains.
- After failed Start: fan-out does nothing.
- During Stop: reconciliation calls the controller directly, bypassing the external gate.
- After Stop and between Stop/Start: fan-out does nothing.
- After same-instance restart: fan-out works and reconciled records transition normally.
- No concurrency or reentrant callback support is introduced.

## Ownership and Lifetime

- Existing owners remain unchanged.
- Friend access adds no ownership or public container exposure.
- Command observers are destroyed before feature reconciliation and module shutdown.
- Feature behavior objects and records remain alive through reconciliation.
- WP-072 callback stability restrictions preserve pointers during callbacks.

## Allowed Dependencies

- Existing Platform/Core/module lifecycle state queries.
- Existing feature activation types.
- Existing technical module/command only for test observability.
- Repository-native GoogleTest and exact existing production sources below.
- Standard exception handling.

## Forbidden Dependencies and Non-Goals

- No DDNet/adapter changes or Core-to-Platform dependency.
- No manager, router, lifecycle coordinator/service, event bus, callback system, transaction, transition enum, in-progress flag, generic iteration callback, module scan, feature dependency graph, ordering policy, generalized registration, or public container/lifecycle/test API.
- No public platform, registry, or behavior accessor for tests. The only allowed production-surface test observability change is the private `CPlatform` friend peer described in Exact Scope, and it must be read-only from tests.
- No change to ordinary WP-072 propagation, pre-state, commit-after-success, duplicate, reentrancy, or side-effect contracts.
- No product Feature/Command, UI, input-loop integration, fan-out redesign, resolver cleanup, audit reconstruction, technical proof removal, public API cleanup, or behavior rollback.
- No staging, commit, reset, checkout, push, or unrelated cleanup.

## Mandatory Tests

Extend controller tests:

1. Mixed active/inactive records including no behavior: only active behaviors deactivate once; all records finish Inactive.
2. Throwing deactivations: no exception escapes; every active behavior is attempted once without assuming iteration order; all records finish Inactive.
3. Repeated reconciliation adds no callback.
4. Existing ordinary throwing Deactivate test still propagates and remains Active.

Add platform lifecycle tests:

5. Before Start, matching input does not execute the technical command and leaves the technical feature activation record Inactive with activation/deactivation counts at zero.
6. Successful Start enables input; matching input increments command exactly once, sets the technical feature activation record Active, and increments the technical behavior activation count to one.
7. Stop disables input, reconciles the technical feature record to Inactive, and increments the technical behavior deactivation count to one before module Feature shutdown.
8. Repeated Stop is safe, keeps the record Inactive, and does not increment technical behavior deactivation or command counts again.
9. Same-instance restart re-enables input; matching input increments the same command to the next count, sets the feature record Active again, and increments the technical behavior activation count to two. This must fail if Stop omits feature reconciliation and restart treats the feature activation as a duplicate.
10. Clearing modules before Start makes Start false; fan-out remains gated, the technical feature record remains Inactive, behavior counts remain unchanged, and Stop is safe. Do not use `Remove()`.

## Exact CMake Test Linkage

The final Sirius `TESTS_EXTRA` entries required by these focused tests must be alphabetized, unique, and limited to:

- `src/sirius/core/config/config_registry.cpp`
- `src/sirius/core/events/event_dispatcher.cpp`
- `src/sirius/core/logging/logger.cpp`
- `src/sirius/core/runtime/core_runtime.cpp`
- `src/sirius/core/runtime/runtime_component_registry.cpp`
- `src/sirius/core/runtime/runtime_context.cpp`
- `src/sirius/core/runtime/runtime_lifecycle.cpp`
- `src/sirius/core/services/service_registry.cpp`
- `src/sirius/core/tasks/task_dispatcher.cpp`
- `src/sirius/core/tasks/task_queue.cpp`
- `src/sirius/platform/commands/activation/command_activation_handler.cpp`
- `src/sirius/platform/commands/activation/command_activation_resolver.cpp`
- `src/sirius/platform/commands/activation/test_activation_command.cpp`
- `src/sirius/platform/commands/command_context.cpp`
- `src/sirius/platform/commands/command_dispatcher.cpp`
- `src/sirius/platform/commands/command_lifecycle.cpp`
- `src/sirius/platform/commands/command_registry.cpp`
- `src/sirius/platform/features/activation/feature_activation_behavior_registry.cpp`
- `src/sirius/platform/features/activation/feature_activation_handler.cpp`
- `src/sirius/platform/features/activation/feature_activation_resolver.cpp`
- `src/sirius/platform/features/activation/test_activation_behavior.cpp`
- `src/sirius/platform/features/feature_activation_controller.cpp`
- `src/sirius/platform/features/feature_activation_registry.cpp`
- `src/sirius/platform/features/feature_context.cpp`
- `src/sirius/platform/features/feature_lifecycle.cpp`
- `src/sirius/platform/features/feature_registry.cpp`
- `src/sirius/platform/input/bindings/activation/binding_activation_adapter.cpp`
- `src/sirius/platform/input/bindings/activation/binding_activation_dispatcher.cpp`
- `src/sirius/platform/input/bindings/activation/binding_activation_registry.cpp`
- `src/sirius/platform/input/bindings/binding_matcher.cpp`
- `src/sirius/platform/input/bindings/binding_registry.cpp`
- `src/sirius/platform/input/dispatch/input_event_forwarder.cpp`
- `src/sirius/platform/input/source/buffered_input_source.cpp`
- `src/sirius/platform/modules/module.cpp`
- `src/sirius/platform/modules/module_context.cpp`
- `src/sirius/platform/modules/module_lifecycle.cpp`
- `src/sirius/platform/modules/module_registry.cpp`
- `src/sirius/platform/modules/services/module_service_context.cpp`
- `src/sirius/platform/modules/services/module_service_lifecycle.cpp`
- `src/sirius/platform/modules/services/module_service_registry.cpp`
- `src/sirius/platform/platform.cpp`

Do not add DDNet sources or `${SIRIUS_CLIENT}` wholesale. If an additional unresolved Sirius symbol is mechanically discovered, stop for WP correction/re-review rather than casually broadening linkage.

## Acceptance Criteria

1. Stop reconciles active feature records before module Feature shutdown.
2. Command observers reset before reconciliation/shutdown.
3. Core stops after reconciliation and module shutdown.
4. Every active record is visited without snapshot allocation or structural mutation.
5. Successful shutdown deactivation observes Active then commits Inactive.
6. Throwing shutdown deactivation cannot escape the `noexcept` boundary.
7. Throwing record is forced Inactive and does not prevent other attempts.
8. Inactive records and repeated shutdown do not repeat callbacks.
9. Ordinary Deactivate still propagates and retains Active on throw.
10. All WP-072 ordinary transition semantics remain.
11. Platform fan-out is disabled unless Core running and module lifecycle initialized.
12. Binding activation and `DeactivateActivation()` share the private gate.
13. Start enables, Stop disables, and same-instance restart re-enables fan-out.
14. Failed Start remains gated; Stop-before-Start/repeated Stop are safe.
15. No public platform/registry/test API is added; the only test observability change is a private read-only `CPlatform` friend peer scoped to the platform lifecycle test.
16. No ordering guarantee or reentrancy support is claimed.
17. Focused controller and platform lifecycle tests pass.
18. CMake test/source entries are alphabetized, exact, and unique.
19. WP-071 ownership remains intact.
20. Protected module registry files retain only their pre-existing diff.
21. No forbidden scope or abstraction enters.
22. `git diff --check` passes.
23. `testrunner` builds and both focused suites pass.
24. Debug `game-client` builds.
25. RelWithDebInfo `game-client` builds.

## Validation

```powershell
git status --short --branch
git diff --check
git diff -- src/sirius/platform/features/feature_activation_registry.h
git diff -- src/sirius/platform/features/feature_activation_controller.h src/sirius/platform/features/feature_activation_controller.cpp
git diff -- src/sirius/platform/features/activation/feature_activation_behavior.h
git diff -- src/sirius/platform/platform.h src/sirius/platform/platform.cpp
git diff -- src/test/sirius_feature_activation_controller_test.cpp src/test/sirius_platform_activation_lifecycle_test.cpp CMakeLists.txt
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
rg -n "DeactivateAllForShutdown|catch|SetState" src/sirius/platform/features/feature_activation_controller.*
rg -n "IsRunning|IsInitialized|FeatureActivationHandler|CommandActivationHandler" src/sirius/platform/platform.cpp
rg -n "DeactivateAllForShutdown|EXPECT_NO_THROW|ExecutionCount|Start|Stop|Clear" src/test/sirius_*activation*test.cpp
cmake --build <test-enabled-build-directory> --target testrunner
& "<test-enabled-build-directory>\testrunner.exe" "--gtest_filter=FeatureActivationController.*:PlatformActivationLifecycle.*"
cmake --build <debug-build-directory> --target game-client
cmake --build <relwithdebinfo-build-directory> --target game-client
```

GoogleTest must be available; report an external acquisition blocker rather than weakening tests or adding production hooks.

## Focused Self-Review

Verify shutdown-before-module ordering, command observer disconnection, dual lifecycle gate, direct controller reconciliation, per-record exception isolation/forced Inactive/continuation, no allocation/mutation/order promise, idempotency, unchanged WP-072 ordinary semantics/contracts, existing-command fan-out observability, private friend-only feature activation observability, exact source closure, no forbidden expansion, and untouched protected module registry files.

## Implementer Report Format

```text
IMPLEMENTATION RESULT
- COMPLETE | BLOCKED

FILES CHANGED
- ...

SHUTDOWN SEMANTICS
- successful active record:
- inactive record:
- throwing behavior:
- continuation across records:
- repeated shutdown:

PLATFORM LIFECYCLE
- pre-Start gate:
- active gate:
- Stop ordering:
- post-Stop gate:
- same-instance restart:
- failed Start:

TESTS / BUILDS
- testrunner and focused suites:
- Debug game-client:
- RelWithDebInfo game-client:

SCOPE CONFIRMATION
- ordinary WP-072 semantics unchanged:
- public API unchanged except shutdown-scoped controller operation:
- no public test API/order/reentrancy abstraction:
- private platform test peer read-only and test-scoped:
- module_registry.* untouched:
- no staged/committed files:

RISKS / NOTES
- ...
```

## Suggested Commit Message

`fix(features): reconcile activation state on shutdown`

Do not stage or commit.

## Sequencing

WP-073 is the mandatory audit correction loop. Do not design or implement WP-074 until WP-073 passes Validator and Independent Reviewer and receives Lead approval.
