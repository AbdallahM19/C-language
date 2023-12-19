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
	Py_ssize_t size, i;
	PyBytesObject *bytes = (PyBytesObject *)p;

	fflush(stdout);

	printf("[.] bytes object info\n");
	if (strcmp(p->ob_type->tp_name, "bytes") != 0)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	printf("  size: %ld\n", ((PyVarObject *)p)->ob_size);
	printf("  trying string: %s\n", bytes->ob_sval);

	if (((PyVarObject *)p)->ob_size >= 10)
		size = 10;
	else
		size = ((PyVarObject *)p)->ob_size + 1;

	printf("  first %ld bytes: ", size);
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
	Py_ssize_t size, alloc, i;
	const char *t;
	PyListObject *lists = (PyListObject *)p;
	PyVarObject *vars = (PyVarObject *)p;

	size = vars->ob_size;
	alloc = lists->allocated;

	fflush(stdout);

	printf("[*] Python list info\n");
	if (strcmp(p->ob_type->tp_name, "list") != 0)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", alloc);
	i = 0;
	while (i < size)
	{
		t = lists->ob_item[i]->ob_type->tp_name;
		printf("Element %ld: %s\n", i, t);
		if (strcmp(t, "bytes") == 0)
			print_python_bytes(lists->ob_item[i]);
		else if (strcmp(t, "float") == 0)
			print_python_float(lists->ob_item[i]);
		i++;
	}
}

/**
 * print_python_float - Prints basic info about Python float objects.
 * @p: a PyObject list object.
 */
void print_python_float(PyObject *p)
{
	char *buffer = NULL;

	PyFloatObject *float_obj = (PyFloatObject *)p;

	fflush(stdout);

	printf("[.] float object info\n");
	if (strcmp(p->ob_type->tp_name, "float") != 0)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	buffer = PyOS_double_to_string(float_obj->ob_fval,
		'r', 0, Py_DTSF_ADD_DOT_0, NULL);
	printf("  value: %s\n", buffer);
	PyMem_Free(buffer);
}