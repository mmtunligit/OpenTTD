/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <https://www.gnu.org/licenses/old-licenses/gpl-2.0>.
 */

/** @file tilepainter_gui.cpp GUI for tile painter. */

#include "stdafx.h"
#include "hotkeys.h"
#include "picker_gui.h"
#include "tilehighlight_func.h"
#include "tilepainter.h"

#include "table/strings.h"

#include "safeguards.h"

/**
 * Get the StringID of a TilePaint name.
 * @param paint The paint to query.
 * @return The StringID of the given TilePaint name.
 */
StringID GetTilePaintName(TilePaint paint)
{
	switch (paint) {
		case TilePaint::Dirt: return STR_NULL; //TODO real strings
		case TilePaint::GrassyDirt: return STR_NULL;
		case TilePaint::Stone: return STR_NULL;

		case TilePaint::None:
		case TilePaint::End:
		default:
			NOT_REACHED();
	}
}

/**
 * Draw a paint that does not exist.
 * @param x Position x of image.
 * @param y Position y of image.
 * @param paint the paint to draw.
 */
void DrawPaintInGUI(int x, int y, TilePaint paint)
{
	auto draw = [](int x, int y, TilePaint paint) {
		DrawSprite(GetPaintedTileBase(paint), PAL_NONE, x, y);
	};

	draw(x, y, paint);
}

class PaintPickerCallbacks : public PickerCallbacks {
public:
	PaintPickerCallbacks() : PickerCallbacks("fav_paint") {}

	static inline int sel_class; ///< Currently selected 'class'.
	static inline int sel_type; ///< Currently selected TilePaint.

	GrfSpecFeature GetFeature() const override { return GrfSpecFeature::Invalid; }

	StringID GetClassTooltip() const override { return STR_UNDEFINED; }
	StringID GetTypeTooltip() const override { return STR_NULL; } //TODO real string
	StringID GetCollectionTooltip() const override { return STR_UNDEFINED; }

	bool IsActive() const override { return true; }
	void Close ([[maybe_unused]] int data) override { ResetObjectToPlace(); }

	bool HasClassChoice() const override { return false; }
	int GetClassCount() const override { return 1; }
	StringID GetClassName([[maybe_unused]] int id) const override { return INVALID_STRING_ID; }
	int GetSelectedClass() const override { return PaintPickerCallbacks::sel_class; }
	void SetSelectedClass([[maybe_unused]] int cls_id) const override { PaintPickerCallbacks::sel_class = 0; }

	bool IsTypeAvailable([[maybe_unused]] int cls_id, [[maybe_unused]] int id) const override { return true; }
	int GetTypeCount([[maybe_unused]] int cls_id) const override { return static_cast<int>(TilePaint::End) - 1; }
	StringID GetTypeName([[maybe_unused]] int cls_id, int id) const override { return GetTilePaintName(static_cast<TilePaint>(id)); }
	std::span<const BadgeID> GetTypeBadges([[maybe_unused]] int cls_id, [[maybe_unused]] int id) const override { return {}; }
	int GetSelectedType() const override { return sel_type; }
	void SetSelectedType(int id) const override { sel_type = id; }
	void DrawType(int x, int y, [[maybe_unused]] int cls_id, int id) const override { DrawPaintInGUI(x, y, static_cast<TilePaint>(id)); }
	bool ShowModes() const override { return false; }

	PickerItem GetPickerItem(int cls_id, int id) const override { return {static_cast<GrfID>(cls_id), static_cast<uint16_t>(id), cls_id, id}; }
	void FillUsedItems([[maybe_unused]] std::set<PickerItem> &items) override {}
	std::map<std::string, std::set<PickerItem>> UpdateSavedItems(const std::map<std::string, std::set<PickerItem>> &src) override { return src; }

	static PaintPickerCallbacks instance;
};
/* static */ PaintPickerCallbacks PaintPickerCallbacks::instance;

struct BuildPaintWindow : public PickerWindow {
	BuildPaintWindow(WindowDesc &desc, WindowNumber) : PickerWindow(desc, nullptr, 0, PaintPickerCallbacks::instance)
	{
		this->ConstructWindow();
	}

	void OnInit() override
	{
		this->InvalidateData(PICKER_INVALIDATION_ALL);
		this->PickerWindow::OnInit();
	}

	static inline HotkeyList hotkeys{"buildpaint", {
		Hotkey('F', "focus_filter_box", PCWHK_FOCUS_FILTER_BOX),
	}};
};

/** Nested widget definition for the build tile paint window. */
static constexpr std::initializer_list<NWidgetPart> _nested_build_paint_widgets = {
	NWidget(NWID_HORIZONTAL),
		NWidget(WWT_CLOSEBOX, Colours::DarkGreen),
		NWidget(WWT_CAPTION, Colours::DarkGreen), SetStringTip(STR_NULL, STR_TOOLTIP_WINDOW_TITLE_DRAG_THIS),
		NWidget(WWT_SHADEBOX, Colours::DarkGreen),
		NWidget(WWT_DEFSIZEBOX, Colours::DarkGreen),
		NWidget(WWT_STICKYBOX, Colours::DarkGreen),
	EndContainer(),
		NWidgetFunction(MakePickerTypeWidgets),
	EndContainer(),
};

/** Window defenition for the tile painting window. */
static WindowDesc _build_paint_desc(
	WindowPosition::Automatic, "build_tile_paint", 0,0,
	WindowClass::BuildPaint, WindowClass::BuildToolbar,
	WindowDefaultFlag::Construction,
	_nested_build_paint_widgets,
	&BuildPaintWindow::hotkeys
);

Window *ShowBuildPaintPicker()
{
	return AllocateWindowDescFront<BuildPaintWindow>(_build_paint_desc, 0);
};
