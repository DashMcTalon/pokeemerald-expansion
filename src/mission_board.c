#include "global.h"
#include "constants/characters.h"
#include "battle.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "mission_board.h"
#include "money.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "constants/event_objects.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/maps.h"
#include "constants/mission_board.h"
#include "constants/species.h"
#include "constants/vars.h"

struct Mission
{
    const u8 *title; // Keep to about 16 characters so it fits in the board menu.
    const u8 *description; // {STR_VAR_1} = species name, {STR_VAR_2} = drop item name.
    u8 type;
    u8 board; // MISSION_BOARD_MAIN (the default) or MISSION_BOARD_LEGENDARY.
    u8 requiredRank;
    enum Species species; // The Pokémon to deliver, or the one at the mission site.
    enum Species species2; // Hordes: the second Pokémon in each wave (SPECIES_NONE = same as species).
    u8 waves; // Hordes: how many double battles in a row.
    u8 level; // Mission site Pokémon only.
    u16 map; // Map with the mission site (MAP_ constant). Mission site missions only.
    enum Item dropItem; // Item-drop missions: the key item the site Pokémon drops.
    enum Move moves[MAX_MON_MOVES]; // Crazed missions: leave empty for its normal moves.
    s8 statBoosts[NUM_BATTLE_STATS]; // Crazed missions: stages raised at battle start, e.g. [STAT_SPEED] = 1. Evasion isn't supported.
    u16 requiredMissions[MAX_REQUIRED_MISSIONS]; // Only offered once all of these are cleared, in any order.
    u16 requiredFlag; // Only offered once this flag is set, e.g. a story event (0 = no requirement).
    bool8 oneTime; // Never offered again once cleared.
    u32 rewardMoney;
    enum Item rewardItem; // ITEM_NONE for no item.
    u16 rewardItemQuantity;
    u16 rewardPoints; // Halved when the mission has been cleared before.
};

struct MissionRank
{
    const u8 *name;
    u16 pointsNeeded;
    enum Item giftItem; // Given once, when the player reaches this rank.
    u16 giftQuantity;
};

static const struct MissionRank sRanks[MISSION_RANK_COUNT] =
{
    [MISSION_RANK_ROOKIE] = { COMPOUND_STRING("Rookie"),    0, ITEM_NONE,        0 },
    [MISSION_RANK_BRONZE] = { COMPOUND_STRING("Bronze"),  100, ITEM_GREAT_BALL,  5 },
    [MISSION_RANK_SILVER] = { COMPOUND_STRING("Silver"),  300, ITEM_ULTRA_BALL,  5 },
    [MISSION_RANK_GOLD]   = { COMPOUND_STRING("Gold"),    700, ITEM_RARE_CANDY,  3 },
    [MISSION_RANK_MASTER] = { COMPOUND_STRING("Master"), 1500, ITEM_MASTER_BALL, 1 },
};

