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
SDName: Boss_KelThuzud
SD%Complete: 50
SDComment:
SDCategory: Naxxramas
SDAuthor: ScrappyDoo (c) Andeeria
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"


enum
{
    //when shappiron dies. dialog between kel and lich king (in this order)
    SAY_SAPP_DIALOG1          = -1533084,
    SAY_SAPP_DIALOG2_LICH     = -1533085,
    SAY_SAPP_DIALOG3          = -1533086,
    SAY_SAPP_DIALOG4_LICH     = -1533087,
    SAY_SAPP_DIALOG5          = -1533088,

    //when cat dies
    SAY_CAT_DIED              = -1533089,

    //when each of the 4 wing bosses dies
    SAY_TAUNT1                = -1533090,
    SAY_TAUNT2                = -1533091,
    SAY_TAUNT3                = -1533092,
    SAY_TAUNT4                = -1533093,

    SAY_SUMMON_MINIONS        = -1533105,                   //start of phase 1

    SAY_AGGRO1                = -1533094,                   //start of phase 2
    SAY_AGGRO2                = -1533095,
    SAY_AGGRO3                = -1533096,

    SAY_SLAY1                 = -1533097,
    SAY_SLAY2                 = -1533098,

    SAY_DEATH                 = -1533099,

    SAY_CHAIN1                = -1533100,
    SAY_CHAIN2                = -1533101,
    SAY_FROST_BLAST           = -1533102,

    SAY_REQUEST_AID           = -1533103,                   //start of phase 3
    SAY_ANSWER_REQUEST        = -1533104,                   //lich king answer

    SAY_SPECIAL1_MANA_DET     = -1533106,
    SAY_SPECIAL3_MANA_DET     = -1533107,
    SAY_SPECIAL2_DISPELL      = -1533108,

    //spells to be casted
    SPELL_FROST_BOLT          = 28478,
    SPELL_FROST_BOLT_H        = 55802,
    SPELL_FROST_BOLT_NOVA     = 28479,
    SPELL_FROST_BOLT_NOVA_H   = 55807,

    SPELL_CHAINS_OF_KELTHUZAD = 28410, //28408, //dev //casted spell should be 28408. Also as of 303, heroic only
	SPELL_MANA_DETONATION     = 27819,
    SPELL_MANA_DETONATIONDMG  = 37158,
    SPELL_SHADOW_FISURE       = 27810,
    SPELL_FROST_BLAST         = 27808,

    //shadow fissure spells
    SPELL_VOIDBLAST           = 27812, //100k near aoe ;D

	CREATURE_ICECROWN_GUARDIAN = 16441, //2 or 4
	CREATURE_SOLDIER		   = 16427, //71
	CREATURE_ABONIAMTION	   = 16428, //8
	CREATURE_BANSHEE		   = 16429, //8
};

//Positional defines
#define ADDX_LEFT_FAR               3783.272705
#define ADDY_LEFT_FAR               -5062.697266
#define ADDZ_LEFT_FAR               143.711203
#define ADDO_LEFT_FAR               3.617599

#define ADDX_LEFT_MIDDLE            3730.291260
#define ADDY_LEFT_MIDDLE            -5027.239258
#define ADDZ_LEFT_MIDDLE            143.956909
#define ADDO_LEFT_MIDDLE            4.461900

#define ADDX_LEFT_NEAR              3683.868652
#define ADDY_LEFT_NEAR              -5057.281250
#define ADDZ_LEFT_NEAR              143.183884
#define ADDO_LEFT_NEAR              5.237086

#define ADDX_RIGHT_FAR              3759.355225
#define ADDY_RIGHT_FAR              -5174.128418
#define ADDZ_RIGHT_FAR              143.802383
#define ADDO_RIGHT_FAR              2.170104

#define ADDX_RIGHT_MIDDLE           370.724365
#define ADDY_RIGHT_MIDDLE           -5185.123047
#define ADDZ_RIGHT_MIDDLE           143.928024
#define ADDO_RIGHT_MIDDLE           1.309310

#define ADDX_RIGHT_NEAR             3665.121094
#define ADDY_RIGHT_NEAR             -5138.679199
#define ADDZ_RIGHT_NEAR             143.183212
#define ADDO_RIGHT_NEAR             0.604023

#define WALKX_LEFT_FAR              3754.431396
#define WALKY_LEFT_FAR              -5080.727734
#define WALKZ_LEFT_FAR              142.036316
#define WALKO_LEFT_FAR              3.736189

