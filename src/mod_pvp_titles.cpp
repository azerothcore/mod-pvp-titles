#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "Player.h"
#include "Chat.h"

enum Ranks
{
	RANK_1	= 50,
	RANK_2	= 100,
	RANK_3	= 500,
	RANK_4	= 1000,
	RANK_5	= 2000,
	RANK_6	= 4000,
	RANK_7	= 5000,
	RANK_8	= 6000,
	RANK_9	= 8000,
	RANK_10 = 10000,
	RANK_11 = 12500,
	RANK_12 = 15000,
	RANK_13 = 20000,
	RANK_14 = 25000,
};

class PVPTitles : public PlayerScript
{
public:
	PVPTitles() : PlayerScript("PVPTitles") { }

	void OnLogin(Player *player) override
	{
		if (sConfigMgr->GetBoolDefault("PvPTitles.Enable", true))
		{
			if (sConfigMgr->GetBoolDefault("PvPTitles.Announce", true))
			{
				ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00PvPTitles |rmodule.");
			}
		}
	}

	void OnPVPKill(Player *Killer, Player *Killed) override
	{
		if (sConfigMgr->GetBoolDefault("PvPTitles.Enable", true))
		{
			if (Killer->GetGUID() == Killed->GetGUID())
				return;

			uint32 team = Killer->GetTeamId();
//			uint32 PlusKill = 14;

			switch (Killer->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS))
			{
			case RANK_1:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(15));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(1));
				break;
			case RANK_2:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(16));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(2));
				break;
			case RANK_3:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(17));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(3));
				break;
			case RANK_4:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(18));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(4));
				break;
			case RANK_5:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(19));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(5));
				break;
			case RANK_6:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(20));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(6));
				break;
			case RANK_7:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(21));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(7));
				break;
			case RANK_8:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(22));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(8));
				break;
			case RANK_9:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(23));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(9));
				break;
			case RANK_10:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(24));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(10));
				break;
			case RANK_11:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(25));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(11));
				break;
			case RANK_12:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(26));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(12));
				break;
			case RANK_13:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(27));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(13));
				break;
			case RANK_14:
				if (team == TEAM_HORDE)
					Killer->SetTitle(sCharTitlesStore.LookupEntry(28));
				else
					Killer->SetTitle(sCharTitlesStore.LookupEntry(14));
				break;
			}
		}
	}
};

class PvpTitlesWorld : public WorldScript
{
public:
	PvpTitlesWorld() : WorldScript("PvpTitlesWorld") { }

	void OnBeforeConfigLoad(bool reload) override
	{
		if (!reload) {
			std::string conf_path = _CONF_DIR;
			std::string cfg_file = conf_path + "/mod_pvptitles.conf";
			std::string cfg_def_file = cfg_file + ".dist";
			sConfigMgr->LoadMore(cfg_def_file.c_str());
			sConfigMgr->LoadMore(cfg_file.c_str());
		}
	}
};

void AddPvpTitlesScripts() 
{
	new PvpTitlesWorld();
	new PVPTitles();
}
