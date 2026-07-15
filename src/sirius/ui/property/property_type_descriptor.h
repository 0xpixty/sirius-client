/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_UI_PROPERTY_PROPERTY_TYPE_DESCRIPTOR_H
#define SIRIUS_UI_PROPERTY_PROPERTY_TYPE_DESCRIPTOR_H

namespace sirius::ui::property
{

	enum class EPropertyValueKind
	{
		Null,
		Bool,
		SignedInteger,
		UnsignedInteger,
		Float,
		String,
		LocalizedTextReference,
		Color,
		Length,
		Vector2,
		Rectangle,
		Enum,
		IdReference,
		List,
		ObjectMap,
	};

	enum class EPropertySemanticKind
	{
		None,
		PixelLength,
		RelativeLength,
		Anchor,
		Margin,
		Padding,
		TypographyReference,
		ThemeTokenReference,
		LocalizationKeyReference,
		ImageReference,
		CommandActionIntentReference,
		AccessibilityRole,
		Duration,
		Easing,
	};

	class CPropertyTypeDescriptor final
	{
	public:
		explicit CPropertyTypeDescriptor(EPropertyValueKind ValueKind) noexcept;
		CPropertyTypeDescriptor(EPropertyValueKind ValueKind, EPropertySemanticKind SemanticKind) noexcept;
		~CPropertyTypeDescriptor() noexcept;

		EPropertyValueKind ValueKind() const noexcept;
		EPropertySemanticKind SemanticKind() const noexcept;

		bool operator==(const CPropertyTypeDescriptor &Other) const noexcept;
		bool operator!=(const CPropertyTypeDescriptor &Other) const noexcept;

	private:
		EPropertyValueKind m_ValueKind = EPropertyValueKind::Null;
		EPropertySemanticKind m_SemanticKind = EPropertySemanticKind::None;
	};

} // namespace sirius::ui::property

#endif
