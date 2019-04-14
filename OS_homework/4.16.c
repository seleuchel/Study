#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

#define THREAD_NUM 3

DWORD average, minimum, maximum;
int cnt = 0;

/* count arguments */
int arrcnt(char * arr[]) { 
	int cnt = 0;
	for (int i = 0; arr[i] != NULL; i++, cnt++);
	cnt--; // for division

	return cnt;
}

//Avg
DWORD WINAPI Avg(void * param) {
	average = 0;
	for (int i = 1; i < cnt + 1; i++) {
		average += atoi(((char**)param)[i]);
	}

	average /= cnt;

	return 0;

}

//Min
DWORD WINAPI Min(void *param) {
	minimum = 0;
	minimum = atoi(((char**)param)[1]);
	
	for (int i = 1; i < cnt + 1; i++) {	
		if (minimum > atoi(((char**)param)[i]))
			minimum = atoi(((char**)param)[i]);
	}

	return 0;
}

//Max
DWORD WINAPI Max(void *param) {
	maximum = 0;
	maximum = atoi(((char**)param)[1]);

	for (int i = 1; i < cnt + 1; i++) {
		if (atoi(((char**)param)[i]) > maximum) {	
			maximum = atoi(((char**)param)[i]);
		}
	}
	return 0;

}


int main(int argc, char * argv[]) {

	DWORD ThreadId[THREAD_NUM] = { 0 };
	HANDLE ThreadHandle[THREAD_NUM];


	if (argc < 2) {
		fprintf(stderr, "input your argument(int)\n");
		return -1;
	}

	cnt = arrcnt(argv);
	for (int i = 1; i < cnt + 1; i++) {
		if (atoi(((char**)argv)[i]) < 0) {
			fprintf(stderr, "input positivie number\n");
			return -1;
		}
	}


	for (int i = 0; i < THREAD_NUM; i++) {
		switch (i) {
		case 0:
			ThreadHandle[i] = CreateThread(NULL, 0, Avg, argv, 0, &ThreadId[i]);
			break;
		case 1:
			ThreadHandle[i] = CreateThread(NULL, 0, Max, argv, 0, &ThreadId[i]);
			
			break;
		case 2:
			ThreadHandle[i] = CreateThread(NULL, 0, Min, argv, 0, &ThreadId[i]);
			break;
		}
	}

	if (ThreadHandle[0] != NULL || ThreadHandle[1] != NULL || ThreadHandle[2] != NULL) {
		WaitForMultipleObjects(THREAD_NUM, ThreadHandle, TRUE, INFINITE);

		for (int i = 0; i < THREAD_NUM; i++) {
			CloseHandle(ThreadHandle[i]);
		}
		printf("The average value is %d\n", average);
		printf("The maximum value is %d\n", maximum);
		printf("The minimum value is %d\n", minimum);
	}

	return 0;
}


/* 함수 포인터를 사용할 수 없었음.
- 함수 : DWORD(__cdecl*)(void *) 에서 LPTHREAD_START_ROUTINE'으로 변환할 수 없습니다.
//DWORD가 unsigned int라서. 음수랑 비교시 음수가 반환
*/