#ifndef SPENCER_ASYNCPROCESSOR_HPP
#define SPENCER_ASYNCPROCESSOR_HPP


#include <Sync/Semaphore.h>
#include <Sync/Mutex.h>
#include <queue>
#include <Util/Task.h>

template<typename T>
class AsyncProcessor {
public:

	/**
	 * Add a job to the queue. When completed, *job.result will point to an instance of *Result.
	 * Ownership of the object is transferred to the caller, and should be deallocated after use.
	 * * @param job
	 */
	void addJob(const T& job);

protected:
	AsyncProcessor(const char* name, uint16_t queueSize = 1);

	virtual void doJob(const T& job) = 0;

private:
	Task task;
	Semaphore semaphore;
	std::queue<T> jobs;
	Mutex jobsMutex;

	[[noreturn]] static void taskFunc(Task* task);

};

template<typename T>
AsyncProcessor<T>::AsyncProcessor(const char* name, uint16_t queueSize) : task(name, taskFunc, 6144, this), semaphore(queueSize){
	task.start(10, 1);
}

template<typename T>
void AsyncProcessor<T>::addJob(const T& job){
	jobsMutex.lock();
	jobs.push(job);
	jobsMutex.unlock();

	semaphore.signal();
}

template<typename T>
void AsyncProcessor<T>::taskFunc(Task* task){
	AsyncProcessor<T>* proc = static_cast<AsyncProcessor<T>*>(task->arg);

	while(task->running){
		if(!proc->semaphore.wait()) continue;

		proc->jobsMutex.lock();
		if(proc->jobs.empty()){
			proc->jobsMutex.unlock();
			continue;
		}

		T job = proc->jobs.front();
		proc->jobs.pop();
		proc->jobsMutex.unlock();

		proc->doJob(job);
	}
}

#endif //SPENCER_ASYNCPROCESSOR_HPP
