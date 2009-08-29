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
SDName: Boss_Telestra
SD%Complete: 95%
SDComment: Playable Normal Heroic Support
SDCategory: Nexus
EndScriptData */

#include "precompiled.h"
#include "def_nexus.h"

enum
{
	SPELL_ICE_NOVA_N          = 47772,
    SPELL_ICE_NOVA_H          = 56935,
    SPELL_FIREBOMB_N          = 47773,
    SPELL_FIREBOMB_H          = 56934,
    SPELL_GRAVITY_WELL        = 47756,
	SPELL_GRAVITY_WELL_EFFECT = 32265,
    SPELL_TELESTRA_BACK       = 47714,
	SPELL_FIREBALL_VOLLEY	  = 43240,	

	//At 50% HP - 3 clones, Frost, Fire, Arcane (and in 15% HP in Heroic)
    MOB_FIRE_MAGUS            = 26928,
    MOB_FROST_MAGUS           = 26930,
    MOB_ARCANE_MAGUS          = 26929,

    SPELL_FIRE_MAGUS_VISUAL   = 47705,
    SPELL_FROST_MAGUS_VISUAL  = 47706,
    SPELL_ARCANE_MAGUS_VISUAL = 47704,

	//Yell
    SAY_AGGRO                 = -1576000,
    SAY_KILL                  = -1576001,
    SAY_DEATH                 = -1576002,
    SAY_MERGE                 = -1576003,
    SAY_SPLIT_1               = -1576004,
    SAY_SPLIT_2               = -1576005
};

float CenterOfRoom[1][4] =
{
    {504.80, 89.07, -16.12, 6.27}
};

/*######
## boss_telestra
######*/

struct MANGOS_DLL_DECL boss_telestraAI : public ScriptedAI
{
    boss_telestraAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsHeroicMode = pCreature->GetMap()->IsHeroic();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsHeroicMode;

    uint64 FireMagusGUID;
    uint64 FrostMagusGUID;
    uint64 ArcaneMagusGUID;
    bool FireMagusDead;
    bool FrostMagusDead;
    bool ArcaneMagusDead;

    uint32 AppearDelay_Timer;
    bool AppearDelay;

	bool bGravityWell;

    uint8 Phase;
	uint8 i;

	uint32 uiGravityWellTimer;                   
    uint32 SPELL_FIREBOMB_Timer;                    
    uint32 SPELL_GRAVITY_WELL_Timer;
	uint32 SPELL_ICE_NOVA_Timer;  
    uint32 Cooldown;

    void Reset()
    {
        Phase = 0;     
		SPELL_ICE_NOVA_Timer =  7000;  
        SPELL_FIREBOMB_Timer =  0;                
        SPELL_GRAVITY_WELL_Timer = 13000;
        Cooldown = 0;

		bGravityWell = false;

        FireMagusGUID = 0;
        FrostMagusGUID = 0;
        ArcaneMagusGUID = 0;

        AppearDelay = false;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);

