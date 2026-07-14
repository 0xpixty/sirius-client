/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "localization_snapshot.h"

#include <utility>

namespace sirius::ui::localization
{

	CLocaleId::CLocaleId(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CLocaleId::~CLocaleId() noexcept = default;

	const std::string &CLocaleId::Value() const noexcept
	{
		return m_Value;
	}

	bool CLocaleId::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CLocaleId::operator==(const CLocaleId &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CLocaleId::operator!=(const CLocaleId &Other) const noexcept
	{
		return !(*this == Other);
	}

	CLocalizedTextKey::CLocalizedTextKey(std::string Value) :
		m_Value(std::move(Value))
	{
	}

	CLocalizedTextKey::~CLocalizedTextKey() noexcept = default;

	const std::string &CLocalizedTextKey::Value() const noexcept
	{
		return m_Value;
	}

	bool CLocalizedTextKey::IsEmpty() const noexcept
	{
		return m_Value.empty();
	}

	bool CLocalizedTextKey::operator==(const CLocalizedTextKey &Other) const noexcept
	{
		return m_Value == Other.m_Value;
	}

	bool CLocalizedTextKey::operator!=(const CLocalizedTextKey &Other) const noexcept
	{
		return !(*this == Other);
	}

	CLocalizationVersion::CLocalizationVersion(std::uint32_t Value) noexcept :
		m_Value(Value)
	{
	}

	CLocalizationVersion::~CLocalizationVersion() noexcept = default;

	std::uint32_t CLocalizationVersion::Value() const noexcept
	{
		return m_Value;
	}

	bool CLocalizationVersion::IsInitial() const noexcept
	{
		return m_Value == 0;
	}

	CLocalizedTextSnapshot::CLocalizedTextSnapshot(
		std::string NamespaceId,
		CLocalizedTextKey Key,
		std::string DefaultText,
		std::string ResolvedText,
		ELocalizationFormattingPolicy FormattingPolicy,
		ELocalizationPluralCategory PluralCategory,
		std::size_t StableOrderIndex) :
		m_NamespaceId(std::move(NamespaceId)),
		m_Key(std::move(Key)),
		m_DefaultText(std::move(DefaultText)),
		m_ResolvedText(std::move(ResolvedText)),
		m_FormattingPolicy(FormattingPolicy),
		m_PluralCategory(PluralCategory),
		m_StableOrderIndex(StableOrderIndex)
	{
	}

	CLocalizedTextSnapshot::~CLocalizedTextSnapshot() noexcept = default;

	const std::string &CLocalizedTextSnapshot::NamespaceId() const noexcept
	{
		return m_NamespaceId;
	}

	const CLocalizedTextKey &CLocalizedTextSnapshot::Key() const noexcept
	{
		return m_Key;
	}

	const std::string &CLocalizedTextSnapshot::DefaultText() const noexcept
	{
		return m_DefaultText;
	}

	const std::string &CLocalizedTextSnapshot::ResolvedText() const noexcept
	{
		return m_ResolvedText;
	}

	ELocalizationFormattingPolicy CLocalizedTextSnapshot::FormattingPolicy() const noexcept
	{
		return m_FormattingPolicy;
	}

	ELocalizationPluralCategory CLocalizedTextSnapshot::PluralCategory() const noexcept
	{
		return m_PluralCategory;
	}

	std::size_t CLocalizedTextSnapshot::StableOrderIndex() const noexcept
	{
		return m_StableOrderIndex;
	}

	CLocalizationSnapshot::CLocalizationSnapshot(
		CLocaleId ActiveLocale,
		CLocalizationVersion Version,
		std::vector<CLocalizedTextSnapshot> Texts,
		std::vector<CLocaleId> FallbackLocales) :
		m_ActiveLocale(std::move(ActiveLocale)),
		m_Version(Version),
		m_Texts(std::move(Texts)),
		m_FallbackLocales(std::move(FallbackLocales))
	{
	}

	CLocalizationSnapshot::~CLocalizationSnapshot() noexcept = default;

	const CLocaleId &CLocalizationSnapshot::ActiveLocale() const noexcept
	{
		return m_ActiveLocale;
	}

	const CLocalizationVersion &CLocalizationSnapshot::Version() const noexcept
	{
		return m_Version;
	}

	const std::vector<CLocalizedTextSnapshot> &CLocalizationSnapshot::Texts() const noexcept
	{
		return m_Texts;
	}

	const std::vector<CLocaleId> &CLocalizationSnapshot::FallbackLocales() const noexcept
	{
		return m_FallbackLocales;
	}

	std::size_t CLocalizationSnapshot::TextCount() const noexcept
	{
		return m_Texts.size();
	}

	bool CLocalizationSnapshot::IsEmpty() const noexcept
	{
		return m_Texts.empty();
	}

} // namespace sirius::ui::localization
