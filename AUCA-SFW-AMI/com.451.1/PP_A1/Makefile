
FLAGS= 	-L/usr/local/cuda/lib64 -I/usr/local/cuda-9.2/targets/x86_64-linux/include -lcuda -lcudart -lpthread


all: hmt 

hmt: interface.o gpu_main.o
	g++ -o hmt interface.o gpu_main.o $(FLAGS)

interface.o: interface.cpp interface.h
	g++ -w -c -std=c++11 -pthread interface.cpp $(FLAGS)

gpu_main.o: gpu_main.cu gpu_main.h
	nvcc -w -c gpu_main.cu

clean:
	rm interface.o;
	rm gpu_main.o;
