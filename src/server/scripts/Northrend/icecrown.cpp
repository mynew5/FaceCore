/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
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

/* ScriptData
SDName: Icecrown
SD%Complete: 100
SDComment: Quest support: 12807
SDCategory: Icecrown
EndScriptData */

/* ContentData
npc_arete
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_arete
######*/

#define GOSSIP_ARETE_ITEM1 "Lord-Commander, I would hear your tale."
#define GOSSIP_ARETE_ITEM2 "<You nod slightly but do not complete the motion as the Lord-Commander narrows his eyes before he continues.>"
#define GOSSIP_ARETE_ITEM3 "I thought that they now called themselves the Scarlet Onslaught?"
#define GOSSIP_ARETE_ITEM4 "Where did the grand admiral go?"
#define GOSSIP_ARETE_ITEM5 "That's fine. When do I start?"
#define GOSSIP_ARETE_ITEM6 "Let's finish this!"
#define GOSSIP_ARETE_ITEM7 "That's quite a tale, Lord-Commander."

enum eArete
{
    GOSSIP_TEXTID_ARETE1        = 13525,
    GOSSIP_TEXTID_ARETE2        = 13526,
    GOSSIP_TEXTID_ARETE3        = 13527,
    GOSSIP_TEXTID_ARETE4        = 13528,
    GOSSIP_TEXTID_ARETE5        = 13529,
    GOSSIP_TEXTID_ARETE6        = 13530,
    GOSSIP_TEXTID_ARETE7        = 13531,

    QUEST_THE_STORY_THUS_FAR    = 12807
};

class npc_arete : public CreatureScript
{
public:
    npc_arete() : CreatureScript("npc_arete") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_THE_STORY_THUS_FAR) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE1, creature->GetGUID());
            return true;
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE2, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE3, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE4, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE5, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE6, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE7, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(QUEST_THE_STORY_THUS_FAR);
                break;
        }

        return true;
    }
};

/*######
## npc_alorah_and_grimmin
######*/

enum ealorah_and_grimmin
{
    SPELL_CHAIN                     = 68341,
    NPC_FJOLA_LIGHTBANE             = 36065,
    NPC_EYDIS_DARKBANE              = 36066,
    NPC_PRIESTESS_ALORAH            = 36101,
    NPC_PRIEST_GRIMMIN              = 36102
};

class npc_alorah_and_grimmin : public CreatureScript
{
public:
    npc_alorah_and_grimmin() : CreatureScript("npc_alorah_and_grimmin") { }

    struct npc_alorah_and_grimminAI : public ScriptedAI
    {
        npc_alorah_and_grimminAI(Creature* creature) : ScriptedAI(creature) {}

        bool uiCast;

        void Reset()
        {
            uiCast = false;
        }

        void UpdateAI(const uint32 /*uiDiff*/)
        {
            if (uiCast)
                return;
            uiCast = true;
            Creature* target = NULL;

            switch (me->GetEntry())
            {
                case NPC_PRIESTESS_ALORAH:
                    target = me->FindNearestCreature(NPC_EYDIS_DARKBANE, 10.0f);
                    break;
                case NPC_PRIEST_GRIMMIN:
                    target = me->FindNearestCreature(NPC_FJOLA_LIGHTBANE, 10.0f);
                    break;
            }
            if (target)
                DoCast(target, SPELL_CHAIN);

            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_alorah_and_grimminAI(creature);
    }
};

/*######
## npc_guardian_pavilion
######*/

enum eGuardianPavilion
{
    SPELL_TRESPASSER_H                            = 63987,
    AREA_SUNREAVER_PAVILION                       = 4676,

    AREA_SILVER_COVENANT_PAVILION                 = 4677,
    SPELL_TRESPASSER_A                            = 63986,
};

class npc_guardian_pavilion : public CreatureScript
{
public:
    npc_guardian_pavilion() : CreatureScript("npc_guardian_pavilion") { }

    struct npc_guardian_pavilionAI : public Scripted_NoMovementAI
    {
        npc_guardian_pavilionAI(Creature* creature) : Scripted_NoMovementAI(creature) {}

