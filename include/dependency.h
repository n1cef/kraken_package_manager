#ifndef DEPENDENCY_H
#define DEPENDENCY_H
#include "/usr/kraken/include/graph.h"

void resolve_dep(Graph *graph);
void install_pkg_dfs(Node *node);




#endif
