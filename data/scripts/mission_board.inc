MissionBoard_EventScript_Sign::
# 4 "data/scripts/mission_board.pory"
	lockall
# 5 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_TryRankUps
# 6 "data/scripts/mission_board.pory"
	compare VAR_MISSION_ACTIVE, MISSION_NONE
	goto_if_ne MissionBoard_EventScript_Sign_2
# 9 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_ChooseMission
MissionBoard_EventScript_Sign_1:
# 11 "data/scripts/mission_board.pory"
	releaseall
	end

MissionBoard_EventScript_Sign_2:
# 7 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_ActiveMenu
	goto MissionBoard_EventScript_Sign_1


MissionBoard_EventScript_LegendarySign::
# 17 "data/scripts/mission_board.pory"
	lockall
# 18 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_TryRankUps
# 19 "data/scripts/mission_board.pory"
	compare VAR_MISSION_ACTIVE, MISSION_NONE
	goto_if_ne MissionBoard_EventScript_LegendarySign_2
# 22 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_ChooseLegendaryMission
MissionBoard_EventScript_LegendarySign_1:
# 24 "data/scripts/mission_board.pory"
	releaseall
	end

MissionBoard_EventScript_LegendarySign_2:
# 20 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_ActiveMenu
	goto MissionBoard_EventScript_LegendarySign_1


MissionBoard_EventScript_ChooseLegendaryMission:
# 29 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_IsLegendaryBoardOpen
# 30 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_ChooseLegendaryMission_2
# 35 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_CountLegendaryMissions
# 36 "data/scripts/mission_board.pory"
	compare VAR_RESULT, 0
	goto_if_eq MissionBoard_EventScript_ChooseLegendaryMission_5
# 42 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_ChooseLegendaryMission_Text_2
# 43 "data/scripts/mission_board.pory"
	waitmessage
# 44 "data/scripts/mission_board.pory"
	setvar VAR_0x8004, 1
MissionBoard_EventScript_ChooseLegendaryMission_8:
# 46 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_FindNextLegendaryMission
# 47 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_ChooseLegendaryMission_16
# 50 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseLegendaryMission_Text_3, VAR_0x8004
# 51 "data/scripts/mission_board.pory"
	addvar VAR_0x8004, 1
	goto MissionBoard_EventScript_ChooseLegendaryMission_8

MissionBoard_EventScript_ChooseLegendaryMission_2:
# 31 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseLegendaryMission_Text_0, MSGBOX_DEFAULT
# 32 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_ChooseLegendaryMission_5:
# 37 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseLegendaryMission_Text_1, MSGBOX_DEFAULT
# 38 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_ChooseLegendaryMission_7:
# 53 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseLegendaryMission_Text_4, MISSION_NONE
# 54 "data/scripts/mission_board.pory"
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 55 "data/scripts/mission_board.pory"
	closemessage
# 57 "data/scripts/mission_board.pory"
	compare VAR_RESULT, MISSION_NONE
	goto_if_eq MissionBoard_EventScript_ChooseLegendaryMission_11
# 57 "data/scripts/mission_board.pory"
	compare VAR_RESULT, MISSIONS_COUNT
	goto_if_ge MissionBoard_EventScript_ChooseLegendaryMission_11
# 61 "data/scripts/mission_board.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 62 "data/scripts/mission_board.pory"
	special MissionBoard_BufferIdDescription
# 63 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 64 "data/scripts/mission_board.pory"
	special MissionBoard_BufferIdReward
# 65 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 66 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseLegendaryMission_Text_5, MSGBOX_YESNO
# 67 "data/scripts/mission_board.pory"
	compare VAR_RESULT, YES
	goto_if_eq MissionBoard_EventScript_ChooseLegendaryMission_19
MissionBoard_EventScript_ChooseLegendaryMission_18:
# 71 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_ChooseLegendaryMission_11:
	return

MissionBoard_EventScript_ChooseLegendaryMission_16:
	goto MissionBoard_EventScript_ChooseLegendaryMission_7

MissionBoard_EventScript_ChooseLegendaryMission_19:
# 68 "data/scripts/mission_board.pory"
	special MissionBoard_AcceptId