        void MoveInLineOfSight(Unit* who)
        {
            if (me->GetAreaId() != AREA_SUNREAVER_PAVILION && me->GetAreaId() != AREA_SILVER_COVENANT_PAVILION)
                return;

            if (!who || who->GetTypeId() != TYPEID_PLAYER || !me->IsHostileTo(who) || !me->isInBackInMap(who, 5.0f))
                return;

            if (who->HasAura(SPELL_TRESPASSER_H) || who->HasAura(SPELL_TRESPASSER_A))
                return;

            if (who->ToPlayer()->GetTeamId() == TEAM_ALLIANCE)
                who->CastSpell(who, SPELL_TRESPASSER_H, true);
            else
                who->CastSpell(who, SPELL_TRESPASSER_A, true);

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_guardian_pavilionAI(creature);
    }
};

/*######
## npc_vereth_the_cunning
######*/

enum eVerethTheCunning
{
    NPC_GEIST_RETURN_BUNNY_KC   = 31049,
    NPC_LITHE_STALKER           = 30894,
    SPELL_SUBDUED_LITHE_STALKER = 58151,
};

class npc_vereth_the_cunning : public CreatureScript
{
public:
    npc_vereth_the_cunning() : CreatureScript("npc_vereth_the_cunning") { }

    struct npc_vereth_the_cunningAI : public ScriptedAI
    {
        npc_vereth_the_cunningAI(Creature* creature) : ScriptedAI(creature) {}

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetEntry() == NPC_LITHE_STALKER && me->IsWithinDistInMap(who, 10.0f))
            {
                if (Unit* owner = who->GetCharmer())
                {
                    if (who->HasAura(SPELL_SUBDUED_LITHE_STALKER))
                        {
                            owner->ToPlayer()->KilledMonsterCredit(NPC_GEIST_RETURN_BUNNY_KC, 0);
                            who->ToCreature()->DisappearAndDie();

                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vereth_the_cunningAI(creature);
    }
};


/*########
## npc_the_ocular
#########*/

enum TheOcularSpells
{
    SPELL_THE_OCULAR_TRANSFORM                              = 55162,
    SPELL_DEATHLY_STARE                                     = 55269,
    SPELL_ITS_ALL_FUN_AND_GAMES_THE_OCULAR_ON_DEATH         = 55288,
    SPELL_ITS_ALL_FUN_AND_GAMES_THE_OCULAR_KILL_CREDIT      = 55289
};

enum ReqCreatures
{
   NPC_THE_OCULAR                                  = 29747,
   NPC_THE_OCULAR_DESTROYED_KILL_CREDIT_BUNNY      = 29803
};

class npc_the_ocular : public CreatureScript
{
public:
    npc_the_ocular() : CreatureScript("npc_the_ocular") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_the_ocularAI (pCreature);
    }

    struct npc_the_ocularAI : public Scripted_NoMovementAI
    {
        npc_the_ocularAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature){ }

        uint32 uiDeathlyStareTimer;

        void Reset()
        {
            uiDeathlyStareTimer = (urand (5000,7000));
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            me->LowerPlayerDamageReq(damage);
        }

        void JustDied (Unit* killer)
        {
            if(killer && killer->ToPlayer())
                killer->ToPlayer()->CastSpell(killer,SPELL_ITS_ALL_FUN_AND_GAMES_THE_OCULAR_KILL_CREDIT,true);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!me->HasAura(SPELL_THE_OCULAR_TRANSFORM))
                DoCast(me,SPELL_THE_OCULAR_TRANSFORM,true);

            if (!UpdateVictim())
                return;

            if (uiDeathlyStareTimer <= uiDiff)
            {
                DoCastVictim(SPELL_DEATHLY_STARE);
                uiDeathlyStareTimer = (urand (7000,9000));
            }
            else uiDeathlyStareTimer -= uiDiff;
        }
    };
};

/*########
## npc_general_lightsbane
#########*/

enum eGeneralLightsbaneSpells
{
    SPELL_CLEAVE                = 15284,
    SPELL_DEATH_AND_DECAY       = 60160,
    SPELL_PLAGUE_STRIKE         = 60186,
};

enum eNpcs
{
    ENTRY_VILE                  = 29860,
    ENTRY_THE_LEAPER            = 29859,
    ENTRY_LADY_NIGHTSWOOD       = 29858,
};

class npc_general_lightsbane : public CreatureScript
{
public:
    npc_general_lightsbane() : CreatureScript("npc_general_lightsbane") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_general_lightsbaneAI (pCreature);
    }

