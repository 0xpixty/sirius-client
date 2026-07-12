# WP-004 - Sirius Service Registry

Status: Planned

Owner: Sirius Platform

Priority: High

Estimated Size: Small

---

# Summary

Introduce the minimal Sirius Core Service Registry.

The registry provides typed ownership and lookup for services derived from the Sirius Core `IService` interface.

WP-004 does not introduce any concrete services or runtime-visible behavior.

---

# Motivation

WP-002 introduced `CCoreRuntime` as the internal Sirius composition boundary.

WP-003 introduced the minimal Core Interfaces layer, including `IService`.

Future Sirius infrastructure needs one runtime-owned place to store service objects without adding globals, singletons, service locators, or DDNet dependencies.

---

# Goals

- Add a Core Service Registry under `src/sirius/core/services/`.
- Store services with explicit RAII ownership.
- Allow exact-type registration and lookup for `IService` implementations.
- Make `CCoreRuntime` own exactly one registry.
- Keep Sirius Core independent from DDNet.
- Preserve current runtime and client behavior.

---

# Non Goals

This work package does NOT implement:

- Logger
- Configuration System
- Scheduler
- Event Bus
- Module System
- Feature Registry
- Plugin loading
- Hot reload
- Networking
- Rendering
- UI
- Settings
- Gameplay logic
- DDNet adapters
- Dependency injection container
- Thread-safe service access
- Named services
- Multiple services per type

---

# Directory Layout

```text
src/sirius/core/services/
    service_registry.h
    service_registry.cpp
```

---

# Service Registry

Introduce `CServiceRegistry`.

Responsibilities:

- Own registered services through `std::unique_ptr`.
- Accept only types derived from `IService`.
- Reject duplicate registrations without replacing the existing service.
- Provide non-owning typed lookup.
- Clear all owned services on request or destruction.

The registry performs exact-type lookup only.

It does not perform inheritance fallback, interface discovery, string lookup, numeric lookup, reflection, or custom RTTI.

The registry does not call `IRuntimeComponent::Initialize()` or `IRuntimeComponent::Shutdown()`.

`IService` and `IRuntimeComponent` remain independent contracts.

---

# Expected API Shape

The public API should provide concepts equivalent to:

```cpp
bool Register(std::unique_ptr<T> pService);
bool Has<T>() const;
T *Get<T>();
const T *Get<T>() const;
void Clear();
```

Missing services return `nullptr` from `Get<T>()`.

Missing services return `false` from `Has<T>()`.

Duplicate registration returns `false` and leaves the existing service unchanged.

Null registration returns `false`.

---

# Runtime Ownership

`CCoreRuntime` must own exactly one service registry as a direct member.

Expected ownership:

```text
CCoreRuntime
    owns
        CServiceRegistry
            owns
                std::unique_ptr<IService>
```

`CCoreRuntime` exposes:

```cpp
CServiceRegistry &Services();
const CServiceRegistry &Services() const;
```

The registry is cleared during runtime shutdown and during normal member destruction.

---

# Dependency Rules

Code under:

```text
src/sirius/core/services/
```

may depend only on:

- the C++ standard library;
- Sirius Core interfaces.

It must not include headers from:

```text
engine/
game/
src/game/
src/engine/
sirius/adapters/
```

---

# CMake Integration

Add the service registry files to the existing Sirius CMake source list.

Do not introduce a new library target.

Do not modify unrelated DDNet CMake source lists.

---

# Observable Behavior

The client must remain behaviorally identical.

WP-004 must not introduce:

- lifecycle logs;
- console output;
- UI;
- renderer integration;
- input integration;
- settings;
- configuration loading;
- networking behavior;
- gameplay behavior;
- new commands;
- visible branding;
- frame callbacks.

---

# Acceptance Criteria

- `CServiceRegistry` exists under `src/sirius/core/services/`.
- Services are owned by `std::unique_ptr`.
- Only `IService`-derived types can be registered.
- Duplicate registration is rejected without overwrite.
- `Has<T>()` reports registered and missing services correctly.
- `Get<T>()` returns registered services and `nullptr` for missing services.
- `Clear()` destroys owned services.
- `CCoreRuntime` owns exactly one registry.
- Sirius Core remains DDNet-independent.
- No concrete services are introduced.
- No runtime or visible client behavior changes.
- Debug build succeeds.
- RelWithDebInfo build succeeds.
- `git diff --check` succeeds.

---

# Deliverables

After implementation, provide:

1. Architectural summary.
2. Implementation plan followed.
3. Exact files created and modified.
4. Registry ownership model.
5. Registration and duplicate behavior.
6. Lookup and missing-service behavior.
7. Runtime integration details.
8. Dependency-boundary confirmation.
9. Build and validation results.
10. `git status --short --branch`.
11. Any deviations from this work package.
12. Suggested commit message.

Suggested commit message:

```text
feat(core): add Sirius service registry
```
