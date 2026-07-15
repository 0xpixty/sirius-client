# WP-070 - Feature Architecture Planning

## 1. Executive Summary

This document defines the architecture rules for future Sirius Features.

The current foundation already separates modules, features, commands, input bindings, and activation. Real product features must build on that separation instead of introducing a new manager, global registry, or cross-feature control layer.

The preferred model is:

```text
Module
    owns Feature registry
    owns Command registry
    owns Module service registry

Feature
    owns product state and product behavior

Command
    requests a specific product operation

Activation
    maps neutral activation ids to feature or command consumers

Platform
    owns composition and wiring only
```

The main rule is simple: a feature owns its own product state and behavior, but it does not own routing, global runtime access, input collection, command dispatch, activation dispatch, or other features.

## 2. Definition of Sirius Feature

A Sirius Feature is a cohesive product capability owned inside a module.

Examples of future features include a server browser shell, replay assistant, settings panel, theme editor, notification center, or HUD panel. A feature should represent a user-facing capability or a coherent product behavior, not a general framework service.

A feature owns:

- its private product state;
- its domain rules;
- its initialized runtime resources;
- its feature-local models and view-facing state;
- its response to lifecycle initialization and shutdown;
- configuration values that belong specifically to that feature.

A feature may expose:

- a minimal `IFeature` lifecycle surface;
- feature-specific methods used by commands or activation behavior when explicitly wired by composition;
- read-only state snapshots when required by UI or diagnostics.

A feature must not own:

- global runtime;
- DDNet input;
- DDNet rendering or low-level engine APIs;
- command routing;
- activation routing;
- binding matching;
- other features;
- platform lifecycle;
- module lifecycle;
- service lookup mechanisms.

Feature state must have one clear owner. If state is shared between features, it is probably not feature state and should be modeled as a module service, platform service, or explicit data source in a later work package.

## 3. Feature vs Module

A Module is a composition boundary. A Feature is product behavior inside that boundary.

Module responsibilities:

- own feature registry;
- own command registry;
- own module service registry;
- initialize and shut down module-owned components through platform lifecycle;
- group related product capabilities;
- provide explicit registration during composition.

Feature responsibilities:

- own one product capability;
- implement feature lifecycle;
- maintain feature-local state;
- expose only the minimal behavior required by its commands, activation behavior, or UI surface.

Ownership rules:

- The module owns the feature registry.
- The platform owns the module registry and module lifecycle execution.
- Feature lifecycle is executed through the module lifecycle.
- Feature activation state is owned by the platform activation composition until a module-owned activation registration model is introduced.
- Feature commands should be registered in the owning module command registry, not in a platform-wide product command registry.

Modules should not become "god modules". A module groups related features, but it should not centralize all product behavior or bypass feature ownership.

## 4. Lifecycle Model

Feature lifecycle and feature activation are different concepts.

Lifecycle answers:

```text
Is the feature constructed, initialized, and able to participate in the platform?
```

Activation answers:

```text
Is this initialized feature currently active from the product user's point of view?
```

Rules:

- A feature may be initialized while inactive.
- Activation may only target a feature that has been registered for activation.
- Real activation should happen after the owning module and feature lifecycle have initialized.
- Shutdown should not leave a feature active.
- If a feature is active during shutdown, composition should deactivate it or guarantee that shutdown safely releases active state before destruction.
- Activation must not replace initialization.
- Deactivation must not replace shutdown.
- `IFeature::Initialize()` prepares stable resources and state.
- `IFeature::Shutdown()` releases lifecycle resources.
- `IFeatureActivationBehavior::Activate()` performs active-state entry behavior.
- `IFeatureActivationBehavior::Deactivate()` performs active-state exit behavior.

The current lifecycle initializes features before commands within a module. That is compatible with command execution depending on initialized feature state.

## 5. Activation Model

Activation remains a neutral boundary.

The intended feature activation flow is:

```text
CActivationId
    -> CFeatureActivationHandler
    -> CFeatureActivationResolver
    -> CFeatureActivationController
    -> IFeatureActivationBehavior
```

`CActivationId` does not know whether the target is a feature, command, UI action, script, or future consumer. Feature-specific mapping belongs to `CFeatureActivationResolver`.

`IFeatureActivationBehavior` should contain only active-state entry and exit behavior. It may call into a feature when explicitly constructed with a reference to that feature by composition, but it must not discover features dynamically.

Belongs in `IFeature`:

- long-lived product state;
- initialization and shutdown;
- domain operations;
- feature-owned models;
- feature-owned configuration state.

Belongs in `IFeatureActivationBehavior`:

- active/inactive transition behavior;
- focus/open/close-like product state transition;
- temporary active-state setup or cleanup;
- calls into the owning feature when required.

Does not belong in activation behavior:

- binding matching;
- command dispatch;
- feature lookup;
- module lookup;
- DDNet input collection;
- global routing.

## 6. Command Ownership Model

Preferred architecture: commands are owned by modules and features, not by Platform.

The platform-local activation command registry is acceptable only as a technical proof. Real commands should belong to the module that owns the feature or product behavior they operate on.

Reasons:

- module-owned commands participate in module lifecycle;
- command ownership stays close to the feature state being changed;
- command shutdown order remains deterministic;
- platform does not become a product command surface;
- command registration does not become a global dumping ground.

Lifecycle implications:

- Commands should be initialized after their owning feature state is initialized.
- Commands should be shut down before or alongside the owning feature state according to module lifecycle rules.
- A command may hold a non-owning reference to its owning feature if composition guarantees lifetime.
- A command must not discover the feature through a service locator or global registry.

Activation mapping:

- Binding activation may produce a neutral `CActivationId`.
- Command activation resolver may map that id to a `CCommandId`.
- Command activation handler dispatches to a command registry.
- For real features, that registry should be module-owned or explicitly exposed through composition, not an unrelated platform-owned product registry.

