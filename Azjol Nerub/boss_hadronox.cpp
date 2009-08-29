/*
 * Copyright (C) 2009 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* Script Data Start
SDName: Boss hadronox
SDAuthor: ScrappyDoo
SD%Complete: 95%
SDComment: pre event not made yet
SDCategory:
Script Data End */

/*** SQL START ***
update creature_template set scriptname = 'boss_hadronox' where entry = '';
*** SQL END ***/

#include "precompiled.h"
#include "def_azjol-nerub.h"

enum
{
	SPELL_WEB_FRONT_DOORS				= 53177, 

	SPELL_ACID_CLOUD					= 53400,
	H_SPELL_ACID_CLOUD					= 59419,
	SPELL_LEECH_POISON					= 53030,
	H_SPELL_LEECH_POISON				= 59417,
	SPELL_LEECH_POISON_DEADTRIGGER		= 53800, 
	SPELL_PIERCE_ARMOR					= 53418,
	SPELL_WEB_GRAB						= 53406,
	H_SPELL_WEB_GRAB					= 59420,

	MOB_CRUSHER							= 28922,
	MOB_CRYPTFIEND						= 29118,
	MOB_CHAMPION						= 29117,
};

float MobPos[6][3] =
{
	{515.017,562.666,734.367},
	{541.832,556.990,731.922},
	{508.719,562.489,734.799},
	{536.496,558.947,732.412},
	{520.641,562.366,733.852},
	{546.612,554.267,731.487},
};

struct MANGOS_DLL_DECL boss_hadronoxAI : public ScriptedAI
{
    boss_hadronoxAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsHeroicMode = pCreature->GetMap()->IsHeroic();
        Reset();
    }

	ScriptedInstance* m_pInstance;
    bool m_bIsHeroicMode;
	bool m_bIsSpawned;
	//bool m_bIsPhase;

	//bool Crusher1Dead;
	//bool Crusher2Dead;

	//uint64 Crusher1GUID;
	//uint64 Crusher2GUID;

	uint32 uiAcidCloudTimer;
	uint32 uiLeechPoisonTimer;
	uint32 uiPierceArmorTimer;
	uint32 uiWebGrabTimer;

    void Reset() 
	{
		//Timers
		uiAcidCloudTimer = 12000;
		uiLeechPoisonTimer = 10000;
		uiPierceArmorTimer = 7000;
		uiWebGrabTimer = 20000;

		//Crusher1GUID = 0;
		//Crusher2GUID = 0;

		//Crusher1Dead = false;
		//Crusher2Dead = false;

		//m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		//m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		//m_creature->SetVisibility(VISIBILITY_OFF);
		m_bIsSpawned = false;
		//m_bIsPhase = true;

	}

    void MoveInLineOfSight(Unit *who)
	{
		if(m_pInstance && m_pInstance->GetData(DATA_CRUSHER_EVENT) == DONE)
		{
			if(!m_bIsSpawned)
			{
				//m_creature->SetVisibility(VISIBILITY_ON);
				//m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				//m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				Aggro(who);
				//SpawnMobs();
				m_bIsSpawned = true;
			}
		}
	}

	void SpawnMobs() 
	{
		//Creature* Crusher = m_creature->SummonCreature(MOB_CRUSHER	, MobPos[0][0], MobPos[0][1], MobPos[0][2], 4, TEMPSUMMON_CORPSE_DESPAWN, 1000);
		//Crusher1GUID = Crusher->GetGUID();
        //Creature* Crusher1 = m_creature->SummonCreature(MOB_CRUSHER	, MobPos[1][0], MobPos[1][1], MobPos[1][2], 4, TEMPSUMMON_CORPSE_DESPAWN, 1000);
		//Crusher2GUID = Crusher1->GetGUID();
	}

    void Aggro(Unit* who) 
	{
		if(!m_creature->getVictim())
			m_creature->AI()->AttackStart(who);
	}

    void JustDied(Unit* killer)  {}

    void KilledUnit(Unit *victim)
    {
        if (victim == m_creature)
            return;

		if(victim->HasAura(m_bIsHeroicMode ? H_SPELL_LEECH_POISON : SPELL_LEECH_POISON))
			DoCast(m_creature, SPELL_LEECH_POISON_DEADTRIGGER);
    }

    void UpdateAI(const uint32 diff)
    {
		/*
		if(m_bIsPhase)
		{
			Unit* Crusher1;
			Unit* Crusher2;
			if (Crusher1GUID)
				Crusher1 = Unit::GetUnit((*m_creature), Crusher1GUID);
			if (Crusher2GUID)
				Crusher2 = Unit::GetUnit((*m_creature), Crusher2GUID);
			if (Crusher1 && Crusher1->isDead() )
				Crusher1Dead = true;
			if (Crusher2 && Crusher2->isDead())
				Crusher2Dead = true;
			if (Crusher1Dead && Crusher2Dead)
			{
				m_creature->GetMotionMaster()->Clear();
				m_creature->SetVisibility(VISIBILITY_ON);
				m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				m_bIsPhase = false;
	
				Crusher1GUID = 0;
				Crusher2GUID = 0;
			}
		} */

		//Return since we have no target
		if (!m_creature->SelectHostilTarget() || !m_creature->getVictim() )
		   return;  

		if(uiPierceArmorTimer < diff)
		{
			DoCast(m_creature->getVictim(), SPELL_PIERCE_ARMOR); 
			uiPierceArmorTimer = 8000+rand()%8000;
		}uiPierceArmorTimer -= diff;

		if(uiAcidCloudTimer < diff)
		{
			if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				m_creature->CastSpell(target, m_bIsHeroicMode ? H_SPELL_ACID_CLOUD : SPELL_ACID_CLOUD, false);
			uiAcidCloudTimer = 25000+rand()%10000;
		}uiAcidCloudTimer -= diff;

		if(uiLeechPoisonTimer < diff)
		{
			for(uint8 i=0; i<3; ++i)
			{
				if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
					m_creature->CastSpell(target, m_bIsHeroicMode ? H_SPELL_LEECH_POISON : SPELL_LEECH_POISON, false);
			}
			uiLeechPoisonTimer = 10000;
		}uiLeechPoisonTimer -= diff;

		if(uiWebGrabTimer < diff)
		{
			DoCast(m_creature->getVictim(), m_bIsHeroicMode ? H_SPELL_WEB_GRAB : SPELL_WEB_GRAB);
			uiWebGrabTimer = 25000+rand()%10000;
		}uiWebGrabTimer -= diff;

		DoMeleeAttackIfReady();

    }
};

CreatureAI* GetAI_boss_hadronox(Creature *_Creature)
{
    return new boss_hadronoxAI (_Creature);
}

void AddSC_boss_hadronox()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="boss_hadronox";
    newscript->GetAI = &GetAI_boss_hadronox;
    newscript->RegisterSelf();
}
