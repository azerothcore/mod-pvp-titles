#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "Player.h"
#include "Chat.h"

struct PvPTitles
{
    uint32 RequiredKills;
    uint32 TitleId;
    uint32 FeatOfStrength;
};

struct PvPTitleData
{
    uint32 TitleId[2];
    uint32 FeatOfStrength[2];
};

enum Ranks
{                             //    A                           H
    RANK_ONE            = 0,  // Private                 &    Scout
    RANK_TWO            = 1,  // Corporal                &    Grunt
    RANK_THREE          = 2,  // Sergeant                &    Sergeant
    RANK_FOUR           = 3,  // Master Sergeant         &    Senior Sergeant
    RANK_FIVE           = 4,  // Sergeant Major          &    First Sergeant
    RANK_SIX            = 5,  // Knight                  &    Stone Guard
    RANK_SEVEN          = 6,  // Knight Lieutenant       &    Blood Guard
    RANK_EIGHT          = 7,  // Knight Captain          &    Legionnaire
    RANK_NINE           = 8,  // Knight Champion         &    Centurion
    RANK_TEN            = 9,  // Lieutenant Commander    &    Champion
    RANK_ELEVEN         = 10, // Commander               &    Lieutenant General
    RANK_TWELVE         = 11, // Marshal                 &    General
    RANK_THIRTEEN       = 12, // Field Marshal           &    Warlord
    RANK_FOURTEEN       = 13  // Grand Marshal           &    High Warlord
};

enum RankReqKillDefault
{
    RANK_ONE_HK_COUNT        = 50,    // Private                 &    Scout
    RANK_TWO_HK_COUNT        = 100,   // Corporal                &    Grunt
    RANK_THREE_HK_COUNT      = 500,   // Sergeant                &    Sergeant
    RANK_FOUR_HK_COUNT       = 1000,  // Master Sergeant         &    Senior Sergeant
    RANK_FIVE_HK_COUNT       = 2000,  // Sergeant Major          &    First Sergeant
    RANK_SIX_HK_COUNT        = 4000,  // Knight                  &    Stone Guard
    RANK_SEVEN_HK_COUNT      = 5000,  // Knight Lieutenant       &    Blood Guard
    RANK_EIGHT_HK_COUNT      = 6000,  // Knight Captain          &    Legionnaire
    RANK_NINE_HK_COUNT       = 8000,  // Knight Champion         &    Centurion
    RANK_TEN_HK_COUNT        = 10000, // Lieutenant Commander    &    Champion
    RANK_ELEVEN_HK_COUNT     = 12500, // Commander               &    Lieutenant General
    RANK_TWELVE_HK_COUNT     = 15000, // Marshal                 &    General
    RANK_THIRTEEN_HK_COUNT   = 20000, // Field Marshal           &    Warlord
    RANK_FOURTEEN_HK_COUNT   = 25000  // Grand Marshal           &    High Warlord
};

enum Titles
{
    // Alliance
    PRIVATE                  = 1,
    CORPORAL                 = 2,
    SERGEANT                 = 3,
    MASTER_SERGEANT          = 4,
    SERGEANT_MAJOR           = 5,
    KNIGHT                   = 6,
    KNIGHT_LIEUTENANT        = 7,
    KNIGHT_CAPTAIN           = 8,
    KNIGHT_CHAMPION          = 9,
    LIEUTENANT_COMMANDER     = 10,
    COMMANDER                = 11,
    MARSHAL                  = 12,
    FIELD_MARSHAL            = 13,
    GRAND_MARSHAL            = 14,
    
    // Horde
    SCOUT                    = 15,
    GRUNT                    = 16,
    SERGEANT_H               = 17,
    SENIOR_SERGEANT          = 18,
    FIRST_SERGEANT           = 19,
    STONE_GUARD              = 20,
    BLOOD_GUARD              = 21,
    LEGIONNAIRE              = 22,
    CENTURION                = 23,
    CHAMPION                 = 24,
    LIEUTENANT_GENERAL       = 25,
    GENERAL                  = 26,
    WARLORD                  = 27,
    HIGH_WARLORD             = 28
};

enum FeatsOfStrength
{
    FOS_GRAND_MARSHAL         = 433,
    FOS_FIELD_MARSHAL         = 434,
    FOS_MARSHAL               = 473,
    FOS_COMMANDER             = 435,
    FOS_LIEUTENANT_COMMANDER  = 436,
    FOS_KNIGHT_CHAMPION       = 437,
    FOS_KNIGHT_CAPTAIN        = 438,
    FOS_KNIGHT_LIEUTENANT     = 472,
    FOS_KNIGHT                = 439,
    FOS_SERGEANT_MAJOR        = 440,
    FOS_MASTER_SERGEANT       = 441,
    FOS_SARGEANT              = 471,
    FOS_CORPORAL              = 470,
    FOS_PRIVATE               = 442,

