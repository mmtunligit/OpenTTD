/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <https://www.gnu.org/licenses/old-licenses/gpl-2.0>.
 */

/** @file tile_map.h Map writing/reading functions for tile painter. */

#ifndef TILEPAINTER_MAP_H
#define TILEPAINTER_MAP_H

#include "map_func.h"
#include "tile_map.h"
#include "tile_type.h"
#include "core/bitmath_func.hpp"

#include "stdafx.h"

enum class TilePaint : uint8_t;
enum class TilePaintDiagonalOrientation : uint8_t;

/**
 * Get the primary paint of a tile.
 * @param t The tile to query.
 * @return The primary paint used on the tile.
 */
inline TilePaint GetPrimaryTilePaint(Tile t)
{
	return TilePaint(GB(t.m8(), 12, 4));
}

/**
 * Set the primary paint of a tile.
 * @param t The tile to paint.
 * @param paint The paint to use.
 */
inline void SetPrimaryTilePaint(Tile t, TilePaint paint)
{
	SB(t.m8(), 12, 4, static_cast<uint8_t>(paint));
}

/**
 * Check if a tile is allowed to have a secondary tile paint (diagonal split).
 * @param t The tile to query.
 * @return \c True iff this tile can have a secondary tile paint.
 */
inline bool CanHaveSecondaryTilePaint(Tile t)
{
	return IsTileType(t, TileType::Clear) || IsTileType(t, TileType::Railway);
}

/**
 * Get the secondary paint of a tile.
 * @param t The tile to query.
 * @return The secondary paint used on the tile.
 */
inline TilePaint GetSecondaryTilePaint(Tile t)
{
	assert(CanHaveSecondaryTilePaint(t));
	return TilePaint(GB(t.m8(), 8, 4));
}

/**
 * Set the secondary paint of a tile.
 * @param t The tile to paint.
 * @param paint The paint to use.
 */
inline void SetSecondaryTilePaint(Tile t, TilePaint paint)
{
	assert(CanHaveSecondaryTilePaint(t));
	SB(t.m8(), 8, 4, static_cast<uint8_t>(paint));
}

/* Get the diagonal orientation of diagonal paint on a tile.
 * @note Only saved for clear tiles, rail tiles can only have two paints on diagonal rail tiles and always have the primary paint under the rail.
 * @param t The tile to query.
 * @return The orientation of the diagonal paint on the tile.
 */
inline TilePaintDiagonalOrientation GetDiagonalPaintOrientation(Tile t)
{
	assert(IsTileType(t, TileType::Clear));
	return TilePaintDiagonalOrientation(GB(t.m8(), 5, 3));
}

/* Set the diagonal orientation of diagonal paint on a tile.
 * @note Only saved for clear tiles, rail tiles can only have two paints on diagonal rail tiles and always have the primary paint under the rail.
 * @param t The tile to query.
 * @return The orientation of the diagonal paint on the tile.
 */
inline void SetDiagonalPaintOrientation(Tile t, TilePaintDiagonalOrientation orientation)
{
	assert(IsTileType(t, TileType::Clear));
	SB(t.m8(), 5, 3, static_cast<uint8_t>(orientation));
}

#endif /* TILEPAINTER_MAP_H */