    struct npc_general_lightsbaneAI : public ScriptedAI
    {
        npc_general_lightsbaneAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        uint32 uiCleave_Timer;
        uint32 uiDeathDecay_Timer;
        uint32 uiPlagueStrike_Timer;
        uint32 uiSummonSupport_Timer;
        bool supportSummoned;

        void Reset()
        {
            uiCleave_Timer = urand (2000,3000);
            uiDeathDecay_Timer = urand (15000,20000);
            uiPlagueStrike_Timer = urand (5000,10000);

            std::list<Creature*> TargetList;
            me->GetCreatureListWithEntryInGrid(TargetList,me->GetEntry(), 100.0f);
            if(TargetList.size() > 1)
            {
                me->DespawnOrUnsummon(1000);
            }

            uiSummonSupport_Timer = 5000;
            supportSummoned = false;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if(!supportSummoned)
                if (uiSummonSupport_Timer <= uiDiff)
                {
                    Creature* temp = DoSummon(ENTRY_VILE,me,5,20000,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT);
                    temp->AI()->AttackStart(me);

                    temp = DoSummon(ENTRY_THE_LEAPER,me,5,20000,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT);
                    temp->AI()->AttackStart(me);

                    temp = DoSummon(ENTRY_LADY_NIGHTSWOOD,me,5,20000,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT);
                    temp->AI()->AttackStart(me);

                    uiSummonSupport_Timer = (urand (4000,5000));
                    supportSummoned = true;
                }
                else uiSummonSupport_Timer -= uiDiff;

            if (uiCleave_Timer <= uiDiff)
            {
                DoCastVictim(SPELL_CLEAVE);
                uiCleave_Timer = (urand (4000,5000));
            }
            else uiCleave_Timer -= uiDiff;

            if (uiDeathDecay_Timer <= uiDiff)
            {
                DoCastVictim(SPELL_DEATH_AND_DECAY);
                uiDeathDecay_Timer = urand (15000,20000);
            }
            else uiDeathDecay_Timer -= uiDiff;

            if (uiPlagueStrike_Timer <= uiDiff)
            {
                DoCastVictim(SPELL_PLAGUE_STRIKE);
                uiPlagueStrike_Timer = urand (5000,10000);
            }
            else uiPlagueStrike_Timer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };
};

/*########
## Saronite Mine Slave
#########*/

enum eEntrysSlaveToSaronite
{
    QUEST_SLAVES_TO_SARONITE_ALLIANCE       = 13300,
    QUEST_SLAVES_TO_SARONITE_HORDE          = 13302,

    ENTRY_SLAVE_QUEST_CREDIT                = 31866,

    SPELL_SLAVE_ENRAGE                      = 8599,
    SPELL_HEAD_CRACK                        = 3148,

    ACTION_ENRAGED                          = 0,
    ACTION_INSANE                           = 1,
    ACTION_FREED                            = 2,
};

const Position FreedPos[2] =
{
    { 7030.0f,  1862.0f, 533.2f, 0.0f },
    { 6947.0f,  2027.0f, 519.7f, 0.0f }
};

#define GOSSIP_OPTION_FREE  "Go on, you're free. Get out of here!"

#define SAY_SLAVE_AGGRO_1 "AHAHAHAHA... you'll join us soon enough!"
#define SAY_SLAVE_AGGRO_2 "I don't want to leave! I want to stay here!"
#define SAY_SLAVE_AGGRO_3 "I won't leave!"
#define SAY_SLAVE_AGGRO_4 "NO! You're wrong! The voices in my head are beautiful!"

#define SAY_SLAVE_INSANE_1 "I must get further underground to where he is. I must jump!"
#define SAY_SLAVE_INSANE_2 "I'll never return. The whole reason for my existence awaits below!"
#define SAY_SLAVE_INSANE_3 "I'm coming, master!"
#define SAY_SLAVE_INSANE_4 "My life for you!"

class npc_saronite_mine_slave : public CreatureScript
{
public:
    npc_saronite_mine_slave() : CreatureScript("npc_saronite_mine_slave") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if ((player->GetQuestStatus(QUEST_SLAVES_TO_SARONITE_HORDE) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(QUEST_SLAVES_TO_SARONITE_ALLIANCE) == QUEST_STATUS_INCOMPLETE) )
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_FREE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();

