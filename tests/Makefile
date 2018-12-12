ARGS = -std=c++11 -I../
GTEST_ARGS = -isystem /home/jcullis/software/googletest-release-1.8.1/googletest/include -pthread
GTEST_LIBS = /home/jcullis/software/googletest-release-1.8.1/googletest/make/libgtest.a /home/jcullis/software/googletest-release-1.8.1/googletest/make/gtest_main.a 
CPP = g++

all: footest tokentest

footest: footest.cpp foo.cpp
	$(CPP) $(ARGS) $(GTEST_ARGS) footest.cpp $(GTEST_LIBS) -o footest

tokentest: tokentest.cpp ../tokens.hpp
	$(CPP) $(ARGS) $(GTEST_ARGS) tokentest.cpp $(GTEST_LIBS) -o tokentest

clean:
	rm *test
