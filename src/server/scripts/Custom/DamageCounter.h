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

#ifndef DAMAGECOUNTER_H
#define DAMAGECOUNTER_H

#include "Database/DatabaseEnv.h"
#include "Player.h"

class DamageCounter
{
    public:
        DamageCounter();
        ~DamageCounter();
        void CombatBegin(Unit* unit);
        void InputDamage(Unit* attacker, uint32 damage);
        void CombatComplete();
    private:
        uint32 entry;
        uint32 mode;
        uint32 begin_time;
        std::map<uint32, uint32> DamageTable;
};

#endif