        if (uiAction == (GOSSIP_ACTION_INFO_DEF + 1))
        {
            creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
            if(urand(0,1) == 0)
            {
                creature->AI()->DoAction(ACTION_FREED);
                player->KilledMonsterCredit(ENTRY_SLAVE_QUEST_CREDIT,0);
            }else
            {
                if(urand(0,1) == 0)
                {
                    creature->AI()->DoAction(ACTION_ENRAGED);
                    creature->setFaction(16);
                    creature->CastSpell(creature,SPELL_SLAVE_ENRAGE);
                    creature->AI()->AttackStart(player);
                }else creature->AI()->DoAction(ACTION_INSANE);
            }
        }
        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_saronite_mine_slaveAI (pCreature);
    }

    struct npc_saronite_mine_slaveAI : public ScriptedAI
    {
        npc_saronite_mine_slaveAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            alreadyFreed = false;
            enraged = false;
        }

        bool enraged;
        bool alreadyFreed;

        uint32 uiHeadCrack_Timer;

        void DoAction(const int32 action)
        {
            switch(action)
            {
            case ACTION_ENRAGED:
                enraged = true;
                alreadyFreed = true;
                switch(urand(0,3))
                {
                case 0:
                    me->MonsterYell(SAY_SLAVE_AGGRO_1,LANG_UNIVERSAL,me->GetGUID());
                    break;
                case 1:
                    me->MonsterYell(SAY_SLAVE_AGGRO_2,LANG_UNIVERSAL,me->GetGUID());
                    break;
                case 2:
                    me->MonsterYell(SAY_SLAVE_AGGRO_3,LANG_UNIVERSAL,me->GetGUID());
                    break;
                case 3:
                    me->MonsterYell(SAY_SLAVE_AGGRO_4,LANG_UNIVERSAL,me->GetGUID());
                    break;
                }
                break;
            case ACTION_FREED:
                alreadyFreed = true;
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(0,FreedPos[0]);
                me->DespawnOrUnsummon(15000);
                break;
            case ACTION_INSANE:
                alreadyFreed = true;
                switch(urand(0,3))
                {
                case 0:
                    me->MonsterYell(SAY_SLAVE_INSANE_1,LANG_UNIVERSAL,me->GetGUID());
                    break;
                case 1:
                    me->MonsterYell(SAY_SLAVE_INSANE_2,LANG_UNIVERSAL,me->GetGUID());
                    break;
                case 2:
                    me->MonsterYell(SAY_SLAVE_INSANE_3,LANG_UNIVERSAL,me->GetGUID());
                    break;
                case 3:
                    me->MonsterYell(SAY_SLAVE_INSANE_4,LANG_UNIVERSAL,me->GetGUID());
                    break;
                }
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(0,FreedPos[1]);
                me->DespawnOrUnsummon(15000);
                break;
            }
        }

        void MoveInLineOfSight(Unit* mover)
        {
            if(!enraged)
                return;

            ScriptedAI::MoveInLineOfSight(mover);
        }

        void AttackStart(Unit* attacker)
        {
            if(!enraged)
                return;

            ScriptedAI::AttackStart(attacker);
        }

        void Reset()
        {
            me->RestoreFaction();
            if(alreadyFreed)
            {
                alreadyFreed = false;
                me->DespawnOrUnsummon(10000);
            }else
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                alreadyFreed = false;
                enraged = false;
            }
        }

        void EnterCombat(Unit* who)
        {
            uiHeadCrack_Timer = urand(5000,7000);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiHeadCrack_Timer <= uiDiff)
            {
                DoCastVictim(SPELL_HEAD_CRACK);
                uiHeadCrack_Timer = (urand (7000,9000));
            }
            else uiHeadCrack_Timer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_icecrown()
{
    new npc_arete;
    new npc_alorah_and_grimmin;
    new npc_guardian_pavilion;
    new npc_vereth_the_cunning;
    new npc_the_ocular();
    new npc_general_lightsbane();
    new npc_saronite_mine_slave();
}
