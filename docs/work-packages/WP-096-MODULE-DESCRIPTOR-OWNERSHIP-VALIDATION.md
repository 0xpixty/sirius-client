# WP-096 - Module Descriptor Ownership Validation

Date: 2026-07-13

## Milestone

Foundation V2: Sirius Module Runtime.

## Roadmap position

WP-093 added descriptors.
WP-094 added definitions.
WP-095 added deterministic registration plan evidence.
WP-096 adds descriptor-backed validation for declared feature, command, and module-service ownership.

This is the last required pre-graph ownership check before dependency/lifecycle graph work can safely begin.

## Repository evidence

- Module descriptors declare feature, command, and module-service IDs.
- Modules still own actual registries for features, commands, and module services.
- Status completeness had local checks for specific feature/command presence.
- Platform can now validate constructed modules before inserting them into `CModuleRegistry`.

## Scope

- Add `IsModuleDescriptorOwnershipValid(const IModule&)`.
- Validate both directions:
  - every descriptor-declared feature/command/module-service exists in the module's registries;
  - every actually registered feature/command/module-service is declared by the descriptor.
- Reject duplicate descriptor declarations.
- Use validation during Platform module registration before `CModuleRegistry::Register()`.
- Use validation in Status completeness.
- Add focused tests and CMake source entries.

## Non-goals

- No diagnostics snapshot or structured validation report.
- No dependency graph.
- No lifecycle graph.
- No typed contracts.
- No import/export resolution.
- No module manager.
- No scanner/discovery system.
- No runtime unloading.
- No service locator/global lookup.
- No UI, HUD editor, theme system, plugin SDK, gameplay module, DDNet, rendering, protocol, config, or input work.

## Ownership and boundaries

- Validation lives under `sirius::platform::modules`.
- It validates one constructed module against its own descriptor.
- It does not own modules, mutate registries, discover modules, or decide lifecycle order.
- Platform remains the composition root and uses the validator before registry insertion.

## Acceptance criteria

- Matching descriptor and actual registry ownership passes.
- Missing actual ownership for a declared ID fails.
- Undeclared actual ownership fails.
- Duplicate descriptor declarations fail.
- Platform rejects invalid constructed modules before registry insertion.
- Status completeness uses descriptor-backed ownership validation.
- No new manager/router/scanner/service-location mechanism is introduced.
- Focused validation tests are wired into CMake for GTest-enabled environments.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Internal review

`ARCHITECT_FALLBACK_APPROVED`

The WP directly follows the approved Module Runtime roadmap and is bounded to descriptor-backed ownership validation.

`DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`

The validator is intentionally boolean-only and single-module scoped. It creates no diagnostics model, dependency graph, lifecycle policy, runtime owner, manager, scanner, or lookup mechanism.

## Validation plan

- `git diff --check`
- Debug `game-client` build through the Visual Studio developer environment
- RelWithDebInfo `game-client` build through the Visual Studio developer environment
- focused C++ tests when GTest targets are available

## Approved commit message

`feat(modules): validate module descriptor ownership`
