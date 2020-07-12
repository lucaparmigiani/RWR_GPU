library(GEOquery) # for gene expression
library(STRINGdb) # for PPI
library(Biobase)
library(igraph)

#gds858 <- getGEO('GDS858', destdir=".")
gds858 <- getGEO(filename='GDS858.soft.gz')
expMat = Table(gds858)
genes = expMat$ID_REF[1:22215]

#write.table(Table(gds858),'expr')

string_db <- STRINGdb$new( version="11", species=9606, #9606 human
                           score_threshold=200, input_directory="")
graph = string_db$get_graph()
V(graph)
mat = as_adj(graph)
mapped_gene <- string_db$map( genes, "gene")


