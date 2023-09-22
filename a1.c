#include "test.h"
void print_array(int a[], int n)
{
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
#include <string.h> // for testing generate_splits()

/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
int count_element(int a[], int n, int element) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == element) {
            count++;
        }
    }
    return count;
}

int find_index(int a[], int n, int element, int b[], int ind) {
    int count=count_element(b,ind+1, element);
    int k=0;
    for (int i = 0; i < n; i++) {
        if (a[i] == element) {
            // k=k+1;
            k++;
            if (k==count) {
            return i;
            // k++;
            }
        }
    }
    return -1;
}


void lex_perm(int a[], int k, int n, int ind, int helper, int b[], void *data, void (*process_selection)(int *b, int k, void *data)) {
    if (ind == k-1) {
        // print_array(b, k);
        process_selection(b, k, data);

        return;
    }
    for (int i=helper;i<n;i++) {
        // ind sp_ind;
        // sp_ind= find_index(a, n, b[ind]);
        if ((ind==-1) || (i > find_index(a, n, b[ind], b, ind))){
            b[ind+1]=a[i];
            // helper=(i > find_index(a, n, b[ind], b, ind));
            helper=i+1;
            lex_perm(a,k,n,ind+1,helper,b,data,process_selection);
        }

    }
    // ind--;
}


void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{
    // b[0] = 2; b[1] = 1;
    // process_selection(b, 2, data);
    // b[0] = 2; b[1] = 6;
    // process_selection(b, 2, data);
    // b[0] = 2; b[1] = 5;
    // process_selection(b, 2, data);
    // b[0] = 1; b[1] = 6;
    // process_selection(b, 2, data);
    // b[0] = 1; b[1] = 5;
    // process_selection(b, 2, data);
    // b[0] = 6; b[1] = 5;
    // process_selection(b, 2, data);
    int ind=-1;
    int helper=0;
   lex_perm(a,k,n,ind,helper, b,data, process_selection);

}

/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_split(char buf[], void *data) {
    printf("%s\n", buf);
}

void generate_splits_helper(const char *source, const char *dictionary[], int nwords, char buf[], int sourceIndex, int bufIndex, void *data, void (*process_split)(char buf[], void *data))
{
    if (sourceIndex == strlen(source)) {
        buf[bufIndex] = '\0';
        process_split(buf, data);
        return;
    }

    char word[100]; 
    int wordIndex = 0; 

    while (sourceIndex < strlen(source)) {
        word[wordIndex] = source[sourceIndex];
        wordIndex++;
        sourceIndex++;
        word[wordIndex] = '\0';
        for (int i = 0; i < nwords; i++) {
            if (strcmp(word, dictionary[i]) == 0) {
                strcpy(buf + bufIndex, word);
                bufIndex += strlen(word);
                if (sourceIndex < strlen(source)) {
                    buf[bufIndex] = ' ';
                    bufIndex++;
                }

                generate_splits_helper(source, dictionary, nwords, buf, sourceIndex, bufIndex, data, process_split);

                bufIndex -= strlen(word);
                if (sourceIndex < strlen(source)) {
                    bufIndex--;
                }
            }
        }
    }
}


void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split)(char buf[], void *data))
{
    // strcpy(buf, "art is toil");
    // process_split(buf, data);
    // strcpy(buf, "artist oil");
    // process_split(buf, data);
     int sourceIndex = 0;
    int bufIndex = 0;
    generate_splits_helper(source, dictionary, nwords, buf, sourceIndex, bufIndex, data, process_split);

}

/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int a[], int start, int end) {
    while (start < end) {
        swap(&a[start], &a[end]);
        start++;
        end--;
    }
}

void previous_permutation(int a[], int n)
{
    // a[0] = 1;
    // a[1] = 5;
    // a[2] = 4;
    // a[3] = 6;
    // a[4] = 3;
    // a[5] = 2;

    int i = n-2 ;
    // not considering the case of adjacent elements being equal 
    while (i>=0 && a[i] <= a[i+1]){
        i--;
    }

    if (i==-1) {
        return ;
    }

    reverse(a, i+1, n-1);
     if (i >= 0) {
        int j = n - 1;
        int min=a[i]-a[j];
        int k=j;


        while (j>i) {
            if (min > (a[i]-a[j]) && (a[i]-a[j])>0 ) {
                min=a[i]-a[j];
                k=j;
            }

            j--;
        }
        swap(&a[i], &a[k]);
    }
}

/* Write your tests here. Use the previous assignment for reference. */


typedef struct {
    int index;
    int err;
    int first;
} state_t;

static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

void count_selections(int b[], int k, void *data)
{
    int *d = (int*)data;
    ++*d;
}

typedef struct {
    int b[100];
} selection_t;

void last_selection(int b[], int k, void *data)
{
    selection_t *s = (selection_t*)data;
    for (int i = 0; i < k; ++i) {
        s->b[i] = b[i];
    }
}

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int b[10];
    state_t s2165 = { .index = 0, .err = 1, .first = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");
    int c = 0;
    int aa[] = { 1, 5, 3, 0, 1, 12, 4, 3, 6, 6 };
    generate_selections(aa, 10, 5, b, &c, count_selections);
    ASSERT_EQ(c, 252, "Failed on 10C5.");

    selection_t s;
    generate_selections(aa, 10, 5, b, &s, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s.b, 5, "Failed on last of 10C5.", 12, 4, 3, 6, 6);
} END_TEST

void test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if (strcmp(buf, "art is toil")) {
            s->err = 1;
        }
        break;
    case 1:
        if (strcmp(buf, "artist oil")) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

BEGIN_TEST(generate_splits) {
    const char *a = "artistoil";
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"
    };
    int nwords = 5;
    state_t s = { .index = 0, .err = 1, .first = 1 };
    char buf[256];
    generate_splits(a, dict, nwords, buf, &s, test_splits_art);
    ASSERT(!s.err, "Failed on 'artistoil'.");
} END_TEST

BEGIN_TEST(previous_permutation) {
    int a[] = { 1, 5, 6, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 5, 4, 6, 3, 2);
    int aa[] = { 1, 2, 3, 5, 4, 6 };
    previous_permutation(aa, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(aa, 3, "Failed on 1 2 3.", 1, 2, 3);
} END_TEST

int main()
{
    run_tests((test_t[]) {
            TEST(generate_selections),
            TEST(generate_splits),
            TEST(previous_permutation),
            0
        });
    return 0;
}