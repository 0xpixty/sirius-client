# WP-072 - Feature Activation Transition Consistency

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Internal Work Package review:

- Sirius Architect: `ARCHITECTURE_APPROVED`.
- Independent Reviewer: `WP_APPROVED` after required test-linkage and contract corrections.
- Devil's Advocate: `NO_BLOCKING_OBJECTION` after required reentrancy, pointer-stability, and side-effect-boundary corrections.
- Architecture Audit: not required before WP-072; reassess cadence after WP-072 completes.
- User decision: not required.

Final implementation evidence:

- Implementer: `COMPLETE`.
- Validator: `PASS` against all 20 acceptance criteria.
- Independent Reviewer: `APPROVED`.
- Devil's Advocate: `NO_BLOCKING_OBJECTION`.
- `git diff --check`: passed.
- `testrunner`: built successfully.
- Focused `FeatureActivationController.*` tests: 5/5 passed.
- Debug `game-client`: passed.
- RelWithDebInfo `game-client`: passed.

Implemented result:

- Duplicate activation and deactivation requests succeed without repeating callbacks.
- Behavior executes against the pre-transition activation record; state commits only after successful return.
- A throwing callback propagates its original exception and leaves the activation record in its pre-call state.
- The behavior contract forbids controller/handler reentry and structural mutation or destruction of the relevant registries, controller, or executing behavior during callbacks.
- Callback side effects are not transactionally rolled back.
- Focused tests are linked through the root CMake test target.
- The pre-existing `module_registry.*` diff remained out of scope and untouched.

## Audit Decision

An Architecture Audit is not required before WP-072. WP-069 through WP-071 are three approved packages since the reported WP-068 audit checkpoint. WP-071 implemented an existing ownership model and introduced no audit trigger.

Reassess audit cadence after WP-072 because it would be the fourth approved package since WP-068.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/work-packages/WP-070-FEATURE-ARCHITECTURE-PLANNING.md`
- `docs/work-packages/WP-071-MODULE-OWNED-COMMAND-COMPOSITION.md`
- `src/sirius/platform/features/feature_activation.h`
- `src/sirius/platform/features/feature_activation_state.h`
- `src/sirius/platform/features/feature_activation_registry.h`
- `src/sirius/platform/features/feature_activation_registry.cpp`
- `src/sirius/platform/features/feature_activation_controller.h`
- `src/sirius/platform/features/feature_activation_controller.cpp`
- `src/sirius/platform/features/activation/feature_activation_behavior.h`
- `src/sirius/platform/features/activation/feature_activation_behavior_registry.h`
- `src/sirius/platform/features/activation/feature_activation_behavior_registry.cpp`
- `src/sirius/platform/features/activation/feature_activation_handler.h`
- `src/sirius/platform/features/activation/feature_activation_handler.cpp`
- `src/sirius/platform/features/activation/test_activation_behavior.h`
- `src/sirius/platform/features/activation/test_activation_behavior.cpp`
- `src/test/test.cpp`
- representative GoogleTest files under `src/test/`
- the `TESTS`, `TESTS_EXTRA`, `testrunner`, and `run_cxx_tests` sections of `CMakeLists.txt`

## Goal

Make feature activation and deactivation idempotent and activation-record-consistent before activation behavior operates on a lifecycle-managed concrete feature.

A behavior callback runs while the activation record retains its pre-transition state. The controller commits the requested state only after the callback returns successfully. If the callback throws, the original exception propagates and the activation record remains in its exact pre-call state.

This guarantee covers only controller-owned activation-record state. It does not claim rollback of side effects already performed inside a throwing behavior.

## Architectural Role

`CFeatureActivationController` remains the sole coordinator of activation-record state and behavior execution:

```text
requested transition
    -> resolve activation record
    -> return success for an already-satisfied request
    -> find optional behavior
    -> invoke behavior while record retains pre-state
    -> commit requested state only after successful return
