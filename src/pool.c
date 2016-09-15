#include <Rinternals.h>
#include <stdlib.h>

void fin_pool(SEXP ptr){
  Rprintf("Finalizing pool!\n");
  free(R_ExternalPtrAddr(ptr));
  R_ClearExternalPtr(ptr);
}

void fin_handle(SEXP ptr){
  Rprintf("Finalizing handle!\n");
  free(R_ExternalPtrAddr(ptr));
  R_ClearExternalPtr(ptr);
}

SEXP c_make_pool(){
  void * pool_obj = malloc(100);
  SEXP pool = PROTECT(R_MakeExternalPtr(pool_obj, R_NilValue, R_NilValue));
  R_RegisterCFinalizerEx(pool, fin_pool, TRUE);

  //add some nodes
  for(int i = 0; i < 10; i++){
    void * handle_obj = malloc(100);
    SEXP handle = PROTECT(R_MakeExternalPtr(handle_obj, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(handle, fin_handle, TRUE);
    R_SetExternalPtrProtected(pool, CONS(handle, R_ExternalPtrProtected(pool)));
    UNPROTECT(1);
  }

  UNPROTECT(1);
  return pool;
}

SEXP c_show_handles(SEXP pool){
  return R_ExternalPtrProtected(pool);
}
