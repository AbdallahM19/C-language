#include <stdio.h>
#include "dog.h"
#include <stdlib.h>

/**
 * free_dog - Free dog structure.
 * @d: pointer
 */
void free_dog(dog_t *d)
{
	if (d)
	{
	free(d->name);
	free(d->owner);
	free(d);
	}
}