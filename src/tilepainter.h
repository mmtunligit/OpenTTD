/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <https://www.gnu.org/licenses/old-licenses/gpl-2.0>.
 */

/** @file tile_map.h Types related to the tile painter. */

#ifndef TILEPAINTER_H
#define TILEPAINTER_H

#include "tilepainter_map.h"
#include "map_func.h"
#include "gfx_type.h"

#include "table/sprites.h"
#include "table/strings.h"

#include "stdafx.h"

/**
 * Possible orientations for a TileType::Clear tile with two paints, split diagonally.
 */
enum class TilePaintDiagonalOrientation : uint8_t {
	SecondaryNorth = 0,
	SecondaryEast,
	SecondarySouth,
	SecondaryWest,
};

/**
 * Available tile paints.
 * @note Limited to None + 15 paints due to savegame storage.
 */
enum class TilePaint : uint8_t {
	Dirt, ///< Brown dirt (matching bare land).
	GrassyDirt, ///< Brown dirt with some green (matching partly regrown grass after bulldozing).
	Stone, ///< Light stone pavers (matching houses, pavements, etc.).
	None, ///< No paint, exposes the actual ground tile.
	End, ///< End Marker.

	/* Space to add tile paints matching popular NewGRFs at a later date. */
};

StringID GetTilePaintName(TilePaint paint);

/**
 * Get the SpriteID of the flat tile matching a given TilePaint.
 * @note The offset for the tile slope is not included and must be added later.
 * @param paint The paint to query.
 * @return The SpriteID of the flat tile matching the given TilePaint.
 */
inline SpriteID GetPaintedTileBase(TilePaint paint)
{
	switch (paint) {
		case TilePaint::Dirt: return SPR_FLAT_BARE_LAND;
		case TilePaint::GrassyDirt: return SPR_FLAT_1_THIRD_GRASS_TILE;
		case TilePaint::Stone: return SPR_CONCRETE_GROUND; // TODO: This sprite lacks slopes, needs redrawing and re-defining.

		case TilePaint::None:
		case TilePaint::End:
		default:
			NOT_REACHED();
	}
}

/**
 * Check if a tile has a primary paint selected.
 * @param t The tile to query.
 * @return \c true iff the tile has a primary paint.
 */
inline bool TileHasPrimaryPaint(Tile t)
{
	return GetPrimaryTilePaint(t) != TilePaint{};
}

/**
 * Check if a tile has a secondary paint selected.
 * @param t The tile to query.
 * @return \c true iff the tile has a secondary paint, false if not selected or if the tile cannot support a secondary paint.
 */
inline bool TileHasSecondaryPaint(Tile t)
{
	return CanHaveSecondaryTilePaint(t) && GetSecondaryTilePaint(t) != TilePaint{};
}

/**
 * Check if a tile has been painted by the player.
 * @param t The tile to query.
 * @return \c true iff the tile has been painted.
 */
inline bool TileIsPainted(Tile t)
{
	return TileHasPrimaryPaint(t) || TileHasSecondaryPaint(t);
}

Window *ShowBuildPaintPicker();

#endif /* TILEPAINTER_H */
