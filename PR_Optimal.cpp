
#include <stdio.h>

int is_exist(int frames[], int frame_count, int page) {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

int find_optimal(int frames[], int frame_count, int pages[], int n, int index) {
    int farthest = -1;
    int pos = 0;

    for (int i = 0; i < frame_count; i++) {
        int j;

        for (j = index; j < n; j++) {
            if (frames[i] == pages[j])
                break;
        }

        if (j == n)
            return i;

        if (j > farthest) {
            farthest = j;
            pos = i;
        }
    }

    return pos;
}

int main() {
    int n, frame, pagefault = 0;

    printf("Enter the total number of pages: ");
    scanf("%d", &n);

    printf("Enter the number of frames: ");
    scanf("%d", &frame);

    if (n <= 0 || frame <= 0) {
        printf("Invalid input");
        return 0;
    }

    int page[n], frames[frame];

    printf("Enter the page numbers (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &page[i]);
    }

    for (int i = 0; i < frame; i++) {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int pos = is_exist(frames, frame, page[i]);

        if (pos == -1) {
            int empty = -1;

            for (int j = 0; j < frame; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1) {
                frames[empty] = page[i];
            } else {
                int optimal_pos = find_optimal(frames, frame, page, n, i + 1);
                frames[optimal_pos] = page[i];
            }

            pagefault++;
        }

        printf("After inserting page %d: ", page[i]);

        for (int j = 0; j < frame; j++) {
            if (frames[j] == -1)
                printf("[ ] ");
            else
                printf("[%d] ", frames[j]);
        }

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pagefault);

    return 0;
}
