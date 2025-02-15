#include "kernel.h"

#include <iostream>
#include <algorithm>

namespace svm
{
    Kernel::Kernel(
                Scheduler scheduler,
                std::vector<Memory::ram_type> executables_paths
            )
        : board(),
          processes(), //
          priorities(), //PRIORITIES
          scheduler(scheduler),
          _last_issued_process_id(0),
          _last_ram_position(0),
          _cycles_passed_after_preemption(0),
          _current_process_index(0)
    {
        std::for_each(
            executables_paths.begin(),
            executables_paths.end(),
            [&](Memory::ram_type &executable) {
                CreateProcess(executable);
            }
        );

        if (scheduler == FirstComeFirstServed) {
            board.pic.isr_0 = [&]() {
                // ToDo: Process the timer interrupt for the FCFS
		std::cout << "Skipping the timer interrupt handler for FCFS" << std::endl;
		return;
            };

            board.pic.isr_3 = [&]() {
                // ToDo: Process the first software interrupt for the FCFS
                std::cout << "The software interrupt handler for FCFS was called" << std::endl;
				std::cout << "Number of Processes left = " 
				<< processes.size() << std::endl;
				
				std::cout << "Exit call on the current process. Unload the current process. Process id = " 
				<< processes[_current_process_index].id
				<< std::endl;
				processes.erase(processes.begin() + _current_process_index);
				std::cout << std::endl;

				// Unload the current process
				if (processes.empty()) {
					std::cout << "There are no processes to perform. Board has been stopped." << std::endl;
					board.Stop();					
				}
				else {
					board.cpu.registers = processes[_current_process_index].registers;
					processes[_current_process_index].state = Process::States::Running;
					std::cout << "Process State: Running" << std::endl;
					std::cout << std::endl;
				}
            };
        } else if (scheduler == ShortestJob) {
            board.pic.isr_0 = [&]() {
                // ToDo: Process the timer interrupt for the Shortest
                std::cout << "Skipping the timer interrupt handler for SJF" << std::endl;
		return;
				//  Job scheduler	
            };

            board.pic.isr_3 = [&]() {
                // ToDo: Process the first software interrupt for the Shortest
				std::cout << "The software interrupt handler for SJF was called" << std::endl;
				std::cout << "Number of Processes left = " 
				<< processes.size() << std::endl;
			

				std::cout <<"Process id: " << processes[_current_process_index].id << ", with time = "	
					  <<processes[_current_process_index].sequential_instruction_count << std::endl;	


				std::cout << "Exit call on the current process. Unload the current process." << std::endl;
				processes.erase(processes.begin() + _current_process_index);
				
				
				if (processes.empty()) {
					std::cout << "There are no processes to perform. Board has been stopped." << std::endl;
					board.Stop();					
				}
                		//  Job scheduler

               	 		// Unload the current process
				else {
					board.cpu.registers = processes[_current_process_index].registers;
					processes[_current_process_index].state = Process::States::Running;
					std::cout << "Process State: Running" << std::endl;
					std::cout << std::endl;
				}
            };
        } else if (scheduler == RoundRobin) {
            board.pic.isr_0 = [&]() {
                // ToDo: Process the timer interrupt for the Round Robin
                //  scheduler
				std::cout << "The timer interrupt handler for RR was called" << std::endl;
			
				
				
				++_cycles_passed_after_preemption;		
				std::cout << "The current cycle count " << _cycles_passed_after_preemption << std::endl;
				std::cout << "Allowing the current process with index: " << _current_process_index << ", to run"
				<< std::endl
				<< std::endl;

				if(_cycles_passed_after_preemption > _MAX_CYCLES_BEFORE_PREEMPTION){
					std::cout << "Max number of Cycles has been reached" << std::endl;
					process_list_type::size_type next_process_index = 
					(_current_process_index + 1)% processes.size();
					
					std::cout << "The current process with index: " << _current_process_index 
							  << ", has consumed it time slice: " << _MAX_CYCLES_BEFORE_PREEMPTION
							  << std::endl
							  << "Switching the context to the next process with index: " << next_process_index
							  << std::endl;
					//switch the context
					
					std::cout 
					<< "Saving all the registers from the CPU to the PCB of the previous process" 
					<< std::endl;
					
					processes[_current_process_index].registers = board.cpu.registers;
					processes[_current_process_index].state = Process::States::Ready;
					
					std::cout 
					<< "Restoring all the registers from the PCB of the next process to the CPU" 
					<< std::endl;
					
					_current_process_index = next_process_index;
					std::cout << "Current Process Index has been incremented" << std::endl;
					
					board.cpu.registers = processes[_current_process_index].registers;
					processes[_current_process_index].state = Process::States::Running;
					std::cout << "Process State: Running" << std::endl;
					
					std::cout << "Restoring the time slice counter" << std::endl;
					_cycles_passed_after_preemption = 0;
					std::cout << std::endl;
				}
            };

            board.pic.isr_3 = [&]() {
                // ToDo: Process the first software interrupt for the
				std::cout << "The software interrupt handler for RR was called" << std::endl;
				std::cout << "Number of Processes left = " 
				<< processes.size() << std::endl;
				
				// exit() and Unload the current process
				std::cout << "Exit call on the current process. Unload the current process and context switch." << std::endl;
				processes.erase(processes.begin() + _current_process_index);

				if (processes.empty()) {
					std::cout << "There are no processes to perform. Board has been stopped." << std::endl;
					board.Stop();					
				}
				else {
					if (_current_process_index >= processes.size()) {
						_current_process_index = 0;
					}
					board.cpu.registers = processes[_current_process_index].registers;
					processes[_current_process_index].state = Process::States::Running;
					std::cout << "Process State: Running" << std::endl;
					std::cout << std::endl;
				}
				
            };
        } else if (scheduler == Priority) {
            board.pic.isr_0 = [&]() {
                // ToDo: Process the timer interrupt for the Priority Queue, using priorities data structure
				std::cout << "The timer interrupt handler for Priority Queue was called" << std::endl;		

			
				// using 1st method for Priority scheduling of decreasing the priority of current process at each clock tick
				// until its' priority gets below the priority of the next process, then context switch occurs 
				//  scheduler

				for (unsigned int i = 1; i < priorities.size(); ++i){
					++priorities[i].priority;
				}


				process_list_type::size_type next_process_index = 
				(_current_process_index + 1)% priorities.size();
				//switch the context

				if (priorities[_current_process_index].priority < priorities[next_process_index].priority) {
					
					std::cout 
					<< "The priority of the current process with id: " << priorities[_current_process_index].id 
					<< ", with priority: "
					<< priorities[_current_process_index].priority
					<< ", has dropped below that of the next highest process with id: " << priorities[next_process_index].id
					<< ", with priority: "
					<< priorities[next_process_index].priority
					<< std::endl
					<< "Switching the context to the next process"
					<< std::endl;
				
					std::cout 
					<< "Saving all the registers from the CPU to the PCB of the previous process" 
					<< std::endl;
					
					priorities[_current_process_index].registers = board.cpu.registers;
					priorities[_current_process_index].state = Process::States::Ready;
					
					std::cout 
					<< "Restoring all the registers from the PCB of the next process to the CPU" 
					<< std::endl;
					// find a way to sort 
					//sort(priorities.begin(), priorities.end());
					//
					//
					for(unsigned int i = 1; i < priorities.size(); ++i){
						int j = i - 1;
						Process _temp = priorities[i];
						while(j >=0 && priorities[j].priority < _temp.priority){
							priorities[j+1] = priorities[j];
							j--;
						}	
						priorities[j+1] = _temp;
					}	
					std::cout << "Current Process Index was changed based on new priorities" << std::endl;
					
					board.cpu.registers = priorities[_current_process_index].registers;
					priorities[_current_process_index].state = Process::States::Running;
					std::cout << "Process State: Running" << std::endl;
					
					_cycles_passed_after_preemption = 0;
					std::cout << std::endl;

				}
			
				
            };

            board.pic.isr_3 = [&]() {
        		        // ToDo: Process the first software interrupt for the Priority
				std::cout << "The software interrupt handler for Priority Queue was called" << std::endl;
               			//  Queue scheduler
				std::cout << "Number of Processes left = " 
				<< priorities.size() << std::endl;
				
				// exit() and Unload the current process
				std::cout << "Exit call on the current process: " << priorities[_current_process_index].id
				<< ", with priority: "
				<< priorities[_current_process_index].priority
				<< ". Unload the current process and context switch." 
				<< std::endl;
				priorities.pop_front();

				if (priorities.empty()) {
					std::cout << "There are no processes to perform. Board has been stopped." << std::endl;
					board.Stop();					
				}
				else {
					if (_current_process_index >= priorities.size()) {
						_current_process_index = 0;
					}
					board.cpu.registers = priorities[_current_process_index].registers;
					priorities[_current_process_index].state = Process::States::Running;
					std::cout << "Process State: Running" << std::endl;
					std::cout << std::endl;
				}
            };
        }

        // ToDo

        // ---
        board.Start();
    }

    Kernel::~Kernel() { }

    void Kernel::CreateProcess(Memory::ram_type &executable)
    {
        std::copy(
            executable.begin(),
            executable.end(),
            board.memory.ram.begin() + _last_ram_position
        );

        Process process(
            _last_issued_process_id++,
            _last_ram_position,
            _last_ram_position + executable.size()
        );
        _last_ram_position +=
            executable.size();

	//generate random priority level for process
	srand (time(NULL));
	process.priority = rand() % (processes.size() + 1) + 1;

	// ToDo: add the new process to an appropriate data structure
	
	if (scheduler == Priority) {			
		priorities.push_back(process);
		std::sort (priorities.begin(), priorities.end());
	}
	else {
		processes.push_back(process);
	}
	// sorting processes by time, using insertion sort for simplicity		
	if (scheduler == ShortestJob) {			
		for(int i = 1; i < processes.size(); ++i){
			int j = i - 1;
			Process _temp = processes[i];
			while(j >=0 && processes[j].sequential_instruction_count > _temp.sequential_instruction_count){
				processes[j+1] = processes[j];
				j--;
			}	
			processes[j+1] = _temp;
		}	
	}	
		
		
		
        // ToDo: process the data structure

        // ---

    }
}