# 69 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseLegendaryMission_Text_6, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_ChooseLegendaryMission_18


MissionBoard_EventScript_ChooseMission:
# 76 "data/scripts/mission_board.pory"
	special MissionBoard_RefillSlots
# 77 "data/scripts/mission_board.pory"
	special MissionBoard_BufferRankStatus
# 78 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_ChooseMission_Text_0
# 79 "data/scripts/mission_board.pory"
	waitmessage
# 81 "data/scripts/mission_board.pory"
	setvar VAR_0x8004, 0
MissionBoard_EventScript_ChooseMission_2:
# 82 "data/scripts/mission_board.pory"
	compare VAR_0x8004, MISSION_BOARD_SLOTS
	goto_if_lt MissionBoard_EventScript_ChooseMission_3
# 89 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseLegendaryMission_Text_4, MISSION_BOARD_SLOTS
# 90 "data/scripts/mission_board.pory"
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 91 "data/scripts/mission_board.pory"
	closemessage
# 93 "data/scripts/mission_board.pory"
	compare VAR_RESULT, MISSION_BOARD_SLOTS
	goto_if_ge MissionBoard_EventScript_ChooseMission_6
# 97 "data/scripts/mission_board.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 98 "data/scripts/mission_board.pory"
	special MissionBoard_BufferSlotDescription
# 99 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 100 "data/scripts/mission_board.pory"
	special MissionBoard_BufferSlotReward
# 101 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 102 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseLegendaryMission_Text_5, MSGBOX_YESNO
# 103 "data/scripts/mission_board.pory"
	compare VAR_RESULT, YES
	goto_if_eq MissionBoard_EventScript_ChooseMission_12
MissionBoard_EventScript_ChooseMission_11:
# 107 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_ChooseMission_3:
# 83 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_BufferSlotTitle
# 84 "data/scripts/mission_board.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq MissionBoard_EventScript_ChooseMission_9
MissionBoard_EventScript_ChooseMission_8:
# 87 "data/scripts/mission_board.pory"
	addvar VAR_0x8004, 1
	goto MissionBoard_EventScript_ChooseMission_2

MissionBoard_EventScript_ChooseMission_6:
	return

MissionBoard_EventScript_ChooseMission_9:
# 85 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseLegendaryMission_Text_3, VAR_0x8004
	goto MissionBoard_EventScript_ChooseMission_8

MissionBoard_EventScript_ChooseMission_12:
# 104 "data/scripts/mission_board.pory"
	special MissionBoard_AcceptSlot
# 105 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseMission_Text_1, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_ChooseMission_11


MissionBoard_EventScript_ActiveMenu:
# 112 "data/scripts/mission_board.pory"
	special MissionBoard_BufferActiveTitle
# 113 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_ActiveMenu_Text_0
# 114 "data/scripts/mission_board.pory"
	waitmessage
# 115 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ActiveMenu_Text_1, 0
# 116 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ActiveMenu_Text_2, 1
# 117 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ActiveMenu_Text_3, 2
# 118 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseLegendaryMission_Text_4, 3
# 119 "data/scripts/mission_board.pory"
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 120 "data/scripts/mission_board.pory"
	closemessage
# 122 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 123 "data/scripts/mission_board.pory"
	case 0, MissionBoard_EventScript_ActiveMenu_3
# 125 "data/scripts/mission_board.pory"
	case 1, MissionBoard_EventScript_ActiveMenu_4
# 131 "data/scripts/mission_board.pory"
	case 2, MissionBoard_EventScript_ActiveMenu_5
MissionBoard_EventScript_ActiveMenu_1:
	return

MissionBoard_EventScript_ActiveMenu_3:
# 124 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_HandIn
	goto MissionBoard_EventScript_ActiveMenu_1

MissionBoard_EventScript_ActiveMenu_4:
# 126 "data/scripts/mission_board.pory"
	special MissionBoard_BufferActiveDescription
# 127 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 128 "data/scripts/mission_board.pory"
	special MissionBoard_BufferActiveReward
# 129 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 130 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_ActiveMenu_1