## 7. Registration Model

Current state:

- `CPlatform` owns composition.
- Private platform registration methods contain technical proof registrations.
- WP-069 split those proof registrations by responsibility.

Future direction:

- Real features should be registered by explicit module composition.
- A module should register its features and commands into its own registries.
- Platform should register modules and wire cross-cutting activation/binding mappings.
- Feature activation registration should be explicit and close to the feature package or module composition.
- Binding registration should remain separate from feature implementation.

Allowed registration shapes:

- module constructor or module composition method registers feature-owned objects;
- explicit platform composition method wires built-in feature packages;
- feature package helper functions may create feature, command, activation behavior, and mapping data when they do not own global state.

Disallowed registration shapes:

- `FeatureManager`;
- `RegistrationManager`;
- `ActivationManager`;
- service locator;
- global command registry for all product behavior;
- feature self-registration through global state.

Registration should remain boring, explicit, and local.

## 8. Dependency Rules

Allowed feature dependencies:

- `sirius::platform::features` APIs;
- `sirius::platform::commands` APIs when defining feature-owned commands;
- `sirius::platform::modules` context or module services when passed explicitly;
- `sirius::core` interfaces exposed through context;
- feature-local value types and models.

Forbidden feature dependencies:

- DDNet engine headers;
- DDNet adapter headers;
- input collection;
- binding matcher/dispatcher internals;
- activation dispatcher internals;
- unrelated features;
- global runtime access;
- service locator-style lookup.

Allowed command dependencies:

- command APIs;
- explicit non-owning references to the feature or service the command operates on;
- command context;
- small value types required by the command.

Forbidden command dependencies:

- DDNet input;
- binding internals;
- activation routing internals;
- unrelated feature registries;
- global platform access.

Allowed activation behavior dependencies:

- activation behavior API;
- explicit non-owning reference to the owning feature when composition guarantees lifetime;
- small value types required for active-state transitions.

Forbidden activation behavior dependencies:

- input bindings;
- command dispatcher;
- module registry;
- DDNet adapter;
- feature lookup by string.

## 9. Example Feature Architecture

Hypothetical feature: Replay Assistant.

Purpose:

- maintain replay assistant state;
- expose operations such as open overlay, close overlay, mark replay moment, and clear marks;
- later provide UI-facing state to a Sirius UI surface.

Architectural shape:

```text
CReplayAssistantFeature : IFeature
    owns replay assistant state
    initializes feature resources
    shuts down feature resources
    exposes Open(), Close(), MarkMoment(), ClearMarks()

CReplayAssistantActivationBehavior : IFeatureActivationBehavior
    holds CReplayAssistantFeature&
    Activate() calls Feature.Open()
    Deactivate() calls Feature.Close()

CReplayMarkMomentCommand : ICommand
    holds CReplayAssistantFeature&
    Execute() calls Feature.MarkMoment()

CReplayClearMarksCommand : ICommand
    holds CReplayAssistantFeature&
    Execute() calls Feature.ClearMarks()

CReplayModule : IModule
    owns feature registry
    owns command registry
    registers replay assistant feature
    registers replay assistant commands
```

Registration location:

- The replay module registers `CReplayAssistantFeature` in its feature registry.
- The replay module registers replay commands in its command registry.
- Platform or explicit built-in composition wires activation ids and bindings to feature/command activation mappings.
- No replay object registers itself globally.

Dependencies:

- Replay feature depends on feature APIs and explicitly passed services.
- Replay commands depend on command APIs and `CReplayAssistantFeature&`.
- Replay activation behavior depends on feature activation behavior API and `CReplayAssistantFeature&`.
- No replay component depends on DDNet, input bindings, or unrelated features.

## 10. Future Risks

FeatureManager temptation:

- Risk: a central object starts owning all features and decisions.
- Prevention: modules own feature registries; platform only composes modules.

God Module:

- Risk: one module accumulates unrelated product behavior.
- Prevention: split modules by coherent product area when behavior or state stops being local.

Platform growth:

- Risk: `CPlatform` becomes product configuration and behavior policy.
- Prevention: keep platform registration explicit, small, and focused on wiring. Move real product registration into modules or feature packages.

Activation misuse:

- Risk: activation becomes a hidden event bus or router.
- Prevention: activation ids only request activation/deactivation. Consumers resolve ids locally.

Command ownership confusion:

- Risk: commands are registered in a platform-wide technical registry and bypass module lifecycle.
- Prevention: real commands belong to modules/features. Platform command registry remains proof-only unless a specific platform command surface is designed.

Cross-feature coupling:

- Risk: feature A directly calls feature B.
- Prevention: shared behavior should move to an explicit service or command boundary, not direct feature ownership.

Lifecycle and activation confusion:

- Risk: activation performs initialization or shutdown work.
- Prevention: initialize through lifecycle, enter active state through activation.

## 11. Final Architecture Rules

1. A Feature owns one coherent product capability.
2. A Module owns feature and command registries for a coherent product area.
3. Platform owns composition and wiring, not product behavior.
4. Lifecycle and activation are separate.
5. Initialized but inactive features are valid.
6. Activation must target already composed and lifecycle-valid objects.
7. Real commands should be module-owned or feature-owned through module composition.
8. Commands may operate on features only through explicit references created by composition.
9. Activation behavior may call a feature only through explicit composition.
10. Input bindings must not know features or commands.
11. Features must not know DDNet adapter or input binding internals.
12. No feature self-registration through globals.
13. No `FeatureManager`, `ActivationManager`, `RegistrationManager`, or service locator.
14. Registration remains explicit and local.
15. New abstractions require concrete pressure from real features.
