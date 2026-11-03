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


MissionBoard_EventScript_ChooseMission:
# 16 "data/scripts/mission_board.pory"
	special MissionBoard_RefillSlots
# 17 "data/scripts/mission_board.pory"
	special MissionBoard_BufferRankStatus
# 18 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_ChooseMission_Text_0
# 19 "data/scripts/mission_board.pory"
	waitmessage
# 21 "data/scripts/mission_board.pory"
	setvar VAR_0x8004, 0
MissionBoard_EventScript_ChooseMission_2:
# 22 "data/scripts/mission_board.pory"
	compare VAR_0x8004, MISSION_BOARD_SLOTS
	goto_if_lt MissionBoard_EventScript_ChooseMission_3
# 29 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseMission_Text_2, MISSION_BOARD_SLOTS
# 30 "data/scripts/mission_board.pory"
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 31 "data/scripts/mission_board.pory"
	closemessage
# 33 "data/scripts/mission_board.pory"
	compare VAR_RESULT, MISSION_BOARD_SLOTS
	goto_if_ge MissionBoard_EventScript_ChooseMission_6
# 37 "data/scripts/mission_board.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 38 "data/scripts/mission_board.pory"
	special MissionBoard_BufferSlotDescription
# 39 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 40 "data/scripts/mission_board.pory"
	special MissionBoard_BufferSlotReward
# 41 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 42 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseMission_Text_3, MSGBOX_YESNO
# 43 "data/scripts/mission_board.pory"
	compare VAR_RESULT, YES
	goto_if_eq MissionBoard_EventScript_ChooseMission_12
MissionBoard_EventScript_ChooseMission_11:
# 47 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_ChooseMission_3:
# 23 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_BufferSlotTitle
# 24 "data/scripts/mission_board.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq MissionBoard_EventScript_ChooseMission_9
MissionBoard_EventScript_ChooseMission_8:
# 27 "data/scripts/mission_board.pory"
	addvar VAR_0x8004, 1
	goto MissionBoard_EventScript_ChooseMission_2

MissionBoard_EventScript_ChooseMission_6:
	return

MissionBoard_EventScript_ChooseMission_9:
# 25 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseMission_Text_1, VAR_0x8004
	goto MissionBoard_EventScript_ChooseMission_8

MissionBoard_EventScript_ChooseMission_12:
# 44 "data/scripts/mission_board.pory"
	special MissionBoard_AcceptSlot
# 45 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ChooseMission_Text_4, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_ChooseMission_11


MissionBoard_EventScript_ActiveMenu:
# 52 "data/scripts/mission_board.pory"
	special MissionBoard_BufferActiveTitle
# 53 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_ActiveMenu_Text_0
# 54 "data/scripts/mission_board.pory"
	waitmessage
# 55 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ActiveMenu_Text_1, 0
# 56 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ActiveMenu_Text_2, 1
# 57 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ActiveMenu_Text_3, 2
# 58 "data/scripts/mission_board.pory"
	dynmultipush MissionBoard_EventScript_ChooseMission_Text_2, 3
# 59 "data/scripts/mission_board.pory"
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 60 "data/scripts/mission_board.pory"
	closemessage
# 62 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 63 "data/scripts/mission_board.pory"
	case 0, MissionBoard_EventScript_ActiveMenu_3
# 65 "data/scripts/mission_board.pory"
	case 1, MissionBoard_EventScript_ActiveMenu_4
# 71 "data/scripts/mission_board.pory"
	case 2, MissionBoard_EventScript_ActiveMenu_5
MissionBoard_EventScript_ActiveMenu_1:
	return

MissionBoard_EventScript_ActiveMenu_3:
# 64 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_HandIn
	goto MissionBoard_EventScript_ActiveMenu_1

MissionBoard_EventScript_ActiveMenu_4:
# 66 "data/scripts/mission_board.pory"
	special MissionBoard_BufferActiveDescription
# 67 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 68 "data/scripts/mission_board.pory"
	special MissionBoard_BufferActiveReward