// The mission list: each row is one mission on the board.
static const struct Mission sMissions[MISSIONS_COUNT] =
{
    [MISSION_DELIVER_NINCADA] =
    {
        .title = COMPOUND_STRING("Bug Delivery"),
        .description = COMPOUND_STRING(
            "A researcher needs a {STR_VAR_1}\n"
            "for a study on shedding shells.\p"
            "Catch one and bring it to the board."),
        .type = MISSION_TYPE_CATCH_DELIVER,
        .requiredRank = MISSION_RANK_ROOKIE,
        .species = SPECIES_NINCADA,
        .rewardMoney = 1000,
        .rewardItem = ITEM_POKE_BALL,
        .rewardItemQuantity = 3,
        .rewardPoints = 10,
    },
    [MISSION_DELIVER_HERACROSS] =
    {
        .title = COMPOUND_STRING("Strong Helper"),
        .description = COMPOUND_STRING(
            "A farmer wants a {STR_VAR_1}\n"
            "to help move heavy logs.\p"
            "Catch one and bring it to the board."),
        .type = MISSION_TYPE_CATCH_DELIVER,
        .requiredRank = MISSION_RANK_ROOKIE,
        .species = SPECIES_HERACROSS,
        .rewardMoney = 1200,
        .rewardItem = ITEM_SUPER_POTION,
        .rewardItemQuantity = 1,
        .rewardPoints = 10,
    },
    [MISSION_DELIVER_HOOTHOOT] =
    {
        .title = COMPOUND_STRING("Night Watch"),
        .description = COMPOUND_STRING(
            "A night guard wants a {STR_VAR_1}\n"
            "to keep watch with them.\p"
            "Catch one and bring it to the board."),
        .type = MISSION_TYPE_CATCH_DELIVER,
        .requiredRank = MISSION_RANK_ROOKIE,
        .species = SPECIES_HOOTHOOT,
        .rewardMoney = 1000,
        .rewardItem = ITEM_POTION,
        .rewardItemQuantity = 2,
        .rewardPoints = 10,
    },
    [MISSION_DELIVER_PIKACHU] =
    {
        .title = COMPOUND_STRING("Power Outage"),
        .description = COMPOUND_STRING(
            "The lab's generator broke! They\n"
            "need a {STR_VAR_1} to help out.\p"
            "Catch one and bring it to the board."),
        .type = MISSION_TYPE_CATCH_DELIVER,
        .requiredRank = MISSION_RANK_ROOKIE,
        .species = SPECIES_PIKACHU,
        .rewardMoney = 1500,
        .rewardItem = ITEM_POKE_BALL,
        .rewardItemQuantity = 5,
        .rewardPoints = 15,
    },
    [MISSION_DELIVER_NINJASK] =
    {
        .title = COMPOUND_STRING("Speed Test"),
        .description = COMPOUND_STRING(
            "A racer wants a {STR_VAR_1} to\n"
            "train with. Evolve a Nincada!\p"
            "Bring one to the board."),
        .type = MISSION_TYPE_CATCH_DELIVER,
        .requiredRank = MISSION_RANK_BRONZE,
        .species = SPECIES_NINJASK,
        .rewardMoney = 2500,
        .rewardItem = ITEM_GREAT_BALL,
        .rewardItemQuantity = 3,
        .rewardPoints = 20,
    },
    [MISSION_RECOVER_SATCHEL] =
    {
        .title = COMPOUND_STRING("Stolen Satchel"),
        .description = COMPOUND_STRING(
            "A wild {STR_VAR_1} ran off with a\n"
            "hiker's {STR_VAR_2}!\p"
            "It was last seen on the test route.\n"
            "Defeat it and bring the bag back."),
        .type = MISSION_TYPE_ITEM_DROP,
        .requiredRank = MISSION_RANK_ROOKIE,
        .species = SPECIES_HERACROSS,
        .level = 6,
        .map = MAP_TEST_MAP1,
        .dropItem = ITEM_LOST_SATCHEL,
        .rewardMoney = 1500,
        .rewardItem = ITEM_POTION,
        .rewardItemQuantity = 3,
        .rewardPoints = 15,
    },
    [MISSION_CRAZED_PIKACHU] =
    {
        .title = COMPOUND_STRING("Crazed Pikachu"),
        .description = COMPOUND_STRING(
            "A crazed {STR_VAR_1} is zapping\n"
            "travelers on the test route!\p"
            "It's too wild to catch.\n"
            "Defeat it to calm it down."),
        .type = MISSION_TYPE_CRAZED,
        .requiredRank = MISSION_RANK_SILVER,
        .species = SPECIES_PIKACHU,
        .level = 10,
        .map = MAP_TEST_MAP1,
        .moves = { MOVE_THUNDER_SHOCK, MOVE_QUICK_ATTACK, MOVE_THUNDER_WAVE, MOVE_DOUBLE_TEAM },
        .statBoosts = { [STAT_SPEED] = 1, [STAT_SPATK] = 1 },
        .rewardMoney = 5000,
        .rewardItem = ITEM_ULTRA_BALL,
        .rewardItemQuantity = 2,
        .rewardPoints = 40,
    },
    [MISSION_CALM_PIKACHU] =
    {
        .title = COMPOUND_STRING("Calm Pikachu"),
        .description = COMPOUND_STRING(
            "The {STR_VAR_1} you calmed down\n"
            "is back on the test route.\p"
            "It's gentle now.\n"
            "Catch it if you can!"),
        .type = MISSION_TYPE_CALM_CATCH,
        .requiredRank = MISSION_RANK_SILVER,
        .species = SPECIES_PIKACHU,
        .level = 10,
        .map = MAP_TEST_MAP1,
        .requiredMissions = { MISSION_CRAZED_PIKACHU },
        .oneTime = TRUE,
        .rewardMoney = 1000,
        .rewardItem = ITEM_NONE,
        .rewardPoints = 20,
    },
    [MISSION_HORDE_BUGS] =
    {
        .title = COMPOUND_STRING("Bug Swarm"),
        .description = COMPOUND_STRING(
            "A swarm of {STR_VAR_1} is chewing\n"
            "up the test route!\p"
            "Fight off every wave. There's\n"
            "no time to heal between waves!"),
        .type = MISSION_TYPE_HORDE,
        .requiredRank = MISSION_RANK_BRONZE,
        .species = SPECIES_NINCADA,
        .species2 = SPECIES_HERACROSS,
        .waves = 3,
        .level = 6,
        .map = MAP_TEST_MAP1,
        .rewardMoney = 2500,
        .rewardItem = ITEM_GREAT_BALL,
        .rewardItemQuantity = 3,
        .rewardPoints = 25,
    },

    // ---- Legendary Board placeholders for testing. Replace with your real missions. ----
    // Switched on and off by MISSION_ENABLE_TEST_LEGENDARIES in include/constants/mission_board.h.
#if MISSION_ENABLE_TEST_LEGENDARIES

    // A legendary you can go after right away.
    [MISSION_TEST_LEGEND_DIRECT] =
    {
        .title = COMPOUND_STRING("Test: Entei"),
        .description = COMPOUND_STRING(
            "PLACEHOLDER: An {STR_VAR_1} has been\n"
            "seen on the test route.\p"
            "Catch it before it runs off!"),
        .type = MISSION_TYPE_LEGENDARY,
        .board = MISSION_BOARD_LEGENDARY,
        .species = SPECIES_ENTEI,
        .level = 80,
        .map = MAP_TEST_MAP1,
        .oneTime = TRUE,
        .rewardMoney = 20000,
        .rewardPoints = 100,
    },
    // Two themed missions that must both be cleared to unlock the chained legendary.
    [MISSION_TEST_LEGEND_STEP_1] =
    {
        .title = COMPOUND_STRING("Test: Sea Omen"),
        .description = COMPOUND_STRING(
            "PLACEHOLDER: Flocks of {STR_VAR_1}\n"
            "are fleeing something at sea.\p"
            "Drive back the panicked waves."),
        .type = MISSION_TYPE_HORDE,
        .board = MISSION_BOARD_LEGENDARY,
        .species = SPECIES_WINGULL,
        .waves = 2,
        .level = 6,
        .map = MAP_TEST_MAP1,
        .oneTime = TRUE,
        .rewardMoney = 10000,
        .rewardPoints = 50,
    },
    [MISSION_TEST_LEGEND_STEP_2] =
    {
        .title = COMPOUND_STRING("Test: Wild Tide"),
        .description = COMPOUND_STRING(
            "PLACEHOLDER: A crazed {STR_VAR_1}\n"
            "senses a great power waking.\p"
            "Calm it down."),
        .type = MISSION_TYPE_CRAZED,
        .board = MISSION_BOARD_LEGENDARY,
        .species = SPECIES_MAGIKARP,
        .level = 7,
        .map = MAP_TEST_MAP1,
        .statBoosts = { [STAT_DEF] = 1 },
        .oneTime = TRUE,
        .rewardMoney = 10000,
        .rewardPoints = 50,
    },
    // Unlocks once both themed missions above are cleared.
    [MISSION_TEST_LEGEND_CHAINED] =
    {
        .title = COMPOUND_STRING("Test: Lugia"),
        .description = COMPOUND_STRING(
            "PLACEHOLDER: The sea has gone still.\n"
            "{STR_VAR_1} has surfaced at last!\p"
            "This is your chance to catch it."),
        .type = MISSION_TYPE_LEGENDARY,
        .board = MISSION_BOARD_LEGENDARY,
        .species = SPECIES_LUGIA,
        .level = 100,
        .map = MAP_TEST_MAP1,
        .requiredMissions = { MISSION_TEST_LEGEND_STEP_1, MISSION_TEST_LEGEND_STEP_2 },
        .oneTime = TRUE,
        .rewardMoney = 30000,
        .rewardPoints = 100,
    },
#endif
};

