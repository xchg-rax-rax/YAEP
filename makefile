./bin/yaep:
	mkdir -p ./bin
	g++ ./src/yaep.cpp -o ./bin/yaep

install: ./bin/yaep
	cp ./bin/yaep /usr/local/bin

clean:
	rm ./bin/*
