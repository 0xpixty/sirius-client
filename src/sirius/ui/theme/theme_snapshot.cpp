/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "theme_snapshot.h"

#include <utility>

namespace sirius::ui::theme
{

	CThemeId::CThemeId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CThemeId::~CThemeId() noexcept = default;

	const std::string &CThemeId::Value() const noexcept
	{
		return m_Value;
	}

	bool CThemeId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CThemeId::operator==(const CThemeId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CThemeId::operator!=(const CThemeId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CThemeTokenId::CThemeTokenId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CThemeTokenId::~CThemeTokenId() noexcept = default;

	const std::string &CThemeTokenId::Value() const noexcept
	{
		return m_Value;
	}

	bool CThemeTokenId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CThemeTokenId::operator==(const CThemeTokenId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CThemeTokenId::operator!=(const CThemeTokenId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CThemeVersion::CThemeVersion(std::uint32_t Value) noexcept :
		m_Value(Value)
	{
	}

	CThemeVersion::~CThemeVersion() noexcept = default;

	std::uint32_t CThemeVersion::Value() const noexcept
	{
		return m_Value;
	}

	bool CThemeVersion::IsInitial() const noexcept
	{
		return m_Value == 0;
	}

	CThemeTokenSnapshot::CThemeTokenSnapshot(
		CThemeTokenId Id,
		EThemeTokenCategory Category,
		EThemeStateDimension State,
		std::string StablePayload,
		bool Required,
		std::size_t StableOrderIndex) :
		m_Id(std::move(Id)),
		m_Category(Category),
		m_State(State),
		m_StablePayload(std::move(StablePayload)),
		m_Required(Required),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CThemeTokenSnapshot::~CThemeTokenSnapshot() noexcept = default;

	const CThemeTokenId &CThemeTokenSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	EThemeTokenCategory CThemeTokenSnapshot::Category() const noexcept
	{
		return m_Category;
	}

	EThemeStateDimension CThemeTokenSnapshot::State() const noexcept
	{
		return m_State;
	}

	const std::string &CThemeTokenSnapshot::StablePayload() const noexcept
	{
		return m_StablePayload;
	}

	bool CThemeTokenSnapshot::Required() const noexcept
	{
		return m_Required;
	}

	std::size_t CThemeTokenSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CThemeSnapshot::CThemeSnapshot(
		CThemeId Id,
		CThemeVersion Version,
		std::vector<CThemeTokenSnapshot> Tokens,
		std::vector<CThemeId> FallbackChain,
		std::vector<EThemeAccessibilityModifier> AccessibilityModifiers) :
		m_Id(std::move(Id)),
		m_Version(Version),
		m_Tokens(std::move(Tokens)),
		m_FallbackChain(std::move(FallbackChain)),
		m_AccessibilityModifiers(std::move(AccessibilityModifiers))
	{
	}

	CThemeSnapshot::~CThemeSnapshot() noexcept = default;

	const CThemeId &CThemeSnapshot::Id() const noexcept
	{
		return m_Id;
	}

	const CThemeVersion &CThemeSnapshot::Version() const noexcept
	{
		return m_Version;
	}

	const std::vector<CThemeTokenSnapshot> &CThemeSnapshot::Tokens() const noexcept
	{
		return m_Tokens;
	}

	const std::vector<CThemeId> &CThemeSnapshot::FallbackChain() const noexcept
	{
		return m_FallbackChain;
	}

	const std::vector<EThemeAccessibilityModifier> &CThemeSnapshot::AccessibilityModifiers() const noexcept
	{
		return m_AccessibilityModifiers;
	}

	std::size_t CThemeSnapshot::TokenCount() const noexcept
	{
		return m_Tokens.size();
	}

	bool CThemeSnapshot::IsEmpty() const noexcept
	{
		return m_Tokens.empty();
	}

} // namespace sirius::ui::theme
