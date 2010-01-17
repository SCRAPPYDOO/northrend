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
SDName: Boss_Volazj
SD%Complete: 95%
SDComment: Clones more support neded
SDCategory: Ahn'kahet
SDAuthor: ScrappyDoo (c) Andeeria
EndScriptData */

/* To Do
Visage Support in DB dmg <- mele
*/

#include "precompiled.h"

//TODO: fill in texts in database. Also need to add text for whisper.
enum Sounds
{
    SAY_AGGRO                       = -1619033,
    SAY_INSANITY                    = -1619034,
    SAY_SLAY_1                      = -1619035,
    SAY_SLAY_2                      = -1619036,
    SAY_SLAY_3                      = -1619037,
    SAY_DEATH_1                     = -1619038,
    SAY_DEATH_2                     = -1619039
};

enum Spells
{
    SPELL_FLY                       = 57941,
    SPELL_FLY_H                     = 59974,
    SPELL_BOLT                      = 57942,
    SPELL_BOLT_H                    = 59975,
    SPELL_SHIVER                    = 57949,
    SPELL_SHIVER_H                  = 59978,

    //Image Spells
    SPELL_PRIEST                    = 47077, // 100%
    SPELL_PALADIN                   = 37369, // 100%
    SPELL_PALADIN2                  = 37369, // 100%
    SPELL_WARLOCK                   = 46190, // 100%
    SPELL_WARLOCK2                  = 47076, // 100%
    SPELL_MAGE                      = 47074, // 100%
    SPELL_ROGUE                     = 45897, // 100%
    SPELL_WARRIOR                   = 17207, // 100%
    SPELL_DRUID                     = 47072, // 100%
    SPELL_SHAMAN                    = 47071, // 100%
    SPELL_HUNTER                    = 48098, // 100%
};

enum Creatures
{
    CREATURE_VISAGE                 = 30625,
};

/*######
## boss_volazj
######*/

struct MANGOS_DLL_DECL boss_volazjAI : public ScriptedAI
{
    boss_volazjAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint64 m_uiImageGUID[4][2];
    uint32 m_uiImageCastTimer;
    uint32 m_uiFlyTimer;
    uint32 m_uiBoltTimer;
    uint8  m_uiPhase;

    void Reset()
    {
        m_uiImageCastTimer  = urand(8000,16000);
        m_uiFlyTimer        = urand(10000,15000);
        m_uiBoltTimer       = urand(5000,10000);
        m_uiPhase           = 1;

        for(uint8 i=0; i<4; ++i)
        {
            m_uiImageGUID[i][0] = 0;
            m_uiImageGUID[i][1] = 0;
        }
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

    void SwitchPhase(uint8 m_uiPhaseNo)
    {
        DoScriptText(SAY_INSANITY, m_creature);
        for(uint8 i =0; i<4; ++i)
        {
            Creature* cImage = m_creature->SummonCreature(CREATURE_VISAGE, m_creature->GetPositionX()+urand(2,25), m_creature->GetPositionY()+urand(2,25), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
            if(cImage)
            {
                m_uiImageGUID[i][0] = cImage->GetGUID();
                if(Unit* pPlayer = SelectUnit(SELECT_TARGET_RANDOM,0))
                {
                    uint32 spell;
                    switch(pPlayer->getClass())
                    {
                        case CLASS_PRIEST:  spell = SPELL_PRIEST; break;
                        case CLASS_PALADIN: spell = SPELL_PALADIN; break;
                        case CLASS_WARLOCK: spell = SPELL_WARLOCK; break;
                        case CLASS_MAGE:    spell = SPELL_MAGE; break;
                        case CLASS_ROGUE:   spell = SPELL_ROGUE; break;
                        case CLASS_WARRIOR: spell = SPELL_WARRIOR; break;
                        case CLASS_DRUID:   spell = SPELL_DRUID; break;
                        case CLASS_SHAMAN:  spell = SPELL_SHAMAN; break;
                        case CLASS_HUNTER:  spell = SPELL_HUNTER; break;
                    }
                    m_uiImageGUID[i][1] = spell;
                    cImage->AI()->AttackStart(pPlayer);
                    cImage->SetDisplayId(pPlayer->GetDisplayId());
                }
            }
        }

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_uiPhase = m_uiPhaseNo;
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(urand(0, 1) ? SAY_DEATH_1 : SAY_DEATH_2, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Images Attack
        if(m_uiImageCastTimer < uiDiff && (m_uiPhase == 2 || m_uiPhase == 3))
        {
            for(uint8 i=0; i<4; ++i)
            {
                Unit* cImage = Unit::GetUnit((*m_creature), m_uiImageGUID[i][0]);
				if(cImage && cImage->isAlive())
					if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
						cImage->CastSpell(target, m_uiImageGUID[i][1], true);
            }
            m_uiImageCastTimer = urand(8000,16000);
        }else m_uiImageCastTimer -= uiDiff;

        if(m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) && (m_uiPhase == 2 || m_uiPhase == 3))
        {
            m_creature->StopMoving();
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveIdle();

            Unit* pImage1 = Unit::GetUnit(*m_creature, m_uiImageGUID[0][0]);
            Unit* pImage2 = Unit::GetUnit(*m_creature, m_uiImageGUID[1][0]);
            Unit* pImage3 = Unit::GetUnit(*m_creature, m_uiImageGUID[2][0]);
            Unit* pImage4 = Unit::GetUnit(*m_creature, m_uiImageGUID[3][0]);
            if(pImage1 && !pImage1->isAlive() && pImage2 && !pImage2->isAlive() && pImage3 && !pImage3->isAlive() && pImage4 && !pImage4->isAlive())
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                if(m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
            }
            return;
        }

        if((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 66 && m_uiPhase < 2)
            SwitchPhase(2);

        if((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 33 && m_uiPhase < 3)
            SwitchPhase(3);
        
        if(m_uiFlyTimer < uiDiff)
        {
            if(m_creature->getVictim())
                m_creature->CastSpell(m_creature->getVictim(), m_bIsRegularMode ? SPELL_FLY : SPELL_FLY_H, false);
            m_uiFlyTimer = urand(10000,15000);
        }else m_uiFlyTimer -= uiDiff;

        if(m_uiBoltTimer < uiDiff)
        {
            if(m_creature->getVictim())
                m_creature->CastSpell(m_creature->getVictim(), m_bIsRegularMode ? SPELL_BOLT : SPELL_BOLT_H, false);
            m_uiBoltTimer = urand(10000,15000);
        }else m_uiBoltTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_volazj(Creature* pCreature)
{
    return new boss_volazjAI(pCreature);
}

void AddSC_boss_volazj()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_volazj";
    newscript->GetAI = &GetAI_boss_volazj;
    newscript->RegisterSelf();
}