# 69 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 70 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_ActiveMenu_1

MissionBoard_EventScript_ActiveMenu_5:
# 72 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ActiveMenu_Text_4, MSGBOX_YESNO
# 73 "data/scripts/mission_board.pory"
	compare VAR_RESULT, YES
	goto_if_eq MissionBoard_EventScript_ActiveMenu_7
MissionBoard_EventScript_ActiveMenu_6:
# 77 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_ActiveMenu_1

MissionBoard_EventScript_ActiveMenu_7:
# 74 "data/scripts/mission_board.pory"
	special MissionBoard_AbandonActive
# 75 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_ActiveMenu_Text_5, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_ActiveMenu_6


MissionBoard_EventScript_HandIn:
# 83 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_GetActiveType
# 84 "data/scripts/mission_board.pory"
	compare VAR_RESULT, MISSION_TYPE_CATCH_DELIVER
	goto_if_ne MissionBoard_EventScript_HandIn_2
# 89 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_HasRewardSpace
# 90 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_HandIn_5
# 96 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_1, MSGBOX_DEFAULT
# 97 "data/scripts/mission_board.pory"
	closemessage
# 98 "data/scripts/mission_board.pory"
	special ChoosePartyMon
# 99 "data/scripts/mission_board.pory"
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge MissionBoard_EventScript_HandIn_8
# 103 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_CheckDelivery
# 104 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 105 "data/scripts/mission_board.pory"
	case DELIVERY_WRONG_SPECIES, MissionBoard_EventScript_HandIn_12
# 107 "data/scripts/mission_board.pory"
	case DELIVERY_EGG, MissionBoard_EventScript_HandIn_13
# 109 "data/scripts/mission_board.pory"
	case DELIVERY_HOLDING_ITEM, MissionBoard_EventScript_HandIn_14
# 111 "data/scripts/mission_board.pory"
	case DELIVERY_LAST_HEALTHY_MON, MissionBoard_EventScript_HandIn_15
# 113 "data/scripts/mission_board.pory"
	case DELIVERY_OK, MissionBoard_EventScript_HandIn_16
MissionBoard_EventScript_HandIn_10:
# 120 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_HandIn_2:
# 85 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_HandInItem
	return

MissionBoard_EventScript_HandIn_5:
# 91 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_0, MSGBOX_DEFAULT
# 92 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_HandIn_8:
	return

MissionBoard_EventScript_HandIn_12:
# 106 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_2, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_13:
# 108 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_3, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_14:
# 110 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_4, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_15:
# 112 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_5, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_16:
# 114 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_6, MSGBOX_YESNO
# 115 "data/scripts/mission_board.pory"
	compare VAR_RESULT, YES
	goto_if_eq MissionBoard_EventScript_HandIn_17
	goto MissionBoard_EventScript_HandIn_10

MissionBoard_EventScript_HandIn_17:
# 116 "data/scripts/mission_board.pory"
	special MissionBoard_RemoveDeliveredMon
# 117 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_Complete
	goto MissionBoard_EventScript_HandIn_10


MissionBoard_EventScript_HandInItem:
# 125 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_CheckItemHandIn
# 126 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 127 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_NOT_YET, MissionBoard_EventScript_HandInItem_3
# 129 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_MISSING, MissionBoard_EventScript_HandInItem_4
# 131 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_NOT_DONE, MissionBoard_EventScript_HandInItem_5
# 133 "data/scripts/mission_board.pory"
	case ITEM_HANDIN_OK, MissionBoard_EventScript_HandInItem_6
MissionBoard_EventScript_HandInItem_1:
# 145 "data/scripts/mission_board.pory"
	closemessage
	return

MissionBoard_EventScript_HandInItem_3:
# 128 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_0, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_4:
# 130 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_1, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_5:
# 132 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_2, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_6:
# 134 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_HasRewardSpace
# 135 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_HandInItem_7
# 138 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_TakeDropItem
# 139 "data/scripts/mission_board.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq MissionBoard_EventScript_HandInItem_11
MissionBoard_EventScript_HandInItem_10:
# 142 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_Complete
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_7:
# 136 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandIn_Text_0, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_1

