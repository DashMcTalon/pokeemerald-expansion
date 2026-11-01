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


TestMap1_TestMapGreeter_Text_0:
# 6 "data/maps/TestMap1/scripts.pory"
	.string "Hello there$"
