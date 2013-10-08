/*
 *
 * Copyright (C) 2013 Emu-Devstore <http://emu-devstore.com/>
 * Written by Teiby <http://www.teiby.de/>
 *
 */

#ifndef ARENA_1V1_H
#define ARENA_1V1_H

// TalentTab.dbc -> TalentTabID
const uint32 FORBIDDEN_TALENTS_IN_1V1_ARENA[] = 
{
    // Healer
    201, // Priest Discipline
    202, // Priest Holy
    382, // Paladin Holy
    262, // Shaman Restoration
    282, // Druid Restoration

    // Tanks
    //383, // Paladin Protection
    //163, // Warrior Protection

    0 // End
};


// Return false, if player have invested more than 35 talentpoints in a forbidden talenttree.
static bool Arena1v1CheckTalents(Player* player)
{
    if(!player)
        return false;

    if(sWorld->getBoolConfig(CONFIG_ARENA_1V1_BLOCK_FORBIDDEN_TALENTS) == false)
        return true;

    uint32 count = 0;
    for (uint32 talentId = 0; talentId < sTalentStore.GetNumRows(); ++talentId)
    {
        TalentEntry const* talentInfo = sTalentStore.LookupEntry(talentId);

        if (!talentInfo)
            continue;

        for (int8 rank = MAX_TALENT_RANK-1; rank >= 0; --rank)
        {
            if (talentInfo->RankID[rank] == 0)
                continue;
                        
            if (player->HasTalent(talentInfo->RankID[rank], player->GetActiveSpec()))
            {
                for(int8 i = 0; FORBIDDEN_TALENTS_IN_1V1_ARENA[i] != 0; i++)
                    if(FORBIDDEN_TALENTS_IN_1V1_ARENA[i] == talentInfo->TalentTab)
                        count += rank + 1;
            }
        }
    }

    if(count >= 36)
    {
        ChatHandler(player->GetSession()).SendSysMessage("You can't join, because you have invested to much points in a forbidden talent. Please edit your talents.");
        return false;
    }
    else
        return true;
}

#endif