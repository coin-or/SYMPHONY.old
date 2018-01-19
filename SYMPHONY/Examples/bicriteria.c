/*===========================================================================*/
/*                                                                           */
/* This file is part of the SYMPHONY MILP Solver Framework.                  */
/*                                                                           */
/* SYMPHONY was jointly developed by Ted Ralphs (ted@lehigh.edu) and         */
/* Laci Ladanyi (ladanyi@us.ibm.com).                                        */
/*                                                                           */
/* The author of this file is Menal Guzelsoy                                 */
/*                                                                           */
/* (c) Copyright 2005-20011 Lehigh University. All Rights Reserved.          */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

#ifdef USE_OSI_INTERFACE

#include "OsiSymSolverInterface.hpp"

int main(int argc, char **argv)
{

  OsiSymSolverInterface si;
  si.parseCommandLine(argc, argv);
  si.loadProblem();

  si.setObj2Coeff(1, 1);

  si.multiCriteriaBranchAndBound();

  return(0);

}

#else

#include "symphony.h"

int main(int argc, char **argv)
{

   sym_environment *env = sym_open_environment();
   sym_parse_command_line(env, argc, argv);
   sym_load_problem(env);

   sym_set_obj2_coeff(env, 1, -1);

   sym_mc_solve(env);
   int nsolutions;
   sym_get_nsolutions(env, &nsolutions);
   printf("nsolutions %d\n", nsolutions);
   sym_solutions solutions;
   for (int i =0; i < nsolutions; i++) {
       sym_get_solution(env, i, &solutions);
       printf("solition %d length %d\n", i, solutions.length);
       for(int j = 0; j < solutions.length; j++) {
           printf("\tindex: %d value %f\n", solutions.indices[j], solutions.values[j]);
        }
    }

   sym_close_environment(env);

   return(0);

}

#endif

