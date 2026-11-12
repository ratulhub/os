#include <stdio.h>

// Function to check if a page exists in frames
int is_exist(int frames[], int frame_count, int page) {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == page)
            return i; // Return position if page found
    }
    return -1; // Page not found
}

// Function to find the optimal page to replace
int find_optimal(int frames[], int frame_count, int pages[], int n, int index) {
    int farthest = index;
    int pos = -1;

    for (int i = 0; i < frame_count; i++) {
        for (int j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) {
            // If the page in frame[i] is never used again
            return i;
        }
    }

    // If all pages are going to be used, replace the farthest one
    if (pos == -1)
        return 0;
    else
        return pos;
}

int main() {
    int n, frame, pagefault = 0;

    printf("Enter the total number of pages: ");
    scanf("%d", &n);

    printf("Enter the number of frames: ");
    scanf("%d", &frame);

    int page[n], frames[frame];

    printf("Enter the page numbers (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &page[i]);
    }

    // Initialize all frames
    for (int i = 0; i < frame; i++) {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int pos = is_exist(frames, frame, page[i]);

        if (pos != -1) {
            // Page hit: do nothing
        } else {
            // Page fault
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

        // Display frames
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
