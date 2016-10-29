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
	
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread3(threadStart, 3, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread4(threadStart, 4, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread5(threadStart, 5, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread6(threadStart, 6, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread7(threadStart, 7, std::ref(mutex), std::ref(q), std::ref(um));
	std::thread thread8(threadStart, 8, std::ref(mutex), std::ref(q), std::ref(um));
	
	if(t == 4){
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
	}	
	else if(t == 1){
		thread1.join();
	}
	else if(t == 2){
		thread1.join();
		thread2.join();
	}
	else if(t == 6){
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
		thread5.join();
		thread6.join();
	}
	else if(t == 8){
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
	//*
	for (unsigned i = 0; i < um.bucket_count(); ++i) {
		for (auto local_it = um.begin(i); local_it!= um.end(i); ++local_it){
		      std::cout << local_it->second;
		}
	}//*credit to http://www.cplusplus.com/reference/unordered_map/unordered_map/begin/ for this idea ^
	std::cout << std::endl;
}
