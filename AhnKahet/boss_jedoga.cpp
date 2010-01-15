/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Jedoga
SD%Complete: 20%
SDComment:
SDCategory: Ahn'kahet
EndScriptData */

#include "precompiled.h"

enum Sounds
{
    SAY_AGGRO                           = -1619017,
    SAY_CALL_SACRIFICE_1                = -1619018,
    SAY_CALL_SACRIFICE_2                = -1619019,
    SAY_SACRIFICE_1                     = -1619020,
    SAY_SACRIFICE_2                     = -1619021,
    SAY_SLAY_1                          = -1619022,
    SAY_SLAY_2                          = -1619023,
    SAY_SLAY_3                          = -1619024,
    SAY_DEATH                           = -1619025,
    SAY_PREACHING_1                     = -1619026,
    SAY_PREACHING_2                     = -1619027,
    SAY_PREACHING_3                     = -1619028,
    SAY_PREACHING_4                     = -1619029,
    SAY_PREACHING_5                     = -1619030,

    SAY_VOLUNTEER_1                     = -1619031,         //said by the volunteer image
    SAY_VOLUNTEER_2                     = -1619032
};

enum Spells
{
    SPELL_CYCLONE_STRIKE                = 56855,
    SPELL_LIGHTING_BOLT                 = 56981,
    SPELL_THUNDER_SHOCK                 = 56926,
    SPELL_GIFT                          = 56219,
};

enum Creatures
{
    CREATURE_VOLUNTEER                  = 30385,
};

/*######
## boss_jedoga
######*/

struct MANGOS_DLL_DECL boss_jedogaAI : public ScriptedAI
{
    boss_jedogaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsSacrifice;

    uint64 m_uiVolunteerGUID;
    uint32 m_uiCycloneTimer;
    uint32 m_uiBoltTimer;
    uint32 m_uiThunderTimer;
    uint32 m_uiNextSurificeTimer;
    uint32 m_uiSacrificeTimer;

    void Reset()
    {
        m_bIsSacrifice = false;

        m_uiVolunteerGUID     = 0;
        m_uiCycloneTimer      = 0;
        m_uiBoltTimer         = 0;
        m_uiThunderTimer      = 0;
        m_uiNextSurificeTimer = 0;
        m_uiSacrificeTimer    = 0;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //timer sprawdzania co sekunde czy mobek zyje
        //jezlein ie wroc  na ziemie


        if(m_bIsSacrifice)
            if(m_uiSacrificeTimer < uiDiff)
            {
                //jezeli mobek zyje cast gift
                if(Unit* Volunteer = Unit::GetUnit(*m_creature, m_uiVolunteerGUID))
                    if(Volunteer->isAlive())
                    {
                        m_creature->CastSpell(m_creature, SPELL_GIFT, false);
                        m_uiVolunteerGUID = 0;
                        Volunteer->SetVisibility(VISIBILITY_ON);
                    }
                    else
                    {
                        //zdejmij unatackable wroc na ziemie
                    }
                m_bIsSacrifice = false;
            }else m_uiSacrificeTimer -= uiDiff;

        if(m_uiNextSurificeTimer < uiDiff)
        {
            //relocate creature w powietrze latanie :X stop movement
            m_creature->StopMoving();
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()+10, m_creature->GetOrientation());
            // podzielic na fazy ??
            //m_creature set  unatackable
            if(Creature* Volunteer = m_creature->SummonCreature(CREATURE_VOLUNTEER, m_creature->GetPositionX()+5, m_creature->GetPositionY()+3, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 20000))
                m_uiVolunteerGUID = Volunteer->GetGUID();
            m_bIsSacrifice = true;
            m_uiSacrificeTimer = 10000; // ?
            m_uiNextSurificeTimer = 0;
        }else m_uiNextSurificeTimer -= uiDiff;

        if(m_uiCycloneTimer < uiDiff)
        {

            m_uiCycloneTimer = 0;
        }else m_uiCycloneTimer -= uiDiff;

        if(m_uiBoltTimer < uiDiff)
        {

            m_uiBoltTimer = 0;
        }else m_uiBoltTimer -= uiDiff;

        if(m_uiThunderTimer < uiDiff)
        {

            m_uiThunderTimer = 0;
        }else m_uiThunderTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_jedoga(Creature* pCreature)
{
    return new boss_jedogaAI(pCreature);
}

void AddSC_boss_jedoga()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_jedoga";
    newscript->GetAI = &GetAI_boss_jedoga;
    newscript->RegisterSelf();
}