MissionBoard_EventScript_ActiveMenu_5:
# 132 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ActiveMenu_Text_4, MSGBOX_YESNO
# 133 "data/scripts/mission_board.pory"
	compare VAR_RESULT, YES
	goto_if_eq MissionBoard_EventScript_ActiveMenu_7
MissionBoard_EventScript_ActiveMenu_6:
# 137 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_ActiveMenu_1

MissionBoard_EventScript_ActiveMenu_7:
# 134 "data/scripts/mission_board.pory"
	special MissionBoard_AbandonActive
# 135 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ActiveMenu_Text_5, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_ActiveMenu_6


MissionBoard_EventScript_HandIn:
# 143 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_GetActiveType
# 144 "data/scripts/mission_board.pory"
	compare VAR_RESULT, MISSION_TYPE_CATCH_DELIVER
	goto_if_ne MissionBoard_EventScript_HandIn_2
# 149 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_HasRewardSpace
# 150 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_HandIn_5
# 156 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_1, MSGBOX_DEFAULT
# 157 "data/scripts/mission_board.pory"
	closemessage
# 158 "data/scripts/mission_board.pory"
	special ChoosePartyMon
# 159 "data/scripts/mission_board.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge MissionBoard_EventScript_HandIn_8
# 163 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_CheckDelivery
# 164 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 165 "data/scripts/mission_board.pory"
	case DELIVERY_WRONG_SPECIES, MissionBoard_EventScript_HandIn_12
# 167 "data/scripts/mission_board.pory"
	case DELIVERY_EGG, MissionBoard_EventScript_HandIn_13
# 169 "data/scripts/mission_board.pory"
	case DELIVERY_HOLDING_ITEM, MissionBoard_EventScript_HandIn_14
# 171 "data/scripts/mission_board.pory"
	case DELIVERY_LAST_HEALTHY_MON, MissionBoard_EventScript_HandIn_15
# 173 "data/scripts/mission_board.pory"
	case DELIVERY_OK, MissionBoard_EventScript_HandIn_16
MissionBoard_EventScript_HandIn_10:
# 180 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_HandIn_2:
# 145 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_HandInItem
	return

MissionBoard_EventScript_HandIn_5:
# 151 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_0, MSGBOX_DEFAULT
# 152 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_HandIn_8:
	return

MissionBoard_EventScript_HandIn_12:
# 166 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_2, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_13:
# 168 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_3, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_14:
# 170 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_4, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_15:
# 172 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_5, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_16:
# 174 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_6, MSGBOX_YESNO
# 175 "data/scripts/mission_board.pory"
	compare VAR_RESULT, YES
	goto_if_eq MissionBoard_EventScript_HandIn_17
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_17:
# 176 "data/scripts/mission_board.pory"
	special MissionBoard_RemoveDeliveredMon
# 177 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_Complete
	goto MissionBoard_EventScript_HandIn_10


MissionBoard_EventScript_HandInItem:
# 185 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_CheckItemHandIn
# 186 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 187 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_NOT_YET, MissionBoard_EventScript_HandInItem_3
# 189 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_MISSING, MissionBoard_EventScript_HandInItem_4
# 191 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_NOT_DONE, MissionBoard_EventScript_HandInItem_5
# 193 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_OK, MissionBoard_EventScript_HandInItem_6
MissionBoard_EventScript_HandInItem_1:
# 205 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_HandInItem_3:
# 188 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_0, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_4:
# 190 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_1, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_5:
# 192 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_2, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_6:
# 194 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_HasRewardSpace
# 195 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_HandInItem_7
# 198 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_TakeDropItem
# 199 "data/scripts/mission_board.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq MissionBoard_EventScript_HandInItem_11
MissionBoard_EventScript_HandInItem_10:
# 202 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_Complete
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_7:
# 196 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_0, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_11:
# 200 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_3, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_10


MissionBoard_EventScript_Site::
# 212 "data/scripts/mission_board.pory"
	lock
# 213 "data/scripts/mission_board.pory"
	faceplayer
# 214 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_PrepareSiteBattle
# 215 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_Site_2
# 220 "data/scripts/mission_board.pory"
	playmoncry VAR_0x8005, CRY_MODE_ENCOUNTER
