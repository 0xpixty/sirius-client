/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_METADATA_SNAPSHOT_H
#define SIRIUS_UI_PROPERTY_PROPERTY_METADATA_SNAPSHOT_H

#include "property_id.h"
#include "property_type_descriptor.h"

#include <cstdint>
#include <string>

namespace sirius::ui::property
{

	enum class EPropertyOwnerKind
	{
		Surface,
		Element,
		Widget,
		ThemeDeclaration,
		LocalizationResource,
		EditorDocumentObject,
		PersistenceProfileRecord,
		AnimationTrack,
		RuntimeInteractionState,
	};

	enum class EPropertyOptionality
	{
		Required,
		Optional,
	};

	enum class EPropertyAccessPolicy
	{
		ReadWrite,
		ReadOnly,
	};

	enum class EPropertyPersistencePolicy
	{
		RuntimeOnly,
		Persisted,
		Generated,
	};

	enum class EPropertyInheritancePolicy
	{
		NotInherited,
		Inherit,
		Override,
		Merge,
		Append,
		Block,
	};

	enum class EPropertyThemePolicy
	{
		NotThemeDriven,
		TokenReference,
		ResolvedThemeValue,
	};

	enum class EPropertyLocalizationPolicy
	{
		NotLocalized,
		LocalizationKeyReference,
		ResolvedLocalizedValue,
	};

	enum class EPropertyAnimationPolicy
	{
		NotAnimatable,
		Animatable,
		AnimationOutput,
	};

	enum class EPropertyEditorPolicy
	{
		Hidden,
		Inspectable,
		Editable,
		PreviewOnly,
	};

	enum class EPropertyDefaultPolicy
	{
		NoDefault,
		ExplicitDefault,
		MandatorySource,
	};

	enum class EPropertyEvaluationStage
	{
		Declaration,
		PersistenceProfile,
		ThemeResolution,
		LocalizationResolution,
		Inheritance,
		ExplicitEffectiveValue,
		ComputedExpression,
		Animation,
		GeneratedRuntime,
		Diagnostics,
	};

	class CPropertyDefaultDescriptor final
	{
	public:
		CPropertyDefaultDescriptor(EPropertyDefaultPolicy Policy, CPropertyTypeDescriptor Type) noexcept;
		~CPropertyDefaultDescriptor() noexcept;

		EPropertyDefaultPolicy Policy() const noexcept;
		const CPropertyTypeDescriptor &Type() const noexcept;

		bool operator==(const CPropertyDefaultDescriptor &Other) const noexcept;
		bool operator!=(const CPropertyDefaultDescriptor &Other) const noexcept;

	private:
		EPropertyDefaultPolicy m_Policy = EPropertyDefaultPolicy::NoDefault;
		CPropertyTypeDescriptor m_Type;
	};

	class CPropertyMetadataSnapshot final
	{
	public:
		CPropertyMetadataSnapshot(
			CPropertyId Id,
			std::string DisplayName,
			EPropertyOwnerKind OwnerKind,
			CPropertyTypeDescriptor Type,
			std::uint32_t SchemaVersion,
			EPropertyOptionality Optionality,
			EPropertyAccessPolicy AccessPolicy,
			EPropertyPersistencePolicy PersistencePolicy,
			EPropertyInheritancePolicy InheritancePolicy,
			EPropertyThemePolicy ThemePolicy,
			EPropertyLocalizationPolicy LocalizationPolicy,
			EPropertyAnimationPolicy AnimationPolicy,
			EPropertyEditorPolicy EditorPolicy,
			CPropertyDefaultDescriptor DefaultDescriptor,
			EPropertyEvaluationStage EvaluationStage);
		~CPropertyMetadataSnapshot() noexcept;

		const CPropertyId &Id() const noexcept;
		const std::string &DisplayName() const noexcept;
		EPropertyOwnerKind OwnerKind() const noexcept;
		const CPropertyTypeDescriptor &Type() const noexcept;
		std::uint32_t SchemaVersion() const noexcept;
		EPropertyOptionality Optionality() const noexcept;
		EPropertyAccessPolicy AccessPolicy() const noexcept;
		EPropertyPersistencePolicy PersistencePolicy() const noexcept;
		EPropertyInheritancePolicy InheritancePolicy() const noexcept;
		EPropertyThemePolicy ThemePolicy() const noexcept;
		EPropertyLocalizationPolicy LocalizationPolicy() const noexcept;
		EPropertyAnimationPolicy AnimationPolicy() const noexcept;
		EPropertyEditorPolicy EditorPolicy() const noexcept;
		const CPropertyDefaultDescriptor &DefaultDescriptor() const noexcept;
		EPropertyEvaluationStage EvaluationStage() const noexcept;

	private:
		CPropertyId m_Id;
		std::string m_DisplayName;
		EPropertyOwnerKind m_OwnerKind = EPropertyOwnerKind::Element;
		CPropertyTypeDescriptor m_Type;
		std::uint32_t m_SchemaVersion = 0;
		EPropertyOptionality m_Optionality = EPropertyOptionality::Required;
		EPropertyAccessPolicy m_AccessPolicy = EPropertyAccessPolicy::ReadWrite;
		EPropertyPersistencePolicy m_PersistencePolicy = EPropertyPersistencePolicy::RuntimeOnly;
		EPropertyInheritancePolicy m_InheritancePolicy = EPropertyInheritancePolicy::NotInherited;
		EPropertyThemePolicy m_ThemePolicy = EPropertyThemePolicy::NotThemeDriven;
		EPropertyLocalizationPolicy m_LocalizationPolicy = EPropertyLocalizationPolicy::NotLocalized;
		EPropertyAnimationPolicy m_AnimationPolicy = EPropertyAnimationPolicy::NotAnimatable;
		EPropertyEditorPolicy m_EditorPolicy = EPropertyEditorPolicy::Hidden;
		CPropertyDefaultDescriptor m_DefaultDescriptor;
		EPropertyEvaluationStage m_EvaluationStage = EPropertyEvaluationStage::Declaration;
	};

} // namespace sirius::ui::property

#endif
