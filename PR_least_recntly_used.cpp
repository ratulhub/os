#include <stdio.h>

// Function to check if a page exists in frames
int is_exist(int frames[], int frame_count, int page) {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i] == page)
            return i; // Return position if page found
    }
    return -1; // Page not found
}

// Function to find the least recently used page
int find_lru(int time[], int frame_count) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frame_count; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int n, frame, pagefault = 0, counter = 0;

    printf("Enter the total number of pages: ");
    scanf("%d", &n);

    printf("Enter the number of frames: ");
    scanf("%d", &frame);

    int page[n], frames[frame], time[frame];

    printf("Enter the page numbers (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &page[i]);
    }

    // Initialize all frames and times
    for (int i = 0; i < frame; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLeast Recently Used (LRU) Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int pos = is_exist(frames, frame, page[i]);

        if (pos != -1) {
            // Page hit: update access time
            counter++;
            time[pos] = counter;
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
                counter++;
                time[empty] = counter;
            } else {
                int lru_pos = find_lru(time, frame);
                frames[lru_pos] = page[i];
                counter++;
                time[lru_pos] = counter;
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