# 221 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 222 "data/scripts/mission_board.pory"
	waitmoncry
# 223 "data/scripts/mission_board.pory"
	closemessage
# 224 "data/scripts/mission_board.pory"
	special MissionBoard_StartSiteBattle
# 225 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_EndSiteBattle
MissionBoard_EventScript_Site_5:
# 227 "data/scripts/mission_board.pory"
	compare VAR_RESULT, SITE_RESULT_WAVE_CLEARED
	goto_if_eq MissionBoard_EventScript_Site_6
# 233 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 234 "data/scripts/mission_board.pory"
	case SITE_RESULT_DROP, MissionBoard_EventScript_Site_10
# 239 "data/scripts/mission_board.pory"
	case SITE_RESULT_CALMED, MissionBoard_EventScript_Site_11
# 242 "data/scripts/mission_board.pory"
	case SITE_RESULT_CAUGHT, MissionBoard_EventScript_Site_12
# 245 "data/scripts/mission_board.pory"
	case SITE_RESULT_HORDE_DONE, MissionBoard_EventScript_Site_13
# 248 "data/scripts/mission_board.pory"
	case SITE_RESULT_FAINTED, MissionBoard_EventScript_Site_14
# 252 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_8, MSGBOX_DEFAULT
MissionBoard_EventScript_Site_8:
# 254 "data/scripts/mission_board.pory"
	release
	end

MissionBoard_EventScript_Site_2:
# 216 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_0, MSGBOX_DEFAULT
# 217 "data/scripts/mission_board.pory"
	release
	end

MissionBoard_EventScript_Site_6:
# 228 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_1, MSGBOX_DEFAULT
# 229 "data/scripts/mission_board.pory"
	closemessage
# 230 "data/scripts/mission_board.pory"
	special MissionBoard_StartSiteBattle
# 231 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_EndSiteBattle
	goto MissionBoard_EventScript_Site_5

MissionBoard_EventScript_Site_10:
# 235 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 236 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_2, MSGBOX_DEFAULT
# 237 "data/scripts/mission_board.pory"
	giveitem VAR_0x8005, 1
# 238 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_3, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_8

MissionBoard_EventScript_Site_11:
# 240 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 241 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_4, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_8

MissionBoard_EventScript_Site_12:
# 243 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 244 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_5, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_8

MissionBoard_EventScript_Site_13:
# 246 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 247 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_6, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_8

MissionBoard_EventScript_Site_14:
# 249 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 250 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_7, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_8


MissionBoard_EventScript_Complete:
# 259 "data/scripts/mission_board.pory"
	special MissionBoard_CompleteActive
# 260 "data/scripts/mission_board.pory"
	playfanfare MUS_LEVEL_UP
# 261 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_Complete_Text_0
# 262 "data/scripts/mission_board.pory"
	waitmessage
# 263 "data/scripts/mission_board.pory"
	waitfanfare
# 264 "data/scripts/mission_board.pory"
	waitbuttonpress
# 265 "data/scripts/mission_board.pory"
	compare VAR_0x8007, TRUE
	goto_if_eq MissionBoard_EventScript_Complete_2
MissionBoard_EventScript_Complete_1:
# 268 "data/scripts/mission_board.pory"
	compare VAR_0x8005, ITEM_NONE
	goto_if_ne MissionBoard_EventScript_Complete_5
MissionBoard_EventScript_Complete_4:
# 271 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_TryRankUps
	return

MissionBoard_EventScript_Complete_2:
# 266 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Complete_Text_1, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Complete_1

MissionBoard_EventScript_Complete_5:
# 269 "data/scripts/mission_board.pory"
	giveitem VAR_0x8005, VAR_0x8006
	goto MissionBoard_EventScript_Complete_4


MissionBoard_EventScript_TryRankUps:
MissionBoard_EventScript_TryRankUps_2:
# 278 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_TryRankUp
# 279 "data/scripts/mission_board.pory"
	compare VAR_RESULT, RANK_UP_NONE
	goto_if_eq MissionBoard_EventScript_TryRankUps_5
# 282 "data/scripts/mission_board.pory"
	compare VAR_RESULT, RANK_UP_BAG_FULL
	goto_if_eq MissionBoard_EventScript_TryRankUps_8
