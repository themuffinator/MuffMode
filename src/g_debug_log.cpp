// Copyright (c) ZeniMax Media Inc.
// Licensed under the GNU General Public License 2.0.

#include "g_local.h"
#include "g_debug_log.h"
#include <fstream>
#include <ctime>
#include <cstdarg>
#include <cstdio>
#ifdef _WIN32
#include <sys/stat.h>
#include <io.h>
#else
#include <sys/stat.h>
#endif

// ==================== CENTRALIZED DEBUG LOGGING ====================
// All MuffMode debug logs go to muffmode_debug.log, controlled by g_muffmode_debug cvar

extern cvar_t *g_muffmode_debug;

namespace {
	std::ofstream g_muffmode_log;
	bool g_log_initialized = false;
	
	bool ShouldTruncateLog()
	{
		// Check if log file exists
#ifdef _WIN32
		struct _stat fileInfo;
		if (_stat("muffmode_debug.log", &fileInfo) != 0)
#else
		struct stat fileInfo;
		if (stat("muffmode_debug.log", &fileInfo) != 0)
#endif
		{
			// File doesn't exist, should truncate (create new)
			return true;
		}
		
		// Get file modification time
		time_t fileTime = fileInfo.st_mtime;
		struct tm* fileTm = localtime(&fileTime);
		
		// Get current time
		time_t now = time(nullptr);
		struct tm* nowTm = localtime(&now);
		
		// Compare dates (year, month, day)
		// If file date is different from today, truncate (new day started)
		if (fileTm->tm_year != nowTm->tm_year ||
			fileTm->tm_mon != nowTm->tm_mon ||
			fileTm->tm_mday != nowTm->tm_mday)
		{
			return true; // Different day, truncate
		}
		
		return false; // Same day, append
	}
	
	void EnsureLogInitialized()
	{
		if (!g_log_initialized)
		{
			// Check if we should truncate (new day) or append (same day)
			bool shouldTruncate = ShouldTruncateLog();
			std::ios_base::openmode mode = shouldTruncate ? std::ios::trunc : std::ios::app;
			
			// Open log file in appropriate mode
			g_muffmode_log.open("muffmode_debug.log", mode);
			if (g_muffmode_log.is_open())
			{
				time_t now = time(nullptr);
				char timestamp[64];
				strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
				
				if (shouldTruncate)
				{
					// New day - write header
					g_muffmode_log << "==========================================\n";
					g_muffmode_log << "MuffMode Debug Log Started: " << timestamp << "\n";
					g_muffmode_log << "==========================================\n";
				}
				else
				{
					// Same day - just add a separator to show continuation
					g_muffmode_log << "\n----------------------------------------\n";
					g_muffmode_log << "Log Continued: " << timestamp << "\n";
					g_muffmode_log << "----------------------------------------\n";
				}
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

