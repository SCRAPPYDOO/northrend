/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Felmyst
SD%Complete: 95%
SDComment: PlayAble
SDCategory: Sunwell Plateau
SDAuthot: Scrappy Doo
EndScriptData */

#include "precompiled.h"
#include "def_sunwell_plateau.h"

enum dev
{
    //Says
    YELL_AGGRO                  = -1930000,
    YELL_CLEAVE			        = -1930001,
    YELL_CORROSION		        = -1930002,
    YELL_NOXIOUSFUMES		    = -1930003,
    YELL_SLAY1			        = -1930004,
    YELL_SLAY2			        = -1930005,
    YELL_SLAY3			        = -1930006,
    YELL_DEATH			        = -1930007,

    //Fly Phase
    SPELL_FOG_BREATH            =   45495,   // zbugownay spel
    SPELL_FOG_FORCE             =   45782,   // nic nie robi
    SPELL_FOG_INFORM            =   45714,   // nic nie robi
    SPELL_FOG_CHARM2            =   45726,   // przyspiesza  bez bufa

    //not in sue 45402.
};

enum Spells
{
    //Aura
    SPELL_SUNWELLRADIANCE_AURA  =   45769,
    SPELL_NOXIOUSFUMES_AURA	    =   47002,

    //Land phase
    SPELL_CLEAVE                =   19983,
    SPELL_CORROSION             =   45866,
    SPELL_GASNOVA               =   45855,
    SPELL_ENCAPSULATE_CHANNEL   =   45661,
    SPELL_ENCAPSULATE_AOE       =   45662,
    // SPELL_ENCAPSULATE_EFFECT    =   45665,

    //Flight phase
    SPELL_VAPOR_SELECT          =   45391,   // fel to player, force cast 45392, 50000y selete target
    SPELL_VAPOR_SUMMON          =   45392,   // player summon vapor, radius around caster, 5y,
    SPELL_VAPOR_FORCE           =   45388,   // vapor to fel, force cast 45389
    SPELL_VAPOR_CHANNEL         =   45389,   // fel to vapor, green beam channel
    SPELL_VAPOR_TRIGGER         =   45411,   // linked to 45389, vapor to self, trigger 45410 and 46931
    

    SPELL_VAPOR_DAMAGE          =   46931,   // vapor damage, 4000
    SPELL_TRAIL_TRIGGER         =   45399,   // trail to self, trigger 454
    
    SPELL_TRAIL_SUMMON          =   45410,   // vapor summon trail
    SPELL_TRAIL_DAMAGE          =   45402,   // trail damage, 2000 + 2000 dot

    SPELL_DEAD_SUMMON           =   45400,   // Sumonuje undeada

    //Fog of Mind Control
    MOB_DEATH_CLOUD             =   25703,         
    SPELL_FOG_TRIGGER           =   45582,   // Visual Effect Chmury
    SPELL_FOG_CHARM             =   45717,   // przyspiesza dmg cast speed

    SPELL_TRANSFORM_TRIGGER     =   44885,   // madrigosa to self, trigger 46350
    SPELL_TRANSFORM_VISUAL      =   46350,   //46411stun?
    SPELL_TRANSFORM_FELMYST     =   45068,   // become fel
    SPELL_FELMYST_SUMMON        =   45069,

    //Other
    SPELL_ENRAGE                =   26662,
    SPELL_BERSERK               =   45078,


    // ID deatch cloud
    SPELL_CLOUD_VISUAL          =   45212,  //chmura  ? nie  potrzebna ? instant  nie schodzi
    SPELL_CLOUD_SUMMON          =   45884,   //sumoje  mobka deatch cloud  w  poalczeniu bedzie chmura
};

enum Creatures
{
    MOB_FELMYST        =   25038,
    MOB_DEAD           =   25268,     //undead podczas  fly fazy

    MOB_MADRIGOSA      =   25160,
    MOB_FELMYST_VISUAL =   25041,
    MOB_FLIGHT_LEFT    =   25357,
    MOB_FLIGHT_RIGHT   =   25358,

    MOB_VAPOR          =   25265,
    MOB_VAPOR_TRAIL    =   25267
};

