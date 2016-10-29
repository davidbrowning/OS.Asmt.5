//https://github.com/2ndchance

#include<iostream>
#include<queue>
#include<mutex>
#include<thread>
#include<cstdlib>
#include<chrono>
#include<utility>

#include"ComputePiDigit.cpp"


//Technically this is a thread and a queue demo screw it, I'm making my project here
int getNext(std::mutex& mutex, std::queue<int>& q){
	std::lock_guard<std::mutex> lock(mutex);
	int task = q.front();
	q.pop();
	return task;
}

/*void recordAns(std::unordered_map<int, int>& um, int task, int answer){
//This is going to work because of the hash table idea
	um.insert({task, answer});
	return;
}*/

void threadStart(int id, std::mutex &m, std::queue<int>& q){
	for(int i = 0; i < 10; i++){
	int task;
	task = getNext(m, q);
	int answer = computePiDigit(task);
	std::cout << "id: " << id << ":" << answer << std::endl;
	//recordAns(map, task, answer);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	std::cout << "done with my loop -" << id << std::endl;
	return;
}

int main(){
	std::queue<int> q;
	for(int i = 0; i < 1000; i++){
		q.push(i);
	}
	//std::unordered_map<int, int> map;
	std::mutex mutex;
	//std::mutex othermutex;
	std::thread thread1(threadStart, 1, std::ref(mutex), std::ref(q));
	std::thread thread2(threadStart, 2, std::ref(mutex), std::ref(q));
	
	thread1.join();
	thread2.join();
	


	/*for(int i = 0; i < 1000; i++){
		std::cout << q.front() << std::endl;
		fout << q.front() << ',';
		q.pop();
	}*/
	
}
