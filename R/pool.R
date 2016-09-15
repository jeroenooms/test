#' @export
#' @useDynLib test c_make_pool
make_pool <- function(){
  .Call(c_make_pool)
}

#' @export
#' @useDynLib test c_show_handles
show_handles <- function(pool){
  stopifnot( typeof(pool) == "externalptr")
  .Call(c_show_handles, pool)
}