    FOS_HIGH_WARLORD          = 443,
    FOS_WARLORD               = 445,
    FOS_GENERAL               = 446,
    FOS_LIEUTENANT_GENERAL    = 444,
    FOS_CHAMPION              = 447,
    FOS_CENTURION             = 448,
    FOS_LEGIONNAIRE           = 469,
    FOS_BLOOD_GUARD           = 449,
    FOS_STONE_GUARD           = 451,
    FOS_FIRST_SARGEANT        = 452,
    FOS_SENIOR_SERGEANT       = 450,
    FOS_SARGEANT_H            = 453,
    FOS_GRUNT                 = 468,
    FOS_SCOUT                 = 454
};

enum CleanUpTitlesModes
{
    CLEAN_UP_NONE             = 0, // Disabled.
    CLEAN_UP_REMOVE_ALL       = 1, // Remove all titles on login.
    CLEAN_UP_REMOVE_INVALID   = 2  // Remove titles if players no longer meet the requirements on login.
};

PvPTitleData const TitleData[14] =
{
    { { PRIVATE,              SCOUT              }, { FOS_PRIVATE,              FOS_SCOUT              } },
    { { CORPORAL,             GRUNT              }, { FOS_CORPORAL,             FOS_GRUNT              } },
    { { SERGEANT,             SERGEANT_H         }, { FOS_SARGEANT,             FOS_SARGEANT_H         } },
    { { MASTER_SERGEANT,      SENIOR_SERGEANT    }, { FOS_MASTER_SERGEANT,      FOS_SENIOR_SERGEANT    } },
    { { SERGEANT_MAJOR,       FIRST_SERGEANT     }, { FOS_SERGEANT_MAJOR,       FOS_FIRST_SARGEANT     } },
    { { KNIGHT,               STONE_GUARD        }, { FOS_KNIGHT,               FOS_STONE_GUARD        } },
    { { KNIGHT_LIEUTENANT,    BLOOD_GUARD        }, { FOS_KNIGHT_LIEUTENANT,    FOS_BLOOD_GUARD        } },
    { { KNIGHT_CAPTAIN,       LEGIONNAIRE        }, { FOS_KNIGHT_CAPTAIN,       FOS_LEGIONNAIRE        } },
    { { KNIGHT_CHAMPION,      CENTURION          }, { FOS_KNIGHT_CHAMPION,      FOS_CENTURION          } },
    { { LIEUTENANT_COMMANDER, CHAMPION           }, { FOS_LIEUTENANT_COMMANDER, FOS_CHAMPION           } },
    { { COMMANDER,            LIEUTENANT_GENERAL }, { FOS_COMMANDER,            FOS_LIEUTENANT_GENERAL } },
    { { MARSHAL,              GENERAL            }, { FOS_MARSHAL,              FOS_GENERAL            } },
    { { FIELD_MARSHAL,        WARLORD            }, { FOS_FIELD_MARSHAL,        FOS_WARLORD            } },
    { { GRAND_MARSHAL,        HIGH_WARLORD       }, { FOS_GRAND_MARSHAL,        FOS_HIGH_WARLORD       } }
};

class PVPTitles : public PlayerScript
{
public:
    PVPTitles() : PlayerScript("PVPTitles") { }