STATIC_ASSERT(MISSIONS_COUNT <= MAX_MISSIONS + 1, TooManyMissions);
STATIC_ASSERT(VAR_MISSION_SLOT_1 + MISSION_BOARD_SLOTS - 1 == VAR_MISSION_SLOT_3, MissionSlotVarsMustBeInOrder);

static u16 GetSlotMissionId(u32 slot)
{
    return VarGet(VAR_MISSION_SLOT_1 + slot);
}

static const struct Mission *GetValidMission(u32 missionId)
{
    // A switched-off mission's row is empty, so it has no title.
    if (missionId == MISSION_NONE || missionId >= MISSIONS_COUNT || sMissions[missionId].title == NULL)
        return NULL;
    return &sMissions[missionId];
}

static const struct Mission *GetSelectedSlotMission(void)
{
    if (gSpecialVar_0x8004 >= MISSION_BOARD_SLOTS)
        return NULL;
    return GetValidMission(GetSlotMissionId(gSpecialVar_0x8004));
}

static const struct Mission *GetActiveMission(void)
{
    return GetValidMission(VarGet(VAR_MISSION_ACTIVE));
}

static u32 GetCurrentRank(void)
{
    return min(VarGet(VAR_MISSION_RANK), MISSION_RANK_COUNT - 1);
}

static bool32 IsMissionCleared(u32 missionId)
{
    return FlagGet(FLAG_MISSION_CLEARED_START + missionId - 1);
}

static u32 GetPointsForMission(const struct Mission *mission)
{
    if (IsMissionCleared(mission - sMissions))
        return mission->rewardPoints / 2;
    return mission->rewardPoints;
}

static bool32 IsMissionOnBoard(u32 missionId)
{
    u32 slot;

    for (slot = 0; slot < MISSION_BOARD_SLOTS; slot++)
    {
        if (GetSlotMissionId(slot) == missionId)
            return TRUE;
    }
    return FALSE;
}

