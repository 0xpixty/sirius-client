# Architecture Audit - WP-073 through WP-076

Date: 2026-07-13

## Status

Completed by Sirius Lead audit fallback.

- Auditor fallback: `AUDITOR_FALLBACK_APPROVED`
- Critical findings: none
- Medium findings: none
- Mandatory correction WP required: no
- User decision required: no
- Audited commit range: `1ecc229b1cf373e9fa85f7c5e393ea6791af2814..e5928fe9448e573cfe8a01d06824b345113d8c1b`

Uncommitted protected `src/sirius/platform/modules/module_registry.*` changes were observed in the working tree but are not part of the audited committed range.

## Executive Summary

WP-073 corrected the lifecycle/activation defect found by the prior audit: platform shutdown now disconnects command activation observers, reconciles active feature activation records, shuts module lifecycle, then stops Core. Activation fan-out is gated to the active platform lifecycle.

WP-074 and WP-076 removed stale activation API surface. The binding-local generic resolver was removed, and the unused public `CPlatform::DeactivateActivation()` wrapper was removed. These changes reduce accidental coupling pressure without altering runtime activation behavior.

WP-075 resolved the missing historical WP-068 audit artifact as a documentation status record only. It did not reconstruct historical findings or override newer approved work.

No new dependency inversion, DDNet leakage, Core-to-Platform dependency, service locator, manager/router abstraction, duplicate event bus, or generalized module scanning was introduced.

## Audited Work

- WP-073: Feature Activation Shutdown/Restart Consistency
- WP-074: Binding Activation Resolver Cleanup
- WP-075: Historical Audit Artifact Status
- WP-076: Remove Unused Platform Deactivation API

## Dependency and Ownership Review

Current Sirius direction remains intact:

```text
DDNet adapter
  -> Platform composition root
       -> Core runtime/services/events/tasks/config/logging
       -> input binding pipeline
       -> neutral activation boundary
            -> feature activation handler/resolver/controller
            -> command activation handler/resolver/dispatcher
       -> module registry and module lifecycle
            -> module-owned feature/command/service registries
```

Verified observations:

- Core does not include Platform, adapter, game, or engine headers.
- DDNet remains outside Platform and enters through adapter-owned integration.
- Platform owns composition and wiring.
- Modules own command, feature, and module-service registries.
- Binding activation remains source-neutral through activation IDs.
- Feature and command activation resolvers remain distinct Platform-owned consumers.
- The deleted binding-local resolver is no longer present in `src/`.
- The deleted public `DeactivateActivation()` API is no longer present in `src/`.

## Lifecycle and Activation Review

WP-073 introduced one shutdown-scoped controller operation:

- ordinary `Activate()`/`Deactivate()` transition semantics remain unchanged;
- `DeactivateAllForShutdown()` is `noexcept`;
- active records are reconciled before module Feature shutdown;
- per-record deactivation exceptions are isolated and force only the matching record Inactive;
- repeated shutdown is callback-idempotent;
- platform fan-out is gated unless Core is running and module lifecycle is initialized.

The architecture distinction between lifecycle and activation remains clear. Shutdown reconciliation is a lifecycle boundary operation, not a replacement for ordinary deactivation semantics.

## API Surface Review

Positive changes:

- Removed obsolete binding-local `IActivationResolver`.
- Removed unused public `CPlatform::DeactivateActivation()`.

Remaining watched surface:

- `CPlatform::Modules()` remains a mutable public escape hatch used by current focused tests to simulate failed module composition. Do not broaden its use into product control flow. A future cleanup may replace this test need with a narrower composition/test seam if concrete pressure appears.
- `CPlatform` still owns fixed two-consumer activation fan-out. This remains acceptable while there are exactly feature and command consumers and no real pressure for a dispatcher/router abstraction.

## Findings

### Critical

None.

### Medium

None.

### Low - Monitor

1. The built-in technical module and technical activation behavior remain proof infrastructure. They must not become a product catch-all.
2. `CPlatform::Modules()` remains broader than ideal, but it is not newly expanded in this range.
3. The private platform test friend introduced in WP-073 is acceptable as the approved focused test seam, but should not be copied as a general testing pattern.
4. Fixed activation fan-out should not be generalized until a third real consumer or repeated policy duplication creates concrete pressure.
5. Focused GoogleTest execution remains limited by local GTest availability; Debug and RelWithDebInfo `game-client` builds passed for implementation WPs.

## Audit Decision

`AUDITOR_FALLBACK_APPROVED`

No mandatory correction is required before the next bounded Work Package.

## Next Safe Step

Continue normal SDS workflow. The next Work Package should be derived from current repository pressure and should remain bounded. Safe areas include incremental reduction of Platform proof/test surface or the next minimal step toward a real module-owned feature/command only if concrete scope can be kept small.
