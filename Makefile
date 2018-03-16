all:
	+$(MAKE) -C dun_gen
	+$(MAKE) -C screens
	make game.exe -f MakeMainDir
