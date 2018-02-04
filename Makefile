hz_%: %.c
	g++ $^ -o $@ && ./$@

clean:
	rm hz_*
