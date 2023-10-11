#include "dog.h"

/**
 * init_dog - Write a function that initialize a variable of type struct dog
 * @d: pointer
 * @name: name, type = char *
 * @age: age, type = float
 * @owner: owner, type = char *
 * Return: 0
*/

void init_dog(struct dog *d, char *name, float age, char *owner)
{
	if (d)
	{
		d->name = name;
		d->age = age;
		d->owner = owner;
	}
}