MissionBoard_EventScript_HandInItem_11:
# 140 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_HandInItem_Text_3, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_HandInItem_10


MissionBoard_EventScript_Site::
# 152 "data/scripts/mission_board.pory"
	lock
# 153 "data/scripts/mission_board.pory"
	faceplayer
# 154 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_PrepareSiteBattle
# 155 "data/scripts/mission_board.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq MissionBoard_EventScript_Site_2
# 160 "data/scripts/mission_board.pory"
	playmoncry VAR_0x8005, CRY_MODE_ENCOUNTER
# 161 "data/scripts/mission_board.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 162 "data/scripts/mission_board.pory"
	waitmoncry
# 163 "data/scripts/mission_board.pory"
	closemessage
# 164 "data/scripts/mission_board.pory"
	special MissionBoard_StartSiteBattle
# 165 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_EndSiteBattle
# 166 "data/scripts/mission_board.pory"
	switch VAR_RESULT
# 167 "data/scripts/mission_board.pory"
	case SITE_RESULT_DROP, MissionBoard_EventScript_Site_6
# 172 "data/scripts/mission_board.pory"
	case SITE_RESULT_CALMED, MissionBoard_EventScript_Site_7
# 175 "data/scripts/mission_board.pory"
	case SITE_RESULT_CAUGHT, MissionBoard_EventScript_Site_8
# 178 "data/scripts/mission_board.pory"
	case SITE_RESULT_FAINTED, MissionBoard_EventScript_Site_9
# 182 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_6, MSGBOX_DEFAULT
MissionBoard_EventScript_Site_4:
# 184 "data/scripts/mission_board.pory"
	release
	end

MissionBoard_EventScript_Site_2:
# 156 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_0, MSGBOX_DEFAULT
# 157 "data/scripts/mission_board.pory"
	release
	end

MissionBoard_EventScript_Site_6:
# 168 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 169 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_1, MSGBOX_DEFAULT
# 170 "data/scripts/mission_board.pory"
	giveitem VAR_0x8005, 1
# 171 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_2, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_4

MissionBoard_EventScript_Site_7:
# 173 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 174 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_3, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_4

MissionBoard_EventScript_Site_8:
# 176 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 177 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_4, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_4

MissionBoard_EventScript_Site_9:
# 179 "data/scripts/mission_board.pory"
	removeobject VAR_LAST_TALKED
# 180 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Site_Text_5, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Site_4


MissionBoard_EventScript_Complete:
# 189 "data/scripts/mission_board.pory"
	special MissionBoard_CompleteActive
# 190 "data/scripts/mission_board.pory"
	playfanfare MUS_LEVEL_UP
# 191 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_Complete_Text_0
# 192 "data/scripts/mission_board.pory"
	waitmessage
# 193 "data/scripts/mission_board.pory"
	waitfanfare
# 194 "data/scripts/mission_board.pory"
	waitbuttonpress
# 195 "data/scripts/mission_board.pory"
	compare VAR_0x8007, TRUE
	goto_if_eq MissionBoard_EventScript_Complete_2
MissionBoard_EventScript_Complete_1:
# 198 "data/scripts/mission_board.pory"
	compare VAR_0x8005, ITEM_NONE
	goto_if_ne MissionBoard_EventScript_Complete_5
MissionBoard_EventScript_Complete_4:
# 201 "data/scripts/mission_board.pory"
	call MissionBoard_EventScript_TryRankUps
	return

MissionBoard_EventScript_Complete_2:
# 196 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_Complete_Text_1, MSGBOX_DEFAULT
	goto MissionBoard_EventScript_Complete_1

MissionBoard_EventScript_Complete_5:
# 199 "data/scripts/mission_board.pory"
	giveitem VAR_0x8005, VAR_0x8006
	goto MissionBoard_EventScript_Complete_4


