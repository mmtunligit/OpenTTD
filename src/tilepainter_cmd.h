/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <https://www.gnu.org/licenses/old-licenses/gpl-2.0>.
 */

/** @file tilepainter_cmd.h Command definitions related to tile painter. */

#ifndef TILEPAINTER_CMD_H
#define TILEPAINTER_CMD_H

#include "command_type.h"
#include "tilepainter.h"

bool TileCanBePainted(TileIndex tile);
void ClearPaintedTile(TileIndex tile);

CommandCost CmdAddPrimaryPaint(TileIndex tile, TilePaint paint);
//CommandCost CmdRemovePrimaryPaint(TileIndex tile); NOTE do you need this? i feel like the other one could just be paint tile and if right click is held it clears the paint

//DEF_CMD_TRAIT(Commands::AddPrimaryPaint, CmdAddPrimaryPaint, CommandFlag::NoWater, CommandType::LandscapeConstruction)

#endif /* TILEPAINTER_CMD_H */
