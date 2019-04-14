#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<time.h>

#define ALL_THROW 100000000
#define THREAD_NUM 10
#define THREAD_THROW 10000000

int count[THREAD_NUM] = { 0 };
//��ũ�� : ��ü ���� ��
//��ũ�� :������� ���� �� (1��)
//��ũ�� : ������ ����
//�������� : �������� �� ���� ��


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

//�Լ� : ������ ���� �����ϴ� �Լ� (1��)
//�Լ� : ���� ������ �� ������ �Ÿ��� ����ϴ� �Լ� -> true �� �������ε� ���� ���� count


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

			int count1 = 0; //�� ī��Ʈ�� ��� ��
			for (int i = 0; i < THREAD_NUM; i++) {
				count1 += count[i];
			}
			printf("������ �ٻ� : %lf\n", (double)(count1 * 4) / ALL_THROW);;

	return 0;
		
	}

/*
������ ���� 10��.
�� �����帶�� ������ ���� ������ �����ϴ� �����带 10�� ����.

������ ����
������ ����.

���Ŀ� ���� ���� ���Ͽ� ���̰��� ��.

*/