// TRUE once the mission's required missions and story flag are all done.
static bool32 AreUnlockRequirementsMet(const struct Mission *mission)
{
    u32 i;

    for (i = 0; i < MAX_REQUIRED_MISSIONS; i++)
    {
        if (mission->requiredMissions[i] != MISSION_NONE && !IsMissionCleared(mission->requiredMissions[i]))
            return FALSE;
    }
    if (mission->requiredFlag != 0 && !FlagGet(mission->requiredFlag))
        return FALSE;
    return TRUE;
}

// TRUE if the mission can be offered on the board it belongs to right now.
static bool32 IsMissionAvailable(u32 missionId)
{
    const struct Mission *mission = &sMissions[missionId];

    if (mission->title == NULL) // Switched off
        return FALSE;
    if (mission->requiredRank > GetCurrentRank())
        return FALSE;
    if (!AreUnlockRequirementsMet(mission))
        return FALSE;
    if (mission->oneTime && IsMissionCleared(missionId))
        return FALSE;
    if (missionId == VarGet(VAR_MISSION_ACTIVE))
        return FALSE;
    return TRUE;
}

static bool32 CanOfferMission(u32 missionId, bool32 onlyUncleared)
{
    if (sMissions[missionId].board != MISSION_BOARD_MAIN)
        return FALSE;
    if (!IsMissionAvailable(missionId))
        return FALSE;
    if (IsMissionOnBoard(missionId))
        return FALSE;
    if (onlyUncleared && IsMissionCleared(missionId))
        return FALSE;
    return TRUE;
}

// Picks a random mission the board can offer, or MISSION_NONE.
static u32 PickRandomMission(bool32 onlyUncleared)
{
    u32 missionId, count = 0, pick;

    for (missionId = MISSION_NONE + 1; missionId < MISSIONS_COUNT; missionId++)
    {
        if (CanOfferMission(missionId, onlyUncleared))
            count++;
    }
    if (count == 0)
        return MISSION_NONE;

    pick = Random() % count;
    for (missionId = MISSION_NONE + 1; missionId < MISSIONS_COUNT; missionId++)
    {
        if (CanOfferMission(missionId, onlyUncleared) && pick-- == 0)
            return missionId;
    }
    return MISSION_NONE;
}

static void BufferDescription(const struct Mission *mission)
{
    if (mission == NULL)
    {
        gStringVar4[0] = EOS;
        return;
    }
    StringCopy(gStringVar1, GetSpeciesName(mission->species));
    if (mission->dropItem != ITEM_NONE)
        CopyItemName(mission->dropItem, gStringVar2);
    StringExpandPlaceholders(gStringVar4, mission->description);
}

static void BufferReward(const struct Mission *mission)
{
    u8 *end;

    if (mission == NULL)
    {
        gStringVar4[0] = EOS;
        return;
    }

    ConvertIntToDecimalStringN(gStringVar1, mission->rewardMoney, STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
    ConvertIntToDecimalStringN(gStringVar2, GetPointsForMission(mission), STR_CONV_MODE_LEFT_ALIGN, 5);
    end = StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Reward: ¥{STR_VAR_1} and {STR_VAR_2} points"));

    if (mission->rewardItem != ITEM_NONE)
    {
        ConvertIntToDecimalStringN(gStringVar1, mission->rewardItemQuantity, STR_CONV_MODE_LEFT_ALIGN, 3);
        CopyItemNameHandlePlural(mission->rewardItem, gStringVar2, mission->rewardItemQuantity);
        end = StringExpandPlaceholders(end, COMPOUND_STRING(",\nplus {STR_VAR_1} {STR_VAR_2}."));
    }
    else
    {
        end = StringExpandPlaceholders(end, COMPOUND_STRING("."));
    }

    if (IsMissionCleared(mission - sMissions))
        StringExpandPlaceholders(end, COMPOUND_STRING("\pYou've done this one before,\nso it's worth half the points."));
}

static bool32 UsesMissionSite(const struct Mission *mission)
{
    return mission->type != MISSION_TYPE_CATCH_DELIVER;
}

// TRUE if clearing this mission was the last thing another mission needed.
static bool32 UnlocksNewMission(u32 clearedMissionId)
{
    u32 missionId, i;

    for (missionId = MISSION_NONE + 1; missionId < MISSIONS_COUNT; missionId++)
    {
        const struct Mission *mission = &sMissions[missionId];

        if (IsMissionCleared(missionId) || !AreUnlockRequirementsMet(mission))
            continue;
        for (i = 0; i < MAX_REQUIRED_MISSIONS; i++)
        {
            if (mission->requiredMissions[i] == clearedMissionId)
                return TRUE;
        }
    }
    return FALSE;
}

static u32 GetSiteMonLevel(const struct Mission *mission)
{
#if MISSION_LEGENDARY_TEST_LEVELS
    if (mission->type == MISSION_TYPE_LEGENDARY)
        return 5 + Random() % 3;
#endif
    return mission->level;
}

// {STR_VAR_2} = the wave the player is on, {STR_VAR_3} = total waves.
static void BufferHordeWave(const struct Mission *mission)
{
    ConvertIntToDecimalStringN(gStringVar2, VarGet(VAR_MISSION_PROGRESS) + 1, STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, mission->waves, STR_CONV_MODE_LEFT_ALIGN, 3);
}

// Makes the crazed Pokémon tougher: perfect IVs, its mission moves, and
// stat boosts shown at the start of battle like a totem Pokémon's aura.
static void MakeCrazedMon(const struct Mission *mission)
{
    struct Pokemon *mon = &gParties[B_TRAINER_OPPONENT_A][0];
    u32 i, perfectIv = MAX_PER_STAT_IVS;
    enum Stat stat;

    for (i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_IV + i, &perfectIv);

    if (mission->moves[0] != MOVE_NONE)
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
            SetMonMoveSlot(mon, mission->moves[i], i);
    }
    CalculateMonStats(mon);

    // Evasion is skipped because the battle's boost list has no room for it.
    for (stat = STAT_ATK; stat < STAT_EVASION; stat++)
    {
        if (mission->statBoosts[stat] > 0)
        {
            gQueuedStatBoosts[B_POSITION_OPPONENT_LEFT].stats |= (1 << stat);
            gQueuedStatBoosts[B_POSITION_OPPONENT_LEFT].statChanges[stat] = mission->statBoosts[stat];
        }
    }
}