MissionBoard_EventScript_TryRankUps:
MissionBoard_EventScript_TryRankUps_2:
# 208 "data/scripts/mission_board.pory"
	specialvar VAR_RESULT, MissionBoard_TryRankUp
# 209 "data/scripts/mission_board.pory"
	compare VAR_RESULT, RANK_UP_NONE
	goto_if_eq MissionBoard_EventScript_TryRankUps_5
# 212 "data/scripts/mission_board.pory"
	compare VAR_RESULT, RANK_UP_BAG_FULL
	goto_if_eq MissionBoard_EventScript_TryRankUps_8
# 217 "data/scripts/mission_board.pory"
	playfanfare MUS_OBTAIN_BADGE
# 218 "data/scripts/mission_board.pory"
	message MissionBoard_EventScript_TryRankUps_Text_1
# 219 "data/scripts/mission_board.pory"
	waitmessage
# 220 "data/scripts/mission_board.pory"
	waitfanfare
# 221 "data/scripts/mission_board.pory"
	waitbuttonpress
# 222 "data/scripts/mission_board.pory"
	compare VAR_0x8005, ITEM_NONE
	goto_if_ne MissionBoard_EventScript_TryRankUps_11
MissionBoard_EventScript_TryRankUps_10:
# 225 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_TryRankUps_2

MissionBoard_EventScript_TryRankUps_1:
	return

MissionBoard_EventScript_TryRankUps_5:
	goto MissionBoard_EventScript_TryRankUps_1

MissionBoard_EventScript_TryRankUps_8:
# 213 "data/scripts/mission_board.pory"
	msgbox MissionBoard_EventScript_TryRankUps_Text_0, MSGBOX_DEFAULT
# 214 "data/scripts/mission_board.pory"
	closemessage
	goto MissionBoard_EventScript_TryRankUps_1

MissionBoard_EventScript_TryRankUps_11:
# 223 "data/scripts/mission_board.pory"
	giveitem VAR_0x8005, VAR_0x8006
	goto MissionBoard_EventScript_TryRankUps_10


MissionBoard_EventScript_ChooseMission_Text_0:
# 18 "data/scripts/mission_board.pory"
	.string "MISSION BOARD · {STR_VAR_1} Rank\nPoints: {STR_VAR_2}{STR_VAR_3}$"

MissionBoard_EventScript_ChooseMission_Text_1:
# 25 "data/scripts/mission_board.pory"
	.string "{STR_VAR_1}$"

MissionBoard_EventScript_ChooseMission_Text_2:
# 29 "data/scripts/mission_board.pory"
	.string "Exit$"

MissionBoard_EventScript_ChooseMission_Text_3:
# 42 "data/scripts/mission_board.pory"
	.string "Accept this mission?$"

MissionBoard_EventScript_ChooseMission_Text_4:
# 45 "data/scripts/mission_board.pory"
	.string "Mission accepted!\nReturn here when it's done.$"

MissionBoard_EventScript_ActiveMenu_Text_0:
# 53 "data/scripts/mission_board.pory"
	.string "Current mission:\n{STR_VAR_1}$"

MissionBoard_EventScript_ActiveMenu_Text_1:
# 55 "data/scripts/mission_board.pory"
	.string "Hand In$"

MissionBoard_EventScript_ActiveMenu_Text_2:
# 56 "data/scripts/mission_board.pory"
	.string "Details$"

MissionBoard_EventScript_ActiveMenu_Text_3:
# 57 "data/scripts/mission_board.pory"
	.string "Abandon$"

MissionBoard_EventScript_ActiveMenu_Text_4:
# 72 "data/scripts/mission_board.pory"
	.string "Abandon this mission?$"

MissionBoard_EventScript_ActiveMenu_Text_5:
# 75 "data/scripts/mission_board.pory"
	.string "Mission abandoned.$"

