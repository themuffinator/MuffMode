# Ruleset Differences Reference (Table-Driven)

This document is the authoritative reference for **table/helper-driven ruleset differences** currently implemented in `src/p_weapon.cpp`.

> Scope note: this covers **`g_ruleset` gameplay differences** (applied across gametypes), not high-level gametype flow/rules.

## Ruleset IDs

- `1` = `RS_Q2RE` (Quake II Rerelease)
- `2` = `RS_MM` (Muff Mode)
- `3` = `RS_Q3A` (Quake III Arena style)
- `4` = `RS_VANILLA_PLUS` (Q2RE Balanced)
- `5` = `RS_Q1` (Quake style)
- `6` = `RS_QC` (Quake Champions style)

---

## Pickup / Drop Tuning

### Slug pickup quantity (`Ruleset_SlugPickupQuantity`)

- Q2RE: `10`
- MM: `5`
- Q3A: `10`
- VANILLA_PLUS: `10`
- Q1: `10`
- QC: `10`

### Weapon pickup ammo behavior (`Ruleset_WeaponPickupAmmoQuantity`)

- If map entity sets `count`, use that value.
- Q3A special behavior:
  - For grenades/rockets/slugs: target quantity `10`
  - For other ammo: target quantity `ammo->quantity`
  - If player already has ammo, pickup gives enough to reach target (minimum `1` if already at/above target)
- Non-Q3A:
  - Slugs: use `Ruleset_SlugPickupQuantity`
  - Others: `ammo->quantity`

### Weapon drop ammo behavior (`Ruleset_WeaponDropAmmoQuantity`)

- Railgun drops use `Ruleset_SlugPickupQuantity`
- Other weapons drop `ammo->quantity`

---

## Weapon Differences by Ruleset

## Machinegun

### Damage (`Ruleset_MachinegunDamage`)

- Q3A: `5` in TDM, otherwise `7`
- QC: `6`
- VANILLA_PLUS: `7` in DM only; non-DM falls back to default
- Default fallback (Q2RE/MM/Q1 and non-DM VANILLA_PLUS): `8`

### Spread (`Ruleset_MachinegunSpread`)

- Q3A: `hspread=200`, `vspread=200`
- All others: default bullet spread constants

---

## Chaingun

### Damage (`Ruleset_ChaingunDamage`)

- QC: `4` in DM, `6` in non-DM
- VANILLA_PLUS: `4` in DM
- Default fallback: `6` in DM, `8` in non-DM

### Spread defaults (`Ruleset_ChaingunSpreadDefaults`)

- Default bullet spread + offset `4.0`
- (Debug weapon-balance cvars can override)

---

## Grenade Launcher

### Defaults (`Ruleset_GrenadeLauncherDefaults`)

- Q3A: `damage=100`, `splash_radius=150`, `speed=700`
- All others: `damage=120`, `splash_radius=damage+40` (160), `speed=600`

---

## Rocket Launcher

### Defaults (`Ruleset_RocketLauncherDefaults`)

- MM: `damage=100`, `splash_damage=100`, `radius=120`, `speed=650`
- QC: `damage=100`, `splash_damage=100`, `radius=120`, `speed=750`
- VANILLA_PLUS: `damage=100`, `splash_damage=100`, `radius=120`, `speed=750` (DM) / `650` (non-DM)
- Q3A: `damage=100`, `splash_damage=120`, `radius=120`, `speed=900`
- Q1: `damage=random(100..120)`, `splash_damage=120`, `radius=120`, `speed=1000`
- Default fallback (Q2RE): `damage=random(100..120)`, `splash_damage=120`, `radius=120`, `speed=650`

### Custom-damage variant (`Ruleset_RocketLauncherDefaultsForCustomDamage`)

When debug damage override is active, `damage` is externally set; ruleset still controls splash/speed as above.

---

## Hyper/Blaster

### Projectile speed (`Ruleset_HyperBlasterSpeed`)

- Q3A: hyper `2000`, blaster `2500`
- VANILLA_PLUS: hyper `1100` (DM) / `1000` (non-DM), blaster `1700` (DM) / `1500` (non-DM)
- All others: hyper `1000`, blaster `1500`

### Hyperblaster damage (`Ruleset_HyperBlasterDamage`)

- Q3A: `20` (DM) / `25` (non-DM)
- QC: `12`
- All others: `15` (DM) / `20` (non-DM)

---

## Shotgun

### Damage (`Ruleset_ShotgunDamage`)

- Q3A: `10`
- All others: `4`

### Pellet count (`Ruleset_ShotgunPelletCount`)

- Q3A: `11`
- All others: `12`

---

## Railgun

### Damage (`Ruleset_RailgunDamage`)

- QC: `80`
- All others: `100` (DM) / `150` (non-DM)

### Kick (`Ruleset_RailgunKick`)

- MM: `damage * 2`
- All others: `200` (DM) / `225` (non-DM)

---

## BFG

### Core defaults (`Ruleset_BFGDefaults`)

- Q3A style: `damage=100`, `radius=120`, `speed=1000`
- All others: `damage=200` (DM) / `500` (non-DM), `radius=1000`, `speed=400`

### Style/consumption helpers

- `Ruleset_BFGUsesQ3Style`: true only in Q3A
- `Ruleset_BFGAmmoPerShot`: `10` in Q3A style, else `50`

### Fire frame path

- Q3A style uses Q3A fire frame set
- Non-Q3A uses default BFG fire frame set

---

## Plasma Beam

### Defaults (`Ruleset_PlasmaBeamDefaults`)

- MM / VANILLA_PLUS / QC: `damage=10` (DM) / `15` (non-DM), `kick=damage`
- Q3A: `damage=8` (DM) / `15` (non-DM), `kick=damage`
- Default fallback (Q2RE/Q1): `damage=15`, `kick=75` (DM) / `30` (non-DM)

---

## Ion Ripper

### Damage (`Ruleset_IonRipperDamage`)

- MM: `20` (DM), `50` (non-DM)
- Others: `30` (DM), `50` (non-DM)

### Speed (`Ruleset_IonRipperSpeed`)

- MM: `800`
- Others: `500`

---

## Source of Truth

- `src/p_weapon.cpp` helper block near top of file (all `Ruleset_*` helpers)
- Any future ruleset changes should be reflected in this file and this document in the same change.