    void OnLogin(Player *player) override
    {
        if (sConfigMgr->GetOption<bool>("PvPTitles.Enable", false))
        {
            if (sConfigMgr->GetOption<bool>("PvPTitles.Announce", true))
            {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00PvPTitles |rmodule.");
            }

            if (sConfigMgr->GetOption<bool>("PvPTitles.AwardTitlesOnLogin", false))
            {
                AwardEarnedTitles(player);
            }

            if (sConfigMgr->GetOption<int32>("PvPTitles.CleanUp", CLEAN_UP_NONE))
            {
                CleanUpTitles(sConfigMgr->GetOption<int32>("PvPTitles.CleanUp", CLEAN_UP_NONE), player);
            }
        }
    }

    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (sConfigMgr->GetOption<bool>("PvPTitles.Enable", false))
        {
            if (killer->GetGUID() == killed->GetGUID())
                return;

            AwardEarnedTitles(killer);
        }
    }

    void AwardEarnedTitles(Player* me)
    {
        TeamId teamId = me->GetTeamId(true);
        uint32 kills = me->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS);

        PvPTitles const pvpTitlesList[14] =
        {
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_1", RANK_ONE_HK_COUNT), TitleData[RANK_ONE].TitleId[teamId], TitleData[RANK_ONE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_2", RANK_TWO_HK_COUNT), TitleData[RANK_TWO].TitleId[teamId], TitleData[RANK_TWO].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_3", RANK_THREE_HK_COUNT), TitleData[RANK_THREE].TitleId[teamId], TitleData[RANK_THREE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_4", RANK_FOUR_HK_COUNT), TitleData[RANK_FOUR].TitleId[teamId], TitleData[RANK_FOUR].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_5", RANK_FIVE_HK_COUNT), TitleData[RANK_FIVE].TitleId[teamId], TitleData[RANK_FIVE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_6", RANK_SIX_HK_COUNT), TitleData[RANK_SIX].TitleId[teamId], TitleData[RANK_SIX].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_7", RANK_SEVEN_HK_COUNT), TitleData[RANK_SEVEN].TitleId[teamId], TitleData[RANK_SEVEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_8", RANK_EIGHT_HK_COUNT), TitleData[RANK_EIGHT].TitleId[teamId], TitleData[RANK_EIGHT].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_9", RANK_NINE_HK_COUNT), TitleData[RANK_NINE].TitleId[teamId], TitleData[RANK_NINE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_10", RANK_TEN_HK_COUNT), TitleData[RANK_TEN].TitleId[teamId], TitleData[RANK_TEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_11", RANK_ELEVEN_HK_COUNT), TitleData[RANK_ELEVEN].TitleId[teamId], TitleData[RANK_ELEVEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_12", RANK_TWELVE_HK_COUNT), TitleData[RANK_TWELVE].TitleId[teamId], TitleData[RANK_TWELVE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_13", RANK_THIRTEEN_HK_COUNT), TitleData[RANK_THIRTEEN].TitleId[teamId], TitleData[RANK_THIRTEEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_14", RANK_FOURTEEN_HK_COUNT), TitleData[RANK_FOURTEEN].TitleId[teamId], TitleData[RANK_FOURTEEN].FeatOfStrength[teamId] },
        };

        for (PvPTitles title : pvpTitlesList)
        {
            if (kills >= title.RequiredKills && !me->HasTitle(title.TitleId))
            {
                me->SetTitle(sCharTitlesStore.LookupEntry(title.TitleId));
            }
        }

        if (sConfigMgr->GetOption<bool>("PvPTitles.AwardFeatOfStrength", false))
        {
            for (PvPTitles title : pvpTitlesList)
            {
                if (kills >= title.RequiredKills)
                {
                    if (AchievementEntry const* achievementEntry = sAchievementStore.LookupEntry(title.FeatOfStrength))
                    {
                        me->CompletedAchievement(achievementEntry);
                    }
                }
            }
        }
    }

    void CleanUpTitles(int32 mode, Player* me)
    {
        TeamId teamId = me->GetTeamId(true);

        PvPTitles const pvpTitlesList[14] =
        {
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_1", RANK_ONE_HK_COUNT), TitleData[RANK_ONE].TitleId[teamId], TitleData[RANK_ONE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_2", RANK_TWO_HK_COUNT), TitleData[RANK_TWO].TitleId[teamId], TitleData[RANK_TWO].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_3", RANK_THREE_HK_COUNT), TitleData[RANK_THREE].TitleId[teamId], TitleData[RANK_THREE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_4", RANK_FOUR_HK_COUNT), TitleData[RANK_FOUR].TitleId[teamId], TitleData[RANK_FOUR].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_5", RANK_FIVE_HK_COUNT), TitleData[RANK_FIVE].TitleId[teamId], TitleData[RANK_FIVE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_6", RANK_SIX_HK_COUNT), TitleData[RANK_SIX].TitleId[teamId], TitleData[RANK_SIX].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_7", RANK_SEVEN_HK_COUNT), TitleData[RANK_SEVEN].TitleId[teamId], TitleData[RANK_SEVEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_8", RANK_EIGHT_HK_COUNT), TitleData[RANK_EIGHT].TitleId[teamId], TitleData[RANK_EIGHT].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_9", RANK_NINE_HK_COUNT), TitleData[RANK_NINE].TitleId[teamId], TitleData[RANK_NINE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_10", RANK_TEN_HK_COUNT), TitleData[RANK_TEN].TitleId[teamId], TitleData[RANK_TEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_11", RANK_ELEVEN_HK_COUNT), TitleData[RANK_ELEVEN].TitleId[teamId], TitleData[RANK_ELEVEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_12", RANK_TWELVE_HK_COUNT), TitleData[RANK_TWELVE].TitleId[teamId], TitleData[RANK_TWELVE].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_13", RANK_THIRTEEN_HK_COUNT), TitleData[RANK_THIRTEEN].TitleId[teamId], TitleData[RANK_THIRTEEN].FeatOfStrength[teamId] },
            { sConfigMgr->GetOption<uint32>("PvPTitles.Rank_14", RANK_FOURTEEN_HK_COUNT), TitleData[RANK_FOURTEEN].TitleId[teamId], TitleData[RANK_FOURTEEN].FeatOfStrength[teamId] },
        };

        for (PvPTitles title : pvpTitlesList)
        {
            if (mode == CLEAN_UP_REMOVE_ALL)
            {
                if (me->HasTitle(title.TitleId))
                {
                    me->SetTitle(sCharTitlesStore.LookupEntry(title.TitleId), true);
                }
            }
            else if (mode == CLEAN_UP_REMOVE_INVALID)
            {
                uint32 kills = me->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS);
                if (kills < title.RequiredKills && me->HasTitle(title.TitleId))
                {
                    me->SetTitle(sCharTitlesStore.LookupEntry(title.TitleId), true);
                }
            }
        }
    }
};

void AddPvpTitlesScripts() 
{
    new PVPTitles();
}
