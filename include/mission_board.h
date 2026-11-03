#ifndef GUARD_MISSION_BOARD_H
#define GUARD_MISSION_BOARD_H

void MissionBoard_RefillSlots(void);
void MissionBoard_BufferRankStatus(void);
u16 MissionBoard_TryRankUp(void);
u16 MissionBoard_BufferSlotTitle(void);
void MissionBoard_BufferSlotDescription(void);
void MissionBoard_BufferSlotReward(void);
void MissionBoard_AcceptSlot(void);
void MissionBoard_BufferActiveTitle(void);
void MissionBoard_BufferActiveDescription(void);
void MissionBoard_BufferActiveReward(void);
u16 MissionBoard_HasRewardSpace(void);
u16 MissionBoard_CheckDelivery(void);
void MissionBoard_RemoveDeliveredMon(void);
void MissionBoard_CompleteActive(void);
void MissionBoard_AbandonActive(void);
u16 MissionBoard_GetActiveType(void);
void MissionBoard_SetupSite(void);
u16 MissionBoard_PrepareSiteBattle(void);
void MissionBoard_StartSiteBattle(void);
u16 MissionBoard_EndSiteBattle(void);
u16 MissionBoard_CheckItemHandIn(void);
u16 MissionBoard_TakeDropItem(void);
u16 MissionBoard_IsLegendaryBoardOpen(void);
u16 MissionBoard_FindNextLegendaryMission(void);
u16 MissionBoard_CountLegendaryMissions(void);
void MissionBoard_BufferIdDescription(void);
void MissionBoard_BufferIdReward(void);
void MissionBoard_AcceptId(void);

#endif // GUARD_MISSION_BOARD_H
