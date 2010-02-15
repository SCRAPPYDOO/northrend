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
SDName: Boss_Sapphiron
SD%Complete: 90
SDComment: 
SDCategory: Naxxramas
SDAuthor: ScrappyDoo (c) Andeeria
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    EMOTE_BREATH       = -1533082,
    EMOTE_ENRAGE       = -1533083,

	//Fly Phase Spells
    SPELL_ICEBOLT      = 28522,
	SPELL_FROST_BREATH = 28524,	
    SPELL_FROST_BREATH_H = 29318,

	//Land Phase Spells
    SPELL_FROST_AURA   = 28531,
	SPELL_FROST_AURA_H = 55799,
    SPELL_LIFE_DRAIN   = 28542,
	SPELL_LIFE_DRAIN_H = 55665,
    SPELL_BLIZZARD     = 28560, //28547,
	SPELL_TAIL_SWEEP   = 55697,
	SPELL_CLEAVE	   = 19983,
    SPELL_BESERK       = 26662
};

struct MANGOS_DLL_DECL boss_sapphironAI : public ScriptedAI
{
    boss_sapphironAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
	bool m_bIsBerserk;
	bool m_bIsLandOff;

    uint32 m_uiBreathTimer;
	uint32 m_uiTailSweepTimer;
	uint32 m_uiCleveTimer;
	uint32 m_uiIceboltTimer;
    uint32 m_uiFlyTimer;
	uint32 m_uiBlizzardTimer;
	uint32 m_uiLifeDrainTimer;
	uint32 m_uiFrostAuraTimer;
	uint32 m_uiBeserkTimer;
	uint32 m_uiLandTimer;
	uint8  m_uiPhase;
	uint8  m_uiIceboltCount;

    void Reset()
    {
		m_bIsLandOff		= false;
		m_bIsBerserk		= false;
		m_uiTailSweepTimer  = urand(10000,15000);
		m_uiCleveTimer		= urand(5000,10000);
		m_uiFlyTimer		= 45000;
		m_uiBlizzardTimer   = 20000;
		m_uiLifeDrainTimer  = 24000;
		m_uiBeserkTimer		= 900000;
		m_uiFrostAuraTimer	= 2000;
		m_uiPhase			= 1;
		m_uiIceboltCount    = 0;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAPPHIRON, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAPPHIRON, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAPPHIRON, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_bIsBerserk && m_uiBeserkTimer < uiDiff)
        {
            DoScriptText(EMOTE_ENRAGE, m_creature);
            m_creature->CastSpell(m_creature, SPELL_BESERK, false);
			m_bIsBerserk = true;
        }else m_uiBeserkTimer -= uiDiff;

        if (m_uiPhase == 1)
        {
			if (m_uiFlyTimer < uiDiff)
			{
				m_uiIceboltTimer = 5000;
                m_uiBreathTimer  = 18000;
				m_uiIceboltCount = 0;
                m_bIsLandOff     = false;
                m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()+15, m_creature->GetOrientation());
				++m_uiPhase;
			}else m_uiFlyTimer -= uiDiff;

            if (m_uiTailSweepTimer < uiDiff)
            {
				if (m_creature->getVictim())
					m_creature->CastSpell(m_creature->getVictim(), SPELL_TAIL_SWEEP, false);
                m_uiTailSweepTimer = urand(10000,15000);
            }else m_uiTailSweepTimer -= uiDiff;

            if (m_uiCleveTimer < uiDiff)
            {
				if (m_creature->getVictim())
					m_creature->CastSpell(m_creature->getVictim(), SPELL_CLEAVE, false);
                m_uiCleveTimer = urand(5000,10000);
            }else m_uiCleveTimer -= uiDiff;

            if (m_uiFrostAuraTimer < uiDiff)
            {
				if (m_creature->getVictim())
					m_creature->CastSpell(m_creature->getVictim(), m_bIsRegularMode ? SPELL_FROST_AURA : SPELL_FROST_AURA_H, false);
                m_uiFrostAuraTimer = 50000; //2000
            }else m_uiFrostAuraTimer -= uiDiff;

            if (m_uiLifeDrainTimer < uiDiff)
            {
				for (uint8 i=0; i<( m_bIsRegularMode ? 2 : 5); ++i)
					if (Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
						m_creature->CastSpell(pPlayer, m_bIsRegularMode ? SPELL_LIFE_DRAIN : SPELL_LIFE_DRAIN_H, false);

                m_uiLifeDrainTimer = 24000;
            }else m_uiLifeDrainTimer -= uiDiff;

            if (m_uiBlizzardTimer < uiDiff)
            {
                if (Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
                    m_creature->CastSpell(pPlayer, SPELL_BLIZZARD, false);

                m_uiBlizzardTimer = 20000;
            }else m_uiBlizzardTimer -= uiDiff;

			DoMeleeAttackIfReady();
        }

        if (m_uiPhase == 2)
        {
			m_creature->StopMoving();
			m_creature->GetMotionMaster()->Clear();
			m_creature->GetMotionMaster()->MoveIdle();

            if (!m_bIsLandOff)
            {
                if (m_uiIceboltTimer < uiDiff && m_uiIceboltCount < (m_bIsRegularMode ? 2 : 3))
                {
				    //dmg incorrect ?
                    if (Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
                        m_creature->CastSpell(pPlayer, SPELL_ICEBOLT, false);

                    ++m_uiIceboltCount;
                    m_uiIceboltTimer = 6000;
                }else m_uiIceboltTimer -= uiDiff;

			    if (m_uiBreathTimer < uiDiff)
                {
				    DoScriptText(EMOTE_BREATH, m_creature);
				    if (m_creature->getVictim())
					    m_creature->CastSpell(m_creature->getVictim(), SPELL_FROST_BREATH, false);
				    m_uiLandTimer = 2000;
				    m_bIsLandOff = true;
                }else m_uiBreathTimer -= uiDiff;
            }

            if (m_bIsLandOff && m_uiLandTimer < uiDiff)
            {
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
                m_creature->SetHover(false);
                m_creature->GetMotionMaster()->Clear(false);
                
				//Timers Phase1
				m_uiFrostAuraTimer = 2000;
				m_uiLifeDrainTimer = 24000;
				m_uiBlizzardTimer  = 20000;
			    m_uiTailSweepTimer = urand(10000,15000);
				m_uiCleveTimer	   = urand(5000,10000);
				m_uiFlyTimer       = 45000;

				//Rest Phase2
                if (m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
				--m_uiPhase;
				return;
            }else m_uiLandTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_boss_sapphiron(Creature* pCreature)
{
    return new boss_sapphironAI(pCreature);
}

void AddSC_boss_sapphiron()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_sapphiron";
    NewScript->GetAI = &GetAI_boss_sapphiron;
    NewScript->RegisterSelf();
}
