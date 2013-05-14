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
    // nothing to initialize
}

DamageCounter::~DamageCounter()
{
    DamageTable.clear();
}

void DamageCounter::CombatBegin(Unit* unit)
{
    sWorld->SendWorldText(LANG_AUTO_BROADCAST, "DamageCounter::CombatBegin()");

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
    std::ostringstream ss;
    ss << "DamageCounter::InputDamage() ";

    if (attacker)
    {
        ss << attacker->GetName();
        if (Player* player = attacker->GetCharmerOrOwnerPlayerOrPlayerItself())
            ss << " in behalf of " << player->GetName();
    }
    else
        ss << "UNKNOWN";
    ss << " damaged creature for " << damage << " damage";

    sWorld->SendWorldText(LANG_AUTO_BROADCAST, ss.str().c_str());

    if (!attacker)
        return;

    if (Player* player = attacker->GetCharmerOrOwnerPlayerOrPlayerItself())
        DamageTable[player->GetGUIDLow()] += damage;
}

void DamageCounter::CombatComplete()
{
    sWorld->SendWorldText(LANG_AUTO_BROADCAST, "DamageCounter::CombatComplete()");

    if (DamageTable.empty())
        return;

    float delta_time = float(GetMSTimeDiffToNow(begin_time)) / 1000.0f;

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_DAMAGECOUNTER_LOG);

    for (std::map<uint32, uint32>::const_iterator itr = DamageTable.begin(); itr != DamageTable.end(); ++itr)
    {
        std::ostringstream ss;
        ss << "GUID:" << itr->first << " did " << itr->second << " total damage";
        sWorld->SendWorldText(LANG_AUTO_BROADCAST, ss.str().c_str());

        stmt->setUInt32(0, entry);
        stmt->setUInt32(1, mode);
        stmt->setUInt32(2, itr->first);
        stmt->setFloat(3, float(itr->second) / delta_time);
        trans->Append(stmt);
    }

    CharacterDatabase.CommitTransaction(trans);

    DamageTable.clear();    
}
