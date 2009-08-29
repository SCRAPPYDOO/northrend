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

/* ScriptData
SDName: boss_krikthir_the_gatewatcher
SDAuthor: ScrappyDoo
SD%Complete: 95% 
SDComment: completed
SDCategory: Azjol Nerub
EndScriptData */

#include "precompiled.h"
#include "def_azjol-nerub.h"

enum
{
//KirikThir Spell
SPELL_MIND_FLAY                    = 52586,
H_SPELL_MIND_FLAY                  = 59367,
SPELL_CURSE_OF_FATIGUE             = 52592,
H_SPELL_CURSE_OF_FATIGUE           = 59368,
SPELL_FRENZY                       = 28747,

MOB_SKITTERING_SWARMER              = 28735,
MOB_SKITTERING_SWARMER_INFECTOR     = 28736,

//Silthil Spell
SPELL_POISON_SPRAY					= 52493,
H_SPELL_POISON_SPRAY				= 59366,
//Grash Spells
SPELL_ENRAGE						= 52470,
//Nargij Spell
SPELL_BINDINGS_WEBS					= 52524,
H_SPELL_BINDINGS_WEBS				= 59365,
//mini boss spells
SPELL_INFECTED_BITE					= 52469,
H_SPELL_INFECTED_BITE				= 59364,
SPELL_WEBWARP						= 52086,

//Yell
SAY_AGGRO                                   = -1601011,
SAY_SLAY_1                                  = -1601012,
SAY_SLAY_2                                  = -1601013,
SAY_SLAY_3                                  = -1601014,
SAY_DEATH                                   = -1601015,
SAY_SEND_GROUP_1                            = -1601018,
SAY_SEND_GROUP_2                            = -1601019,
SAY_SEND_GROUP_3                            = -1601020,
SAY_SWARM_1                                 = -1601016,
SAY_SWARM_2                                 = -1601017,
SAY_PREFIGHT_1                              = -1601021,
SAY_PREFIGHT_2                              = -1601022,
SAY_PREFIGHT_3                              = -1601023,
};

struct MANGOS_DLL_DECL boss_krik_thirAI : public ScriptedAI
{
    boss_krik_thirAI(Creature *pCreature) : ScriptedAI(pCreature) 
	{
	    m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsHeroicMode = pCreature->GetMap()->IsHeroic();
		Reset();
	}

	ScriptedInstance* m_pInstance;
    bool m_bIsHeroicMode;
	bool m_bIsEnraged;
	bool speak;
	uint32 m_uiMindFlyTimer;
	uint32 m_uiSwarmTimer;
	uint32 m_uiCurseTimer;

    void Reset() 
	{
		m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

		m_uiMindFlyTimer = 15000+rand()%5000;
		m_uiSwarmTimer	 = 15000;
		m_uiCurseTimer	 = 25000+rand()%10000;
	}

    void MoveInLineOfSight(Unit *who)
	{
		if(speak)
		{
			switch(rand()%3)
			{
				case 0: DoScriptText(SAY_PREFIGHT_1, m_creature);break;
				case 1: DoScriptText(SAY_PREFIGHT_2, m_creature);break;
				case 2: DoScriptText(SAY_PREFIGHT_3, m_creature);break;
			}
			speak = false;
		}

		if (m_pInstance && m_pInstance->GetData(DATA_SILTHIK_EVENT) == DONE &&
			m_pInstance->GetData(DATA_GASHRA_EVENT) == DONE && m_pInstance->GetData(DATA_NARJIL_EVENT) == DONE)
		{
			m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			Aggro(who);
		}
    }

    void Aggro(Unit* who)
    {
        DoScriptText(SAY_AGGRO, m_creature);
		if(!m_creature->getVictim())
			m_creature->AI()->AttackStart(who);
    }

    void JustDied(Unit* killer)
    {
        DoScriptText(SAY_DEATH, m_creature);
		if (m_pInstance)
            m_pInstance->SetData(TYPE_KRIKTHIR, DONE);
    }

