all: test_models

clean:
	rm test_models lpsolver.o

lpsolver.o: lpsolver.cpp lpsolver.hpp


test_models: lpsolver.o test_models.cpp


