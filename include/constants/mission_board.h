#ifndef GUARD_CONSTANTS_MISSION_BOARD_H
#define GUARD_CONSTANTS_MISSION_BOARD_H

// Mission IDs. 0 means "no mission". To add a mission, add an ID here, raise
// MISSIONS_COUNT, then add its row to sMissions in src/mission_board.c.
#define MISSION_NONE              0
#define MISSION_DELIVER_NINCADA   1
#define MISSION_DELIVER_HERACROSS 2
#define MISSION_DELIVER_HOOTHOOT  3
#define MISSION_DELIVER_PIKACHU   4
#define MISSION_DELIVER_NINJASK   5
#define MISSION_RECOVER_SATCHEL   6
#define MISSION_CRAZED_PIKACHU    7
#define MISSION_CALM_PIKACHU      8
#define MISSION_HORDE_BUGS        9
// Legendary Board placeholders for testing. Replace these with your real legendary missions.
// They're only offered while MISSION_ENABLE_TEST_LEGENDARIES is TRUE.
#define MISSION_TEST_LEGEND_DIRECT  10
#define MISSION_TEST_LEGEND_STEP_1  11
#define MISSION_TEST_LEGEND_STEP_2  12
#define MISSION_TEST_LEGEND_CHAINED 13
#define MISSIONS_COUNT            14

// Which board a mission appears on.
#define MISSION_BOARD_MAIN         0 // Random missions, 3 at a time.
#define MISSION_BOARD_LEGENDARY    1 // Lists every available mission. Needs all 8 badges and Master Rank.

// Legendary levels to use: 50 for lesser legendaries on the main board, 75-90 on
// the Legendary Board, and 100 for legendaries that need other missions first.
// While this is TRUE, every legendary battle is level 5-7 instead, for testing.
// Set it to FALSE before releasing the game.
#define MISSION_LEGENDARY_TEST_LEVELS FALSE

// Set to TRUE to put the "Test:" placeholder missions back on the Legendary Board.
#define MISSION_ENABLE_TEST_LEGENDARIES FALSE

// Most missions a mission can require before it's offered.
#define MAX_REQUIRED_MISSIONS      4

// One FLAG_MISSION_CLEARED flag exists for each mission, so IDs stop at 64.
#define MAX_MISSIONS              64

#define MISSION_BOARD_SLOTS       3

#define MISSION_TYPE_CATCH_DELIVER 0
#define MISSION_TYPE_ITEM_DROP     1
#define MISSION_TYPE_CRAZED        2 // Boosted boss at a mission site; can't be caught.
#define MISSION_TYPE_CALM_CATCH    3 // Unlocked by a crazed mission; catch it at the site.
#define MISSION_TYPE_HORDE         4 // Waves of double battles at a mission site, with no healing between.
#define MISSION_TYPE_LEGENDARY     5 // Catch a legendary at a mission site. Fainting or running lets you retry.

#define MISSION_STATE_NONE         0
#define MISSION_STATE_IN_PROGRESS  1
#define MISSION_STATE_READY        2 // Objective done; hand in at the board.

// Results from MissionBoard_CheckItemHandIn
#define ITEM_HANDIN_OK             0
#define ITEM_HANDIN_NOT_YET        1
#define ITEM_HANDIN_MISSING        2
#define ITEM_HANDIN_NOT_DONE       3 // Site missions with no item to recover.

// Results from MissionBoard_EndSiteBattle
#define SITE_RESULT_NOT_DONE       0 // Ran away, or the Pokémon fled.
#define SITE_RESULT_DROP           1 // Item-drop target beaten or caught.
#define SITE_RESULT_CALMED         2 // Crazed Pokémon beaten.
#define SITE_RESULT_CAUGHT         3 // Calm Pokémon caught.
#define SITE_RESULT_FAINTED        4 // Calm Pokémon fainted; it comes back later.
#define SITE_RESULT_WAVE_CLEARED   5 // Horde wave won; more waves left.
#define SITE_RESULT_HORDE_DONE     6 // Last horde wave won.

// Ranks. Points needed and rank-up gifts are in sRanks in src/mission_board.c.
#define MISSION_RANK_ROOKIE        0
#define MISSION_RANK_BRONZE        1
#define MISSION_RANK_SILVER        2
#define MISSION_RANK_GOLD          3
#define MISSION_RANK_MASTER        4
#define MISSION_RANK_COUNT         5

// Results from MissionBoard_TryRankUp
#define RANK_UP_NONE               0
#define RANK_UP_DONE               1
#define RANK_UP_BAG_FULL           2

// Results from MissionBoard_CheckDelivery
#define DELIVERY_OK                0
#define DELIVERY_WRONG_SPECIES     1
#define DELIVERY_EGG               2
#define DELIVERY_HOLDING_ITEM      3
#define DELIVERY_LAST_HEALTHY_MON  4

#endif // GUARD_CONSTANTS_MISSION_BOARD_H
