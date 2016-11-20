#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//virtual address length
#define VM 20

//physical address length
#define PM 20

//page size
#define P 12

//physical page number
#define PPN PM - P

//virtual page number
#define VPN VM - P

//TLB setting
#define USE_TLB 1

//TLB size
#define TLB_SIZE 6

//access memory time
#define AMT 200

//access TLB time
#define ATT 20

//simulation number
#define SIM_NUM 30

//init page table
void init_pt(int *pt, int len)
{
  int i, j, a;
  for (i=0; i<len; i++) {
    a = rand() % len;
    for (j=0; j<i; j++) {
      if (pt[j] == a) {
        i--;
        continue;
      };
    }
    pt[i] = a;
  }
}

//init TLB
void init_tlb(int *tlb, int len, int *pt, int pt_len)
{
  int m;
  for (m=0; m<pt_len; m++)
    tlb[m] = 100;

  int i, j, a;
  for (i=0; i<len; i++) {
    a = rand() % pt_len;
    if (tlb[a] != 100) {
      continue;
      i--;
    }
    tlb[a] = pt[a];
  }
}

//print page table
void print_pt(int *pt, int len)
{
  int i;
  for (i=0; i<len; i++)
    printf("%d %d\n", i, pt[i]);
}

void print_tlb(int *tlb, int len)
{
  int i;
  for (i=0; i<len; i++) {
    if (tlb[i] != 100)
      printf("%d %d\n", i, tlb[i]);
  }
}

int gen_virtual_addr(pt_len)
{
  int addr;
  addr = rand() % pt_len;
  addr = addr << P;
  int offset  =rand() % (int)pow(2, P);
  addr += offset;
  return addr;
}
