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


void recordAns(std::unordered_map<int, int>& um, int task, int answer){
//This is going to work because of the hash table idea
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
	recordAns(um, task, ans);
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
	auto t = std::thread::hardware_concurrency();
	for(int i = 0; i < t; i++){
		std::thread thr(threadStart, i, std::ref(mutex), std::ref(q), std::ref(um));
		thr.join();
	}
	/*std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q), std::ref(um));
	
	thread1.join();
	thread2.join();*/
	
	std::cout << "\n\n3.";
	//*
	for (unsigned i = 0; i < um.bucket_count(); ++i) {
		for (auto local_it = um.begin(i); local_it!= um.end(i); ++local_it){
		      std::cout << local_it->second;
		}
	}//*credit to http://www.cplusplus.com/reference/unordered_map/unordered_map/begin/ for this idea ^
	std::cout << std::endl;
}