static void ClearActiveMission(void)
{
    u32 slot;
    u16 missionId = VarGet(VAR_MISSION_ACTIVE);
    const struct Mission *mission = GetActiveMission();

    // Take back a mission key item so none are left over after the mission ends.
    if (mission != NULL && mission->dropItem != ITEM_NONE && CheckBagHasItem(mission->dropItem, 1))
        RemoveBagItem(mission->dropItem, 1);
    FlagSet(FLAG_MISSION_TARGET_HIDDEN);

    for (slot = 0; slot < MISSION_BOARD_SLOTS; slot++)
    {
        if (GetSlotMissionId(slot) == missionId)
            VarSet(VAR_MISSION_SLOT_1 + slot, MISSION_NONE);
    }
    VarSet(VAR_MISSION_ACTIVE, MISSION_NONE);
    VarSet(VAR_MISSION_STATE, MISSION_STATE_NONE);
    VarSet(VAR_MISSION_PROGRESS, 0);
}

// Fills empty board slots with random missions the player's rank allows.
// New missions come first; cleared ones only fill slots nothing new can.
void MissionBoard_RefillSlots(void)
{
    u32 slot, missionId;

    for (slot = 0; slot < MISSION_BOARD_SLOTS; slot++)
    {
        if (GetSlotMissionId(slot) != MISSION_NONE)
            continue;

        missionId = PickRandomMission(TRUE);
        if (missionId == MISSION_NONE)
            missionId = PickRandomMission(FALSE);
        VarSet(VAR_MISSION_SLOT_1 + slot, missionId);
    }
}

// {STR_VAR_1} = rank name, {STR_VAR_2} = points, {STR_VAR_3} = points for the next rank.
void MissionBoard_BufferRankStatus(void)
{
    u32 rank = GetCurrentRank();

    StringCopy(gStringVar1, sRanks[rank].name);
    ConvertIntToDecimalStringN(gStringVar2, VarGet(VAR_MISSION_POINTS), STR_CONV_MODE_LEFT_ALIGN, 5);
    if (rank + 1 < MISSION_RANK_COUNT)
    {
        u8 *end = StringCopy(gStringVar3, COMPOUND_STRING("/"));
        ConvertIntToDecimalStringN(end, sRanks[rank + 1].pointsNeeded, STR_CONV_MODE_LEFT_ALIGN, 5);
    }
    else
    {
        gStringVar3[0] = EOS;
    }
}

// Raises the rank by one if the player has enough points. On RANK_UP_DONE,
// {STR_VAR_1} = new rank name, VAR_0x8005 = gift item, VAR_0x8006 = quantity.
// If the gift won't fit in the Bag, the rank-up waits until it will.
u16 MissionBoard_TryRankUp(void)
{
    u32 nextRank = GetCurrentRank() + 1;

    if (nextRank >= MISSION_RANK_COUNT || VarGet(VAR_MISSION_POINTS) < sRanks[nextRank].pointsNeeded)
        return RANK_UP_NONE;

    StringCopy(gStringVar1, sRanks[nextRank].name);
    if (sRanks[nextRank].giftItem != ITEM_NONE
     && !CheckBagHasSpace(sRanks[nextRank].giftItem, sRanks[nextRank].giftQuantity))
        return RANK_UP_BAG_FULL;

    VarSet(VAR_MISSION_RANK, nextRank);
    gSpecialVar_0x8005 = sRanks[nextRank].giftItem;
    gSpecialVar_0x8006 = sRanks[nextRank].giftQuantity;
    return RANK_UP_DONE;
}

