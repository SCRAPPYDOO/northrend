/* Copyright 2006,2007 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: boss_kiljaden
SD%Complete: 0
SDComment:
EndScriptData */
 
#include "precompiled.h"
#include "def_sunwell_plateau.h"
 
enum spells
{
    //Kilajden Spells
    AURA_SUNWELL_RADIANCE       = 45769,
    SPELL_SOULFLY               = 0,
    SPELL_ARMAGEDDON            = 0,
    SPELL_DARKNESS_OF_SOULS     = 46605,
    SPELL_DESTROY_DRAKES        = 46707,
    SPELL_FIREBLOOM             = 45641,
    SPELL_FLAMEDARTS            = 45737,
    SPELL_LEGION_LIGHTING       = 45664,
    SPELL_SHADOWSPIKE           = 46680,
    SPELL_SINISTER_REFLECTION   = 45892,
    SPELL_SACRIFICE_OF_ANVEENA  = 0,

    SPELL_KNOCKBACK             = 0,

    //Hand of the Deceiver Spells
    SPELL_FELLFIRE_PORTAL       = 46875,
    SPELL_SHADOWBOLT_VOLLEY     = 45770,
    SPELL_SHADOWINFUSION        = 45772,

    //Orb Spells
    SPELL_ORB_BOLT              = 45680,

    //Reflections Spells
    SPELL_PRIEST                =0,
    SPELL_PALADIN               =0,
    SPELL_WARLOCK               =0,
    SPELL_MAGE                  =0,
    SPELL_ROGUE                 =0,
    SPELL_WARRIOR               =0,
    SPELL_DRUID                 =0,
    SPELL_SHAMAN                =0,
    SPELL_HUNTER                =0,
};
 
enum ids
{
	ID_KILJADEN		= 25315,
    ID_DECIVER      = 25588,
    ID_SHIELDORB    = 25502,
    ID_SINISTER     = 25708,
};
 
float OrbSpawn [4][2] =
{
    {1853.300,588.653},
    {1781.502,659.254},
    {1853.300,588.653},
    {1853.300,588.653},
};

/* --- Kiljaden --- */
    
struct MANGOS_DLL_DECL boss_kiljadenAI : public ScriptedAI
{
    boss_kiljadenAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
 
    ScriptedInstance* pInstance;

    //Phase2
    uint32 SoulFlyTimer;
    uint32 LegionLightingTimer;
    uint32 FireBloomTimer;
    uint32 ShieldOrbTimer;

    //Phase3
    bool Phase3;
    uint32 ShadowSpikeTimer;
    uint32 FlameDartTimer;
    uint32 DarknessOfSoulsTimer;
    bool ShadowSpikeEnds; /* When the Shadow Spikes have finished, 
    Kalecgos will empower 1 of the 4 Orbs of the Blue Dragonflight
    (which will from now on be referred to as dragon orbs for simplicity)
    located around the room.*/

    //Phase4
    bool Phase4;
    bool DarknessOfSoulsCasting;
    uint32 AramageddonTimer;
    
    //Phase5
    bool Phase5;
    bool ArwenaSacrificedSelf;
    uint32 ArwenaSacrificeTimer;

    //Sinister Reflections
    uint64 SinisterGUID[12][2];
    uint32 SinnisterCastTimer;
 
    void Reset()
    {
        SinnisterCastTimer = 10000;

        //Phase2
        SoulFlyTimer = 10000;
        LegionLightingTimer = 15000;
        FireBloomTimer = 20000;
        ShieldOrbTimer = 25000;

        Phase3 = false;
        Phase4 = false;
        Phase5 = false;

        // wyczyscic tabele?

        //m_creature->SetVisibility(VISIBILITY_OFF);
        //m_creature->setFaction(35);

        //if(!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            //m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if(!m_creature->HasAura(AURA_SUNWELL_RADIANCE, 0))
            m_creature->CastSpell(m_creature, AURA_SUNWELL_RADIANCE, true);
    }
    
    void Aggro(Unit *who)
    {
        if(!who)
            return;

        m_creature->StopMoving();
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MoveIdle();
    }

    void KilledUnit(Unit *Victim) {}