#define WALKX_LEFT_MIDDLE           3724.396484
#define WALKY_LEFT_MIDDLE           -5061.330566
#define WALKZ_LEFT_MIDDLE           142.032700
#define WALKO_LEFT_MIDDLE           4.564785

#define WALKX_LEFT_NEAR             3687.158424
#define WALKY_LEFT_NEAR             -5076.834473
#define WALKZ_LEFT_NEAR             142.017319
#define WALKO_LEFT_NEAR             5.237086

#define WALKX_RIGHT_FAR             3687.571777
#define WALKY_RIGHT_FAR             -5126.831055
#define WALKZ_RIGHT_FAR             142.017807
#define WALKO_RIGHT_FAR             0.604023

#define WALKX_RIGHT_MIDDLE          3707.990733
#define WALKY_RIGHT_MIDDLE          -5151.450195
#define WALKZ_RIGHT_MIDDLE          142.032562
#define WALKO_RIGHT_MIDDLE          1.376855

#define WALKX_RIGHT_NEAR            3739.500000
#define WALKY_RIGHT_NEAR            -5141.883989
#define WALKZ_RIGHT_NEAR            142.0141130
#define WALKO_RIGHT_NEAR            2.121412

struct MANGOS_DLL_DECL boss_kelthuzadAI : public ScriptedAI
{
    boss_kelthuzadAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiFrostBoltTimer;
    uint32 m_uiFrostBoltNovaTimer;
    uint32 m_uiChainsOfKelthuzadTimer;
    uint32 m_uiManaDetonationTimer;
    uint32 m_uiShadowFisureTimer;
    uint32 m_uiFrostBlastTimer;
	uint32 m_uiPhaseTimer;
	uint8  m_uiPhase;
	uint32 m_uiDialogTimer;
	uint8  m_uiDialogCount;
	uint32 m_uiAddsTimer;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        m_uiFrostBoltTimer			= urand(1000, 10000);             
        m_uiFrostBoltNovaTimer		= 15000;                      
        m_uiChainsOfKelthuzadTimer	= urand(30000, 60000);      
        m_uiManaDetonationTimer		= 20000;                       
        m_uiShadowFisureTimer		= 25000;                       
        m_uiFrostBlastTimer			= urand(30000, 60000);  
		m_uiPhaseTimer				= 10000, //228000;	
		m_uiPhase					= 1;
		m_uiDialogTimer				= 5000;
		m_uiDialogCount				= 0;
		m_uiAddsTimer				= 5000;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_KELTHUZAD, NOT_STARTED);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1)?SAY_SLAY1:SAY_SLAY2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_KELTHUZAD, DONE);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_SUMMON_MINIONS, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_KELTHUZAD, IN_PROGRESS);
    }

    void UpdateAI(const uint32 uiDiff)
    {
		//Intro Dialog
        if (m_pInstance && m_pInstance->GetData(TYPE_SAPPHIRON) == DONE)
        { 
			if (m_uiDialogCount < 6)
			{
				if (m_uiDialogTimer < uiDiff)
				{
					switch(m_uiDialogCount)
					{
						case 0: DoScriptText(SAY_SAPP_DIALOG1, m_creature); break;
						case 1: DoScriptText(SAY_SAPP_DIALOG2_LICH, m_creature); break;
						case 2: DoScriptText(SAY_SAPP_DIALOG3, m_creature); break;
						case 3: DoScriptText(SAY_SAPP_DIALOG4_LICH, m_creature); break;
						case 4: DoScriptText(SAY_SAPP_DIALOG5, m_creature); break;
						default: break;
					}
					++m_uiDialogCount;
					m_uiDialogTimer = 10000;
				}else m_uiDialogTimer -= uiDiff;
			}
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiPhase == 1)
        {
			m_creature->StopMoving();
			m_creature->GetMotionMaster()->Clear();
			m_creature->GetMotionMaster()->MoveIdle();
/*
			if (m_uiAddsTimer < uiDiff)
			{
				for (uint8 i=0; i<3; ++i) //11 dev
				{
					if (i == 1)
						ID = CREATURE_BANSHEE;
					if (i == 0)
						ID = CREATURE_ABONIAMTION;
                    if (i > 1)
						ID = CREATURE_SOLDIER;

					Creature* pAdd = m_creature->SummonCreature(ID, m_creature->GetPositionX()+15, m_creature->GetPositionY()+15, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
					if (pAdd)
						if (Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
							pAdd->AI()->AttackStart(pPlayer);
				}
				m_uiAddsTimer = 25000;
			}else m_uiAddsTimer -= uiDiff;
*/
            if (m_uiPhaseTimer < uiDiff)
            {
                switch(urand(0, 2))
                {
                    case 0: DoScriptText(SAY_AGGRO1, m_creature); break;
                    case 1: DoScriptText(SAY_AGGRO2, m_creature); break;
                    case 2: DoScriptText(SAY_AGGRO3, m_creature); break;
                }
				m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                if (m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                ++m_uiPhase;
            }else m_uiPhaseTimer -= uiDiff;
        }

        if (m_uiPhase > 1)
        {
            //At 45% health, Kel'Thuzad will call for help, summoning 2 (25 Player: 4) Guardians of Icecrown. The fight becomes a DPS race during this Phase.
			if (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 45 && m_uiPhase == 2)
			{
                DoScriptText(SAY_REQUEST_AID, m_creature);
                //here Lich King should respond to KelThuzad but I don't know which creature to make talk
                //so for now just make Kelthuzad says it.
                DoScriptText(SAY_ANSWER_REQUEST, m_creature);

				for (uint8 i=0; i<(m_bIsRegularMode ? 2 : 4); ++i)
				{
					Creature* pGuardian = m_creature->SummonCreature(CREATURE_ICECROWN_GUARDIAN, m_creature->GetPositionX()+15, m_creature->GetPositionY()+15, m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
					if(pGuardian)
						if(Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
							pGuardian->AI()->AttackStart(pPlayer);
				}
				++m_uiPhase;
			}

            //Check for Frost Bolt
            if (m_uiFrostBoltTimer < uiDiff)
            {
				if (Unit* pPlayer = SelectUnit(SELECT_TARGET_TOPAGGRO, 0))
					m_creature->CastSpell(pPlayer, m_bIsRegularMode ? SPELL_FROST_BOLT : SPELL_FROST_BOLT_H, false);
                m_uiFrostBoltTimer = urand(1000, 60000);
            }else m_uiFrostBoltTimer -= uiDiff;

            //Check for Frost Bolt Nova
            if (m_uiFrostBoltNovaTimer < uiDiff)
            {
				if (m_creature->getVictim())
					m_creature->CastSpell(m_creature->getVictim(), m_bIsRegularMode ? SPELL_FROST_BOLT_NOVA : SPELL_FROST_BOLT_NOVA_H, false);
                m_uiFrostBoltNovaTimer = urand(20000,30000);
            }else m_uiFrostBoltNovaTimer -= uiDiff;

            //Check for Chains Of Kelthuzad
            if (m_uiChainsOfKelthuzadTimer < uiDiff)
            {
                if (urand(0, 1))
                    DoScriptText(SAY_CHAIN1, m_creature);
                else
                    DoScriptText(SAY_CHAIN2, m_creature);

				DoCast(m_creature->getVictim(),SPELL_CHAINS_OF_KELTHUZAD);

                m_uiChainsOfKelthuzadTimer = 90000;
            }else m_uiChainsOfKelthuzadTimer -= uiDiff;

            //Check for Mana Detonation
            if (m_uiManaDetonationTimer < uiDiff)
			{
				if (urand(0, 1)) DoScriptText(SAY_SPECIAL1_MANA_DET, m_creature);
                    
				if (Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM, 0))
					m_creature->CastSpell(pPlayer, SPELL_MANA_DETONATION, false);

                m_uiManaDetonationTimer = 30000;
            }else m_uiManaDetonationTimer -= uiDiff;

            //Check for Shadow Fissure
            if (m_uiShadowFisureTimer < uiDiff)
            {
                if (urand(0, 1)) DoScriptText(SAY_SPECIAL3_MANA_DET, m_creature);

				if (Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM, 0))
					m_creature->CastSpell(pPlayer, SPELL_SHADOW_FISURE, false);

                m_uiShadowFisureTimer = 25000;
            }else m_uiShadowFisureTimer -= uiDiff;

            //Check for Frost Blast
            if (m_uiFrostBlastTimer < uiDiff)
            {
                if (Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM, 0))
					m_creature->CastSpell(pPlayer, SPELL_FROST_BLAST, false);

                if (urand(0, 1))
                    DoScriptText(SAY_FROST_BLAST, m_creature);

                m_uiFrostBlastTimer = 45000;
            }else m_uiFrostBlastTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_kelthuzadAI(Creature* pCreature)
{
    return new boss_kelthuzadAI(pCreature);
}

void AddSC_boss_kelthuzad()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_kelthuzad";
    NewScript->GetAI = &GetAI_boss_kelthuzadAI;
    NewScript->RegisterSelf();
}
