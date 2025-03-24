compileandexecute:
	@g++ main.cpp -o a.out && ./a.out && rm a.out
	@make -s tests

tests:
	#
