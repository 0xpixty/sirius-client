/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "property_metadata_snapshot.h"

#include <utility>

namespace sirius::ui::property
{

	CPropertyDefaultDescriptor::CPropertyDefaultDescriptor(EPropertyDefaultPolicy Policy, CPropertyTypeDescriptor Type) noexcept :
		m_Policy(Policy),
		m_Type(Type)
	{
	}

	CPropertyDefaultDescriptor::~CPropertyDefaultDescriptor() noexcept = default;

	EPropertyDefaultPolicy CPropertyDefaultDescriptor::Policy() const noexcept
	{
		return m_Policy;
	}

	const CPropertyTypeDescriptor &CPropertyDefaultDescriptor::Type() const noexcept
	{
		return m_Type;
	}

	bool CPropertyDefaultDescriptor::operator==(const CPropertyDefaultDescriptor &Other) const noexcept
	{
		return m_Policy == Other.m_Policy && m_Type == Other.m_Type;
	}

	bool CPropertyDefaultDescriptor::operator!=(const CPropertyDefaultDescriptor &Other) const noexcept
	{
		return !(*this == Other);
	}

	CPropertyMetadataSnapshot::CPropertyMetadataSnapshot(
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
		EPropertyEvaluationStage EvaluationStage) :
		m_Id(std::move(Id)),
		m_DisplayName(std::move(DisplayName)),
		m_OwnerKind(OwnerKind),
		m_Type(Type),
		m_SchemaVersion(SchemaVersion),
		m_Optionality(Optionality),
		m_AccessPolicy(AccessPolicy),
		m_PersistencePolicy(PersistencePolicy),
		m_InheritancePolicy(InheritancePolicy),
		m_ThemePolicy(ThemePolicy),
		m_LocalizationPolicy(LocalizationPolicy),
		m_AnimationPolicy(AnimationPolicy),
		m_EditorPolicy(EditorPolicy),
		m_DefaultDescriptor(DefaultDescriptor),
		m_EvaluationStage(EvaluationStage)
	{
	}

	CPropertyMetadataSnapshot::~CPropertyMetadataSnapshot() noexcept = default;

	const CPropertyId &CPropertyMetadataSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	const std::string &CPropertyMetadataSnapshot::DisplayName() const noexcept
	{
		return m_DisplayName;
	}

	EPropertyOwnerKind CPropertyMetadataSnapshot::OwnerKind() const noexcept
	{
		return m_OwnerKind;
	}

	const CPropertyTypeDescriptor &CPropertyMetadataSnapshot::Type() const noexcept
	{
		return m_Type;
	}

	std::uint32_t CPropertyMetadataSnapshot::SchemaVersion() const noexcept
	{
		return m_SchemaVersion;
	}

	EPropertyOptionality CPropertyMetadataSnapshot::Optionality() const noexcept
	{
		return m_Optionality;
	}

	EPropertyAccessPolicy CPropertyMetadataSnapshot::AccessPolicy() const noexcept
	{
		return m_AccessPolicy;
	}

	EPropertyPersistencePolicy CPropertyMetadataSnapshot::PersistencePolicy() const noexcept
	{
		return m_PersistencePolicy;
	}

	EPropertyInheritancePolicy CPropertyMetadataSnapshot::InheritancePolicy() const noexcept
	{
		return m_InheritancePolicy;
	}

	EPropertyThemePolicy CPropertyMetadataSnapshot::ThemePolicy() const noexcept
	{
		return m_ThemePolicy;
	}

	EPropertyLocalizationPolicy CPropertyMetadataSnapshot::LocalizationPolicy() const noexcept
	{
		return m_LocalizationPolicy;
	}

	EPropertyAnimationPolicy CPropertyMetadataSnapshot::AnimationPolicy() const noexcept
	{
		return m_AnimationPolicy;
	}

	EPropertyEditorPolicy CPropertyMetadataSnapshot::EditorPolicy() const noexcept
	{
		return m_EditorPolicy;
	}

	const CPropertyDefaultDescriptor &CPropertyMetadataSnapshot::DefaultDescriptor() const noexcept
	{
		return m_DefaultDescriptor;
	}

	EPropertyEvaluationStage CPropertyMetadataSnapshot::EvaluationStage() const noexcept
	{
		return m_EvaluationStage;
	}

} // namespace sirius::ui::property