        if(m_pInstance)
            m_pInstance->SetData(DATA_MAGUS_TELESTRA_EVENT, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
		if (m_pInstance)
            m_pInstance->SetData(DATA_MAGUS_TELESTRA_EVENT, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (rand()%2)
            DoScriptText(SAY_KILL, m_creature);
    }

    uint64 SplitPersonality(uint32 entry)
    {
        Creature* Summoned = m_creature->SummonCreature(entry, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
        if (Summoned)
        {
            switch (entry)
            {
                case MOB_FIRE_MAGUS:
                {
                    Summoned->CastSpell(Summoned, SPELL_FIRE_MAGUS_VISUAL, false);
                    break;
                }
                case MOB_FROST_MAGUS:
                {
                    Summoned->CastSpell(Summoned, SPELL_FROST_MAGUS_VISUAL, false);
                    break;
                }
                case MOB_ARCANE_MAGUS:
                {
                    Summoned->CastSpell(Summoned, SPELL_ARCANE_MAGUS_VISUAL, false);
                    break;
                }
            }
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                Summoned->AI()->AttackStart(target);
            return Summoned->GetGUID();
        }
        return 0;
    }
    
    void UpdateAI(const uint32 diff) 
    {
	    if (!m_creature->SelectHostilTarget() || !m_creature->getVictim() )
           return;

		if (AppearDelay)
		{
			m_creature->StopMoving();
			m_creature->AttackStop();
			if (AppearDelay_Timer < diff)
			{
				m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				AppearDelay = false;
				SPELL_GRAVITY_WELL_Timer = 500;
			}else AppearDelay_Timer -= diff;
			return;
		}

		if ((Phase == 1)||(Phase == 3))
		{
			Unit* FireMagus;
			Unit* FrostMagus;
			Unit* ArcaneMagus;
			if (FireMagusGUID)
				FireMagus = Unit::GetUnit((*m_creature), FireMagusGUID);
			if (FrostMagusGUID)
				FrostMagus = Unit::GetUnit((*m_creature), FrostMagusGUID);
			if (ArcaneMagusGUID)
				ArcaneMagus = Unit::GetUnit((*m_creature), ArcaneMagusGUID);
			if (FireMagus && FireMagus->isDead())
				FireMagusDead = true;
			if (FrostMagus && FrostMagus->isDead())
				FrostMagusDead = true;
			if (ArcaneMagus && ArcaneMagus->isDead())
				ArcaneMagusDead = true;
			if (FireMagusDead && FrostMagusDead && ArcaneMagusDead)
			{
				m_creature->GetMotionMaster()->Clear();
				m_creature->GetMap()->CreatureRelocation(m_creature, CenterOfRoom[0][0], CenterOfRoom[0][1], CenterOfRoom[0][2], CenterOfRoom[0][3]);
				DoCast(m_creature, SPELL_TELESTRA_BACK);
				m_creature->SetVisibility(VISIBILITY_ON);
				if (Phase == 1)
					Phase = 2;
				if (Phase == 3)
					Phase = 4;
				FireMagusGUID = 0;
				FrostMagusGUID = 0;
				ArcaneMagusGUID = 0;
				AppearDelay = true;
				AppearDelay_Timer = 4000;
				DoScriptText(SAY_MERGE, m_creature);
			}else
				return;
		}

		if ((Phase == 0) && (m_creature->GetHealth() <= (m_creature->GetMaxHealth() * 0.5)))
		{     
			Phase = 1;
			m_creature->CastStop();
			m_creature->SetVisibility(VISIBILITY_OFF);
			m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			FireMagusGUID = SplitPersonality(MOB_FIRE_MAGUS);
			FrostMagusGUID = SplitPersonality(MOB_FROST_MAGUS); 
			ArcaneMagusGUID = SplitPersonality(MOB_ARCANE_MAGUS);
			FireMagusDead = false;
			FrostMagusDead = false;
			ArcaneMagusDead = false;
			switch(rand()%2)
			{
				case 0: DoScriptText(SAY_SPLIT_1, m_creature); break;
				case 1: DoScriptText(SAY_SPLIT_2, m_creature); break;
			}
			return;
		}

		if (m_bIsHeroicMode && (Phase == 2) && (m_creature->GetHealth() <= (m_creature->GetMaxHealth() * 0.15))) 
		{     
			Phase = 3;
			m_creature->CastStop();
			m_creature->SetVisibility(VISIBILITY_OFF);
			m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			FireMagusGUID = SplitPersonality(MOB_FIRE_MAGUS);
			FrostMagusGUID = SplitPersonality(MOB_FROST_MAGUS); 
			ArcaneMagusGUID = SplitPersonality(MOB_ARCANE_MAGUS);
			FireMagusDead = false;
			FrostMagusDead = false;
			ArcaneMagusDead = false;
			switch(rand()%2)
			{
				case 0: DoScriptText(SAY_SPLIT_1, m_creature); break;
				case 1: DoScriptText(SAY_SPLIT_2, m_creature); break;
			}
			return;
		}

		if(Cooldown)
		{
			if(Cooldown < diff)
			{
				Cooldown = 0;
			}
			else
			{
				Cooldown -= diff;
				return;                                     
			}
		}

		if(i>4)
			bGravityWell = false;

		if(bGravityWell)
			if(uiGravityWellTimer < diff)
			{
				DoCast(m_creature, SPELL_GRAVITY_WELL_EFFECT, true);
				uiGravityWellTimer = 1250;
				Cooldown = 0;
				i++;
				SPELL_GRAVITY_WELL_Timer = 13000;
				SPELL_FIREBOMB_Timer = 2000;
			}uiGravityWellTimer -= diff;

		if (SPELL_GRAVITY_WELL_Timer < diff)
		{
			if (Unit* target = m_creature->getVictim())
				DoCast(target, SPELL_GRAVITY_WELL, true);
			uiGravityWellTimer = 150;
			bGravityWell = true;
			i = 0;
			Cooldown = 0;
			SPELL_GRAVITY_WELL_Timer = 13000;
		}else SPELL_GRAVITY_WELL_Timer -=diff;

        if (SPELL_ICE_NOVA_Timer < diff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            {
                DoCast(target, m_bIsHeroicMode ? SPELL_ICE_NOVA_H : SPELL_ICE_NOVA_N);
                Cooldown = 1500;
            }
            SPELL_ICE_NOVA_Timer = 15000;
        }else SPELL_ICE_NOVA_Timer -=diff;

		if (SPELL_FIREBOMB_Timer < diff)
		{
			if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
			{
				DoCast(target, m_bIsHeroicMode ? SPELL_FIREBOMB_H : SPELL_FIREBOMB_N);
				Cooldown = 1600;
			}
			SPELL_FIREBOMB_Timer = 1500;
		}else SPELL_FIREBOMB_Timer -=diff;

		DoMeleeAttackIfReady(); 
    }
};

CreatureAI* GetAI_boss_telestra(Creature* pCreature)
{
    return new boss_telestraAI(pCreature);
}

void AddSC_boss_telestra()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_telestra";
    newscript->GetAI = &GetAI_boss_telestra;
    newscript->RegisterSelf();
}
