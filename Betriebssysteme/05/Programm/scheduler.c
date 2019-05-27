#include "scheduler.h"

void appendJob(listProcess *list, char processname[50], int time, int priority) {
	job *process = LIST_NEW_NODE(job);
    strcpy(process->name, processname);
    process->time = time;
    process->priority = priority;
	List_append(list, process);
}

void firstComeFirstServed(listProcess *list) {
	job *node = list->head;
	int amount = list->count;
	float currentTime = 0;
	float totalTime = 0;
	float averageTime = 0;

	printf("First Come First Served:\n");

	while(node != NULL) {
		currentTime += node->time;
		totalTime += node->time * list->count;
		//Muss an sich nicht gemacht werden, symbolisiert aber, dass die Jobzeit nach dem Arbeiten auf 0 ist
		node->time -= node->time;

		printf("%s wurde abgearbeitet (Akutelle Zeit: %.3f).\n", node->name, currentTime);
		node = List_remove(list, node);
	}
	averageTime = totalTime / amount;
	printf("Mittlere Verweilzeit: %.3f\n", averageTime);

}

int main() {
	listProcess list;
	List_init(&list);

	appendJob(&list, "A", 30, 2);
	appendJob(&list, "B", 20, 1);
	appendJob(&list, "C", 25, 5);
	appendJob(&list, "D", 28, 4);
	appendJob(&list, "E", 18, 3);
	firstComeFirstServed(&list);

	

	return 0;
}
