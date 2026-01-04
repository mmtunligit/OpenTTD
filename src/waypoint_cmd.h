/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <https://www.gnu.org/licenses/old-licenses/gpl-2.0>.
 */

/** @file waypoint_cmd.h Command definitions related to waypoints. */

#ifndef WAYPOINT_CMD_H
#define WAYPOINT_CMD_H

#include "command_type.h"
#include "command_func.h"
#include "station_type.h"


enum StationClassID : uint16_t;
enum RoadStopClassID : uint16_t;

CommandCost CmdBuildRailWaypoint(DoCommandFlags flags, TileIndex start_tile, Axis axis, uint8_t width, uint8_t height, StationClassID spec_class, uint16_t spec_index, StationID station_to_join, bool adjacent);
CommandCost CmdRemoveFromRailWaypoint(DoCommandFlags flags, TileIndex start, TileIndex end, bool keep_rail);
CommandCost CmdBuildRoadWaypoint(DoCommandFlags flags, TileIndex start_tile, Axis axis, uint8_t width, uint8_t height, std::vector<RoadStopClassID> spec_classes, std::vector<uint16_t> spec_indicies, StationID station_to_join, bool adjacent);
CommandCost CmdRemoveFromRoadWaypoint(DoCommandFlags flags, TileIndex start, TileIndex end);
CommandCost CmdBuildBuoy(DoCommandFlags flags, TileIndex tile);
CommandCost CmdRenameWaypoint(DoCommandFlags flags, StationID waypoint_id, const std::string &text);
std::tuple<CommandCost, StationID> CmdMoveWaypointName(DoCommandFlags flags, StationID waypoint_id, TileIndex tile);

DEF_CMD_TRAIT(CMD_BUILD_RAIL_WAYPOINT,       CmdBuildRailWaypoint,      {},        CommandType::LandscapeConstruction)
DEF_CMD_TRAIT(CMD_REMOVE_FROM_RAIL_WAYPOINT, CmdRemoveFromRailWaypoint, {},        CommandType::LandscapeConstruction)
DEF_CMD_TRAIT(CMD_BUILD_ROAD_WAYPOINT,       CmdBuildRoadWaypoint,      {},        CommandType::LandscapeConstruction)
DEF_CMD_TRAIT(CMD_REMOVE_FROM_ROAD_WAYPOINT, CmdRemoveFromRoadWaypoint, {},        CommandType::LandscapeConstruction)
DEF_CMD_TRAIT(CMD_BUILD_BUOY,                CmdBuildBuoy,              CommandFlag::Auto, CommandType::LandscapeConstruction)
DEF_CMD_TRAIT(CMD_RENAME_WAYPOINT,           CmdRenameWaypoint,         {},        CommandType::OtherManagement)
DEF_CMD_TRAIT(CMD_MOVE_WAYPOINT_NAME,        CmdMoveWaypointName,       {},        CommandType::OtherManagement)

void CcMoveWaypointName(Commands cmd, const CommandCost &result, StationID waypoint_id);

template <typename Tcont, typename Titer>
inline EndianBufferWriter<Tcont, Titer> &operator <<(EndianBufferWriter<Tcont, Titer> &buffer, const std::vector<RoadStopClassID> &classes)
{
	int size = classes.size();
	buffer << size;
	for (const RoadStopClassID &cls : classes) {
		buffer << cls;
	}
	return buffer;
}

inline EndianBufferReader &operator >>(EndianBufferReader &buffer, std::vector<RoadStopClassID> &classes)
{
	int size;
	buffer >> size;
	classes.reserve(size);
	RoadStopClassID cls;
	for (int i = 0; i != size; i++) {
		buffer >> cls;
		classes.emplace_back(cls);
	}
	return buffer;
}

template <typename Tcont, typename Titer>
inline EndianBufferWriter<Tcont, Titer> &operator <<(EndianBufferWriter<Tcont, Titer> &buffer, const std::vector<uint16_t> &ids)
{
	int size = ids.size();
	buffer << size;
	for (const uint16_t &id : ids) {
		buffer << id;
	}
	return buffer;
}

inline EndianBufferReader &operator >>(EndianBufferReader &buffer, std::vector<uint16_t> &ids)
{
	int size;
	buffer >> size;
	ids.reserve(size);
	RoadStopClassID id;
	for (int i = 0; i != size; i++) {
		buffer >> id;
		ids.emplace_back(id);
	}
	return buffer;
}

#endif /* WAYPOINT_CMD_H */