	void SummonSwarm()
	{
		for(uint8 j=0; j<15; j++)
		{
			Creature* Summoned = m_creature->SummonCreature(MOB_SKITTERING_SWARMER, m_creature->GetPositionX()+rand()%20, m_creature->GetPositionY()+rand()%20, m_creature->GetPositionZ()+rand()%20, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
			if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				Summoned->AI()->AttackStart(target);
		}

		for(uint8 k=0; k<3; k++)
		{
			Creature* Summoned = m_creature->SummonCreature(MOB_SKITTERING_SWARMER_INFECTOR, m_creature->GetPositionX()+rand()%20, m_creature->GetPositionY()+rand()%20, m_creature->GetPositionZ()+rand()%20, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
			if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				Summoned->AI()->AttackStart(target);
		}
	}

    void KilledUnit(Unit *victim)
    {
        if (victim == m_creature)
            return;

        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature);break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature);break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature);break;
        }
	}

	void UpdateAI(const uint32 diff)
    {
		if(!m_creature->SelectHostilTarget() || !m_creature->getVictim() )
		   return;  

		if((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 10)
		{
			if(!m_bIsEnraged)
			{
				DoCast(m_creature, SPELL_FRENZY);
				m_bIsEnraged = true;
			}
		}

		if(m_uiMindFlyTimer < diff)
		{
			Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0);
			DoCast(target, m_bIsHeroicMode ? H_SPELL_MIND_FLAY : SPELL_MIND_FLAY, false); 
			m_uiMindFlyTimer = 15000+rand()%5000;
		}m_uiMindFlyTimer -= diff;

		if(m_uiCurseTimer < diff)
		{
			Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0);
			m_creature->CastSpell(target, m_bIsHeroicMode ? H_SPELL_CURSE_OF_FATIGUE : SPELL_CURSE_OF_FATIGUE, false); 
			m_uiCurseTimer = 25000+rand()%10000;
		}m_uiCurseTimer -= diff;

		if(m_uiSwarmTimer < diff)
		{
			switch(rand()%2)
			{
				case 0: DoScriptText(SAY_SWARM_1, m_creature);break;
				case 1: DoScriptText(SAY_SWARM_2, m_creature);break;
			}
			SummonSwarm();
			m_uiSwarmTimer = 15000;
		}m_uiSwarmTimer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_krik_thir(Creature *_Creature)
{
    return new boss_krik_thirAI (_Creature);
}

//Silithik
struct MANGOS_DLL_DECL mob_silthikAI : public ScriptedAI
{
    mob_silthikAI(Creature *c) : ScriptedAI(c)
    {
		m_pInstance = (ScriptedInstance*)c->GetInstanceData();
		m_bIsHeroicMode = c->GetMap()->IsHeroic();
		Reset();
    }

    ScriptedInstance* m_pInstance;
	bool m_bIsHeroicMode;

	uint32 PoisonSprayTimer;
	uint32 InfectedBiteTimer;
	uint32 WebWarpTimer;

    void Reset()
    {
		PoisonSprayTimer = 5000;
		InfectedBiteTimer = 1000;
		WebWarpTimer = 15000+rand()%10000;
    }

	void MoveInLineOfSight(Unit *who)
	{
		if(m_pInstance && m_pInstance->GetData(DATA_NARJIL_EVENT) == DONE)
			Aggro(who);
	}

	void Aggro(Unit *who)
	{
		DoScriptText(SAY_SEND_GROUP_1, m_creature);
		if(!m_creature->getVictim())
			m_creature->AI()->AttackStart(who);
	}

    void JustDied(Unit *killer)
    {
		if (m_pInstance)
            m_pInstance->SetData(DATA_SILTHIK_EVENT, DONE);
    }

