#include <Python.h>

void print_python_bytes(PyObject *p);
void print_python_list(PyObject *p);
void print_python_float(PyObject *p);

/**
 * print_python_bytes - Prints basic info about Python byte objects.
 * @p: a PyObject byte object.
 */
void print_python_bytes(PyObject *p)
{
	unsigned char i, size;
	PyBytesObject *bytes = (PyBytesObject *)p;

	printf("[.] bytes object info\n");
	if (strcmp(p->ob_type->tp_name, "bytes") != 0)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	printf("  size: %ld\n", ((PyVarObject *)p)->ob_size);
	printf("  trying string: %s\n", bytes->ob_sval);
	if (((PyVarObject *)p)->ob_size > 10)
		size = 10;
	else
		size = ((PyVarObject *)p)->ob_size + 1;
	printf("  first %d bytes: ", size);
	i = 0;
	while (i < size)
	{
		printf("%02hhx", bytes->ob_sval[i]);
		if (i == (size - 1))
			printf("\n");
		else
			printf(" ");
		i++;
	}
}

/**
 * print_python_list - Prints basic info about Python lists.
 * @p: a PyObject list object.
 */
void print_python_list(PyObject *p)
{
	int size, alloc, i;
	const char *t;
	PyListObject *lists = (PyListObject *)p;
	PyVarObject *vars = (PyVarObject *)p;

	size = vars->ob_size;
	alloc = lists->allocated;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %d\n", size);
	printf("[*] Allocated = %d\n", alloc);
	i = 0;
	while (i < size)
	{
		t = lists->ob_item[i]->ob_type->tp_name;
		printf("Element %d: %s\n", i, t);
		if (strcmp(t, "bytes") == 0)
			print_python_bytes(lists->ob_item[i]);
		i++;
	}
}

/**
 * print_python_float - Prints basic info about Python float objects.
 * @p: a PyObject float object.
 */
void print_python_float(PyObject *p)
{
	printf("[.] float object info\n");

	if (strcmp(p->ob_type->tp_name, "float") != 0)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	printf("  value: %lf\n", PyFloat_AsDouble(p));
}
