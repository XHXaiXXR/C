test:test.cpp
	g++ -o test test.cpp -g
-PHONY:clean
clean:
	rm -f test