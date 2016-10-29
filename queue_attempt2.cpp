#include<iostream>
#include<queue>
#include<fstream>
#include<mutex>
#include<thread>
#include<cstdlib>
#include<chrono>
#include<utility>
#include<unordered_map>

#include "ComputePiDigit.cpp"

int getNext(std::mutex& mutex, std::queue<int>& q){
	std::lock_guard<std::mutex> lock(mutex);
	int task = q.front();
	q.pop();
	return task;
}

void threadStart(int id, std::mutex &m, std::queue<int>& q, std::unordered_map<int, int> um){
	for(int i = 0; i < 5; i++){
	int task;
	//std::cout << "id: " << id << std::endl;
	//std::cout.flush();
	task = getNext(m, q);
	int ans;
	//std::cout << "task: " << task << std::endl;
	//std::cout.flush();
	ans = computePiDigit(task);
	//std::cout << "ans: " << ans << std::endl;
	//std::cout.flush();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main(){
	std::ofstream fout;
	fout.open("qtest.txt");
	std::queue<int> q;
	for(int i = 1; i < 1000; i++){
		q.push(i);
	}
	std::unordered_map<int, int> um;
	std::mutex mutex;
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q), std::ref(um));
	
	thread1.join();
	thread2.join();
	
	/*for(int i = 0; i < 1000; i++){
		std::cout << q.front() << std::endl;
		fout << q.front() << ',';
		q.pop();
	}*/
	
}
