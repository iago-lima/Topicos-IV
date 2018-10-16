
#include <stdio.h>
#include "/home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/util/util.h"
#include "/home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/cudd/cudd.h"


void print_dd (DdManager *gbm, DdNode *dd, int n, int pr )
{
    printf("DdManager nodes: %ld |\n ", Cudd_ReadNodeCount(gbm)); /*Reports the number of live nodes in BDDs and ADDs*/
    printf("DdManager vars: %d |\n ", Cudd_ReadSize(gbm) ); /*Returns the number of BDD variables in existence*/
    printf("DdManager reorderings: %d |\n ", Cudd_ReadReorderings(gbm) ); /*Returns the number of times reordering has occurred*/
    printf("DdManager memory: %ld \n", Cudd_ReadMemoryInUse(gbm) ); /*Returns the memory in use by the manager measured in bytes*/
    Cudd_PrintDebug(gbm, dd, n, pr);  // Prints to the standard output a DD and its statistics: number of nodes, number of leaves, number of minterms.
}

void write_dd (DdManager *gbm, DdNode *dd, char* filename)
{
    FILE *outfile; // output file pointer for .dot file
    outfile = fopen(filename,"w");
    if(outfile == NULL){
      printf("File didn't open\n");
      return;
    }
    DdNode **ddnodearray = (DdNode**)malloc(sizeof(DdNode*)); // initialize the function array
    ddnodearray[0] = dd;
    Cudd_DumpDot(gbm, 1, ddnodearray, NULL, NULL, outfile); // dump the function to .dot file
    free(ddnodearray);
    fclose (outfile); // close the file */
}

int main(){
  char filename[30];
  DdManager *gbm;
  gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
  DdNode *bdd, *x1, *x2, *x3;

  x1 = Cudd_bddNewVar(gbm);
  x2 = Cudd_bddNewVar(gbm);
  x3 = Cudd_bddNewVar(gbm);

  bdd = Cudd_bddAnd(gbm, x1, x2);
  bdd = Cudd_bddAnd(gbm, bdd, x3);
  Cudd_Ref(bdd);
  bdd = Cudd_BddToAdd(gbm, bdd);
  print_dd(gbm, bdd, 2,4);
  sprintf(filename, "/home/iago/bdd/graph.dot");
  write_dd(gbm, bdd, filename);
  Cudd_Quit(gbm);

  return 0;
}


















