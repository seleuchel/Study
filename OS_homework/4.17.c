#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<time.h>

#define ALL_THROW 100000000
#define THREAD_NUM 10
#define THREAD_THROW 10000000

int count[THREAD_NUM] = { 0 };
//매크로 : 전체 던진 수
//매크로 :스레드당 던질 수 (1만)
//매크로 : 스레드 개수
//전역변수 : 원안으로 들어간 점의 수


DWORD WINAPI createSpot(void * arr) {

	srand(time(NULL));
	for (int i = 0; i < THREAD_THROW; i++) {
		double x = rand() / (double)RAND_MAX * 2.0 - 1;
		double y = rand() / (double)RAND_MAX * 2.0 - 1;

		double distance = sqrt(x*x + y * y);
		if (distance <= 1) {
			*(int *)arr += 1;
		}
	}

	return 0;

}

//함수 : 임의의 점을 생성하는 함수 (1만)
//함수 : 원과 임의의 점 사이의 거리를 계산하는 함수 -> true 시 원안으로들어간 점의 수로 count


int main() {

	DWORD ThreadId[THREAD_NUM] = { 0 };
	HANDLE ThreadHandle[THREAD_NUM];
	for (int i = 0; i < THREAD_NUM; i++) {

		ThreadHandle[i] = CreateThread(NULL, 0, createSpot, &count[i], 0, &ThreadId[i]);
	}

	DWORD k = WaitForMultipleObjects(THREAD_NUM, ThreadHandle, TRUE, INFINITE);

		for (int i = 0; i < THREAD_NUM; i++) {
			CloseHandle(ThreadHandle[i]);
		}

			int count1 = 0; //각 카운트의 모든 합
			for (int i = 0; i < THREAD_NUM; i++) {
				count1 += count[i];
			}
			printf("파이의 근삿값 : %lf\n", (double)(count1 * 4) / ALL_THROW);;

	return 0;
		
	}

/*
스레드 생성 10개.
각 스레드마다 임의의 점을 만개씩 생산하는 스레드를 10개 생성.

스레드 수행
스레드 모음.

공식에 따라 값을 구하여 파이값과 비교.

*/