// VAR_0x8004 = slot. Returns TRUE and puts the title in {STR_VAR_1} if the slot has a mission.
u16 MissionBoard_BufferSlotTitle(void)
{
    const struct Mission *mission = GetSelectedSlotMission();

    if (mission == NULL)
        return FALSE;
    StringCopy(gStringVar1, mission->title);
    return TRUE;
}

void MissionBoard_BufferSlotDescription(void)
{
    BufferDescription(GetSelectedSlotMission());
}

void MissionBoard_BufferSlotReward(void)
{
    BufferReward(GetSelectedSlotMission());
}

void MissionBoard_AcceptSlot(void)
{
    if (GetSelectedSlotMission() == NULL)
        return;

    VarSet(VAR_MISSION_ACTIVE, GetSlotMissionId(gSpecialVar_0x8004));
    VarSet(VAR_MISSION_STATE, MISSION_STATE_IN_PROGRESS);
    VarSet(VAR_MISSION_PROGRESS, 0);
}

void MissionBoard_BufferActiveTitle(void)
{
    const struct Mission *mission = GetActiveMission();

    if (mission != NULL)
        StringCopy(gStringVar1, mission->title);
    else
        gStringVar1[0] = EOS;
}

void MissionBoard_BufferActiveDescription(void)
{
    BufferDescription(GetActiveMission());
}

void MissionBoard_BufferActiveReward(void)
{
    BufferReward(GetActiveMission());
}

// Checked before a Pokémon is taken, so a full bag can't cost the player a reward.
u16 MissionBoard_HasRewardSpace(void)
{
    const struct Mission *mission = GetActiveMission();

    if (mission == NULL)
        return FALSE;
    if (mission->rewardItem == ITEM_NONE)
        return TRUE;
    return CheckBagHasSpace(mission->rewardItem, mission->rewardItemQuantity);
}

// VAR_0x8004 = party slot. Also puts the requested species' name in {STR_VAR_1}.
u16 MissionBoard_CheckDelivery(void)
{
    const struct Mission *mission = GetActiveMission();
    struct Pokemon *mon;
    enum Species species;

    if (mission == NULL || gSpecialVar_0x8004 >= PARTY_SIZE)
        return DELIVERY_WRONG_SPECIES;

    StringCopy(gStringVar1, GetSpeciesName(mission->species));
    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);

    if (species == SPECIES_EGG)
        return DELIVERY_EGG;
    if (GET_BASE_SPECIES_ID(species) != GET_BASE_SPECIES_ID(mission->species))
        return DELIVERY_WRONG_SPECIES;
    if (GetMonData(mon, MON_DATA_HELD_ITEM) != ITEM_NONE)
        return DELIVERY_HOLDING_ITEM;
    if (CountPartyAliveNonEggMonsExcept(gSpecialVar_0x8004) == 0)
        return DELIVERY_LAST_HEALTHY_MON;
    return DELIVERY_OK;
}

// VAR_0x8004 = party slot, already approved by MissionBoard_CheckDelivery.
void MissionBoard_RemoveDeliveredMon(void)
{
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
        return;

    ZeroMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004]);
    CompactPartySlots();
    CalculatePlayerPartyCount();
}

// Pays money and points, then ends the mission. The item is given by the
// script: VAR_0x8005 = item, VAR_0x8006 = quantity. VAR_0x8007 = TRUE if a new mission unlocked.
void MissionBoard_CompleteActive(void)
{
    const struct Mission *mission = GetActiveMission();
    u32 missionId = VarGet(VAR_MISSION_ACTIVE);
    u32 earnedPoints, totalPoints;
    bool32 firstClear;

    gSpecialVar_0x8005 = ITEM_NONE;
    gSpecialVar_0x8006 = 0;
    gSpecialVar_0x8007 = FALSE;
    if (mission == NULL)
        return;

    // Work out the points before marking it cleared, so a first clear pays in full.
    firstClear = !IsMissionCleared(missionId);
    earnedPoints = GetPointsForMission(mission);
    AddMoney(&gSaveBlock1Ptr->money, mission->rewardMoney);
    totalPoints = VarGet(VAR_MISSION_POINTS) + earnedPoints;
    VarSet(VAR_MISSION_POINTS, min(totalPoints, USHRT_MAX));
    FlagSet(FLAG_MISSION_CLEARED_START + missionId - 1);
    gSpecialVar_0x8007 = firstClear && UnlocksNewMission(missionId); // Tells the script to announce it.

    ConvertIntToDecimalStringN(gStringVar1, mission->rewardMoney, STR_CONV_MODE_LEFT_ALIGN, MAX_MONEY_DIGITS);
    ConvertIntToDecimalStringN(gStringVar2, earnedPoints, STR_CONV_MODE_LEFT_ALIGN, 5);
    gSpecialVar_0x8005 = mission->rewardItem;
    gSpecialVar_0x8006 = mission->rewardItemQuantity;

    ClearActiveMission();
}

