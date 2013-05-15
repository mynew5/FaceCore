/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "DamageCounter.h"

DamageCounter::DamageCounter()
{
    in_combat = false;
}

DamageCounter::~DamageCounter()
{
    DamageTable.clear();
}

void DamageCounter::CombatBegin(Unit* unit)
{
    in_combat = true;
    begin_time = getMSTime();

    entry = unit->GetEntry();

    if (Map* map = unit->GetMap())
    {
        if (map->IsRaid())
        {
            if (map->Is25ManRaid())
                mode = map->IsHeroic() ? 5 : 3;
            else
                mode = map->IsHeroic() ? 4 : 2;
        }
        else
            mode = map->IsHeroic() ? 1 : 0;
    }
    else
        mode = 0;

    DamageTable.clear();
}

void DamageCounter::InputDamage(Unit* attacker, uint32 damage)
{
    if (!attacker || !in_combat)
        return;

    if (Player* player = attacker->GetCharmerOrOwnerPlayerOrPlayerItself())
        DamageTable[player->GetGUIDLow()] += damage;
}

void DamageCounter::CombatComplete()
{
    if (DamageTable.empty() || !in_combat)
        return;

    in_combat = false;

    float delta_time = float(GetMSTimeDiffToNow(begin_time)) / 1000.0f;

    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    for (std::map<uint32, uint32>::const_iterator itr = DamageTable.begin(); itr != DamageTable.end(); ++itr)
        trans->PAppend("INSERT INTO `dps_counters` (`entry`, `mode`, `guid`, `dps`) VALUES (%d, %d, %d, %f) ON DUPLICATE KEY UPDATE `dps` = GREATEST(`dps`, VALUES(`dps`))", entry, mode, itr->first, float(itr->second) / delta_time);

    CharacterDatabase.CommitTransaction(trans);

    DamageTable.clear();    
}
