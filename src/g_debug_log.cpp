// Copyright (c) ZeniMax Media Inc.
// Licensed under the GNU General Public License 2.0.

#include "g_local.h"
#include "g_debug_log.h"
#include <fstream>
#include <ctime>
#include <cstdarg>
#include <cstdio>

// ==================== CENTRALIZED DEBUG LOGGING ====================
// All MuffMode debug logs go to muffmode_debug.log, controlled by g_muffmode_debug cvar

extern cvar_t *g_muffmode_debug;

namespace {
	std::ofstream g_muffmode_log;
	bool g_log_initialized = false;
	
	void EnsureLogInitialized()
	{
		if (!g_log_initialized)
		{
			// Open log file in truncate mode (clear old log)
			g_muffmode_log.open("muffmode_debug.log", std::ios::trunc);
			if (g_muffmode_log.is_open())
			{
				time_t now = time(nullptr);
				char timestamp[64];
				strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
				g_muffmode_log << "==========================================\n";
				g_muffmode_log << "MuffMode Debug Log Started: " << timestamp << "\n";
				g_muffmode_log << "==========================================\n";
				g_muffmode_log.flush();
			}
			g_log_initialized = true;
		}
	}
}

void MuffModeLog(const char* category, const char* format, ...)
{
	// Check if debug logging is enabled
	if (!g_muffmode_debug || !g_muffmode_debug->integer)
		return;
	
	EnsureLogInitialized();
	
	if (!g_muffmode_log.is_open())
		return;

	// Get timestamp
	time_t now = time(nullptr);
	char timestamp[32];
	strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&now));

	// Format message
	char buffer[512];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	// Write to log: [TIME] [CATEGORY] message
	g_muffmode_log << "[" << timestamp << "] [" << category << "] " << buffer << std::endl;
	g_muffmode_log.flush(); // Ensure it's written immediately
}

void MuffModeLog_Separator()
{
	if (!g_muffmode_debug || !g_muffmode_debug->integer)
		return;
	
	EnsureLogInitialized();
	
	if (!g_muffmode_log.is_open())
		return;
	
	g_muffmode_log << "----------------------------------------\n";
	g_muffmode_log.flush();
}

