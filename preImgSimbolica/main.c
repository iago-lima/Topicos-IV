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

void write_dd (DdManager *gbm, DdNode *dd, char* filename, char** names)
{
    FILE *outfile; // output file pointer for .dot file
    outfile = fopen(filename,"w");
    if(outfile == NULL){
      printf("File didn't open\n");
      return;
    }
    DdNode **ddnodearray = (DdNode**)malloc(sizeof(DdNode*)); // initialize the function array
    ddnodearray[0] = dd;
    Cudd_DumpDot(gbm, 1, ddnodearray, names, NULL, outfile); // dump the function to .dot file
    free(ddnodearray);
    fclose (outfile); // close the file */
}

int main(){

    char filename[100];
    DdManager *gbm;
    gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
    DdNode *prop[8], *propl[4],*prop4[4], *trans[23], *states[16], *Xdd;
    int i = 0;
    char *names[8] = {"p", "p'", "q", "q'","r", "r'", "s","s'"};
    int permutation[8] = {1,0,3,2,5,4,7,6};

    // p = Cudd_bddIthVar(gbm,0);    //Criamos uma variável de índice 0
    // Cudd_Ref(p);                  //Incrementamos sua referência. Necessário para manter o controle dos nós.
    // q = Cudd_bddIthVar(gbm,1);
    // Cudd_Ref(q);
    // r = Cudd_bddIthVar(gbm,2);
    // Cudd_Ref(r);
    // s = Cudd_bddIthVar(gbm,3);
    // Cudd_Ref(s);


/* ******************** Creating Propositions ***************************** */
     for(i = 0; i < 8; i++){
        prop[i] = Cudd_bddIthVar(gbm,i);
        Cudd_Ref(prop[i]);
     }

     for(i = 0; i < 4; i++){
        prop4[i] = Cudd_bddIthVar(gbm,i);
        Cudd_Ref(prop4[i]);
        propl[i] = Cudd_bddIthVar(gbm,i);
        Cudd_Ref(propl[i]);
     }

/* *********************** Creating Diagram States(Xdd) *********************** */
    states[0] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], Cudd_Not(prop[2])), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), Cudd_Not(prop[6])));
    Cudd_Ref(states[0]);
    
    states[1] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), Cudd_Not(prop[2])), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), Cudd_Not(prop[6])));
    Cudd_Ref(states[1]);
    
    states[2] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], prop[2]), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), Cudd_Not(prop[6])));
    Cudd_Ref(states[2]);
    
    states[3] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], Cudd_Not(prop[2])), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), prop[6]));
    Cudd_Ref(states[3]);

    states[4] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], Cudd_Not(prop[2])), Cudd_bddAnd(gbm, prop[4], Cudd_Not(prop[6])));
    Cudd_Ref(states[4]);

    states[5] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), Cudd_Not(prop[2])), Cudd_bddAnd(gbm, prop[4], Cudd_Not(prop[6])));
    Cudd_Ref(states[5]);

    states[6] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], Cudd_Not(prop[2])), Cudd_bddAnd(gbm, prop[4], prop[6]));
    Cudd_Ref(states[6]);

    states[7] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), Cudd_Not(prop[2])), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), prop[6]));
    Cudd_Ref(states[7]);

    states[8] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), prop[2]), Cudd_bddAnd(gbm, prop[4], Cudd_Not(prop[6])));
    Cudd_Ref(states[8]);

    states[9] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], prop[2]), Cudd_bddAnd(gbm, prop[4], Cudd_Not(prop[6])));
    Cudd_Ref(states[9]);

    states[10] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), prop[2]), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), Cudd_Not(prop[6])));
    Cudd_Ref(states[10]);

    states[11] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), prop[2]), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), prop[6]));
    Cudd_Ref(states[11]);

    states[12] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], prop[2]), Cudd_bddAnd(gbm, Cudd_Not(prop[4]), prop[6]));
    Cudd_Ref(states[12]);

    states[13] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), prop[2]), Cudd_bddAnd(gbm, prop[4], prop[6]));
    Cudd_Ref(states[13]);

    states[14] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], prop[2]), Cudd_bddAnd(gbm, prop[4], prop[6]));
    Cudd_Ref(states[14]);

    states[15] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), Cudd_Not(prop[2])), Cudd_bddAnd(gbm, prop[4], prop[6]));
    Cudd_Ref(states[15]);

    for (int i = 0; i < 14; i = i + 2)
    {
      Xdd = Cudd_bddOr(gbm, states[i], states[i+1]);
    }


/* ***************************** Creating Transitions ************************** */
  /*(s0,s1)*/  trans[0] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], Cudd_Not(prop[1])), Cudd_bddAnd(gbm, Cudd_Not(prop[2]), Cudd_Not(prop[3]))),
               Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[4]), Cudd_Not(prop[5])), Cudd_bddAnd(gbm, Cudd_Not(prop[6]), Cudd_Not(prop[7]))) );

 /*(s0,s4)*/  trans[1] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[0], Cudd_Not(prop[1])), Cudd_bddAnd(gbm, Cudd_Not(prop[2]), Cudd_Not(prop[3]))),
               Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[4], Cudd_Not(prop[5])), Cudd_bddAnd(gbm, prop[6], Cudd_Not(prop[7]))) );

 /*(s1,s2)*/  trans[2] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), Cudd_Not(prop[1])), Cudd_bddAnd(gbm, Cudd_Not(prop[2]), Cudd_Not(prop[3]))),
               Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, prop[4], prop[5]), Cudd_bddAnd(gbm, Cudd_Not(prop[6]), Cudd_Not(prop[7]))) );

 /*(s1,s5)*/  trans[3] = Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[0]), Cudd_Not(prop[1])), Cudd_bddAnd(gbm, Cudd_Not(prop[2]), Cudd_Not(prop[3]))),
               Cudd_bddAnd(gbm, Cudd_bddAnd(gbm, Cudd_Not(prop[4]), Cudd_Not(prop[5])), Cudd_bddAnd(gbm, prop[6], Cudd_Not(prop[7]))) );

/* ********************** Seting Pairs ****************** */
    for(i = 0; i < 8; i++){
        if(!Cudd_bddSetPairIndex(gbm, i, i+1)){
            printf("Pair didn't set \n");
        }
    }
/* ************************ Creating X'dd *************** */
      // DdNode* s7dd = Cudd_bddSwapVariables(gbm, s6dd, prop, propl, 4);
    DdNode*s7dd = Cudd_bddPermute(gbm, Xdd, permutation); 
       if(s7dd == NULL){
            printf("Replace failed\n");
       }


    print_dd(gbm, Xdd, 8,4);
    sprintf(filename, "/home/iago/bdd/graph.dot");
    write_dd(gbm, Xdd, filename, (char **)names);
    Cudd_Quit(gbm);

     return 0;
}
//Dúvida 01: podemos fazer desse jeito, deixando os linhas no final ao invés de alternando entre os não linha?
//Dúvida 02: como a função de swap funciona? Por que ela reconhece as quatro primeiras posições e as quatro últimas posições do vetor?
