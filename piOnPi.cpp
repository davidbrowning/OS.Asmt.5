#include<iostream>
#include<queue>
#include<fstream>
#include<mutex>
#include<thread>
#include<cstdlib>
#include<chrono>
#include<utility>
#include<unordered_map>

#include "computePiDigit.hpp"

int getNext(std::mutex& mutex, std::queue<int>& q){
	std::lock_guard<std::mutex> lock(mutex);
	int task = q.front();
	q.pop();
	return task;
}


void recordAns(std::mutex& mutex, std::unordered_map<int, int>& um, int task, int answer){
//This is going to work because of the hash table idea
	std::lock_guard<std::mutex> lock(mutex);
	um.insert({task, answer});
	return;
}

void threadStart(int id, std::mutex &m, std::queue<int>& q, std::unordered_map<int, int>& um){
	while(!q.empty()){
	int task;
	//std::cout << "id: " << id << std::endl;
	//std::cout.flush();
	task = getNext(m, q);
	int ans;
	//std::cout << "task: " << task << std::endl;
	//std::cout.flush();
	std::cout << '.';
	std::cout.flush();
	ans = computePiDigit(task);
	recordAns(m, um, task, ans);
	//std::cout << "ans: " << ans << std::endl;
	//std::cout.flush();
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main(){
	std::ofstream fout;
	//fout.open("qtest.txt");
	std::queue<int> q;
	for(int i = 1; i < 1001; i++){ //If I'm starting at 1 I have to end at 1001
		q.push(i);
	}
	std::unordered_map<int, int> um;
	std::mutex mutex;
	auto t = std::thread::hardware_concurrency();
	
//I'm fully aware that this part is horribly ugly, but I got confused regarding how to make the creation of threads dependent upon an iterator. I tried making a vector of threads but just wound up with a bunch of errors. I figured I start with the 4 case as I feel it is the most likely. 	
	if(t == 4){
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread3(threadStart, 3, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread4(threadStart, 4, std::ref(mutex), std::ref(q), std::ref(um));
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
	}	
	else if(t == 1){
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
		thread1.join();
	}
	else if(t == 2){
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q), std::ref(um));
		thread1.join();
		thread2.join();
	}
	else if(t == 6){
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread3(threadStart, 3, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread4(threadStart, 4, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread5(threadStart, 5, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread6(threadStart, 6, std::ref(mutex), std::ref(q), std::ref(um));
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
		thread5.join();
		thread6.join();
	}
	else if(t == 8){
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread3(threadStart, 3, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread4(threadStart, 4, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread5(threadStart, 5, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread6(threadStart, 6, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread7(threadStart, 7, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread8(threadStart, 8, std::ref(mutex), std::ref(q), std::ref(um));
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
		thread5.join();
		thread6.join();
		thread7.join();
		thread8.join();
	}
	//thread1.join();
	//thread2.join();
	
	std::cout << "\n\n3.";
	for (int j = 1; j < 1001; j++) {
		std::cout << um.at(j);
	}
	std::cout << std::endl;

}