MissionBoard_EventScript_HandIn_Text_0:
# 91 "data/scripts/mission_board.pory"
	.string "Your Bag has no room for the reward.\nMake some space and come back.$"

MissionBoard_EventScript_HandIn_Text_1:
# 96 "data/scripts/mission_board.pory"
	.string "Which Pokémon will you hand in?$"

MissionBoard_EventScript_HandIn_Text_2:
# 106 "data/scripts/mission_board.pory"
	.string "This mission needs a {STR_VAR_1}.$"

MissionBoard_EventScript_HandIn_Text_3:
# 108 "data/scripts/mission_board.pory"
	.string "An Egg can't be handed in.$"

MissionBoard_EventScript_HandIn_Text_4:
# 110 "data/scripts/mission_board.pory"
	.string "Take its held item first.\nThat item is yours to keep.$"

MissionBoard_EventScript_HandIn_Text_5:
# 112 "data/scripts/mission_board.pory"
	.string "You can't hand over your\nlast healthy Pokémon!$"

MissionBoard_EventScript_HandIn_Text_6:
# 114 "data/scripts/mission_board.pory"
	.string "Hand over this {STR_VAR_1}?\nYou won't get it back.$"

MissionBoard_EventScript_HandInItem_Text_0:
# 128 "data/scripts/mission_board.pory"
	.string "You haven't recovered the\n{STR_VAR_1} yet.$"

MissionBoard_EventScript_HandInItem_Text_1:
# 130 "data/scripts/mission_board.pory"
	.string "You don't have the {STR_VAR_1}\nin your Bag.$"

MissionBoard_EventScript_HandInItem_Text_2:
# 132 "data/scripts/mission_board.pory"
	.string "You haven't finished this\nmission yet.$"

MissionBoard_EventScript_HandInItem_Text_3:
# 140 "data/scripts/mission_board.pory"
	.string "You handed over the {STR_VAR_1}.$"

MissionBoard_EventScript_Site_Text_0:
# 156 "data/scripts/mission_board.pory"
	.string "It's holding the {STR_VAR_2}!\pYour Key Items pocket is full.\nMake room before you fight it.$"

MissionBoard_EventScript_Site_Text_1:
# 169 "data/scripts/mission_board.pory"
	.string "It dropped something!$"

MissionBoard_EventScript_Site_Text_2:
# 171 "data/scripts/mission_board.pory"
	.string "Take it back to the mission board.$"

MissionBoard_EventScript_Site_Text_3:
# 174 "data/scripts/mission_board.pory"
	.string "The {STR_VAR_1} calmed down\nand wandered off.\pReport back to the mission board.$"

MissionBoard_EventScript_Site_Text_4:
# 177 "data/scripts/mission_board.pory"
	.string "Report your catch to the\nmission board.$"

MissionBoard_EventScript_Site_Text_5:
# 180 "data/scripts/mission_board.pory"
	.string "The {STR_VAR_1} fainted and was\ncarried off by its friends.\pIt should be back soon.\nLeave the area and return.$"

MissionBoard_EventScript_Site_Text_6:
# 182 "data/scripts/mission_board.pory"
	.string "The {STR_VAR_1} is still here.\nTry again!$"

MissionBoard_EventScript_Complete_Text_0:
# 191 "data/scripts/mission_board.pory"
	.string "Mission complete!\nYou earned ¥{STR_VAR_1} and {STR_VAR_2} points.$"

MissionBoard_EventScript_Complete_Text_1:
# 196 "data/scripts/mission_board.pory"
	.string "A new mission has appeared\non the board!$"

MissionBoard_EventScript_TryRankUps_Text_0:
# 213 "data/scripts/mission_board.pory"
	.string "You've earned {STR_VAR_1} Rank!\pYour Bag has no room for the gift.\nMake space and check the board again.$"

MissionBoard_EventScript_TryRankUps_Text_1:
# 218 "data/scripts/mission_board.pory"
	.string "Rank up!\nYou're now {STR_VAR_1} Rank!$"