# 287 "data/scripts/mission_board.pory"
	playfanfare MUS_OBTAIN_BADGE
# 288 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_TryRankUps_Text_1
# 289 "data/scripts/mission_board.pory"
	waitmessage
# 290 "data/scripts/mission_board.pory"
	waitfanfare
# 291 "data/scripts/mission_board.pory"
	waitbuttonpress
# 292 "data/scripts/mission_board.pory"
	compare VAR_0x8005, ITEM_NONE
	goto_if_ne MissionBoard_EventScript_TryRankUps_11
MissionBoard_EventScript_TryRankUps_10:
# 295 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_TryRankUps_2

MissionBoard_EventScript_TryRankUps_1:
	return

MissionBoard_EventScript_TryRankUps_5:
	goto MissionBoard_EventScript_TryRankUps_1

MissionBoard_EventScript_TryRankUps_8:
# 283 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_TryRankUps_Text_0, MSGBOX_DEFAULT
# 284 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_TryRankUps_1

MissionBoard_EventScript_TryRankUps_11:
# 293 "data/scripts/mission_board.pory"
	giveitem VAR_0x8005, VAR_0x8006
	goto MissionBoard_EventScript_TryRankUps_10


MissionBoard_EventScript_ChooseLegendaryMission_Text_0:
# 31 "data/scripts/mission_board.pory"
	.string "LEGENDARY BOARD\pOnly trainers with all 8 Gym Badges\nand Master Rank may take these.$"

MissionBoard_EventScript_ChooseLegendaryMission_Text_1:
# 37 "data/scripts/mission_board.pory"
	.string "LEGENDARY BOARD\pThere are no legendary missions\nright now.$"

MissionBoard_EventScript_ChooseLegendaryMission_Text_2:
# 42 "data/scripts/mission_board.pory"
	.string "LEGENDARY BOARD\nChoose a mission.$"

MissionBoard_EventScript_ChooseLegendaryMission_Text_3:
# 50 "data/scripts/mission_board.pory"
	.string "{STR_VAR_1}$"

MissionBoard_EventScript_ChooseLegendaryMission_Text_4:
# 53 "data/scripts/mission_board.pory"
	.string "Exit$"

MissionBoard_EventScript_ChooseLegendaryMission_Text_5:
# 66 "data/scripts/mission_board.pory"
	.string "Accept this mission?$"

MissionBoard_EventScript_ChooseLegendaryMission_Text_6:
# 69 "data/scripts/mission_board.pory"
	.string "Mission accepted!\nReturn to either board when it's done.$"

MissionBoard_EventScript_ChooseMission_Text_0:
# 78 "data/scripts/mission_board.pory"
	.string "MISSION BOARD · {STR_VAR_1} Rank\nPoints: {STR_VAR_2}{STR_VAR_3}$"

MissionBoard_EventScript_ChooseMission_Text_1:
# 105 "data/scripts/mission_board.pory"
	.string "Mission accepted!\nReturn here when it's done.$"

MissionBoard_EventScript_ActiveMenu_Text_0:
# 113 "data/scripts/mission_board.pory"
	.string "Current mission:\n{STR_VAR_1}$"

MissionBoard_EventScript_ActiveMenu_Text_1:
# 115 "data/scripts/mission_board.pory"
	.string "Hand In$"

MissionBoard_EventScript_ActiveMenu_Text_2:
# 116 "data/scripts/mission_board.pory"
	.string "Details$"

MissionBoard_EventScript_ActiveMenu_Text_3:
# 117 "data/scripts/mission_board.pory"
	.string "Abandon$"

MissionBoard_EventScript_ActiveMenu_Text_4:
# 132 "data/scripts/mission_board.pory"
	.string "Abandon this mission?$"

MissionBoard_EventScript_ActiveMenu_Text_5:
# 135 "data/scripts/mission_board.pory"
	.string "Mission abandoned.$"

MissionBoard_EventScript_HandIn_Text_0:
# 151 "data/scripts/mission_board.pory"
	.string "Your Bag has no room for the reward.\nMake some space and come back.$"

