#include<stdio.h>
#include<stdlib.h>

int rd_que[20]; //Ready Queue

struct Process_Structure //Structure for the process
{
	int process_id, arrival_time, burst_time, completion_time;
}; //end of structure

void swap(struct Process_Structure proc[], int n, int k, int l) //To swap all the process elements
{
	int temp;

	temp = proc[k].process_id;
	proc[k].process_id = proc[l].process_id;
	proc[l].process_id = temp;

	temp = proc[k].burst_time;
	proc[k].burst_time = proc[l].burst_time;
	proc[l].burst_time = temp;

	temp = proc[k].arrival_time;
	proc[k].arrival_time = proc[l].arrival_time;
	proc[l].arrival_time = temp;

	temp = proc[k].completion_time;
	proc[k].completion_time = proc[l].completion_time;
	proc[l].completion_time = temp;
} //end of function

void sort_by_completion_time(struct Process_Structure process_obj[], int n) //To sort processes according to completion time
{
	int first, second, min, temp;
	for (first = 0; first < n; first++)
	{
		min = process_obj[first].completion_time;
		for (second = first + 1; second < n; second++)
		{
			if (process_obj[second].completion_time <= min)
			{
				min = process_obj[second].completion_time;
				swap(process_obj, n, first, second);
			}
		}
		rd_que[first] = process_obj[first].process_id;
	}
} //end of function

void sort_by_burst_time(struct Process_Structure process_obj[], int n) //To sort the processes according to burst time to find which one to execute first
{
	int i, j, max, temp;
	for (i = 0; i < n; i++)
	{
		max = process_obj[i].burst_time;
		for (j = i + 1; j < n; j++)
		{
			if (process_obj[j].burst_time >= max)
			{
				max = process_obj[j].burst_time;
				swap(process_obj, n, i, j);
			}
		}
		rd_que[i] = process_obj[i].process_id;
	}
} //end of function



int main() //main
{
	int time = 0, checker = 0, Tot_TAT = 0, Tot_Wait = 0, startTime;
	int i, j, num_proc, min, temp, wait_time, turnaroundTime, burst_rep[20];
	printf("\n\tEnter the Number of Processes : ");
	scanf("%d", &num_proc);
	struct Process_Structure process[num_proc];
	for (i = 0; i < num_proc; i++)
	{
		process[i].process_id = i + 1;
		printf("\n\tEnter Process ID   : %d", process[i].process_id);
		printf("\n\n\tEnter Arrival Time : ");
		scanf("%d", &process[i].arrival_time);
		printf("\n\tEnter Burst Time   : ");
		scanf("%d", &process[i].burst_time);
		while (process[i].burst_time < 10)
		{
			printf("\n\tBurst time cannot be less than 10");
			printf("\n\tRe-enter the value : ");
			scanf("%d", &process[i].burst_time);
		}
		printf("\n=====================================================\n");
		process[i].completion_time = 0;
		burst_rep[i] = process[i].burst_time;
		rd_que[i] = process[i].process_id;
		checker++;
	}

	for (i = 0; i < num_proc; i++) //To sort processes according to their arrival time in the ready queue
	{
		min = process[i].arrival_time;
		for (j = i + 1; j < num_proc; j++)
		{
			if (process[j].arrival_time <= min)
			{
				min = process[j].arrival_time;
				swap(process, num_proc, i, j);
			}
		}
		rd_que[i] = process[i].process_id;
	}

	for (i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			startTime = time;
			printf("\n\tProcess %d started from %d seconds and ran for 6 seconds", process[i].process_id, startTime);
			process[i].burst_time -= 6;
			time += 6;
		}
		if (num_proc > 1)
		{
			if (i == 1)
			{
				startTime = time;
				printf("\n\tProcess %d started from %d seconds and ran for 10 seconds", process[i].process_id, startTime);
				process[i].burst_time -= 10;
				time += 10;
			}
			else
			{
				sort_by_burst_time(process, num_proc);
			}
		}

	}

	i = 0;

	while (checker != 0)
	{
		if (process[i].burst_time >= 10)
		{
			startTime = time;
			printf("\n\tProcess %d started from %d seconds and ran for 10 seconds", process[i].process_id, startTime);
			process[i].burst_time -= 10;
			time += 10;

			if (process[i].burst_time == 0)
			{
				process[i].completion_time = time;
				--checker;
			}

			sort_by_burst_time(process, num_proc);
		}
		else
		{
			startTime = time;
			time = time + process[i].burst_time;
			printf("\n\tProcess %d started from %d seconds and ran for %d seconds", process[i].process_id, process[i].burst_time, startTime);
			process[i].burst_time -= process[i].burst_time;

			if (process[i].burst_time == 0)
			{
				process[i].completion_time = time;
				--checker;
			}

			sort_by_burst_time(process, num_proc);
		}
	}

	if (checker == 0)
	{
		sort_by_completion_time(process, num_proc);
		printf("\n\n\t!!! The Processes have Completed their Execution !!!\n\n");
	}

	printf("\n\t======================================================\n");
	printf("\t Process_ID \t Turnaround Time \t Waiting Time");
	printf("\n\t======================================================\n");
	for (i = 0; i < num_proc; i++)
	{
		turnaroundTime = process[i].completion_time - process[i].arrival_time;
		if (turnaroundTime <= 0)
			turnaroundTime = 0;
		Tot_TAT += turnaroundTime;
		wait_time = turnaroundTime - burst_rep[(rd_que[i] - 1)];
		if (wait_time < 0)
			wait_time = 0;
		Tot_Wait += wait_time;
		printf("\t    %d \t\t       %d \t%\t     %d", rd_que[i], turnaroundTime, wait_time);
		printf("\n\n");
	}

	printf("\n\tAverage Turn around Time is : %.2f", ((float)Tot_TAT / num_proc));
	printf("\n\tAverage Waiting Time is     : %.2f", ((float)Tot_Wait / num_proc));
	getch();
	return 0;
}	//end of main
