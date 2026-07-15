/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_LOCALIZATION_LOCALIZATION_SNAPSHOT_H
#define SIRIUS_UI_LOCALIZATION_LOCALIZATION_SNAPSHOT_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace sirius::ui::localization
{

	class CLocaleId final
	{
	public:
		explicit CLocaleId(std::string Value);
		~CLocaleId() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CLocaleId &Other) const noexcept;
		bool operator!=(const CLocaleId &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CLocalizedTextKey final
	{
	public:
		explicit CLocalizedTextKey(std::string Value);
		~CLocalizedTextKey() noexcept;

		const std::string &Value() const noexcept;
		bool IsEmpty() const noexcept;

		bool operator==(const CLocalizedTextKey &Other) const noexcept;
		bool operator!=(const CLocalizedTextKey &Other) const noexcept;

	private:
		std::string m_Value;
	};

	class CLocalizationVersion final
	{
	public:
		explicit CLocalizationVersion(std::uint32_t Value) noexcept;
		~CLocalizationVersion() noexcept;

		std::uint32_t Value() const noexcept;
		bool IsInitial() const noexcept;

	private:
		std::uint32_t m_Value = 0;
	};

	enum class ELocalizationFormattingPolicy
	{
		None,
		Number,
		Date,
		Time,
		DateTime,
		Custom,
	};

	enum class ELocalizationPluralCategory
	{
		None,
		Zero,
		One,
		Two,
		Few,
		Many,
		Other,
	};

	class CLocalizedTextSnapshot final
	{
	public:
		CLocalizedTextSnapshot(
			std::string NamespaceId,
			CLocalizedTextKey Key,
			std::string DefaultText,
			std::string ResolvedText,
			ELocalizationFormattingPolicy FormattingPolicy,
			ELocalizationPluralCategory PluralCategory,
			std::size_t StableOrderIndex);
		~CLocalizedTextSnapshot() noexcept;

		const std::string &NamespaceId() const noexcept;
		const CLocalizedTextKey &Key() const noexcept;
		const std::string &DefaultText() const noexcept;
		const std::string &ResolvedText() const noexcept;
		ELocalizationFormattingPolicy FormattingPolicy() const noexcept;
		ELocalizationPluralCategory PluralCategory() const noexcept;
		std::size_t StableOrderIndex() const noexcept;

	private:
		std::string m_NamespaceId;
		CLocalizedTextKey m_Key;
		std::string m_DefaultText;
		std::string m_ResolvedText;
		ELocalizationFormattingPolicy m_FormattingPolicy = ELocalizationFormattingPolicy::None;
		ELocalizationPluralCategory m_PluralCategory = ELocalizationPluralCategory::None;
		std::size_t m_StableOrderIndex = 0;
	};

	class CLocalizationSnapshot final
	{
	public:
		CLocalizationSnapshot(
			CLocaleId ActiveLocale,
			CLocalizationVersion Version,
			std::vector<CLocalizedTextSnapshot> Texts,
			std::vector<CLocaleId> FallbackLocales);
		~CLocalizationSnapshot() noexcept;

		const CLocaleId &ActiveLocale() const noexcept;
		const CLocalizationVersion &Version() const noexcept;
		const std::vector<CLocalizedTextSnapshot> &Texts() const noexcept;
		const std::vector<CLocaleId> &FallbackLocales() const noexcept;
		std::size_t TextCount() const noexcept;
		bool IsEmpty() const noexcept;

	private:
		CLocaleId m_ActiveLocale;
		CLocalizationVersion m_Version;
		std::vector<CLocalizedTextSnapshot> m_Texts;
		std::vector<CLocaleId> m_FallbackLocales;
	};

} // namespace sirius::ui::localization

#endif