void MissionBoard_AbandonActive(void)
{
    ClearActiveMission();
}

u16 MissionBoard_GetActiveType(void)
{
    const struct Mission *mission = GetActiveMission();

    if (mission == NULL)
        return MISSION_TYPE_CATCH_DELIVER;
    return mission->type;
}

// Runs when a map with a mission site loads. Shows the site's Pokémon only if
// the active mission takes place on this map and isn't finished yet.
void MissionBoard_SetupSite(void)
{
    const struct Mission *mission = GetActiveMission();
    u16 currentMap = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;

    if (mission != NULL
     && UsesMissionSite(mission)
     && VarGet(VAR_MISSION_STATE) == MISSION_STATE_IN_PROGRESS
     && mission->map == currentMap)
    {
        VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_MON + mission->species);
        FlagClear(FLAG_MISSION_TARGET_HIDDEN);
    }
    else
    {
        FlagSet(FLAG_MISSION_TARGET_HIDDEN);
    }
}

// Returns FALSE if the drop item won't fit in the Bag. Otherwise
// {STR_VAR_1} = species, {STR_VAR_2} = drop item, VAR_0x8005 = species (for its cry).
u16 MissionBoard_PrepareSiteBattle(void)
{
    const struct Mission *mission = GetActiveMission();

    if (mission == NULL || !UsesMissionSite(mission))
        return FALSE;

    StringCopy(gStringVar1, GetSpeciesName(mission->species));
    gSpecialVar_0x8005 = mission->species;
    if (mission->dropItem != ITEM_NONE)
    {
        CopyItemName(mission->dropItem, gStringVar2);
        if (!CheckBagHasSpace(mission->dropItem, 1))
            return FALSE;
    }

    // gStringVar4 = what the player sees before the battle.
    switch (mission->type)
    {
    case MISSION_TYPE_CRAZED:
        StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("The crazed {STR_VAR_1} is going wild!\nIt's too wild to catch. Calm it down!"));
        break;
    case MISSION_TYPE_CALM_CATCH:
        StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("It's the {STR_VAR_1} you calmed down.\nIt looks gentle now."));
        break;
    case MISSION_TYPE_HORDE:
        BufferHordeWave(mission);
        StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("A horde of {STR_VAR_1} attacks!\nWave {STR_VAR_2} of {STR_VAR_3}!"));
        break;
    case MISSION_TYPE_LEGENDARY:
        StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("A powerful aura fills the air...\pIt's the legendary {STR_VAR_1}!"));
        break;
    default:
        StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("It's the {STR_VAR_1} from the mission!\nIt's holding the {STR_VAR_2}!"));
        break;
    }
    return TRUE;
}

void MissionBoard_StartSiteBattle(void)
{
    const struct Mission *mission = GetActiveMission();

    if (mission == NULL)
        return;

    if (mission->type == MISSION_TYPE_HORDE)
    {
        enum Species species2 = (mission->species2 != SPECIES_NONE) ? mission->species2 : mission->species;

        CreateScriptedDoubleWildMon(mission->species, mission->level, ITEM_NONE, species2, mission->level, ITEM_NONE);
        BattleSetup_StartScriptedDoubleWildBattle();
        return;
    }

    if (mission->type == MISSION_TYPE_LEGENDARY)
    {
        CreateScriptedWildMon(mission->species, GetSiteMonLevel(mission), ITEM_NONE);
        BattleSetup_StartLegendaryBattle();
        return;
    }

    CreateScriptedWildMon(mission->species, mission->level, ITEM_NONE);
    if (mission->type == MISSION_TYPE_CRAZED)
    {
        MakeCrazedMon(mission);
        FlagSet(FLAG_MISSION_NO_CATCHING); // Also cleared by the game if the player blacks out.
    }
    BattleSetup_StartScriptedWildBattle();
}