    void Sinister(Player* victim,uint8 i,uint8 k)
    {
        uint32 spell;

        switch(victim->getClass())
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

        for(i=0; i<k; ++i)
        {
            Creature* Sinister = m_creature->SummonCreature(ID_SINISTER, victim->GetPositionX()+rand()%3, victim->GetPositionY()+rand()%3, m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
            if(Sinister)
                Sinister->AI()->AttackStart(Sinister->getVictim());
            SinisterGUID[i][0] = Sinister->GetGUID();
            SinisterGUID[i][1] = spell;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if(pInstance && pInstance->GetData(DATA_DECIVER) == SPECIAL)
        {
            //Knockback players at start.
            DoCast(m_creature->getVictim(), SPELL_KNOCKBACK);

            m_creature->setFaction(14);
            m_creature->SetVisibility(VISIBILITY_ON);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            
            pInstance->SetData(DATA_KILJAEDEN_EVENT, IN_PROGRESS);
            pInstance->SetData(DATA_DECIVER, DONE);        
        }

        if(!m_creature->SelectHostilTarget() || !m_creature->getVictim())
               return;
        
        //Phases
        if(((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 85) && !Phase3)
        {
            if(Unit* victim = SelectUnit(SELECT_TARGET_RANDOM,0)) 
                if (victim && (victim->GetTypeId() == TYPEID_PLAYER))
                    Sinister(((Player*)victim),0,4);

            //Start Timerow  Dochodzacych w 3 Fazie
            ShadowSpikeTimer        = 0;
            FlameDartTimer          = 0;
            DarknessOfSoulsTimer    = 0;
            ShadowSpikeEnds         = false;

            Phase3 = true;
        }

        if(((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 55) && !Phase4)
        {
            if(Unit* victim = SelectUnit(SELECT_TARGET_RANDOM,0)) 
                if (victim && (victim->GetTypeId() == TYPEID_PLAYER))
                    Sinister(((Player*)victim),4,8);

            //Start Timerow  Dochodzacych w 3 Fazie
            DarknessOfSoulsCasting = false;
            AramageddonTimer       = 8000;  //100% ok

            Phase4 = true;
        }

        if(((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 25) && !Phase5)
        {
            if(Unit* victim = SelectUnit(SELECT_TARGET_RANDOM,0)) 
                if (victim && (victim->GetTypeId() == TYPEID_PLAYER))
                    Sinister(((Player*)victim),8,12);

            //Start Timerow  Dochodzacych w 3 Fazie
            ShadowSpikeTimer = 1000;
            ArwenaSacrificeTimer = 29000;
            ArwenaSacrificedSelf = false;
            Phase5 = true;
        }

        if(AramageddonTimer < diff)
        {
            /*
            3 of these will be in flight constantly throughout this phase and they will 
            stop spawning while he is casting Darkness of a Thousand Souls. 
            */
            uint8 h=3;
            if(Phase5)
                h=5;
            if(!Phase5 && DarknessOfSoulsCasting)
                h=0;
            for(uint8 i=0; i<h; ++i);
            {
                Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0);
                m_creature->CastSpell(target, SPELL_ARMAGEDDON, true);
            }
            DarknessOfSoulsCasting = false;

            AramageddonTimer = 8000;
        }else AramageddonTimer -= diff;

        if(ArwenaSacrificeTimer < diff && !ArwenaSacrificedSelf)
        {
            DoCast(m_creature, SPELL_SACRIFICE_OF_ANVEENA, true);
            ArwenaSacrificedSelf = true;
        }else ArwenaSacrificeTimer -= diff;
       
        if(DarknessOfSoulsTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_DARKNESS_OF_SOULS);
            DarknessOfSoulsCasting = true;
            DarknessOfSoulsTimer = 45000;
        }DarknessOfSoulsTimer -= diff;

        if(ShadowSpikeTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_SHADOWSPIKE);
            ShadowSpikeTimer = 60000;
            if(Phase5)
                ShadowSpikeTimer = 25000;
        }else ShadowSpikeTimer -= diff;

        if(FlameDartTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_FLAMEDARTS);
            FlameDartTimer = 33000;
        }else FlameDartTimer -= diff;

        if(SoulFlyTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_SOULFLY);
            SoulFlyTimer = 15000;
        }else SoulFlyTimer -= diff;

        if(LegionLightingTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_LEGION_LIGHTING);
            LegionLightingTimer = 23000;
        }else LegionLightingTimer -= diff;

