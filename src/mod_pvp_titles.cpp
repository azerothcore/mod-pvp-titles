#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "Player.h"
#include "Chat.h"

class PVPTitles : public PlayerScript
{
public:
    PVPTitles() : PlayerScript("PVPTitles") { }

    void OnLogin(Player *player) override
    {
        if (sConfigMgr->GetBoolDefault("PvPTitles.Enable", false))
        {
            if (sConfigMgr->GetBoolDefault("PvPTitles.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00PvPTitles |rmodule.");
            }
        }
    }

    void OnPVPKill(Player *Killer, Player *Killed) override
    {
        if (sConfigMgr->GetBoolDefault("PvPTitles.Enable", false))
        {
            if (Killer->GetGUID() == Killed->GetGUID())
                return;

            uint32 team = Killer->GetTeamId(true);
//			uint32 PlusKill = 14;

            const uint32 PVP_LIFETIME_HONORABLE_KILLS = Killer->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS);
            
            const uint32 RANK_1	= sConfigMgr->GetIntDefault("PvPTitles.Rank_1", 50);
            const uint32 RANK_2	= sConfigMgr->GetIntDefault("PvPTitles.Rank_2", 100);
            const uint32 RANK_3	= sConfigMgr->GetIntDefault("PvPTitles.Rank_3", 500);
            const uint32 RANK_4	= sConfigMgr->GetIntDefault("PvPTitles.Rank_4", 1000);
            const uint32 RANK_5	= sConfigMgr->GetIntDefault("PvPTitles.Rank_5", 2000);
            const uint32 RANK_6	= sConfigMgr->GetIntDefault("PvPTitles.Rank_6", 4000);
            const uint32 RANK_7	= sConfigMgr->GetIntDefault("PvPTitles.Rank_7", 5000);
            const uint32 RANK_8	= sConfigMgr->GetIntDefault("PvPTitles.Rank_8", 6000);
            const uint32 RANK_9	= sConfigMgr->GetIntDefault("PvPTitles.Rank_9", 8000);
            const uint32 RANK_10 = sConfigMgr->GetIntDefault("PvPTitles.Rank_10", 10000);
            const uint32 RANK_11 = sConfigMgr->GetIntDefault("PvPTitles.Rank_11", 12500);
            const uint32 RANK_12 = sConfigMgr->GetIntDefault("PvPTitles.Rank_12", 15000);
            const uint32 RANK_13 = sConfigMgr->GetIntDefault("PvPTitles.Rank_13", 20000);
            const uint32 RANK_14 = sConfigMgr->GetIntDefault("PvPTitles.Rank_14", 25000);

            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_1 )
            {
                if (team == TEAM_HORDE)
                {   
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(15)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(15));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(1)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(1));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_2 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(16)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(16));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(2)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(2));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_3 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(17)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(17));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(3)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(3));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_4 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(18)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(18));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(4)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(4));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_5 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(19)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(19));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(5)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(5));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_6 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(20)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(20));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(6)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(6));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_7 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(21)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(21));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(7)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(7));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_8 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(22)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(22));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(8)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(8));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_9 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(23)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(23));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(9)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(9));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_10 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(24)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(24));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(10)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(10));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_11 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(25)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(25));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(11)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(11));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_12 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(26)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(26));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(12)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(12));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_13 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(27)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(27));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(13)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(13));
                    }
                }
            }
            if (PVP_LIFETIME_HONORABLE_KILLS >= RANK_14 )
            {
                if (team == TEAM_HORDE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(28)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(28));
                    }
                }
                else if (team == TEAM_ALLIANCE)
                {
                    if (!Killer->HasTitle(sCharTitlesStore.LookupEntry(14)))
                    {
                        Killer->SetTitle(sCharTitlesStore.LookupEntry(14));
                    }
                }
            }
        }
    }
};

void AddPvpTitlesScripts() 
{
    new PVPTitles();
}