```

Registries remain passive storage. Behaviors remain responsible for entry or exit work. The handler remains an activation-ID adapter.

Reentrant transitions and registry mutation during a behavior callback are outside the supported contract. This WP introduces no in-progress state, transition stack, transaction object, or reentrancy coordinator.

## Exact Scope

1. Modify `src/sirius/platform/features/feature_activation_controller.cpp`.
2. Modify `src/sirius/platform/features/activation/feature_activation_behavior.h` only to document the callback contract:
   - callbacks must not directly or indirectly invoke the feature activation controller or handler;
   - callbacks must not structurally mutate, replace, assign, move from, or destroy either registry or the active controller while executing; `Register()`, `Remove()`, and `Clear()` are specific forbidden examples;
   - callbacks may throw, but the controller guarantees only activation-record consistency, not rollback of callback side effects.
3. Do not change public method signatures.
4. `Activate()` must return `false` for a missing record; return `true` without behavior when already active; invoke optional behavior while the record remains inactive; set active only after successful return; propagate an exception unchanged while leaving inactive; and set active immediately when no behavior exists.
5. `Deactivate()` must return `false` for a missing record; return `true` without behavior when already inactive; invoke optional behavior while the record remains active; set inactive only after successful return; propagate an exception unchanged while leaving active; and set inactive immediately when no behavior exists.
6. Do not catch and translate, log, swallow, retry, or replace behavior exceptions. No catch is needed merely to preserve state because commit follows successful callback completion.
7. Add `src/test/sirius_feature_activation_controller_test.cpp`.
8. Update root `CMakeLists.txt` by adding the new test to the alphabetized `TESTS` list and adding these existing files to `TESTS_EXTRA`:
   - `src/sirius/platform/features/activation/feature_activation_behavior_registry.cpp`
   - `src/sirius/platform/features/feature_activation_controller.cpp`
   - `src/sirius/platform/features/feature_activation_registry.cpp`
   - `src/sirius/platform/features/feature_registry.cpp`
9. Test-only behavior doubles may track call counts and throw a test-local exception with a distinguishable payload, and must exist only in the new test file.
10. Add no failure flags or test hooks to production behavior classes.
11. Do not edit `src/sirius/platform/modules/module_registry.h` or `.cpp`; their `Remove()` diff is pre-existing user work.

## Callback Preconditions

During `IFeatureActivationBehavior::Activate()` or `Deactivate()`:

- The callback must not call `CFeatureActivationController::Activate()`, `Deactivate()`, or `IsActive()`.
- The callback must not invoke `CFeatureActivationHandler` directly or indirectly.
- The callback must not structurally mutate, replace, assign, move from, swap, or destroy either registry; this includes `Register()`, `Remove()`, and `Clear()`.
- The callback must not replace, move from, or destroy the active controller while its call is in progress.
- The callback must not destroy or replace itself.

These restrictions preserve activation-record and behavior pointers held across callback execution. Opposite- and same-direction reentry are both forbidden. No behavior under this WP may claim reentrancy support.

## Ownership and Lifetime

- The activation registry continues to own activation records by value.
- The behavior registry continues to uniquely own behavior objects.
- The controller continues to hold non-owning references to both registries.
- No new ownership or lifetime layer is introduced.
- The controller may retain current activation-record and behavior pointers across a callback only because the callback contract forbids registry mutation.
- An exception changes no ownership.
- Callback side effects are behavior-owned and are not transactionally rolled back.

## Transition Semantics

| Pre-state | Request | Behavior call | Successful result | Behavior throws |
|---|---|---:|---|---|
| Inactive | Activate | once | Active | record remains Inactive; original exception propagates |
| Active | Activate | never | Active | not applicable |
| Active | Deactivate | once | Inactive | record remains Active; original exception propagates |
| Inactive | Deactivate | never | Inactive | not applicable |
| Missing record | either | never | unchanged; return `false` | not applicable |
| Record without behavior | transition | none | requested state; return `true` | not applicable |

No reentrant transition semantics are defined or supported.

## Mandatory Mechanical Tests

`src/test/sirius_feature_activation_controller_test.cpp` must use existing GoogleTest/`testrunner` infrastructure and cover:

1. Missing record: both operations return `false`, and an unrelated behavior is not called.
2. Missing behavior: inactive activates and active deactivates with correct resulting states.
3. Success and duplicates: first activation/deactivation calls the respective method exactly once; duplicate requests succeed without increasing counts.
4. Activation exception: a test-local exception with known payload reaches the caller unchanged; activation count is one, deactivation count zero, record remains inactive.
5. Deactivation exception: after successful activation, configured deactivation throws the test-local exception unchanged; activation count remains one, deactivation count is one, record remains active.

Tests must not exercise forbidden reentry or callback-driven registry mutation as supported behavior.

## Allowed Dependencies

- Existing feature activation state, registry, behavior registry, and controller types.
- Repository-native GoogleTest under `src/test`.
- Standard-library facilities for test-local doubles and exceptions.
- The four existing Sirius implementation files listed for `TESTS_EXTRA`.

## Forbidden Dependencies

- Core, DDNet, input, bindings, commands, modules, or `CPlatform`.
- New transition enum, in-progress flag, transaction type, guard framework, manager, router, registry, event, or callback system.
- New public API, reentrant transition policy, or registry mutation during behavior execution.
- Cross-feature ordering, batching, or rollback.
- Exception conversion, swallowing, retry, or logging.
- Claims that callback side effects are rolled back.
- Production test hooks, lifecycle/shutdown changes, or dependence on dirty `CModuleRegistry::Remove()` work.

## Non-Goals

- No concrete `IFeature`, command-to-feature reference, module-owned activation behavior registry, active-feature shutdown policy, deactivate-all operation, lifecycle gating, fan-out redesign, behavior result-status redesign, product behavior, UI, DDNet integration, obsolete resolver cleanup, or historical audit reconstruction.
- No staging, commit, or push.

## Acceptance Criteria

1. Missing records return `false` without behavior execution.
2. Records without behavior transition successfully.
3. Already-satisfied requests return `true` without repeated behavior execution.
4. Successful transitions invoke applicable behavior exactly once and then commit requested state.
5. Throwing activation leaves the record inactive.
6. Throwing deactivation leaves the record active.
7. Original exception type and distinguishing payload propagate unchanged.
8. No rollback of behavior-owned side effects is claimed.
9. Callback reentry and structural mutation, replacement, assignment, move, or destruction of the registries or active controller are explicitly forbidden in the behavior contract.
10. No reentrancy guarantee remains in WP or implementation.
11. All five mandatory scenarios pass.
12. No public signature changes.
13. No new abstraction or ownership layer.
14. Resolver, handler, bindings, commands, modules, and platform fan-out remain unchanged.
15. `module_registry.h/.cpp` retain only their pre-existing diff.
16. `git diff --check` passes.
17. `testrunner` builds.
18. Focused feature activation controller tests pass.
19. Debug `game-client` builds.
20. RelWithDebInfo `game-client` builds.

## Validation

```powershell
git status --short --branch
git diff --check
git diff -- src/sirius/platform/features/feature_activation_controller.cpp
git diff -- src/sirius/platform/features/activation/feature_activation_behavior.h
git diff -- src/test/sirius_feature_activation_controller_test.cpp CMakeLists.txt
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp

