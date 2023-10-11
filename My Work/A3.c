#include <stdlib.h>
#include "dog.h"

/**
 * _strlen - loop of len strings
 * @s: char
 * Return: len
*/

int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}

/**
 * _strcpy - Copy a str from source to destination.
 * @d: Destination string.
 * @s: Source string.
 * Return: pointer to the destination string.
*/

char *_strcpy(char *d, char *s)
{
	int a, i;

	a = 0;

	while (s[a] != '\0')
		a++;
	for (i = 0; i < a; i++)
		d[i] = s[i];
	d[i] = '\0';

	return (d);
}

/**
 * new_dog - creates a new dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 *
 * Return: pointer to the new dog (Success), NULL otherwise
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	int len1, len2;

	len1 = _strlen(name);
	len2 = _strlen(owner);

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	dog->name = malloc(sizeof(char) * (len1 + 1));
	if (dog->name == NULL)
	{
		free(dog);
		return (NULL);
	}
	dog->owner = malloc(sizeof(char) * (len2 + 1));
	if (dog->owner == NULL)
	{
		free(dog);
		free(dog->name);
		return (NULL);
	}
	_strcpy(dog->name, name);
	_strcpy(dog->owner, owner);
	dog->age = age;

	return (dog);
}