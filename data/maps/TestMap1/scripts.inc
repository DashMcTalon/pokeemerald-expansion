TestMap1_MapScripts::
	.byte 0


TestMap1_TestMapGreeter::
# 4 "data/maps/TestMap1/scripts.pory"
	lock
# 5 "data/maps/TestMap1/scripts.pory"
	faceplayer
# 6 "data/maps/TestMap1/scripts.pory"
	msgbox TestMap1_TestMapGreeter_Text_0, MSGBOX_NPC
# 7 "data/maps/TestMap1/scripts.pory"
	release
	end


TestMap1_Trainer_Joey::
# 12 "data/maps/TestMap1/scripts.pory"
	trainerbattle_single TRAINER_TEST_1, TestMap1_Text_JoeyIntro, TestMap1_Text_JoeyDefeat
# 13 "data/maps/TestMap1/scripts.pory"
	msgbox TestMap1_Text_JoeyPost, MSGBOX_AUTOCLOSE
	end


TestMap1_TestMapGreeter_Text_0:
# 6 "data/maps/TestMap1/scripts.pory"
	.string "Hello there$"

TestMap1_Text_JoeyIntro::
# 17 "data/maps/TestMap1/scripts.pory"
	.string "My Rattata is in the top percentage\n"
	.string "of all Rattata!$"

TestMap1_Text_JoeyDefeat::
# 22 "data/maps/TestMap1/scripts.pory"
	.string "Aw, I lost!$"

TestMap1_Text_JoeyPost::
# 26 "data/maps/TestMap1/scripts.pory"
	.string "You're pretty strong.$"
