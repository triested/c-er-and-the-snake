all:
	+$(MAKE) -C dun_gen
	make game.exe -f MakeMainDir