// Call right after a site battle. Returns a SITE_RESULT_ value.
// {STR_VAR_1} = species name. On SITE_RESULT_DROP, VAR_0x8005 = item for the script to give.
u16 MissionBoard_EndSiteBattle(void)
{
    const struct Mission *mission = GetActiveMission();
    bool32 beaten = (gBattleOutcome == B_OUTCOME_WON);
    bool32 caught = (gBattleOutcome == B_OUTCOME_CAUGHT);
    u16 result = SITE_RESULT_NOT_DONE;

    FlagClear(FLAG_MISSION_NO_CATCHING);
    gSpecialVar_0x8005 = ITEM_NONE;
    if (mission == NULL)
        return SITE_RESULT_NOT_DONE;

    StringCopy(gStringVar1, GetSpeciesName(mission->species));
    switch (mission->type)
    {
    case MISSION_TYPE_ITEM_DROP:
        if (beaten || caught)
        {
            gSpecialVar_0x8005 = mission->dropItem;
            result = SITE_RESULT_DROP;
        }
        break;
    case MISSION_TYPE_CRAZED:
        if (beaten)
            result = SITE_RESULT_CALMED;
        break;
    case MISSION_TYPE_CALM_CATCH:
    case MISSION_TYPE_LEGENDARY:
        if (caught)
            result = SITE_RESULT_CAUGHT;
        else if (beaten)
            return SITE_RESULT_FAINTED; // Mission continues; it's back next time the map loads.
        break;
    case MISSION_TYPE_HORDE:
        // Catching one of the pair also ends the wave, so it counts too.
        if (beaten || caught)
        {
            VarSet(VAR_MISSION_PROGRESS, VarGet(VAR_MISSION_PROGRESS) + 1);
            if (VarGet(VAR_MISSION_PROGRESS) < mission->waves)
            {
                BufferHordeWave(mission);
                return SITE_RESULT_WAVE_CLEARED; // Saved, so a blackout or running away keeps it.
            }
            result = SITE_RESULT_HORDE_DONE;
        }
        break;
    }

    if (result != SITE_RESULT_NOT_DONE)
    {
        VarSet(VAR_MISSION_STATE, MISSION_STATE_READY);
        FlagSet(FLAG_MISSION_TARGET_HIDDEN);
    }
    return result;
}

// Hand-in check for mission site missions. {STR_VAR_1} = drop item name, if any.
u16 MissionBoard_CheckItemHandIn(void)
{
    const struct Mission *mission = GetActiveMission();

    if (mission == NULL)
        return ITEM_HANDIN_NOT_DONE;

    if (mission->dropItem != ITEM_NONE)
        CopyItemName(mission->dropItem, gStringVar1);
    if (VarGet(VAR_MISSION_STATE) != MISSION_STATE_READY)
        return (mission->dropItem != ITEM_NONE) ? ITEM_HANDIN_NOT_YET : ITEM_HANDIN_NOT_DONE;
    if (mission->dropItem == ITEM_NONE)
        return ITEM_HANDIN_OK;
    if (!CheckBagHasItem(mission->dropItem, 1))
        return ITEM_HANDIN_MISSING;
    return ITEM_HANDIN_OK;
}

// Returns TRUE if the mission had an item to take back.
u16 MissionBoard_TakeDropItem(void)
{
    const struct Mission *mission = GetActiveMission();

    if (mission == NULL || mission->dropItem == ITEM_NONE)
        return FALSE;
    RemoveBagItem(mission->dropItem, 1);
    return TRUE;
}

// The Legendary Board opens with all 8 Gym Badges and Master Rank.
u16 MissionBoard_IsLegendaryBoardOpen(void)
{
    u32 badge;

    for (badge = FLAG_BADGE01_GET; badge <= FLAG_BADGE08_GET; badge++)
    {
        if (!FlagGet(badge))
            return FALSE;
    }
    return GetCurrentRank() == MISSION_RANK_MASTER;
}

static bool32 IsLegendaryBoardMissionAvailable(u32 missionId)
{
    return sMissions[missionId].board == MISSION_BOARD_LEGENDARY && IsMissionAvailable(missionId);
}

// Finds the next available Legendary Board mission with an ID of VAR_0x8004 or more.
// If found, returns TRUE, sets VAR_0x8004 to its ID and puts its title in {STR_VAR_1}.
u16 MissionBoard_FindNextLegendaryMission(void)
{
    u32 missionId;

    for (missionId = max(gSpecialVar_0x8004, MISSION_NONE + 1); missionId < MISSIONS_COUNT; missionId++)
    {
        if (IsLegendaryBoardMissionAvailable(missionId))
        {
            gSpecialVar_0x8004 = missionId;
            StringCopy(gStringVar1, sMissions[missionId].title);
            return TRUE;
        }
    }
    return FALSE;
}

u16 MissionBoard_CountLegendaryMissions(void)
{
    u32 missionId, count = 0;

    for (missionId = MISSION_NONE + 1; missionId < MISSIONS_COUNT; missionId++)
    {
        if (IsLegendaryBoardMissionAvailable(missionId))
            count++;
    }
    return count;
}

// These three use VAR_0x8004 = mission ID (the Legendary Board has no slots).
void MissionBoard_BufferIdDescription(void)
{
    BufferDescription(GetValidMission(gSpecialVar_0x8004));
}

void MissionBoard_BufferIdReward(void)
{
    BufferReward(GetValidMission(gSpecialVar_0x8004));
}

void MissionBoard_AcceptId(void)
{
    if (GetValidMission(gSpecialVar_0x8004) == NULL)
        return;

    VarSet(VAR_MISSION_ACTIVE, gSpecialVar_0x8004);
    VarSet(VAR_MISSION_STATE, MISSION_STATE_IN_PROGRESS);
    VarSet(VAR_MISSION_PROGRESS, 0);
}