struct MANGOS_DLL_DECL boss_felmystAI : public ScriptedAI
{
    boss_felmystAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }

    ScriptedInstance* pInstance;

    uint32 EnrageTimer;

    //groundphase timers
    uint32 FlyPhaseTimer;
    uint32 NoxiousFumesTimer;
    uint32 CorrosionTimer;
    uint32 CleaveTimer;
    uint32 EncapsulateTimer;
    uint32 GasNovaTimer;
    uint32 EncapsulateAOETimer;

    uint8  EncapsulateCount;

    uint64 EncapsulateGUID;

    bool CastedNoxiousFumes;
    bool FlyPhase;

    //flyphase timers
    uint32 DemonicVaporTimer;
    uint32 FogOfCorruptionTimer;
    uint32 LandPhaseTimer;
    uint8 BreathCount;

    bool FogOfCorruption;

    void Reset()
    {
        EnrageTimer             = 600000;

        //groundphase timers
        FlyPhaseTimer           = 60000;
    	NoxiousFumesTimer	    = 1000;
    	CorrosionTimer	        = 72000;
    	CleaveTimer		        = 28000;  
        EncapsulateTimer        = 10000;
        GasNovaTimer            = 30000;

        EncapsulateCount        = 6;

        //guids
        EncapsulateGUID         = 0;

        CastedNoxiousFumes      = false;
        FlyPhase                = true; //false;

        //flyphase timers
        BreathCount             = 0;   
        FogOfCorruptionTimer = 5000;

        FogOfCorruption         = false;

        if (pInstance)
            pInstance->SetData(DATA_FELMYST_EVENT, NOT_STARTED);

        //if (!m_creature->HasAura(SPELL_SUNWELLRADIANCE_AURA))
            //DoCast(m_creature, SPELL_SUNWELLRADIANCE_AURA);
    }

    void Aggro(Unit *who)
    {
        DoScriptText(YELL_AGGRO, m_creature);

        if (pInstance)
            pInstance->SetData(DATA_FELMYST_EVENT, IN_PROGRESS);
    }

    void KilledUnit(Unit* victim)
    {
        switch(rand()%3)
        {
            case 0: DoScriptText(YELL_SLAY1, m_creature); break;
            case 1: DoScriptText(YELL_SLAY2, m_creature); break;
            case 2: DoScriptText(YELL_SLAY3, m_creature); break;
        }
        switch(rand()%2)
        {
            case 0: DoPlaySoundToSet(m_creature, 12480); break;
            case 1: DoPlaySoundToSet(m_creature, 12481); break;
        }
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(YELL_DEATH, m_creature);
	    DoPlaySoundToSet(m_creature, 12483);

	    if(pInstance)
        	pInstance->SetData(DATA_FELMYST_EVENT, DONE);
    }

    void UpdateAI(const uint32 diff)
    {
        //if (pInstance && pInstance->GetData(DATA_BRUTALLUS_EVENT) == DONE)
            //Set Visibility On
            //Set Faction 14

        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        if (EnrageTimer < diff)
        {
            DoCast(m_creature, SPELL_ENRAGE, true);
            EnrageTimer = 30000;
        }EnrageTimer -= diff;    

        if (!FlyPhase)
        { 
            if (FlyPhaseTimer < diff)
            {
                //wzniesc sie w  powietrze
                //stopmovement
                //movemenflat flying
                //m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()+15, m_creature->GetOrientation());
                //m_creature->StopMoving();
                DemonicVaporTimer = 5000;
                BreathCount = 0;
                FlyPhase = true;
                return;
            }else FlyPhaseTimer -= diff;

            //100%
            if (CorrosionTimer < diff)
            {
	            DoScriptText(YELL_CORROSION, m_creature);
                if (m_creature->getVictim())
                    DoCast(m_creature->getVictim(), SPELL_CORROSION);
                CorrosionTimer = 72000;
            }else CorrosionTimer -= diff;

            if (EncapsulateCount < 5)
                if (EncapsulateAOETimer < diff)
                {
                    if (Unit* target = Unit::GetUnit(*m_creature, EncapsulateGUID))
                    {
                        target->CastSpell(target, SPELL_ENCAPSULATE_AOE, true);
                        ++EncapsulateCount;
                    }
                    EncapsulateAOETimer = 1000;
                    return;
                }else EncapsulateAOETimer -= diff;

            //100%
            if (NoxiousFumesTimer < diff && !CastedNoxiousFumes)
            {
	            DoScriptText(YELL_NOXIOUSFUMES, m_creature);
                DoCast(m_creature, SPELL_NOXIOUSFUMES_AURA);
                DoCast(m_creature, SPELL_SUNWELLRADIANCE_AURA);
	            CastedNoxiousFumes = true;
	            DoPlaySoundToSet(m_creature, 12478);
            }else NoxiousFumesTimer -= diff;

            //100%
            if (GasNovaTimer < diff)
            {                
                if (m_creature->getVictim())
                    DoCast(m_creature, SPELL_GASNOVA);
                GasNovaTimer = 35000;
            }else GasNovaTimer -= diff;

            //100%
            if (EncapsulateTimer < diff)
            {
                if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                {
                    EncapsulateGUID = target->GetGUID();
                    DoCast(target, SPELL_ENCAPSULATE_CHANNEL);
                }
                EncapsulateTimer = 40000;
                EncapsulateAOETimer = 1000;
                EncapsulateCount = 0;
            }else EncapsulateTimer -= diff;

            //100%
            if (CleaveTimer < diff)
            {
	            DoScriptText(YELL_CLEAVE, m_creature);
                if (m_creature->getVictim())
                    DoCast(m_creature->getVictim(), SPELL_CLEAVE);
                CleaveTimer = 28000;
            }else CleaveTimer -= diff;

            DoMeleeAttackIfReady();
        }
        else
        {  
            if (DemonicVaporTimer < diff)
            {
                if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                {
                    DoCast(target, SPELL_VAPOR_DAMAGE, true);

                    /*
                    for (uint8 i=0; i<2; ++i)
                    {
                        Creature *Undead = m_creature->SummonCreature(MOB_DEAD, target->GetPositionX()+urand(1,20), target->GetPositionY()+urand(1,20), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 5000);
                        if (Undead)
                            Undead->AI()->AttackStart(Undead->getVictim());
                    }
                    */
                    /*
                    Creature *Vapor = m_creature->SummonCreature(MOB_VAPOR, target->GetPositionX()+15, target->GetPositionY()+15, target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    if (Vapor)
                    {
                        //float x, y, z;
                        //Vapor->GetMotionMaster()->MovePoint(0, Vapor->GetPositionX()+urand(-20,40), Vapor->GetPositionY()+urand(-20,40), Vapor->GetPositionZ());
                    }
                    */

                }
                ++BreathCount;
                DemonicVaporTimer = 25000;
            }else DemonicVaporTimer -= diff;
            
            //if (FogOfCorruption)
                if (FogOfCorruptionTimer < diff)
                {
                    //summon mobka  jakos srodek chmury  na 100 yardow srpawdzanie  kto jest  i niewiem uspienie itd lub rozbudowane  ai
                    if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                    {
                        m_creature->SummonCreature(MOB_DEATH_CLOUD, target->GetPositionX()+20, target->GetPositionY()+20, target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                        m_creature->SummonCreature(MOB_DEATH_CLOUD, target->GetPositionX()-20, target->GetPositionY()-20, target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                        m_creature->SummonCreature(MOB_DEATH_CLOUD, target->GetPositionX()+60, target->GetPositionY()+60, target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                        m_creature->SummonCreature(MOB_DEATH_CLOUD, target->GetPositionX()-60, target->GetPositionY()-60, target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 15000);   
                    }
                    ++BreathCount;
                    FogOfCorruptionTimer = 20000;
                    LandPhaseTimer = 15000;    
                }else FogOfCorruptionTimer -= diff;

            /*if(!FogOfCorruption)
                if (BreathCount > 1)
                {
                    FogOfCorruptionTimer = 5000;
                    FogOfCorruption = true;
                } */

            /*
            if (BreathCount >= 3)
                if (LandPhaseTimer < diff)
                {
                    FlyPhaseTimer = 60000;
                    FlyPhase = false;
                    //start move
				    m_creature->GetMotionMaster()->Clear();
				    Unit *victim = m_creature->getVictim();
				    if (victim)
				        m_creature->GetMotionMaster()->MoveChase(victim);
                }LandPhaseTimer -= diff;
            */
        }
    }
};

//DeatchCloud 100yard range -> mind control
struct MANGOS_DLL_DECL mob_deathcloudAI : public Scripted_NoMovementAI
{
    mob_deathcloudAI(Creature *c) : Scripted_NoMovementAI(c)
    {
        m_pInstance = (ScriptedInstance*)c->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint64 FelmystGUID;
    uint32 CheckTimer;

    void Reset() 
    {
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);

        CheckTimer = 1000;

        DoCast(m_creature,SPELL_FOG_TRIGGER, true);

        if(m_pInstance)
			FelmystGUID = m_pInstance->GetData64(DATA_FELMYST);
        else
            FelmystGUID = 0;
    }


    void UpdateAI(const uint32 diff)
    {
        if (CheckTimer < diff)
		{
			Unit* Felmyst = Unit::GetUnit((*m_creature), FelmystGUID);

            if (!Felmyst)
                return;

			std::list<HostilReference *> t_list = Felmyst->getThreatManager().getThreatList();
			for(std::list<HostilReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
			{
				if(Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid()))
					if(target && target->GetTypeId() == TYPEID_PLAYER && m_creature->IsWithinDistInMap(target, 100))
                    {
                        //Mind Control
                    }
			}
			CheckTimer = 1000;
		}CheckTimer -= diff;

    }
};

// ten mobek sprawdzaa  czy ktos jest  w  poblizu zadaje dmg  i sumonuje szkielety
struct MANGOS_DLL_DECL mob_felmyst_vaporAI : public Scripted_NoMovementAI
{
    mob_felmyst_vaporAI(Creature *c) : Scripted_NoMovementAI(c)
    {
        m_pInstance = (ScriptedInstance*)c->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint64 FelmystGUID;
    uint32 CheckTimer;

    void Reset() 
    {
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);

        CheckTimer = 1000;

        DoCast(m_creature,SPELL_TRAIL_TRIGGER, true);

        if(m_pInstance)
			FelmystGUID = m_pInstance->GetData64(DATA_FELMYST);
        else
            FelmystGUID = 0;
    }


    void UpdateAI(const uint32 diff)
    {
        if (CheckTimer < diff)
		{
			Unit* Felmyst = Unit::GetUnit((*m_creature), FelmystGUID);

            if (!Felmyst)
                return;

			std::list<HostilReference *> t_list = Felmyst->getThreatManager().getThreatList();
			for(std::list<HostilReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
			{
				if(Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid()))
					if(target && target->GetTypeId() == TYPEID_PLAYER && m_creature->IsWithinDistInMap(target, 3))
                    {
                        //min control trigget
                    }
			}
			CheckTimer = 1000;
		}CheckTimer -= diff;

    }
};

// ten mobek chdozi i zostaiwa  vapory 
struct MANGOS_DLL_DECL mob_felmyst_trailAI : public ScriptedAI
{
    mob_felmyst_trailAI(Creature *c) : ScriptedAI(c)
    {
        Reset();
    }

    uint32 VaporTimer;

    void Reset() 
    {
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);
        VaporTimer = 1000;
    }

    void UpdateAI(const uint32 diff) 
    {
        if (VaporTimer < diff)
        {
            Creature *Vapor = m_creature->SummonCreature(MOB_VAPOR, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
            VaporTimer = 2000;
        }VaporTimer -= diff;
    }
};

CreatureAI* GetAI_mob_deathcloud(Creature* _Creature)
{
    return new mob_deathcloudAI(_Creature);
}

CreatureAI* GetAI_mob_felmyst_vapor(Creature* _Creature)
{
    return new mob_felmyst_vaporAI(_Creature);
}

CreatureAI* GetAI_mob_felmyst_trail(Creature* _Creature)
{
    return new mob_felmyst_trailAI(_Creature);
}

CreatureAI* GetAI_boss_felmyst(Creature *_Creature)
{
    return new boss_felmystAI (_Creature);
}

void AddSC_boss_felmyst()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_felmyst";
    newscript->GetAI = &GetAI_boss_felmyst;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_felmyst_vapor";
    newscript->GetAI = &GetAI_mob_felmyst_vapor;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="mob_felmyst_trail";
    newscript->GetAI = &GetAI_mob_felmyst_trail;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_deathcloud";
    newscript->GetAI = &GetAI_mob_deathcloud;
    newscript->RegisterSelf();
}
