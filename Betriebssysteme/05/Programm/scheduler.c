#include "scheduler.h"

void appendJob(listProcess *list, char processname[50], int time, int priority) {
	job *process = LIST_NEW_NODE(job);
    strcpy(process->name, processname);
    process->time = time;
    process->priority = priority;
	List_append(list, process);
}

void runJob(listProcess *list){

	job *node = list->head;
	int amount = list->count;
	float currentTime = 0;
	float totalTime = 0;
	float averageTime = 0;

	while(node != NULL) {
		currentTime += node->time;
		totalTime += node->time * list->count;
		//Muss an sich nicht gemacht werden, symbolisiert aber, dass die Jobzeit nach dem Arbeiten auf 0 ist
		node->time -= node->time;

		printf("%s wurde abgearbeitet (Akutelle Zeit: %.3f).\n", node->name, currentTime);
		node = node->next;
	}
	averageTime = totalTime / amount;
	printf("Mittlere Verweilzeit: %.3f\n", averageTime);

}

void firstComeFirstServed(listProcess *list) {
	printf("First Come First Served:\n");
	runJob(list);
}

void shortestJobFirst(listProcess *list){
	List_sort(list,(ListNodeCompareFunction)cmp, NULL);
	job *node = list->head;
	int amount = list->count;
	float currentTime = 0;
	float totalTime = 0;
	float averageTime = 0;

	while(node != NULL){
		node = node->next;
	}
}


int cmp(job *node1, job *node2, void *dummy){
//	if (node1->priority < node2->priority){return -1;}
//	else if (node1->priority == node2->priority){return 0;}
//	else if (node1->priority > node2->priority){return 1;}
	return node1->priority - node2->priority;
}

void prioScheduling(listProcess *list){

}
void roundRobin(listProcess *list){

}
void roundRobinPrio(listProcess *list){

}
void initJobs(listProcess *list){
	appendJob(list, "A", 30, 2);
	appendJob(list, "B", 20, 1);
	appendJob(list, "C", 25, 5);
	appendJob(list, "D", 28, 4);
	appendJob(list, "E", 18, 3);
}

int main() {
	listProcess list;
	List_init(&list);
	initJobs(&list);
	firstComeFirstServed(&list);
	initJobs(&list);
	shortestJobFirst(&list);
	return 0;
}
