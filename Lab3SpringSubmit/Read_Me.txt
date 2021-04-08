1. Data Structure
	a. The individual input is saved in Task class.
		The Task class has member variables which are state, task name, resource type, delay and resource unit.
	b. Each cycle has a vector which has all tasks.
		ex) task_vector for cycle 1 = {task 1, task 2, task 3....}
		    task_vector for cycle 2 = {task 1, task 2, task 3....}
		    task_vector for cycle 3 = {task 1, task 2, task 3....}....
	c. The task_vectors for each cycle is contained in struc. The structs are 
		saved in vector again.	    
		ex) Task_vector_vector = {task_vector for cycle 1, task_vector for cycle 2,
			task_vector for cycle 3.......}
	d.Access to a task
		task = Task_vector_vector[cycle][nth task]

2. Compile and execute
	a. First unzip the file. And go to unziped folder which has main.cpp file.
	b. compile: g++ main.cpp 
	c. execute: ./a.out ./data/input-13
		The path for input is relative path(address)