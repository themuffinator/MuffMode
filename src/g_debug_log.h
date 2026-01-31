// Copyright (c) ZeniMax Media Inc.
// Licensed under the GNU General Public License 2.0.

#pragma once

// ==================== CENTRALIZED DEBUG LOGGING ====================
// All MuffMode debug logs go to muffmode_debug.log, controlled by g_muffmode_debug cvar

void MuffModeLog(const char* category, const char* format, ...);
void MuffModeLog_Separator();