rg -n "CFeatureActivationController::Activate|CFeatureActivationController::Deactivate|SetState" src/sirius/platform/features/feature_activation_controller.cpp
rg -n "re-enter|registry|Register|Remove|Clear|side effect" src/sirius/platform/features/activation/feature_activation_behavior.h
rg -n "FeatureActivationController|EXPECT_|ASSERT_|throw" src/test/sirius_feature_activation_controller_test.cpp

cmake --build <test-enabled-build-directory> --target testrunner
& "<test-enabled-build-directory>\testrunner.exe" "--gtest_filter=FeatureActivationController.*"
cmake --build <debug-build-directory> --target game-client
cmake --build <relwithdebinfo-build-directory> --target game-client
```

A test-enabled build must have `SERVER=ON` and GoogleTest available, matching the existing root CMake condition. If GoogleTest acquisition is blocked, report a concrete validation blocker; do not make tests optional or replace them with production hooks.

## Focused Self-Review

Verify state changes only after successful callbacks; duplicates skip callbacks; exceptions are not caught/replaced unnecessarily; tests verify type, payload, state, and exact counts; no reentrancy support is claimed; callback-time structural mutation/replacement/assignment/move/destruction of registries or controller is forbidden; no side-effect rollback is claimed; CMake links exactly the four required isolated Sirius implementation sources; no public interface/lifecycle/routing/ownership changes occur; and WP-071 plus pre-existing `module_registry.*` changes remain intact.

## Implementer Report Format

```text
IMPLEMENTATION RESULT
- COMPLETE | BLOCKED

FILES CHANGED
- ...

TRANSITION SEMANTICS
- missing activation:
- missing behavior:
- duplicate activate:
- duplicate deactivate:
- activation exception:
- deactivation exception:
- callback preconditions:

TESTS
- testrunner build:
- focused controller tests:
- scenarios covered:

BUILDS
- Debug game-client:
- RelWithDebInfo game-client:
- unrelated blockers:

SCOPE CONFIRMATION
- public API unchanged:
- no reentrancy abstraction:
- no production test hooks:
- module_registry.* untouched:
- no staged or committed files:

RISKS / NOTES
- ...
```

## Suggested Commit Message

`fix(features): keep activation transitions consistent`

Do not stage or commit.

## Sequencing Note

After WP-072, reassess Architecture Audit cadence before generating another implementation package.
