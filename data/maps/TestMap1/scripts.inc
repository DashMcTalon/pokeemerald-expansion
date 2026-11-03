TestMap1_MapScripts::
# 2 "data/maps/TestMap1/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, TestMap1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

TestMap1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/TestMap1/scripts.pory"
	special MissionBoard_SetupSite
	return


TestMap1_TestMapGreeter::
# 8 "data/maps/TestMap1/scripts.pory"
	lock
# 9 "data/maps/TestMap1/scripts.pory"
	faceplayer
# 10 "data/maps/TestMap1/scripts.pory"
	msgbox TestMap1_TestMapGreeter_Text_0, MSGBOX_NPC
# 11 "data/maps/TestMap1/scripts.pory"
	release
	end


TestMap1_Trainer_Joey::
# 16 "data/maps/TestMap1/scripts.pory"
	trainerbattle_single TRAINER_TEST_1, TestMap1_Text_JoeyIntro, TestMap1_Text_JoeyDefeat
# 17 "data/maps/TestMap1/scripts.pory"
	msgbox TestMap1_Text_JoeyPost, MSGBOX_AUTOCLOSE
	end


TestMap1_TestMapGreeter_Text_0:
# 10 "data/maps/TestMap1/scripts.pory"
	.string "Hello there$"

TestMap1_Text_JoeyIntro::
# 21 "data/maps/TestMap1/scripts.pory"
	.string "My Rattata is in the top percentage\n"
	.string "of all Rattata!$"

TestMap1_Text_JoeyDefeat::
# 26 "data/maps/TestMap1/scripts.pory"
	.string "Aw, I lost!$"

TestMap1_Text_JoeyPost::
# 30 "data/maps/TestMap1/scripts.pory"
	.string "You're pretty strong.$"