        if(FireBloomTimer < diff)
        {
            for(uint8 i=0; i<5; ++i)
            {
                Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0);
                DoCast(target, SPELL_FIREBLOOM);
            }
            FireBloomTimer = 30000;
        }else FireBloomTimer -= diff;

        if(ShieldOrbTimer < diff && !Phase5)
        {
            uint8 l=1;
            if(Phase3)
                l=2;
            if(Phase4)
                l=3;
            for(uint8 k=0; k<l; ++k)
            {
                Creature* ShieldOrb = m_creature->SummonCreature(ID_SHIELDORB, OrbSpawn[k][0], OrbSpawn[k][1], m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                if(ShieldOrb)
                    ShieldOrb->AI()->AttackStart(m_creature->getVictim()); 
            }
            ShieldOrbTimer = 35000; 
        }else ShieldOrbTimer -= diff;

        if(SinnisterCastTimer < diff)
        {
            uint8 SinisterCount = 0;
            if(Phase3)
                SinisterCount = 4;
            if(Phase4)
                SinisterCount = 8;
            if(Phase5)
                SinisterCount = 12;
            for(uint8 i=0; i<SinisterCount; ++i)
            {
                //SinisterCast();
            }
            SinnisterCastTimer = 10000;
        }else SinnisterCastTimer -= diff;
            
            
            DoMeleeAttackIfReady();
    }
};

struct MANGOS_DLL_DECL mob_deceiverAI : public ScriptedAI
{
    mob_deceiverAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
 
    ScriptedInstance* pInstance;

    uint32 BoltTimer;
    uint32 PortalTimer;
 
    void Reset()
    {
        PortalTimer = 25000;
        BoltTimer = 10000;
    }
    
    void Aggro(Unit *who) {}

    void JustDied(Unit* Killer) 
    {
        if(pInstance && pInstance->GetData(DATA_DECIVER) == NOT_STARTED)
            pInstance->SetData(DATA_DECIVER, IN_PROGRESS);
        else 
            if(pInstance && pInstance->GetData(DATA_DECIVER) == IN_PROGRESS)
                pInstance->SetData(DATA_DECIVER, DONE);
            else
                if(pInstance && pInstance->GetData(DATA_DECIVER) == DONE)
                    pInstance->SetData(DATA_DECIVER, SPECIAL);
    }

    void KilledUnit(Unit *Victim) {}
     
    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
                return;

        if(BoltTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_SHADOWBOLT_VOLLEY);
            BoltTimer = 10000;
        }else BoltTimer -= diff;

        if((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 20)
            if(!m_creature->HasAura(SPELL_SHADOWINFUSION,0))
                m_creature->CastSpell(m_creature, SPELL_SHADOWINFUSION, true);

        if(PortalTimer < diff)
        {
            //summon portal
            //summon  mobka na  portalu
            //wziasc id  i spowodowac wybuch po chwili czy pisac odzielny ai ?
            PortalTimer = 25000;
        }else PortalTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct MANGOS_DLL_DECL mob_sinisterAI : public ScriptedAI
{
    mob_sinisterAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
 
    ScriptedInstance* pInstance;

    uint32 SpellTimer;
 
    void Reset()
    {
        SpellTimer = 10000;
    }
    
    void Aggro(Unit *who) {}

    void JustDied(Unit* Killer) {}

    void KilledUnit(Unit *Victim) {}
     
    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
                return;

        if(SpellTimer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_SHADOWBOLT_VOLLEY);
            SpellTimer = 10000;
        }else SpellTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_deceiver(Creature *_Creature)
{
    return new mob_deceiverAI(_Creature);
}

CreatureAI* GetAI_boss_kiljaden(Creature *_Creature)
{
    return new boss_kiljadenAI(_Creature);
}

CreatureAI* GetAI_mob_sinister(Creature *_Creature)
{
    return new mob_sinisterAI(_Creature);
}
  

void AddSC_boss_kiljaden()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="boss_kiljaden";
    newscript->GetAI = &GetAI_boss_kiljaden;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_sinister";
    newscript->GetAI = &GetAI_mob_sinister;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_deceiver";
    newscript->GetAI = &GetAI_mob_deceiver;
    newscript->RegisterSelf();
}