    void UpdateAI(const uint32 diff) 
    {
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

		if(PoisonSprayTimer <diff)
		{
			if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				m_creature->CastSpell(target, m_bIsHeroicMode ? H_SPELL_POISON_SPRAY : SPELL_POISON_SPRAY, false);
			PoisonSprayTimer = 10000;
		}PoisonSprayTimer -= diff;

		if(InfectedBiteTimer < diff)
		{
			DoCast(m_creature->getVictim(), m_bIsHeroicMode ? H_SPELL_INFECTED_BITE : SPELL_INFECTED_BITE); 
			InfectedBiteTimer = 9000;
		}InfectedBiteTimer -= diff;

		if(WebWarpTimer <diff)
		{
			if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				m_creature->CastSpell(target, SPELL_WEBWARP, false);
			WebWarpTimer = 25000;
		}WebWarpTimer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_silthik(Creature *_Creature)
{
    return new mob_silthikAI (_Creature);
}

//Gashra
struct MANGOS_DLL_DECL mob_gashraAI : public ScriptedAI
{
    mob_gashraAI(Creature *c) : ScriptedAI(c)
    {
		m_pInstance = (ScriptedInstance*)c->GetInstanceData();
		m_bIsHeroicMode = c->GetMap()->IsHeroic();
		Reset();
    }

    ScriptedInstance* m_pInstance;
	bool m_bIsHeroicMode;

	uint32 EnrageTimer;
	uint32 InfectedBiteTimer;
	uint32 WebWarpTimer;

    void Reset()
    {
		EnrageTimer = 5000;
		InfectedBiteTimer = 1000;
		WebWarpTimer = 15000+rand()%10000;
    }

	void MoveInLineOfSight(Unit *who)
	{
		if(m_pInstance && m_pInstance->GetData(DATA_SILTHIK_EVENT) == DONE)
			Aggro(who);
	}

	void Aggro(Unit *who)
	{
		DoScriptText(SAY_SEND_GROUP_2, m_creature);
		if(!m_creature->getVictim())
			m_creature->AI()->AttackStart(who);
	}

    void JustDied(Unit *killer)
    {
		if (m_pInstance)
            m_pInstance->SetData(DATA_GASHRA_EVENT, DONE);
    }

    void UpdateAI(const uint32 diff) 
    {
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

		if(EnrageTimer <diff)
		{
			DoCast(m_creature, SPELL_ENRAGE);
			EnrageTimer = 15000+rand()%5000;
		}EnrageTimer -= diff;

		if(InfectedBiteTimer < diff)
		{
			DoCast(m_creature->getVictim(), m_bIsHeroicMode ? H_SPELL_INFECTED_BITE : SPELL_INFECTED_BITE); 
			InfectedBiteTimer = 9000;
		}InfectedBiteTimer -= diff;

		if(WebWarpTimer <diff)
		{
			if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				m_creature->CastSpell(target, SPELL_WEBWARP, false);
			WebWarpTimer = 25000;
		}WebWarpTimer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_gashra(Creature *_Creature)
{
    return new mob_gashraAI (_Creature);
}

//Gashra
struct MANGOS_DLL_DECL mob_narjilAI : public ScriptedAI
{
    mob_narjilAI(Creature *c) : ScriptedAI(c)
    {
		m_pInstance = (ScriptedInstance*)c->GetInstanceData();
		m_bIsHeroicMode = c->GetMap()->IsHeroic();
		Reset();
    }

    ScriptedInstance* m_pInstance;
	bool m_bIsHeroicMode;

	uint32 WebTimer;
	uint32 InfectedBiteTimer;
	uint32 WebWarpTimer;

    void Reset()
    {
		WebTimer = 5000;
		InfectedBiteTimer = 1000;
		WebWarpTimer = 15000+rand()%10000;
    }

	void MoveInLineOfSight(Unit *who)
	{
		if(m_pInstance && m_pInstance->GetData(DATA_GASHRA_EVENT) == DONE)
			Aggro(who);
	}

	void Aggro(Unit *who)
	{
		DoScriptText(SAY_SEND_GROUP_3, m_creature);
		if(!m_creature->getVictim())
			m_creature->AI()->AttackStart(who);
	}

    void JustDied(Unit *killer)
    {
		if (m_pInstance)
            m_pInstance->SetData(DATA_NARJIL_EVENT, DONE);
    }

    void UpdateAI(const uint32 diff) 
    {
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

		if(WebTimer <diff)
		{
			DoCast(m_creature->getVictim(), m_bIsHeroicMode ? H_SPELL_BINDINGS_WEBS : SPELL_BINDINGS_WEBS);
			WebTimer = 15000+rand()%5000;
		}WebTimer -= diff;

		if(InfectedBiteTimer < diff)
		{
			DoCast(m_creature->getVictim(), m_bIsHeroicMode ? H_SPELL_INFECTED_BITE : SPELL_INFECTED_BITE); 
			InfectedBiteTimer = 9000;
		}InfectedBiteTimer -= diff;

		if(WebWarpTimer <diff)
		{
			if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
				m_creature->CastSpell(target, SPELL_WEBWARP, false);
			WebWarpTimer = 25000;
		}WebWarpTimer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_narjil(Creature *_Creature)
{
    return new mob_narjilAI (_Creature);
}

void AddSC_boss_krik_thir()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="boss_krik_thir";
    newscript->GetAI = &GetAI_boss_krik_thir;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name="mob_silthik";
    newscript->GetAI = &GetAI_mob_silthik;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name="mob_gashra";
    newscript->GetAI = &GetAI_mob_gashra;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name="mob_narjil";
    newscript->GetAI = &GetAI_mob_narjil;
    newscript->RegisterSelf();
}
