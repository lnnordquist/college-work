#include "cachelab.h"
#include "stdlib.h"
#include "stdio.h"


int h = 0;
int m = 0;
int ev = 0;

struct line{
    int v;
    unsigned long tag;
    int last_mod;
} line;

/* new_blank_cache: takes dimensions (s,e,b) of the cache and creates a version 
                    on the stack full of 0s. Returns a pointer to the new cache
                    struct (which is a 2D array of lines). Always free before 
                    finishing.
*/
struct line ** new_blank_cache(int s, int e, int b) {
    struct line **lines = (struct line**)malloc(sizeof(struct line *)*s);
    for(int j=0;j<s;j++){
        lines[j] = (struct line *)malloc(sizeof(struct line)*e);
        for(int i=0;i<e;i++){
            lines[j][i].v = 0;
            lines[j][i].tag = 0;
            lines[j][i].last_mod = 0;
        }
    }
    return lines;
}

/* set_calc:    calculates the set number from a given address and returns it.
*/

int set_calc(unsigned long address, int s, int b){
    unsigned long add = address >> b;
    unsigned long mask = ~((~0)<<s);
    return add & mask;
}

/* tag_calc:    calucates the tag number from a given address and returns it.
*/

unsigned long tag_calc(unsigned long long address, int s, int b){
    return address >> (b+s);
}

/* write_line:  writes an address to the appropriate location in the cache.
                takes tag and set of address. Also requires counters for hits, 
                misses, evictions to be updated if needed, and time committed.
                Does not return anything.
*/
void write_line(unsigned long tag, int set, int e, struct line **cache, int *hi, int *mi, 
                                                        int *ev, int time){
    int old = 0;
    for(int i = 0; i<e; i++){
        if(cache[set][i].v == 1 && cache[set][i].tag == tag){        
            (*hi)++;
            cache[set][i].last_mod = time;
            return;
        }
    }
    for(int i = 0; i<e; i++){
        if(cache[set][i].v == 0){
            (*mi)++;
            cache[set][i].v = 1;
            cache[set][i].tag = tag;
            cache[set][i].last_mod = time;
            return;
        }
        if(cache[set][i].last_mod < cache[set][old].last_mod){
            old = i;
        }
    }
    (*mi)++;
    (*ev)++;
    cache[set][old].v = 1;
    cache[set][old].tag = tag;
    cache[set][old].last_mod = time;
    return;
}


int main(int argc, char **argv)
{

    int time = 0;

    int s = atoi(argv[2]);
    int e = atoi(argv[4]);
    int b = atoi(argv[6]);
    FILE *f = fopen(argv[8], "r");

    struct line **cache = new_blank_cache(1<<s,e,b);

    char space;
    int size;
    unsigned long long op_add;
    char read[40];
    while(fgets(read, 40, f)){

        time +=1;
        sscanf(read, "%s %llx,%d", &space, &op_add, &size);
        unsigned long tag = tag_calc(op_add, s, b);
        int set = set_calc(op_add, s, b);
        switch(space){
            case 'I':
                break;
            case 'S':
                write_line(tag, set, e, cache, &h, &m, &ev, time);
                break;
            case 'L':
                write_line(tag, set, e, cache, &h, &m, &ev, time);
                break;
            case 'M':
                write_line(tag, set, e, cache, &h, &m, &ev, time);
                write_line(tag, set, e, cache, &h, &m, &ev, time);
                break;
        }
    }
    for(int i = 0; i<s; i++){
        free(cache[i]);
    }
    free(cache);
    fclose(f);
    printSummary(h, m, ev);
    return 0;
}
