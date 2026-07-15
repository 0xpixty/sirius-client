# WP-094 - Module Runtime Definitions

Date: 2026-07-13

## Milestone

Foundation V2: Sirius Module Runtime.

## Roadmap position

WP-093 added immutable module descriptors. WP-094 adds the next smallest Module Runtime capability: explicit module definitions that pair a descriptor with a construction factory so runtime metadata can exist before module instances.

This directly advances the Module Runtime roadmap toward deterministic registration and descriptor-backed validation. It is not a cleanup Work Package.

## Repository evidence

- `CModuleRegistry` currently registers already-created `IModule` instances.
- `CPlatform` constructs the technical and Status modules directly.
- WP-093 descriptors now provide immutable declared module-owned runtime surface.
- The next runtime pressure is the absence of a definition object that can be ordered/validated before construction.

## Scope

- Add `CModuleDefinition` under `src/sirius/platform/modules/`.
- A definition owns:
  - a `CModuleDescriptor`;
  - a local construction factory returning `std::unique_ptr<IModule>`.
- Expose read-only `Descriptor()`.
- Expose `CanCreate()` and `CreateModule()`.
- Add `SiriusStatusModuleDefinition()` that pairs the Status descriptor with the existing Status module factory.
- Adapt Platform-local technical and Status module construction to go through definitions.
- Preserve the existing explicit Platform composition root.
- Add focused definition tests and build source entries.

## Non-goals

- No module manager.
- No scanner/discovery system.
- No dynamic plugin loading.
- No dependency graph.
- No lifecycle graph.
- No diagnostics snapshot.
- No typed contract imports/exports.
- No changes to module registry ownership or lifecycle order.
- No DDNet, UI, console, rendering, gameplay, protocol, config, or input binding work.

## Ownership and boundaries

- Definitions live in `sirius::platform::modules`.
- Platform remains the explicit composition owner.
- Definitions are construction descriptions, not a new runtime owner.
- Factories are local and explicit; no ambient lookup or service locator is introduced.

## Acceptance criteria

- `CModuleDefinition` exists and exposes its descriptor before instance construction.
- Empty factories are safe and return no module.
- Technical module construction still registers `module.sirius.technical`.
- Status module construction still registers `module.sirius.status`.
- Status feature/command behavior remains unchanged.
- Platform uses definitions locally without introducing scanning, routing, or generalized manager behavior.
- Focused definition tests are wired into CMake for GTest-enabled environments.
- `git diff --check` passes.
- Debug `game-client` build passes.
- RelWithDebInfo `game-client` build passes.

## Internal review

`ARCHITECTURE_APPROVED`

The late Architect result independently identified module definitions as the next roadmap step after descriptors. Lead narrowed the design to descriptor + factory only, leaving validation, dependency graph, diagnostics, and runtime composition for later WPs.

`DEVIL_FALLBACK_NO_BLOCKING_OBJECTION`

Definitions do not own modules after construction, do not scan modules, do not resolve dependencies, and do not change lifecycle order. The main risk is future factory sprawl; the next WP should move toward deterministic definition registration/validation rather than adding more ad hoc Platform factories.

## Validation plan

- `git diff --check`
- Debug `game-client` build through the Visual Studio developer environment
- RelWithDebInfo `game-client` build through the Visual Studio developer environment
- focused C++ tests when GTest targets are available

## Approved commit message

`feat(modules): add module runtime definitions`
