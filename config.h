#pragma once

#include <limits>

		   const int N_OF_TESTS  =	20;	// NUMBER OF TESTS
#define                 EPSILON     0.0000001
#define                  NUM_SM     6
#define          MAX_CONCURR_TH		(NUM_SM * 2048)	// Number of Resident Threads
#define	               BLOCKDIM		1024		
            //important BLOCKDIM = POWER OF 2


// -------------------------------------------------------------------------------------
        typedef unsigned dist_t;			// ONLY UNSIGNED TYPE	(suggested unsigned short for high-diameter graph, unsigned char for low-diamter graph)

#define   	     		 MIN_VW		4		// Min Virtual Warp
#define   	             MAX_VW		4		// Max Virtual Warp (suggested: 32)
#define           DYNAMIC_VWARP     1       // If 1 


// -------------------------------------------------------------------------------------
#define             SMEM_KERNEL     1
