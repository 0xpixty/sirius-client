/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "declaration_validation.h"

#include <string>
#include <vector>

namespace sirius::ui::declaration
{
	namespace
	{
		bool ContainsValue(const std::vector<std::string> &Values, const std::string &Value) noexcept
		{
			for(const auto &Existing : Values)
			{
				if(Existing == Value)
				{
					return true;
				}
			}

			return false;
		}

		std::string PropertyKey(const sirius::ui::property::CPropertyId &Id)
		{
			return Id.ModuleScopeId().Value() + "\n" + Id.SurfaceId().Value() + "\n" + Id.OwnerId().Value() + "\n" + Id.NameId().Value();
		}

		void AddDiagnostic(
			std::vector<CDeclarationDiagnostic> &Diagnostics,
			EDeclarationDiagnosticCode Code,
			std::string Message,
			std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceId,
			std::optional<sirius::ui::scene::CUiElementId> ElementId,
			std::optional<sirius::ui::property::CPropertyId> PropertyId,
			std::optional<sirius::ui::action::CUiActionIntentId> ActionIntentId)
		{
			Diagnostics.emplace_back(
				EDeclarationDiagnosticSeverity::Error,
				Code,
				std::move(Message),
				std::move(SurfaceId),
				std::move(ElementId),
				std::move(PropertyId),
				std::move(ActionIntentId),
				Diagnostics.size());
		}

		void ValidateActionIntents(
			const sirius::ui::action::CUiActionIntentSnapshotList &Intents,
			const std::optional<sirius::ui::scene::CUiSurfaceId> &SurfaceId,
			const std::optional<sirius::ui::scene::CUiElementId> &ElementId,
			std::vector<CDeclarationDiagnostic> &Diagnostics)
		{
			std::vector<std::string> SeenIntentIds;

			for(const auto &Intent : Intents.Intents())
			{
				const auto &IntentId = Intent.Id();
				if(IntentId.IsEmpty())
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::EmptyActionIntentId,
						"Declaration action intent ID must not be empty.",
						SurfaceId,
						ElementId,
						std::nullopt,
						IntentId);
					continue;
				}

				if(ContainsValue(SeenIntentIds, IntentId.Value()))
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::DuplicateActionIntentId,
						"Declaration action intent ID must be unique within its owner declaration.",
						SurfaceId,
						ElementId,
						std::nullopt,
						IntentId);
					continue;
				}

				SeenIntentIds.push_back(IntentId.Value());
			}
		}
	}

	CDeclarationDiagnosticSnapshot ValidateUiDeclarationSnapshot(const CUiDeclarationSnapshot &Declarations)
	{
		std::vector<CDeclarationDiagnostic> Diagnostics;
		std::vector<std::string> SeenSurfaceIds;

		for(const auto &SurfaceSnapshot : Declarations.Surfaces())
		{
			const auto &Surface = SurfaceSnapshot.Surface();
			const auto &SurfaceId = Surface.SurfaceId();
			const std::optional<sirius::ui::scene::CUiSurfaceId> SurfaceContext = SurfaceId;

			if(SurfaceId.IsEmpty())
			{
				AddDiagnostic(
					Diagnostics,
					EDeclarationDiagnosticCode::EmptySurfaceId,
					"Declaration surface ID must not be empty.",
					SurfaceContext,
					std::nullopt,
					std::nullopt,
					std::nullopt);
			}
			else if(ContainsValue(SeenSurfaceIds, SurfaceId.Value()))
			{
				AddDiagnostic(
					Diagnostics,
					EDeclarationDiagnosticCode::DuplicateSurfaceId,
					"Declaration surface ID must be unique.",
					SurfaceContext,
					std::nullopt,
					std::nullopt,
					std::nullopt);
			}
			else
			{
				SeenSurfaceIds.push_back(SurfaceId.Value());
			}

			ValidateActionIntents(Surface.DeclaredActionIntents(), SurfaceContext, std::nullopt, Diagnostics);

			std::vector<std::string> SeenElementIds;
			for(const auto &Element : SurfaceSnapshot.Elements().Elements())
			{
				const auto &ElementId = Element.Id();
				const std::optional<sirius::ui::scene::CUiElementId> ElementContext = ElementId;

				if(ElementId.IsEmpty())
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::EmptyElementId,
						"Declaration element ID must not be empty.",
						SurfaceContext,
						ElementContext,
						std::nullopt,
						std::nullopt);
				}
				else if(ContainsValue(SeenElementIds, ElementId.Value()))
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::DuplicateElementId,
						"Declaration element ID must be unique within its surface.",
						SurfaceContext,
						ElementContext,
						std::nullopt,
						std::nullopt);
				}
				else
				{
					SeenElementIds.push_back(ElementId.Value());
				}

				ValidateActionIntents(Element.DeclaredActionIntents(), SurfaceContext, ElementContext, Diagnostics);
			}

			for(const auto &Element : SurfaceSnapshot.Elements().Elements())
			{
				if(Element.ParentId().has_value() && !Element.ParentId()->IsEmpty() && !ContainsValue(SeenElementIds, Element.ParentId()->Value()))
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::MissingParentElement,
						"Declaration element parent ID must refer to an element in the same surface.",
						SurfaceContext,
						Element.Id(),
						std::nullopt,
						std::nullopt);
				}
			}

			std::vector<std::string> SeenPropertyIds;
			for(const auto &Property : SurfaceSnapshot.Properties().Properties())
			{
				const auto &PropertyId = Property.Metadata().Id();
				const std::optional<sirius::ui::property::CPropertyId> PropertyContext = PropertyId;

				if(!PropertyId.IsComplete())
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::EmptyPropertyId,
						"Declaration property ID must be complete.",
						SurfaceContext,
						std::nullopt,
						PropertyContext,
						std::nullopt);
				}
				else
				{
					const std::string Key = PropertyKey(PropertyId);
					if(ContainsValue(SeenPropertyIds, Key))
					{
						AddDiagnostic(
							Diagnostics,
							EDeclarationDiagnosticCode::DuplicatePropertyId,
							"Declaration property ID must be unique within its surface.",
							SurfaceContext,
							std::nullopt,
							PropertyContext,
							std::nullopt);
					}
					else
					{
						SeenPropertyIds.push_back(Key);
					}
				}

				if(Property.SurfaceOwnerId().has_value() && *Property.SurfaceOwnerId() != SurfaceId)
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::InvalidPropertyOwner,
						"Declaration property surface owner must match the containing surface.",
						SurfaceContext,
						std::nullopt,
						PropertyContext,
						std::nullopt);
				}

				if(Property.ElementOwnerId().has_value() && !ContainsValue(SeenElementIds, Property.ElementOwnerId()->Value()))
				{
					AddDiagnostic(
						Diagnostics,
						EDeclarationDiagnosticCode::InvalidPropertyOwner,
						"Declaration property element owner must refer to an element in the same surface.",
						SurfaceContext,
						*Property.ElementOwnerId(),
						PropertyContext,
						std::nullopt);
				}
			}
		}

		return CDeclarationDiagnosticSnapshot(std::move(Diagnostics));
	}

} // namespace sirius::ui::declaration