MissionBoard_EventScript_HandIn_Text_1:
# 156 "data/scripts/mission_board.pory"
	.string "Which Pokémon will you hand in?$"

MissionBoard_EventScript_HandIn_Text_2:
# 166 "data/scripts/mission_board.pory"
	.string "This mission needs a {STR_VAR_1}.$"

MissionBoard_EventScript_HandIn_Text_3:
# 168 "data/scripts/mission_board.pory"
	.string "An Egg can't be handed in.$"

MissionBoard_EventScript_HandIn_Text_4:
# 170 "data/scripts/mission_board.pory"
	.string "Take its held item first.\nThat item is yours to keep.$"

MissionBoard_EventScript_HandIn_Text_5:
# 172 "data/scripts/mission_board.pory"
	.string "You can't hand over your\nlast healthy Pokémon!$"

MissionBoard_EventScript_HandIn_Text_6:
# 174 "data/scripts/mission_board.pory"
	.string "Hand over this {STR_VAR_1}?\nYou won't get it back.$"

MissionBoard_EventScript_HandInItem_Text_0:
# 188 "data/scripts/mission_board.pory"
	.string "You haven't recovered the\n{STR_VAR_1} yet.$"

MissionBoard_EventScript_HandInItem_Text_1:
# 190 "data/scripts/mission_board.pory"
	.string "You don't have the {STR_VAR_1}\nin your Bag.$"

MissionBoard_EventScript_HandInItem_Text_2:
# 192 "data/scripts/mission_board.pory"
	.string "You haven't finished this\nmission yet.$"

MissionBoard_EventScript_HandInItem_Text_3:
# 200 "data/scripts/mission_board.pory"
	.string "You handed over the {STR_VAR_1}.$"

MissionBoard_EventScript_Site_Text_0:
# 216 "data/scripts/mission_board.pory"
	.string "It's holding the {STR_VAR_2}!\pYour Key Items pocket is full.\nMake room before you fight it.$"

MissionBoard_EventScript_Site_Text_1:
# 228 "data/scripts/mission_board.pory"
	.string "Wave cleared! Here comes the next one!\nWave {STR_VAR_2} of {STR_VAR_3}!$"

MissionBoard_EventScript_Site_Text_2:
# 236 "data/scripts/mission_board.pory"
	.string "It dropped something!$"

MissionBoard_EventScript_Site_Text_3:
# 238 "data/scripts/mission_board.pory"
	.string "Take it back to the mission board.$"

MissionBoard_EventScript_Site_Text_4:
# 241 "data/scripts/mission_board.pory"
	.string "The {STR_VAR_1} calmed down\nand wandered off.\pReport back to the mission board.$"

MissionBoard_EventScript_Site_Text_5:
# 244 "data/scripts/mission_board.pory"
	.string "Report your catch to the\nmission board.$"

MissionBoard_EventScript_Site_Text_6:
# 247 "data/scripts/mission_board.pory"
	.string "The horde scattered!\nReport back to the mission board.$"

MissionBoard_EventScript_Site_Text_7:
# 250 "data/scripts/mission_board.pory"
	.string "The {STR_VAR_1} fainted, then fled\nto recover.\pIt should be back soon.\nLeave the area and return.$"

MissionBoard_EventScript_Site_Text_8:
# 252 "data/scripts/mission_board.pory"
	.string "The {STR_VAR_1} is still here.\nTry again!$"

MissionBoard_EventScript_Complete_Text_0:
# 261 "data/scripts/mission_board.pory"
	.string "Mission complete!\nYou earned ¥{STR_VAR_1} and {STR_VAR_2} points.$"

MissionBoard_EventScript_Complete_Text_1:
# 266 "data/scripts/mission_board.pory"
	.string "A new mission has appeared\non the board!$"

MissionBoard_EventScript_TryRankUps_Text_0:
# 283 "data/scripts/mission_board.pory"
	.string "You've earned {STR_VAR_1} Rank!\pYour Bag has no room for the gift.\nMake space and check the board again.$"

MissionBoard_EventScript_TryRankUps_Text_1:
# 288 "data/scripts/mission_board.pory"
	.string "Rank up!\nYou're now {STR_VAR_1} Rank!$"
