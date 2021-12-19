./bin/yaep:
	g++ ./src/yaep.cpp -o ./bin/yaep

install:
	cp ./bin/yaep /usr/local/bin

clean:
	rm ./bin/*
