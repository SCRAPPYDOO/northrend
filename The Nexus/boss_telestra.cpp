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
#include "nexus.h"

enum Sounds
{
    SAY_AGGRO                 = -1576000,
    SAY_KILL                  = -1576001,
    SAY_DEATH                 = -1576002,
    SAY_MERGE                 = -1576003,
    SAY_SPLIT_1               = -1576004,
    SAY_SPLIT_2               = -1576005
};

enum Spells
{
	SPELL_ICE_NOVA_N          = 47772,
    SPELL_ICE_NOVA_H          = 56935,
    SPELL_FIREBOMB_N          = 47773,
    SPELL_FIREBOMB_H          = 56934,
    SPELL_GRAVITY_WELL        = 47756,
	SPELL_GRAVITY_WELL_EFFECT = 32265,
    SPELL_TELESTRA_BACK       = 47714,
	SPELL_FIREBALL_VOLLEY	  = 43240,	

    SPELL_FIRE_MAGUS_VISUAL   = 47705,
    SPELL_FROST_MAGUS_VISUAL  = 47706,
    SPELL_ARCANE_MAGUS_VISUAL = 47704
};

enum Creatures
{
    MOB_FIRE_MAGUS            = 26928,
    MOB_FROST_MAGUS           = 26930,
    MOB_ARCANE_MAGUS          = 26929
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
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool   m_bIsRegularMode;

    uint64 m_uiFireMagusGUID;
    uint64 m_uiFrostMagusGUID;
    uint64 m_uiArcaneMagusGUID;
    bool   m_bIsFireMagusDead;
    bool   m_bIsFrostMagusDead;
    bool   m_bIsArcaneMagusDead;

    uint32 m_uiAppearDelayTimer;
    bool   m_bIsAppearDelay;

	bool   m_bIsGravityWell;

    uint8  m_uiPhase;
	uint8  m_uiGravityCount;

	uint32 m_uiGravityWellTimer;                   
    uint32 m_uiFireBombTimer;                    
    uint32 m_uiSpellGravityWellTimer;
	uint32 m_uiIceNovaTimer;  
    uint32 m_uiCooldown;

    void Reset()
    {
        m_uiPhase                   = 0;     
		m_uiIceNovaTimer            = 7000;  
        m_uiFireBombTimer           = 0;                
        m_uiSpellGravityWellTimer   = 13000;
        m_uiCooldown                = 0;

		m_bIsGravityWell            = false;

        m_uiFireMagusGUID           = 0;
        m_uiFrostMagusGUID          = 0;
        m_uiArcaneMagusGUID         = 0;

        m_bIsAppearDelay            = false;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);

