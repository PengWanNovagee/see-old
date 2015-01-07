 

/**@file TBI_ragel_state.c
 * @brief Ragel state for SIP, HTTP and MSRP parsing.
 *

 *

 */
#include "TBI_ragel_state.h"

/**@defgroup TBI_ragel_state_group Ragel state for SIP, HTTP and MSRP parsing.
*/

/**@ingroup TBI_ragel_state_group
* Initialize/Reset the ragel state with default values.
* @param state The ragel @a state to initialize.
* @param data The @a data to parse.
* @param size The @a size of the data.
*/
void TBI_ragel_state_init(TBI_ragel_state_t *state, const char *data, TBI_size_t size)
{
	state->cs = 0;
	state->p = data;
	state->pe = state->p + size;
	state->eof = 0;
	
	state->tag_start = 0;
	state->tag_end = 0;
}
