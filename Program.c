#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// comparison function for qsort
int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// helper to build a sorted array containing all requests + head
// returns pointer to new array of size n+1; caller must free()
int *build_sorted_with_head(int *req, int n, int head) {
    int *arr = malloc((n + 1) * sizeof(int));
    if (!arr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) arr[i] = req[i];
    arr[n] = head;
    qsort(arr, n + 1, sizeof(int), cmpfunc);
    return arr;
}

// FCFS algorithm
void fcfs(int *req, int n, int head) {
    int current = head;
    long total = 0;
    printf("\n--- FCFS ---\n");
    printf("Initial head position: %d\n", head);
    for (int i = 0; i < n; i++) {
        int move = abs(req[i] - current);
        printf("%3d -> %3d : movement = %3d\n", current, req[i], move);
        total += move;
        current = req[i];
    }
    printf("Total head movement = %ld\n", total);
    printf("Average movement per request = %.2f\n", (double)total / n);
}

// SCAN algorithm (elevator): go toward 0 first, then to max
void scan_algo(int *req, int n, int head, int max_index) {
    int *sorted = build_sorted_with_head(req, n, head);
    // find head position in sorted
    int idx;
    for (idx = 0; idx < n + 1; idx++) {
        if (sorted[idx] == head) break;
    }
    long total = 0;
    int current = head;
    printf("\n--- SCAN (toward 0 first) ---\n");
    printf("Initial head position: %d\n", head);
    // move 0 direction
    for (int i = idx - 1; i >= 0; i--) {
        int move = abs(current - sorted[i]);
        printf("%3d -> %3d : movement = %3d\n", current, sorted[i], move);
        total += move;
        current = sorted[i];
    }
    // go to max end
    if (current > 0) {
        int move = abs(current - 0);
        printf("%3d -> %3d : movement = %3d\n", current, 0, move);
        total += move;
        current = 0;
    }
    // then from 0 up to max
    for (int i = idx + 1; i < n + 1; i++) {
        int move = abs(sorted[i] - current);
        printf("%3d -> %3d : movement = %3d\n", current, sorted[i], move);
        total += move;
        current = sorted[i];
    }
    printf("Total head movement = %ld\n", total);
    printf("Average movement per request = %.2f\n", (double)total / n);
    free(sorted);
}

// C-SCAN algorithm
void cscan_algo(int *req, int n, int head, int max_index) {
    int *sorted = build_sorted_with_head(req, n, head);
    // find head position in sorted
    int idx;
    for (idx = 0; idx < n + 1; idx++) {
        if (sorted[idx] == head) break;
    }
    long total = 0;
    int current = head;
    printf("\n--- C-SCAN (toward max then wrap) ---\n");
    printf("Initial head position: %d\n", head);
    // go from head up to max
    for (int i = idx + 1; i < n + 1; i++) {
        int move = abs(current - sorted[i]);
        printf("%3d -> %3d : movement = %3d\n", current, sorted[i], move);
        total += move;
        current = sorted[i];
    }
    // jump to end and wrap to 0
    if (current < max_index) {
        int move = abs(current - max_index);
        printf("%3d -> %3d : movement = %3d\n", current, max_index, move);
        total += move;
        current = max_index;
    }
    printf("%3d -> %3d : movement = %3d (wrap)\n", current, 0, abs(current - 0));
    total += abs(current - 0);
    current = 0;
    // service remaining below head
    for (int i = 0; i < idx; i++) {
        int move = abs(current - sorted[i]);
        printf("%3d -> %3d : movement = %3d\n", current, sorted[i], move);
        total += move;
        current = sorted[i];
    }
    printf("Total head movement = %ld\n", total);
    printf("Average movement per request = %.2f\n", (double)total / n);
    free(sorted);
}

// generate random requests
void generateRandomRequests(int *req, int n, int max_index) {
    for (int i = 0; i < n; i++)
        req[i] = rand() % (max_index + 1);
}

// flush stdin on bad input
void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    srand((unsigned)time(NULL));
    int n, head, max_index;
    printf("Disk Scheduling Simulator\n");
    printf("Enter maximum cylinder index (e.g. 4999): ");
    if (scanf("%d", &max_index) != 1 || max_index < 1) {
        fprintf(stderr, "Invalid maximum index.\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of I/O requests: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid number of requests.\n");
        return EXIT_FAILURE;
    }

    int *requests = malloc(n * sizeof(int));
    if (!requests) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    printf("Enter initial head position (0..%d): ", max_index);
    if (scanf("%d", &head) != 1 || head < 0 || head > max_index) {
        fprintf(stderr, "Invalid head position.\n");
        free(requests);
        return EXIT_FAILURE;
    }

    char choice;
    printf("Generate random requests? (y/n): ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        generateRandomRequests(requests, n, max_index);
        printf("Generated requests:\n");
        for (int i = 0; i < n; i++) printf("%d ", requests[i]);
        printf("\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("Request %d (0..%d): ", i+1, max_index);
            if (scanf("%d", &requests[i])!=1 || requests[i]<0 || requests[i]>max_index) {
                fprintf(stderr, " Invalid! Try again.\n");
                flush_stdin();
                i--;
            }
        }
    }

    int opt;
    do {
        printf("\nMenu:\n1.FCMS  2.SCAN  3.C-SCAN  4.All  0.Exit\nChoose: ");
        if (scanf("%d", &opt)!=1) { flush_stdin(); continue; }
        switch(opt) {
            case 1: fcfs(requests, n, head);            break;
            case 2: scan_algo(requests, n, head, max_index); break;
            case 3: cscan_algo(requests, n, head, max_index); break;
            case 4:
                fcfs(requests,n,head);
                scan_algo(requests,n,head,max_index);
                cscan_algo(requests,n,head,max_index);
                break;
            case 0: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(opt!=0);

    free(requests);
    return EXIT_SUCCESS;
}