        if(m_pInstance)
            m_pInstance->SetData(TYPE_TELESTRA, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
		if (m_pInstance)
            m_pInstance->SetData(TYPE_TELESTRA, DONE);
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
	    if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
           return;

		if (m_bIsAppearDelay)
		{
			m_creature->StopMoving();
			m_creature->AttackStop();
			if (m_uiAppearDelayTimer < diff)
			{
				m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				m_bIsAppearDelay = false;
				m_uiSpellGravityWellTimer = 500;
			}else m_uiAppearDelayTimer -= diff;
			return;
		}

		if ((m_uiPhase == 1)||(m_uiPhase == 3))
		{
			Unit* FireMagus;
			Unit* FrostMagus;
			Unit* ArcaneMagus;
			if (m_uiFireMagusGUID)
				FireMagus = Unit::GetUnit((*m_creature), m_uiFireMagusGUID);
			if (m_uiFrostMagusGUID)
				FrostMagus = Unit::GetUnit((*m_creature), m_uiFrostMagusGUID);
			if (m_uiArcaneMagusGUID)
				ArcaneMagus = Unit::GetUnit((*m_creature), m_uiArcaneMagusGUID);
			if (FireMagus && FireMagus->isDead())
				m_bIsFireMagusDead = true;
			if (FrostMagus && FrostMagus->isDead())
				m_bIsFrostMagusDead = true;
			if (ArcaneMagus && ArcaneMagus->isDead())
				m_bIsArcaneMagusDead = true;
			if (m_bIsFireMagusDead && m_bIsFrostMagusDead && m_bIsArcaneMagusDead)
			{
				m_creature->GetMotionMaster()->Clear();
				m_creature->GetMap()->CreatureRelocation(m_creature, CenterOfRoom[0][0], CenterOfRoom[0][1], CenterOfRoom[0][2], CenterOfRoom[0][3]);
				DoCast(m_creature, SPELL_TELESTRA_BACK);
				m_creature->SetVisibility(VISIBILITY_ON);
				if (m_uiPhase == 1)
					m_uiPhase = 2;
				if (m_uiPhase == 3)
					m_uiPhase = 4;
				m_uiFireMagusGUID = 0;
				m_uiFrostMagusGUID = 0;
				m_uiArcaneMagusGUID = 0;
				m_bIsAppearDelay = true;
				m_uiAppearDelayTimer = 4000;
				DoScriptText(SAY_MERGE, m_creature);
			}else
				return;
		}

		if ((m_uiPhase == 0) && (m_creature->GetHealth() <= (m_creature->GetMaxHealth() * 0.5)))
		{     
			m_uiPhase = 1;
			m_creature->CastStop();
			m_creature->SetVisibility(VISIBILITY_OFF);
			m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			m_uiFireMagusGUID    = SplitPersonality(MOB_FIRE_MAGUS);
			m_uiFrostMagusGUID   = SplitPersonality(MOB_FROST_MAGUS); 
			m_uiArcaneMagusGUID  = SplitPersonality(MOB_ARCANE_MAGUS);
			m_bIsFireMagusDead   = false;
			m_bIsFrostMagusDead  = false;
			m_bIsArcaneMagusDead = false;
			switch(rand()%2)
			{
				case 0: DoScriptText(SAY_SPLIT_1, m_creature); break;
				case 1: DoScriptText(SAY_SPLIT_2, m_creature); break;
			}
			return;
		}

		if (m_bIsRegularMode && (m_uiPhase == 2) && (m_creature->GetHealth() <= (m_creature->GetMaxHealth() * 0.15))) 
		{     
			m_uiPhase = 3;
			m_creature->CastStop();
			m_creature->SetVisibility(VISIBILITY_OFF);
			m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			m_uiFireMagusGUID    = SplitPersonality(MOB_FIRE_MAGUS);
			m_uiFrostMagusGUID   = SplitPersonality(MOB_FROST_MAGUS); 
			m_uiArcaneMagusGUID  = SplitPersonality(MOB_ARCANE_MAGUS);
			m_bIsFireMagusDead   = false;
			m_bIsFrostMagusDead  = false;
			m_bIsArcaneMagusDead = false;
			switch(rand()%2)
			{
				case 0: DoScriptText(SAY_SPLIT_1, m_creature); break;
				case 1: DoScriptText(SAY_SPLIT_2, m_creature); break;
			}
			return;
		}

		if(m_uiCooldown)
		{
			if(m_uiCooldown < diff)
			{
				m_uiCooldown = 0;
			}
			else
			{
				m_uiCooldown -= diff;
				return;                                     
			}
		}

		if(m_uiGravityCount>4)
			m_bIsGravityWell = false;

		if(m_bIsGravityWell)
			if(m_uiGravityWellTimer < diff)
			{
				DoCast(m_creature, SPELL_GRAVITY_WELL_EFFECT, true);
				m_uiGravityWellTimer = 1250;
				m_uiCooldown = 0;
				++m_uiGravityCount;
				m_uiSpellGravityWellTimer = 13000;
				m_uiFireBombTimer = 2000;
			}m_uiGravityWellTimer -= diff;

		if (m_uiSpellGravityWellTimer < diff)
		{
			if (Unit* target = m_creature->getVictim())
				DoCast(target, SPELL_GRAVITY_WELL, true);
			m_uiGravityWellTimer = 150;
			m_bIsGravityWell = true;
			m_uiGravityCount = 0;
			m_uiCooldown = 0;
			m_uiSpellGravityWellTimer = 13000;
		}else m_uiSpellGravityWellTimer -=diff;

        if (m_uiIceNovaTimer < diff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            {
                DoCast(target, m_bIsRegularMode ? SPELL_ICE_NOVA_N : SPELL_ICE_NOVA_H);
                m_uiCooldown = 1500;
            }
            m_uiIceNovaTimer = 15000;
        }else m_uiIceNovaTimer -=diff;

		if (m_uiFireBombTimer < diff)
		{
			if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
			{
				DoCast(target, m_bIsRegularMode ? SPELL_FIREBOMB_N : SPELL_FIREBOMB_H);
				m_uiCooldown = 1600;
			}
			m_uiFireBombTimer = 1500;
		}else m_uiFireBombTimer -=diff;

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
