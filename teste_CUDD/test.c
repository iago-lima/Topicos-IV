
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
	DdManager *manager;
    DdNode *f, *var, *tmp;
    int i;
 	manager = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
    f = Cudd_ReadOne(manager);
    Cudd_Ref(f);
    for (i = 3; i >= 0; i--) {
    	var = Cudd_bddIthVar(manager,i);
        tmp = Cudd_bddAnd(manager,var,f);
        Cudd_Ref(tmp);
        Cudd_RecursiveDeref(manager,f);
        f = tmp;
    }


	char filename[30];
	// DdManager *gbm;
	// gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
	// DdNode *bdd, *x1, *x2, *x3;

	// x1 = Cudd_bddNewVar(gbm,);
	// Cudd_Ref(x1);
	// x2 = Cudd_bddNewVar(gbm);
	// Cudd_Ref(x2);
	// x3 = Cudd_bddOr(gbm, x1, x2);
	// Cudd_Ref(x3);



	//Cudd_Ref(f);
	f = Cudd_BddToAdd(manager, f);
	print_dd(manager, f, 2,4);
	sprintf(filename, "/home/iago/bdd/graph.dot");
	write_dd(manager, f, filename);
	Cudd_Quit(manager);

	return 0;
}


















