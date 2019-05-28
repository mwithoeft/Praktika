#include "scheduler.h"

void firstComeFirstServed(listProcess *list) {
	printf("First Come First Served:\n");
	runJob(list);
}
void shortestJobFirst(listProcess *list){
	List_sort(list,(ListNodeCompareFunction)cmpTime, NULL);
	printf("Shortest Job First:\n");
	runJob(list);
}
void prioScheduling(listProcess *list){
	List_sort(list,(ListNodeCompareFunction)cmpPrio, NULL);
	printf("Prio Scheduling:\n");
	runJob(list);
}
void appendJob(listProcess *list, char processname[50], int time, int priority) {
	job *process = LIST_NEW_NODE(job);
    strcpy(process->name, processname);
    process->time = time;
    process->priority = priority;
	List_append(list, process);
}
void roundRobin(listProcess *list){

}
void roundRobinPrio(listProcess *list){

}
void runJob(listProcess *list){
	job *node = list->head;
	int amount = list->count;
	int counter = 0;
	float currentTime = 0;
	float totalTime = 0;
	float averageTime = 0;

	while(node != NULL) {
		currentTime += node->time;
		totalTime += node->time * (list->count - counter);
		//Muss an sich nicht gemacht werden, symbolisiert aber, dass die Jobzeit nach dem Arbeiten auf 0 ist
//		node->time -= node->time;
		printf("%s wurde abgearbeitet (Akutelle Zeit: %.2f).\n", node->name, currentTime);
		node = node->next;
		counter++;
	}
	averageTime = totalTime / amount;
	printf("Mittlere Verweilzeit: %.3f\n", averageTime);
}
int cmpPrio(job *node1, job *node2, void *dummy){
	return node2->priority - node1->priority;
}

int cmpTime(job *node1, job *node2, void *dummy){
	return node1->time - node2->time;
}
void initJobs(listProcess *list){
	appendJob(list, "A", 30, 2);
	appendJob(list, "B", 20, 1);
	appendJob(list, "C", 25, 5);
	appendJob(list, "D", 28, 4);
	appendJob(list, "E", 18, 3);
}
void printJob(listProcess *list){
	job *node = list->head;
	while(node != NULL){
		printf("Job:%s	Time:%.2f	Prio:%i\n",node->name, node->time, node->priority);
		node = node->next;
	}
}
int main() {
	listProcess list;
	List_init(&list);
	initJobs(&list);
	printJob(&list);
	firstComeFirstServed(&list);
	shortestJobFirst(&list);
	prioScheduling(&list);
	return 0;
}
