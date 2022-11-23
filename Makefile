make:
	make shell
	make _mkdir
	make _rm
	make _date
	make _cat
	make _ls 

clean:
	rm -f shell
	rm -f _mkdir
	rm -f _rm
	rm -f _date
	rm -f _cat
	rm -f _ls

run:
	./shell