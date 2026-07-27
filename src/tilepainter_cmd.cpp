/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <https://www.gnu.org/licenses/old-licenses/gpl-2.0>.
 */

/** @file tilepainter_cmd.cpp Commands related to tile painter. */

#include "command_func.h"
#include "command_type.h"
#include "company_base.h"
#include "company_type.h"
#include "company_func.h"
#include "water_map.h"
#include "tilepainter.h"
#include "tilepainter_map.h"
#include "tile_type.h"
#include "tile_map.h"

#include "safeguards.h"

/**
 * Check if a tile can be painted.
 * @param tile The tile to paint.
 * @return \c true iff the tile can be painted by the current company.
 */
static bool TileCanBePainted(TileIndex tile)
{
	switch (GetTileType(tile)) {
		/* I see a void tile and I want it painted black... */
		case TileType::Void:
			return false;

		/* Some tiles can always be painted, even if it won't actually be visible. */
		case TileType::Clear:
		case TileType::House:
		case TileType::Trees:
		case TileType::Industry: // TODO: Figure out how to handle oil rigs!
			return true;

		/* Coast tiles can be painted. TODO: Draw waves overlay sprite where the painted land meets the water. */
		case TileType::Water:
			return (GetWaterTileType(tile) == WaterTileType::Coast);

		/* Don't allow painting tiles owned by a different human player (AI is fine). */
		case TileType::Railway:
		case TileType::Road:
		case TileType::Station:
		case TileType::TunnelBridge:
		case TileType::Object: {
			Owner owner = GetTileOwner(tile);
			if (owner != _current_company && Company::IsHumanID(owner)) return false;
		}

		default:
			return false;
	}
}

/**
 * Add a TilePaint to a tile's primary paint slot.
 * @param tile The tile to paint.
 * @param paint The paint to add.
 */
/*CommandCost CmdAddPrimaryPaint(TileIndex tile, TilePaint paint)
{
	if (!TileCanBePainted(tile)) return CMD_ERROR; // TODO: Throw more descriptive error.

	SetPrimaryTilePaint(tile, paint);

	return CommandCost();
}*/

/**
 * Remove a TilePaint from a tile's primary paint slot.
 * @param tile The tile to remove the paint from.
 */
/*CommandCost CmdRemovePrimaryPaint(TileIndex tile)
{
	/* If it can't be painted, it can't be un-painted. */
	/*if (!TileCanBePainted(tile)) return CMD_ERROR; // TODO: Throw more descriptive error.

	SetPrimaryTilePaint(tile, TilePaint::None);

	return CommandCost();
}*/

/**
 * Remove any paint from a tile, whether it supports it or not.
 * @param tile The tile to clear.
 */
static void ClearPaintedTile(TileIndex tile)
{
	//CmdRemovePrimaryPaint(tile);
	// TODO: Remove secondary paint.
}
