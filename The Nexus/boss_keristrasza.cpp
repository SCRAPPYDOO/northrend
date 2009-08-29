/*
/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Keristrasza
SD%Complete: 
SDComment: 
SDCategory: The Nexus, The Nexus
EndScriptData */

#include "precompiled.h"
#include "def_nexus.h"

enum
{
	//Achiviement Trinity Support
    //ACHIEVEMENT_INTENSE_COLD                        = 2036,

    //Spells
    SPELL_FROZEN_PRISON                             = 47854,
    SPELL_TAIL_SWEEP                                = 50155,
    SPELL_CRYSTAL_CHAINS                            = 50997,
    SPELL_ENRAGE                                    = 8599,
    SPELL_CRYSTALFIRE_BREATH_N                      = 48096,
    SPELL_CRYSTALFIRE_BREATH_H                      = 57091,
    SPELL_CRYSTALIZE                                = 48179,
    SPELL_INTENSE_COLD                              = 48094,
    SPELL_INTENSE_COLD_TRIGGERED                    = 48095,

    //Yell
    SAY_AGGRO                                    = -1576040,
    SAY_SLAY                                     = -1576041,
    SAY_ENRAGE                                   = -1576042,
    SAY_DEATH                                    = -1576043,
    SAY_CRYSTAL_NOVA                             = -1576044
};

struct MANGOS_DLL_DECL boss_keristraszaAI : public ScriptedAI
{
	boss_keristraszaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsHeroicMode = pCreature->GetMap()->IsHeroic();
		Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsHeroicMode;

    uint32 CRYSTALFIRE_BREATH_Timer;
    uint32 CRYSTAL_CHAINS_CRYSTALIZE_Timer;
    uint32 TAIL_SWEEP_Timer;
    bool Enrage;

    uint32 CheckIntenseColdTimer;
    //bool MoreThanTwoIntenseCold; // needed for achievement: Intense Cold(2036)

    void Reset() 
    {
        CRYSTALFIRE_BREATH_Timer = 14000;
        CRYSTAL_CHAINS_CRYSTALIZE_Timer = m_bIsHeroicMode ? 30000 : 11000;
        TAIL_SWEEP_Timer = 5000;
        Enrage = false;

        CheckIntenseColdTimer = 2000;
        //MoreThanTwoIntenseCold = false;
		m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

		m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        if (m_pInstance && m_pInstance->GetData(DATA_KERISTRASZA_FREED) == DONE)
			m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		else
		{
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->CastSpell(m_creature, SPELL_FROZEN_PRISON, false);
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (m_pInstance && m_pInstance->GetData(DATA_KERISTRASZA_FREED) != DONE && m_pInstance->GetData(DATA_MAGUS_TELESTRA_EVENT) == DONE &&
            m_pInstance->GetData(DATA_ANOMALUS_EVENT) == DONE && m_pInstance->GetData(DATA_ORMOROK_EVENT) == DONE)
        {
            m_pInstance->SetData(DATA_KERISTRASZA_FREED, DONE);
        }
        if (m_pInstance && m_pInstance->GetData(DATA_KERISTRASZA_FREED) == DONE)
        {
            m_creature->RemoveAurasDueToSpell(SPELL_FROZEN_PRISON);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            ScriptedAI::MoveInLineOfSight(who);
        }
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit* killer)  
    {
        DoScriptText(SAY_DEATH, m_creature);
        
		/* Avhiement Trinity Support
        if(m_bIsHeroicMode && !MoreThanTwoIntenseCold)
        {
            AchievementEntry const *AchievIntenseCold = GetAchievementStore()->LookupEntry(ACHIEVEMENT_INTENSE_COLD);
            if(AchievIntenseCold)
            {
                Map *map = m_creature->GetMap();
                if(map && map->IsDungeon())
                {
                    Map::PlayerList const &players = map->GetPlayers();
                    for(Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        itr->getSource()->CompletedAchievement(AchievIntenseCold);
                }
            }
        }
		*/
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(SAY_SLAY, m_creature);
    }

    void UpdateAI(const uint32 diff) 
    {
	    if (!m_creature->SelectHostilTarget() || !m_creature->getVictim() )
           return;  

		if(CheckIntenseColdTimer < diff /*&& !MoreThanTwoIntenseCold*/)
		{
			std::list<HostilReference*> ThreatList = m_creature->getThreatManager().getThreatList();
			for(std::list<HostilReference*>::const_iterator itr = ThreatList.begin(); itr != ThreatList.end(); itr++)
			{
				Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
				target->CastSpell(target, SPELL_INTENSE_COLD_TRIGGERED, true);
			}
			CheckIntenseColdTimer = 1000;
		}else CheckIntenseColdTimer -= diff;

        if (!Enrage && (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.25))
        {
            DoScriptText(SAY_ENRAGE , m_creature);
            DoCast(m_creature, SPELL_ENRAGE);
            Enrage = true;
        }

        if (CRYSTALFIRE_BREATH_Timer < diff)
        {
            DoCast(m_creature->getVictim(), m_bIsHeroicMode ? SPELL_CRYSTALFIRE_BREATH_H : SPELL_CRYSTALFIRE_BREATH_N);
            CRYSTALFIRE_BREATH_Timer = 14000;
        }else CRYSTALFIRE_BREATH_Timer -=diff;

        if (TAIL_SWEEP_Timer < diff)
        {
            DoCast(m_creature, SPELL_TAIL_SWEEP);
            TAIL_SWEEP_Timer = 4000;
        }else TAIL_SWEEP_Timer -=diff;

        if (CRYSTAL_CHAINS_CRYSTALIZE_Timer < diff)
        {
            DoScriptText(SAY_CRYSTAL_NOVA , m_creature);
            if (m_bIsHeroicMode)
                DoCast(m_creature, SPELL_CRYSTALIZE);
            else
                if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_CRYSTAL_CHAINS);
            CRYSTAL_CHAINS_CRYSTALIZE_Timer = m_bIsHeroicMode ? 25000 : 11000;
        }else CRYSTAL_CHAINS_CRYSTALIZE_Timer -= diff;

        DoMeleeAttackIfReady();    
    }
};

CreatureAI* GetAI_boss_keristrasza(Creature *_Creature)
{
    return new boss_keristraszaAI (_Creature);
}

void AddSC_boss_keristrasza()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="boss_keristrasza";
    newscript->GetAI = &GetAI_boss_keristrasza;
    newscript->RegisterSelf();
}
