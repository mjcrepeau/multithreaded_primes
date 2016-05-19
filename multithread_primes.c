#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define NUM_THREADS 4

struct th_info {
	int i, n;
	int *array;
};

void *start_thread(void *arg)
{
	int *arr = ((struct th_info *)arg)->array;
	int i = ((struct th_info *)arg)->i;
	int n = ((struct th_info *)arg)->n;
	int j;

	for(j = 2; (j * i) < n; j++){
		arr[j * i] = 0;
	}

	return NULL;
}

int main(int argc, char **argv)
{
        pthread_t tid1, tid2, tid3, tid4;
        void *status = NULL;

	if(argc != 2) {
		printf("usage: ./primes [n]\n");
		printf("This will calculate the prime numbers between 1 and n.\n");
		exit(0);
	}

	int n = atoi(argv[1]);
	int i;

	int *primes = calloc(n, sizeof(int));
	assert(primes);

	for(i = 2; i < n; i++) {
		primes[i] = i;
	}

	/* Create an array of structures */
	struct th_info *str_array = malloc(4 * sizeof(struct th_info));

	for(i = 2; i < sqrt(n); i += 4) {
		//create thread that zeroes multiples of i
		str_array[0].i = i;
		str_array[0].array = primes;
		str_array[0].n = n;
		pthread_create(&tid1, NULL, start_thread, (void *)(&str_array[0]));

		//create thread that zeroes multiples of i+1
		if((i + 1) < sqrt(n)) {
			str_array[1].i = i + 1;
			str_array[1].array = primes;
			str_array[1].n = n;
			pthread_create(&tid2, NULL, start_thread, (void *)(&str_array[1]));
		}

		//create thread that zeroes multiples of i+2
		if((i + 2) < sqrt(n)) {
			str_array[2].i = i + 2;
			str_array[2].array = primes;
			str_array[2].n = n;
			pthread_create(&tid3, NULL, start_thread, (void *)(&str_array[2]));
		}


		//create thread that zeroes multiples of i+3
		if((i + 3) < sqrt(n)) {
			str_array[3].i = i + 3;
			str_array[3].array = primes;
			str_array[3].n = n;
			pthread_create(&tid4, NULL, start_thread, (void *)(&str_array[3]));
		}

		pthread_join(tid1, &status);
		if((i + 1) < sqrt(n)) {
			pthread_join(tid2, &status);
		}
		if((i + 2) < sqrt(n)) {
			pthread_join(tid3, &status);
		}
		if((i + 3) < sqrt(n)) {
			pthread_join(tid4, &status);
		}

	}

	for(i = 0; i < n; i++) {
		if(primes[i] != 0) {
			printf("%d\n", primes[i]);
		}
	}

        return 0;
}
