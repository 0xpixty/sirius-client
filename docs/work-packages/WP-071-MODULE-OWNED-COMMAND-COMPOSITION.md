# WP-071 - Module-Owned Command Composition Foundation

## Status

Completed and approved by Sirius Lead on 2026-07-13.

Final evidence:

- Validator: `PASS` after the lifetime fix and re-validation.
- Independent Reviewer: `APPROVED` after the lifetime fix and re-review.
- Devil's Advocate: `NO_BLOCKING_OBJECTION`.
- Documentation Guardian: required checkpoint updates were applied before Lead approval.
- `git diff --check`: passed.
- Debug `game-client`: passed.
- RelWithDebInfo `game-client`: passed.

Implemented scope:

- Added passive `CModule`, owning feature, command, and module-service registries by value.
- Registered built-in `module.sirius.technical` before module lifecycle initialization.
- Moved unique ownership of `CTestActivationCommand` into that module's command registry.
- Removed platform-local `m_ActivationCommandRegistry` and bound dispatch explicitly to the module-owned registry only while lifecycle state is active.
- Added no product behavior.
- Preserved the pre-existing, out-of-scope `CModuleRegistry::Remove()` working-tree diff without editing those files.

## Read First

- `AGENTS.md`
- `.codex/AGENTS.md`
- `.codex/docs/CURRENT_STATE.md`
- `.codex/docs/PROJECT_CONTEXT.md`
- `.codex/docs/ARCHITECTURE_MAP.md`
- `.codex/docs/BUILD_AND_TEST.md`
- `docs/work-packages/WP-070-FEATURE-ARCHITECTURE-PLANNING.md`
- `src/sirius/platform/modules/module.h`
- `src/sirius/platform/modules/module_id.h`
- `src/sirius/platform/modules/module_registry.h`
- `src/sirius/platform/modules/module_lifecycle.cpp`
- `src/sirius/platform/modules/services/module_service_registry.h`
- `src/sirius/platform/features/feature_registry.h`
- `src/sirius/platform/commands/command_registry.h`
- `src/sirius/platform/commands/command_dispatcher.h`
- `src/sirius/platform/commands/activation/command_activation_handler.h`
- `src/sirius/platform/commands/activation/test_activation_command.h`
- `src/sirius/platform/platform.h`
- `src/sirius/platform/platform.cpp`
- `src/sirius/CMakeLists.txt`

## Goal

Establish the first concrete module composition boundary and prove that a command already used by the activation pipeline is owned and lifecycle-managed by that module, rather than by a parallel platform-local command registry. This is a foundation/composition WP and adds no user-facing product behavior.

## Architectural Role

Introduce one small, passive concrete implementation of `IModule` that owns its feature, command, and module-service registries and exposes them only through the existing contract. Use that module as the composition owner of the existing technical activation command proof. `CPlatform` remains responsible only for construction, explicit registration, and activation wiring.

## Exact Scope

1. Add `src/sirius/platform/modules/module.cpp`.
2. Extend `module.h` with `CModule final : public IModule`, or add a narrowly named adjacent header only if repository include conventions require it.
3. Store by value one immutable `CModuleId`, one `CFeatureRegistry`, one `CCommandRegistry`, and one `CModuleServiceRegistry`.
4. Accept the ID at construction, expose registries through `IModule`, implement successful no-op module initialization and no-op shutdown, be non-copyable/non-movable, and contain no dynamic discovery.
5. Update `src/sirius/CMakeLists.txt` as needed.
6. Update `CPlatform` to create one built-in technical module with stable non-empty ID `module.sirius.technical`, register `CTestActivationCommand` in its command registry before lifecycle initialization, register the module in `m_Modules`, dispatch command activation against that module-owned registry, remove `m_ActivationCommandRegistry`, preserve existing activation/command IDs, and guarantee reference lifetimes by construction order.
7. Make command or module registration failure explicit. It must not leave activation wiring referring to destroyed or unowned storage; a small private composition helper and/or standard exception is allowed.
8. Preserve current technical binding, feature-activation behavior, and command-execution proof; only command ownership moves.
9. Do not edit `src/sirius/platform/modules/module_registry.h` or `.cpp`; their `Remove()` diff is pre-existing user work and outside WP-071.

## Ownership and Lifetime

- `CPlatform` owns `CModuleRegistry`.
- `CModuleRegistry` uniquely owns the concrete module.
- The module owns all three registries by value.
- Its command registry uniquely owns `CTestActivationCommand`.
- Dispatcher/handler references are non-owning, established only after successful registration, and outlived by the referenced module and registry.
- Existing module lifecycle ordering governs the command.
- No global state, service locator, module scan, or ambient string lookup is allowed.

## Allowed Dependencies

- Concrete module to existing module/feature-registry/command-registry/module-service-registry APIs.
- `CPlatform` to the concrete module and existing registration/activation APIs.
- Command dispatcher to the explicitly supplied module-owned command registry.

## Forbidden Dependencies

- Core to Platform or DDNet.
- Module implementation to DDNet, input, bindings, activation routing, or `CPlatform`.
- Feature/command implementations to module lookup, global platform access, or binding internals.
- New manager, catalog, router, aggregate registry, service locator, event bus, or callback registry.
- Execution-time scanning across modules.
- New public `CPlatform` registry convenience APIs.
- Dependence on the dirty `CModuleRegistry::Remove()` change.

## Non-Goals

- No real user-facing Feature or Command.
- No product-domain selection, feature package, module activation-registration API, or multi-module command router.
- No feature activation ownership, binding cleanup, exception-policy, active-feature shutdown, restart/lifecycle, DDNet, or UI redesign.
- No technical proof cleanup, tests-framework introduction, or documentation-state reconciliation.
- No staging or committing.

## Acceptance Criteria

1. A passive concrete `IModule` owns exactly the existing module-level registries.
2. No duplicate ID, registry, lifecycle, manager, or service abstraction is introduced.
3. `CPlatform` no longer contains `m_ActivationCommandRegistry`.
4. The registered module's command registry uniquely owns the technical activation command.
5. Activation dispatch uses that specific registry via explicit composition, without module scanning.
6. The module is registered before lifecycle initialization.
7. The command participates in module command lifecycle initialization and shutdown.
8. Failure cannot leave dangling references or a partially registered command path.
9. Feature activation and binding behavior are otherwise unchanged.
10. `module_registry.h/.cpp` retain only their pre-existing user diff.
11. No Core/DDNet dependency violation is introduced.
12. `git diff --check` passes.
13. Debug `game-client` build passes.
14. RelWithDebInfo `game-client` build passes.

## Validation

```powershell
git status --short --branch
git diff --check
git diff -- src/sirius/platform/modules/module_registry.h src/sirius/platform/modules/module_registry.cpp
rg -n "m_ActivationCommandRegistry|CTestActivationCommand|CCommandDispatcher|module.sirius.technical" src/sirius/platform
rg -n "public IModule|CFeatureRegistry|CCommandRegistry|CModuleServiceRegistry" src/sirius/platform/modules
cmake --build <debug-build-directory> --target game-client
cmake --build <relwithdebinfo-build-directory> --target game-client
```

If build directories do not exist, configure separate directories with the documented Ninja/toolchain settings. Report unrelated GoogleTest/network failures separately when `game-client` itself builds.

## Focused Self-Review

Verify passive module responsibility, platform composition-only behavior, unique command ownership, absence of module scanning/new public platform APIs, declaration/construction/destruction lifetime safety, command lifecycle participation, safe failure paths, and preservation of the dirty `module_registry.*` files.

## Suggested Commit Message

`feat(modules): compose activation command in module`

Do not stage or commit.
