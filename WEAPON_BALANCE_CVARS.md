# Weapon Balancing CVars - Enable/Disable Instructions

This document explains how to enable or disable the weapon balancing cvars that were added to MuffMode.

## Overview

The following weapon balancing cvars were added but are currently **disabled** by default:

- `g_chaingun_max_shots` - Maximum shots per frame for chaingun (default: 3)
- `g_chaingun_damage` - Damage per bullet for chaingun (default: 0 = auto, uses 6 DM / 8 coop)
- `g_machinegun_damage` - Damage per bullet for machinegun (default: 0 = auto, uses 8 normal / 5-7 Q3A)
- `g_hyperblaster_speed` - Projectile speed for hyperblaster (default: 0 = auto, uses 1000 normal / 2000 Q3A)
- `g_railgun_damage` - Damage per shot for railgun (default: 0 = auto, uses 100 DM / 150 coop)

## Current Status: DISABLED

The cvars are currently disabled in two places:
1. **Initialization** in `src/g_main.cpp` (lines ~1068-1072)
2. **Usage checks** in `src/p_weapon.cpp` (5 locations with "DISABLED" markers)

## How to ENABLE the CVars

To enable the weapon balancing cvars:

### Step 1: Uncomment Initialization

In `src/g_main.cpp`, find the section around line 1068 and uncomment these lines:

```cpp
// DISABLED: Weapon balancing cvars - uncomment to re-enable
g_chaingun_max_shots = gi.cvar("g_chaingun_max_shots", "3", CVAR_NOFLAGS);
g_chaingun_damage = gi.cvar("g_chaingun_damage", "0", CVAR_NOFLAGS);
g_machinegun_damage = gi.cvar("g_machinegun_damage", "0", CVAR_NOFLAGS);
g_hyperblaster_speed = gi.cvar("g_hyperblaster_speed", "0", CVAR_NOFLAGS);
g_railgun_damage = gi.cvar("g_railgun_damage", "0", CVAR_NOFLAGS);
```

### Step 2: Uncomment Usage Checks

In `src/p_weapon.cpp`, find and uncomment the following sections:

#### Chaingun Damage (around line 1908):
```cpp
// DISABLED: Uncomment below to re-enable chaingun damage cvar
if (g_chaingun_damage->integer > 0)
	damage = g_chaingun_damage->integer;
```

#### Chaingun Max Shots (around line 1958):
```cpp
// DISABLED: Uncomment below to re-enable chaingun max shots cvar
int max_shots = g_chaingun_max_shots->integer;
if (max_shots > 0 && shots > max_shots)
	shots = max_shots;
```

#### Machinegun Damage (around line 1834):
```cpp
// DISABLED: Uncomment below to re-enable machinegun damage cvar
if (g_machinegun_damage->integer > 0)
	damage = g_machinegun_damage->integer;
```

#### Hyperblaster Speed (around line 1703):
```cpp
// DISABLED: Uncomment below to re-enable hyperblaster speed cvar
if (hyper && g_hyperblaster_speed->integer > 0)
	speed = g_hyperblaster_speed->integer;
```

#### Railgun Damage (around line 2125):
```cpp
// DISABLED: Uncomment below to re-enable railgun damage cvar
if (g_railgun_damage->integer > 0)
	damage = g_railgun_damage->integer;
```

### Step 3: Rebuild

After uncommenting, rebuild the project:
```bash
# On Windows
build.bat

# Or use your preferred build method
```

## How to DISABLE the CVars

To disable the cvars again, simply reverse the process:

1. **Comment out** the initialization lines in `src/g_main.cpp` (add `//` before each line)
2. **Comment out** all 5 usage check sections in `src/p_weapon.cpp` (add `//` before each line)
3. Rebuild the project

## Usage Examples (when enabled)

Once enabled, you can use the cvars in-game or in config files:

```bash
# Balance chaingun
set g_chaingun_max_shots 2      # Limit to 2 shots per frame
set g_chaingun_damage 4         # Reduce damage to 4 per bullet

# Balance machinegun
set g_machinegun_damage 7       # Reduce damage to 7 per bullet

# Adjust hyperblaster
set g_hyperblaster_speed 1100   # Increase projectile speed

# Adjust railgun
set g_railgun_damage 90         # Reduce damage to 90
```

## Default Values Reference

When cvars are set to `0` (or not set), weapons use these defaults:

- **Chaingun**: 6 damage (DM) / 8 damage (coop), max 3 shots per frame
- **Machinegun**: 8 damage (normal) / 5-7 damage (Q3A ruleset)
- **Hyperblaster**: 1000 speed (normal) / 2000 speed (Q3A ruleset)
- **Railgun**: 100 damage (DM) / 150 damage (coop)

## Notes

- The cvars are declared in `src/g_local.h` and `src/g_main.cpp` - these should **not** be commented out as they're needed for compilation
- Only the **initialization** and **usage** sections need to be commented/uncommented
- All cvars default to `0`, which means "use default behavior"
- Setting a cvar to `0` after it's been set will restore default behavior

