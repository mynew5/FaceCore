# Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  Custom/custom.cpp
  Custom/TrialOfTheChampion/TW_instance_trial_of_the_champion.cpp
  Custom/TrialOfTheChampion/TW_trial_of_the_champion.h
  Custom/TrialOfTheChampion/TW_boss_argent_challenge.cpp
  Custom/TrialOfTheChampion/TW_boss_grand_champions.cpp
  Custom/TrialOfTheChampion/TW_boss_black_knight.cpp
  Custom/TrialOfTheChampion/TW_trial_of_the_champion.cpp
  ${scripts_STAT_SRCS}
  Custom/npc_arena1v1.cpp
  Custom/mod_ArenaWatcher.cpp
  Custom/Transmogrification.h
  Custom/Transmogrification.cpp
  Custom/Transmogrifier.cpp
  Custom/icc_rings.cpp
  Custom/cs_questcompleter.cpp
)

message("  -> Prepared: Custom")
